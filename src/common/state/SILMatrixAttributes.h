#ifndef SILMATRIXATTRIBUTES_H
#define SILMATRIXATTRIBUTES_H
#include <state_exports.h>
#include <string>
#include <AttributeSubject.h>

// ****************************************************************************
// Class: SILMatrixAttributes
//
// Purpose:
//    This class contain the information needed to represent a SIL Matrix.
//
// Notes:      Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Wed Jul 23 11:31:38 PDT 2003
//
// Modifications:
//   
// ****************************************************************************

class STATE_API SILMatrixAttributes : public AttributeSubject
{
public:
    SILMatrixAttributes();
    SILMatrixAttributes(const SILMatrixAttributes &obj);
    virtual ~SILMatrixAttributes();

    virtual void operator = (const SILMatrixAttributes &obj);
    virtual bool operator == (const SILMatrixAttributes &obj) const;
    virtual bool operator != (const SILMatrixAttributes &obj) const;

    virtual const std::string TypeName() const;
    virtual bool CopyAttributes(const AttributeGroup *);
    virtual AttributeSubject *CreateCompatible(const std::string &) const;
    virtual AttributeSubject *NewInstance(bool) const;

    // Property selection methods
    virtual void SelectAll();
    void SelectSet1();
    void SelectCategory1();
    void SelectSet2();
    void SelectCategory2();

    // Property setting methods
    void SetSet1(const intVector &set1_);
    void SetCategory1(const std::string &category1_);
    void SetRole1(int role1_);
    void SetSet2(const intVector &set2_);
    void SetCategory2(const std::string &category2_);
    void SetRole2(int role2_);

    // Property getting methods
    const intVector   &GetSet1() const;
          intVector   &GetSet1();
    const std::string &GetCategory1() const;
          std::string &GetCategory1();
    int               GetRole1() const;
    const intVector   &GetSet2() const;
          intVector   &GetSet2();
    const std::string &GetCategory2() const;
          std::string &GetCategory2();
    int               GetRole2() const;

    // Persistence methods
    virtual bool CreateNode(DataNode *node, bool forceAdd);
    virtual void SetFromNode(DataNode *node);


    // Keyframing methods
    virtual std::string               GetFieldName(int index) const;
    virtual AttributeGroup::FieldType GetFieldType(int index) const;
    virtual std::string               GetFieldTypeName(int index) const;
    virtual bool                      FieldsEqual(int index, const AttributeGroup *rhs) const;

private:
    intVector   set1;
    std::string category1;
    int         role1;
    intVector   set2;
    std::string category2;
    int         role2;
};

#endif
