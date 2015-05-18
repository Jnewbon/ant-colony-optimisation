#pragma once
#include "CLS_MovableObject.h"
#include <list>

class CLS_Flock: public CLS_MovableObject
{
public:
	
	CLS_Flock();
	~CLS_Flock();

	void move();
	void addObject(CLS_MovableObject*);
	std::list<CLS_MovableObject*> getList();
	void draw(float screenWidth, int gridSize);

private:

	std::list<CLS_MovableObject*> flockies;
};

