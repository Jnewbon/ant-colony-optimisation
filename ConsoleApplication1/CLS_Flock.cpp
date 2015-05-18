#include "CLS_Flock.h"
#include "CLS_Ant.h"
#include "CoreStructures\CoreStructures.h"
#include <iostream>
using namespace std;


CLS_Flock::CLS_Flock()
{
	this->setObjType(this->FLOCK);
}

CLS_Flock::~CLS_Flock()
{
	
	long initSize = flockies.size();
	int percStep;
	int dotStep;
	if (initSize > 100000)
	{
		percStep = flockies.size() / 100;
		dotStep = percStep / 5;
	}
	else if (initSize > 10000)
	{
		percStep = flockies.size() / 50;
		dotStep = percStep / 5;
	}
	else if (initSize > 1000)
	{
		percStep = flockies.size() / 10;
		dotStep = percStep / 5;
	}
	else
	{
		percStep = flockies.size();
		dotStep = percStep / 10;
	}

	cout << "Deleting " << flockies.size() << " ants";

	while(!flockies.empty())
	{
		delete (CLS_Ant*)(flockies.front());
		flockies.pop_front();
		if (flockies.size() % percStep == 0)
			cout << "\n" << int(float((initSize - flockies.size()) / float(initSize))*100.0f) << "%";
		if (flockies.size() % dotStep == 0)
			cout << ".";
	}
	cout << endl;
}

void CLS_Flock::move()
{
	
	for( list<CLS_MovableObject*>::iterator i = this->flockies.begin(); i != this->flockies.end(); i++)
	{
		(*i)->move();
	}

}

void CLS_Flock::addObject(CLS_MovableObject* value)
{
	this->flockies.push_back(value);
}

list<CLS_MovableObject*> CLS_Flock::getList()
{
	return this->flockies;
}

void CLS_Flock::draw(float screenWidth, int gridSize)
{
	
	for( list<CLS_MovableObject*>::iterator i = this->flockies.begin(); i != this->flockies.end(); i++)
	{
		(*i)->draw(screenWidth,gridSize);
	}

}