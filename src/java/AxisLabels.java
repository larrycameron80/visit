// ***************************************************************************
//
// Copyright (c) 2000 - 2012, Lawrence Livermore National Security, LLC
// Produced at the Lawrence Livermore National Laboratory
// LLNL-CODE-442911
// All rights reserved.
//
// This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
// full copyright notice is contained in the file COPYRIGHT located at the root
// of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
//
// Redistribution  and  use  in  source  and  binary  forms,  with  or  without
// modification, are permitted provided that the following conditions are met:
//
//  - Redistributions of  source code must  retain the above  copyright notice,
//    this list of conditions and the disclaimer below.
//  - Redistributions in binary form must reproduce the above copyright notice,
//    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
//    documentation and/or other materials provided with the distribution.
//  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
//    be used to endorse or promote products derived from this software without
//    specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
// ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
// LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
// DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
// SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
// CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
// LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
// OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
// DAMAGE.
//
// ***************************************************************************

package llnl.visit;


// ****************************************************************************
// Class: AxisLabels
//
// Purpose:
//    Contains the label properties for one axis.
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

public class AxisLabels extends AttributeSubject
{
    private static int AxisLabels_numAdditionalAtts = 3;

    public AxisLabels()
    {
        super(AxisLabels_numAdditionalAtts);

        visible = true;
        font = new FontAttributes();
        scaling = 0;
    }

    public AxisLabels(int nMoreFields)
    {
        super(AxisLabels_numAdditionalAtts + nMoreFields);

        visible = true;
        font = new FontAttributes();
        scaling = 0;
    }

    public AxisLabels(AxisLabels obj)
    {
        super(AxisLabels_numAdditionalAtts);

        visible = obj.visible;
        font = new FontAttributes(obj.font);
        scaling = obj.scaling;

        SelectAll();
    }

    public int Offset()
    {
        return super.Offset() + super.GetNumAdditionalAttributes();
    }

    public int GetNumAdditionalAttributes()
    {
        return AxisLabels_numAdditionalAtts;
    }

    public boolean equals(AxisLabels obj)
    {
        // Create the return value
        return ((visible == obj.visible) &&
                (font.equals(obj.font)) &&
                (scaling == obj.scaling));
    }

    // Property setting methods
    public void SetVisible(boolean visible_)
    {
        visible = visible_;
        Select(0);
    }

    public void SetFont(FontAttributes font_)
    {
        font = font_;
        Select(1);
    }

    public void SetScaling(int scaling_)
    {
        scaling = scaling_;
        Select(2);
    }

    // Property getting methods
    public boolean        GetVisible() { return visible; }
    public FontAttributes GetFont() { return font; }
    public int            GetScaling() { return scaling; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
            buf.WriteBool(visible);
        if(WriteSelect(1, buf))
            font.Write(buf);
        if(WriteSelect(2, buf))
            buf.WriteInt(scaling);
    }

    public void ReadAtts(int index, CommunicationBuffer buf)
    {
        switch(index)
        {
        case 0:
            SetVisible(buf.ReadBool());
            break;
        case 1:
            font.Read(buf);
            Select(1);
            break;
        case 2:
            SetScaling(buf.ReadInt());
            break;
        }
    }

    public String toString(String indent)
    {
        String str = new String();
        str = str + boolToString("visible", visible, indent) + "\n";
        str = str + indent + "font = {\n" + font.toString(indent + "    ") + indent + "}\n";
        str = str + intToString("scaling", scaling, indent) + "\n";
        return str;
    }


    // Attributes
    private boolean        visible;
    private FontAttributes font;
    private int            scaling;
}

