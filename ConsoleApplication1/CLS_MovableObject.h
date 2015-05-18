#pragma once

class CLS_MovableObject
{
public:
	enum objectType { ANT, FLOCK };

	CLS_MovableObject();
	virtual ~CLS_MovableObject(void);

	virtual void move() = 0;
	objectType getObjType();
	void setObjType(objectType);
	virtual void draw(float, int) = 0;

private:

	objectType objType;


};

