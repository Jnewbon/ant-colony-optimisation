#include "CLS_Ant.h"
#include "CLS_AI_ACO.h"
#include "CLS_AI_Rank.h"
#include "CLS_AI_Rank_Food.h"
#include <iostream>
#include "GL\glew\glew.h"
#include "GL\glut.h"
#include "GL\freeglut.h"
#include "GL\glew\wglew.h"

CLS_Ant::CLS_Ant()
{
	this->setObjType(this->ANT);
	this->foundFood = false;
	this->currentLocation = nullptr;
	this->lastLocation = nullptr;
	this->homeLocation = nullptr;
//	this->antAI = nullptr;
}
CLS_Ant::~CLS_Ant()
{
	
	this->setObjType(this->ANT);
	this->foundFood = false;
	this->currentLocation = nullptr;
	this->lastLocation = nullptr;
	this->homeLocation = nullptr;
	delete (this->antAI);
	this->antAI = nullptr;
	while(!this->history.empty()) 
		this->history.pop_back();
	
}

void CLS_Ant::move()
{

	if(currentLocation == nullptr)
		throw 1; 
	//else if (antAI == nullptr)
	//	throw 2;
			
	if (this->currentLocation->getFood())
	{

		this->antAI->returnMove(this->history);
		this->currentLocation = this->homeLocation;
		while(!this->history.empty()) 
			this->history.pop_back();
	}
	CLS_Maze_Cell* temp;
	int i = 0;
	do
	{
		temp = this->antAI->move(this->currentLocation);
		i++;
	}
	while (temp == this->lastLocation && i <= 2);


	this->lastLocation = this->currentLocation;
	this->currentLocation = temp;

	this->history.push_back(this->currentLocation);


}

void CLS_Ant::setAI(CLS_AI_AntSuperCL::antAItypes aiType)
{
	if (aiType == CLS_AI_AntSuperCL::BASIC)
		this->antAI = new CLS_AI_ACO();
	else if (aiType == CLS_AI_AntSuperCL::RANK)
		this->antAI = new CLS_AI_Rank();
	else if( aiType == CLS_AI_AntSuperCL::RANK_FOOD)
		this->antAI = new CLS_AI_Rank_Food();
}
void CLS_Ant::setHome(CLS_Maze_Cell* home)
{
	this->homeLocation = home;
	this->currentLocation = home;
}

std::ostream& operator<<(std::ostream &out, const CLS_Ant& a)
{
	out << "Loc {\t"	<< a.currentLocation->getPosistion().x << 
			",\t"		<< a.currentLocation->getPosistion().y << 
			",\t"		<< a.currentLocation->getPosistion().z << 
			"} \t hist: "	<< a.history.size() <<
			"\t Phero: "	<< a.currentLocation->getPhero();
	return out;
}
void CLS_Ant::draw(float screenWidth, int gridSize)
{

	glPointSize(3.0f);
	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
	glBegin(GL_POINTS);
	//All the axis are divided by the X axis so the grid will aprear Square rather then elongated.
	glVertex3f(
		((screenWidth / (gridSize)) * this->currentLocation->getPosistion().x) - (screenWidth /2) + ((float(rand() % 1000) / 100.0f) - 5.0f),
		((screenWidth / (gridSize)) * this->currentLocation->getPosistion().y) - (screenWidth /2) + ((float(rand() % 1000) / 100.0f) - 5.0f),
		((screenWidth / (gridSize)) * this->currentLocation->getPosistion().z) - (screenWidth /2) + ((float(rand() % 1000) / 100.0f) - 5.0f)
		);
	glEnd();
}

