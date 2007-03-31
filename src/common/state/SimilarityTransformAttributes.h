#ifndef SIMILARITYTRANSFORMATTRIBUTES_H
#define SIMILARITYTRANSFORMATTRIBUTES_H
#include <state_exports.h>
#include <string>
#include <AttributeSubject.h>

// ****************************************************************************
// Class: SimilarityTransformAttributes
//
// Purpose:
//    This class contains attributes for the similarity transform.
//
// Notes:      Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Wed Jul 23 11:31:48 PDT 2003
//
// Modifications:
//   
// ****************************************************************************

class STATE_API SimilarityTransformAttributes : public AttributeSubject
{
public:
    enum AngleType
    {
        Deg,
        Rad
    };

    SimilarityTransformAttributes();
    SimilarityTransformAttributes(const SimilarityTransformAttributes &obj);
    virtual ~SimilarityTransformAttributes();

    virtual void operator = (const SimilarityTransformAttributes &obj);
    virtual bool operator == (const SimilarityTransformAttributes &obj) const;
    virtual bool operator != (const SimilarityTransformAttributes &obj) const;

    virtual const std::string TypeName() const;
    virtual bool CopyAttributes(const AttributeGroup *);
    virtual AttributeSubject *CreateCompatible(const std::string &) const;
    virtual AttributeSubject *NewInstance(bool) const;

    // Property selection methods
    virtual void SelectAll();
    void SelectRotateOrigin();
    void SelectRotateAxis();
    void SelectScaleOrigin();

    // Property setting methods
    void SetDoRotate(bool doRotate_);
    void SetRotateOrigin(const float *rotateOrigin_);
    void SetRotateAxis(const float *rotateAxis_);
    void SetRotateAmount(float rotateAmount_);
    void SetRotateType(AngleType rotateType_);
    void SetDoScale(bool doScale_);
    void SetScaleOrigin(const float *scaleOrigin_);
    void SetScaleX(float scaleX_);
    void SetScaleY(float scaleY_);
    void SetScaleZ(float scaleZ_);
    void SetDoTranslate(bool doTranslate_);
    void SetTranslateX(float translateX_);
    void SetTranslateY(float translateY_);
    void SetTranslateZ(float translateZ_);

    // Property getting methods
    bool        GetDoRotate() const;
    const float *GetRotateOrigin() const;
          float *GetRotateOrigin();
    const float *GetRotateAxis() const;
          float *GetRotateAxis();
    float       GetRotateAmount() const;
    AngleType   GetRotateType() const;
    bool        GetDoScale() const;
    const float *GetScaleOrigin() const;
          float *GetScaleOrigin();
    float       GetScaleX() const;
    float       GetScaleY() const;
    float       GetScaleZ() const;
    bool        GetDoTranslate() const;
    float       GetTranslateX() const;
    float       GetTranslateY() const;
    float       GetTranslateZ() const;

    // Persistence methods
    virtual bool CreateNode(DataNode *node, bool forceAdd);
    virtual void SetFromNode(DataNode *node);

    // Enum conversion functions
    static std::string AngleType_ToString(AngleType);
    static bool AngleType_FromString(const std::string &, AngleType &);
protected:
    static std::string AngleType_ToString(int);
public:

    // Keyframing methods
    virtual std::string               GetFieldName(int index) const;
    virtual AttributeGroup::FieldType GetFieldType(int index) const;
    virtual std::string               GetFieldTypeName(int index) const;
    virtual bool                      FieldsEqual(int index, const AttributeGroup *rhs) const;

private:
    bool  doRotate;
    float rotateOrigin[3];
    float rotateAxis[3];
    float rotateAmount;
    int   rotateType;
    bool  doScale;
    float scaleOrigin[3];
    float scaleX;
    float scaleY;
    float scaleZ;
    bool  doTranslate;
    float translateX;
    float translateY;
    float translateZ;
};

#endif
