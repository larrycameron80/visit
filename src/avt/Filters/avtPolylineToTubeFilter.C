/*****************************************************************************
*
* Copyright (c) 2000 - 2019, Lawrence Livermore National Security, LLC
* Produced at the Lawrence Livermore National Laboratory
* LLNL-CODE-442911
* All rights reserved.
*
* This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
* full copyright notice is contained in the file COPYRIGHT located at the root
* of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
*
* Redistribution  and  use  in  source  and  binary  forms,  with  or  without
* modification, are permitted provided that the following conditions are met:
*
*  - Redistributions of  source code must  retain the above  copyright notice,
*    this list of conditions and the disclaimer below.
*  - Redistributions in binary form must reproduce the above copyright notice,
*    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
*    documentation and/or other materials provided with the distribution.
*  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
*    be used to endorse or promote products derived from this software without
*    specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
* ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
* LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
* DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
* SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
* CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
* LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
* OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*
*****************************************************************************/

// ************************************************************************* //
//                          avtPolylineToTubeFilter.C                        //
// ************************************************************************* //

#include <avtPolylineToTubeFilter.h>

#include <vtkAppendPolyData.h>
#include <vtkCellData.h>
#include <vtkCleanPolyData.h>
#include <vtkDataSet.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>

// VisIt vtk classes
#include <vtkVisItTubeFilter.h>


// ****************************************************************************
//  Method: avtPolylineToTubeFilter constructor
//
//  Purpose:
//      Defines the constructor.  Note: this should not be inlined in the
//      header because it causes problems for certain compilers.
//
//  Programmer: Allen Sanderson
//  Creation:   Feb 12 2016
//
// ****************************************************************************

avtPolylineToTubeFilter::avtPolylineToTubeFilter() : avtDataTreeIterator()
{
}

// ****************************************************************************
//  Method: avtPolylineToTubeFilter destructor
//
//  Purpose:
//      Defines the destructor.  Note: this should not be inlined in the header
//      because it causes problems for certain compilers.
//
//  Programmer: Allen Sanderson
//  Creation:   Feb 12 2016
//
// ****************************************************************************

avtPolylineToTubeFilter::~avtPolylineToTubeFilter()
{
}

// ****************************************************************************
//  Method: avtPolylineToTubeFilter::ExecuteData
//
//  Purpose:
//    Creates a tube from a polyline
//
//  Arguments:
//      inDR       The input data representation.
//
//  Returns:       The output data representation.
//
//  Note: The cell data copying is untested.
//
//  Programmer: Allen Sanderson
//  Creation:   Feb 12 2016
//
//  Modifications:
//    Eric Brugger, Thu Oct 20 14:15:30 PDT 2016
//    I added code to remove duplicate points from the lines since the 
//    vtkTubeFilter exits on any lines that have duplicate points.
//
//    Kathleen Biagas, Thu Jun 13 13:34:35 PDT 2019
//    Use vtkVisItTubeFilter instead of vtkTubeFilter. Support cell scalars.
//    Only use append filter if input contains more than just lines.
//
// ****************************************************************************

avtDataRepresentation *
avtPolylineToTubeFilter::ExecuteData(avtDataRepresentation *inDR)
{
    //
    // Get the VTK data set.
    //
    vtkDataSet *inDS = inDR->GetDataVTK();

    if (inDS->GetDataObjectType() != VTK_POLY_DATA)
    {
        // We only work on line data
        EXCEPTION1(VisItException, "avtPolylineToTubeFilter::ExecuteDataTree "
                                   "-- Did not get polydata");
    }

    if (GetInput()->GetInfo().GetAttributes().GetTopologicalDimension() != 1)
    {
        return inDR;
    }

    vtkDataArray *activePtScalars = inDS->GetPointData()->GetScalars();
    vtkDataArray *activeCellScalars = inDS->GetCellData()->GetScalars();

    vtkPolyData *data = vtkPolyData::SafeDownCast(inDS);
    vtkPolyData *output = NULL;

    // Create the tube polydata.
    vtkVisItTubeFilter *tubeFilter = vtkVisItTubeFilter::New();
    tubeFilter->SetInputData(data);
    tubeFilter->SetRadius(radius);
    tubeFilter->SetNumberOfSides(numberOfSides);
    tubeFilter->SetCapping(1);
    tubeFilter->ReleaseDataFlagOn();

    if (varyRadius)
    {
        if (!radiusVar.empty() && radiusVar != "default")
        {
            tubeFilter->SetScalarsForRadius(radiusVar.c_str());
        }
        tubeFilter->SetVaryRadiusToVaryRadiusByScalar();
        tubeFilter->SetRadiusFactor(radiusFactor);
    }
    tubeFilter->Update();
    output = tubeFilter->GetOutput();

    vtkPolyData *outPD = output;
    vtkAppendPolyData *append = NULL;

    if (data->GetNumberOfLines() < data->GetNumberOfCells())
    {
        // Append the original data and tube polydata
        append = vtkAppendPolyData::New();

        append->AddInputData(data);
        append->AddInputData(output);
        append->Update();
        outPD = append->GetOutput();
        // KSB:  This seems problematic, as the celldata arrays will now be
        // incorrect. I think instead the 'data' polydata should have all
        // non-line cells extracted to a new dataset and then that new dataset
        // is used in the append filter along with the tube-filter output.
        // Remove the lines.
        outPD->SetLines(NULL);
        outPD->RemoveDeletedCells();
    }

    outPD->Register(NULL);
    if(append)
        append->Delete();

    // Restore the active scalars.
    if (activePtScalars)
    {
        outPD->GetPointData()->SetActiveScalars(activePtScalars->GetName());
    }
    if (activeCellScalars)
    {
        outPD->GetCellData()->SetActiveScalars(activeCellScalars->GetName());
    }

    // Create the output data rep.
    avtDataRepresentation *outDR =
        new avtDataRepresentation(outPD, inDR->GetDomain(), inDR->GetLabel());

    return outDR;
}


// ****************************************************************************
//  Method: avtPolylineToTubeFilter::UpdateDataObjectInfo
//
//  Purpose:
//      Indicate that this invalidates the zone numberings.
//
//  Programmer: Allen Sanderson
//  Creation:   Feb 12 2016
//
// ****************************************************************************

void
avtPolylineToTubeFilter::UpdateDataObjectInfo(void)
{
    if (GetInput()->GetInfo().GetAttributes().GetTopologicalDimension() == 1)
        GetOutput()->GetInfo().GetValidity().InvalidateZones();
}
