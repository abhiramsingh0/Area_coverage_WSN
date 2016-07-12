//
// Generated file, do not edit! Created by opp_msgc 4.4 from Broadmsg.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "Broadmsg_m.h"

USING_NAMESPACE

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




Register_Class(Broadmsg);

Broadmsg::Broadmsg(const char *name, int kind) : cMessage(name,kind)
{
    this->hopc_var = 0;
    this->xcor_var = 0;
    this->ycor_var = 0;
}

Broadmsg::Broadmsg(const Broadmsg& other) : cMessage(other)
{
    copy(other);
}

Broadmsg::~Broadmsg()
{
}

Broadmsg& Broadmsg::operator=(const Broadmsg& other)
{
    if (this==&other) return *this;
    cMessage::operator=(other);
    copy(other);
    return *this;
}

void Broadmsg::copy(const Broadmsg& other)
{
    this->hopc_var = other.hopc_var;
    this->xcor_var = other.xcor_var;
    this->ycor_var = other.ycor_var;
}

void Broadmsg::parsimPack(cCommBuffer *b)
{
    cMessage::parsimPack(b);
    doPacking(b,this->hopc_var);
    doPacking(b,this->xcor_var);
    doPacking(b,this->ycor_var);
}

void Broadmsg::parsimUnpack(cCommBuffer *b)
{
    cMessage::parsimUnpack(b);
    doUnpacking(b,this->hopc_var);
    doUnpacking(b,this->xcor_var);
    doUnpacking(b,this->ycor_var);
}

int Broadmsg::getHopc() const
{
    return hopc_var;
}

void Broadmsg::setHopc(int hopc)
{
    this->hopc_var = hopc;
}

double Broadmsg::getXcor() const
{
    return xcor_var;
}

void Broadmsg::setXcor(double xcor)
{
    this->xcor_var = xcor;
}

double Broadmsg::getYcor() const
{
    return ycor_var;
}

void Broadmsg::setYcor(double ycor)
{
    this->ycor_var = ycor;
}

class BroadmsgDescriptor : public cClassDescriptor
{
  public:
    BroadmsgDescriptor();
    virtual ~BroadmsgDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(BroadmsgDescriptor);

BroadmsgDescriptor::BroadmsgDescriptor() : cClassDescriptor("Broadmsg", "cMessage")
{
}

BroadmsgDescriptor::~BroadmsgDescriptor()
{
}

bool BroadmsgDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<Broadmsg *>(obj)!=NULL;
}

const char *BroadmsgDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int BroadmsgDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int BroadmsgDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *BroadmsgDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "hopc",
        "xcor",
        "ycor",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int BroadmsgDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='h' && strcmp(fieldName, "hopc")==0) return base+0;
    if (fieldName[0]=='x' && strcmp(fieldName, "xcor")==0) return base+1;
    if (fieldName[0]=='y' && strcmp(fieldName, "ycor")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *BroadmsgDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "double",
        "double",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *BroadmsgDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int BroadmsgDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    Broadmsg *pp = (Broadmsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string BroadmsgDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    Broadmsg *pp = (Broadmsg *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getHopc());
        case 1: return double2string(pp->getXcor());
        case 2: return double2string(pp->getYcor());
        default: return "";
    }
}

bool BroadmsgDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    Broadmsg *pp = (Broadmsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setHopc(string2long(value)); return true;
        case 1: pp->setXcor(string2double(value)); return true;
        case 2: pp->setYcor(string2double(value)); return true;
        default: return false;
    }
}

const char *BroadmsgDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<3) ? fieldStructNames[field] : NULL;
}

void *BroadmsgDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    Broadmsg *pp = (Broadmsg *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


