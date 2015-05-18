#include "CLS_MovableObject.h"

CLS_MovableObject::CLS_MovableObject()
{

}
CLS_MovableObject::~CLS_MovableObject(void)
{

}

CLS_MovableObject::objectType CLS_MovableObject::getObjType()
{
	return this->objType;
}
void CLS_MovableObject::setObjType(CLS_MovableObject::objectType value)
{
	this->objType = value;
}
