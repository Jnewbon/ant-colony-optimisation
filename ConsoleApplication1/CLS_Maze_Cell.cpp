#include "CLS_Maze_Cell.h"


CLS_Maze_Cell::CLS_Maze_Cell(void)
{
	//Pheromones levels Are 0 to start with
	this->pheromoneLevel = 0.0f;

	for (int i = 0; i < 6; i++)
	{
		//set the adjacent cells to null pointer
		this->LinkedCells[i] = nullptr;
	}

	//No cell will have been visited yet
	beenVisited = false;
	this->pheromoneLevel = 0;
	this->containsFood = false;
	this->foodAmount = 0;
}

CLS_Maze_Cell::~CLS_Maze_Cell(void)
{
	for (int i = 0; i < 6; i++)
	{
		//set the adjacent cells to null pointer
		this->AdjacentCells[i] = nullptr;
		this->LinkedCells[i] = nullptr;
	}
	
}

void CLS_Maze_Cell::setPosition(CoOrd3D<int> Pos)
{

	this->position = Pos;

}
void CLS_Maze_Cell::setAdjacent(side cellside, CLS_Maze_Cell* addr)
{

	this->AdjacentCells[cellside] = addr;

}
void CLS_Maze_Cell::setLink(side cellside, CLS_Maze_Cell* addr)
{

	this->LinkedCells[cellside] = addr;

}
void CLS_Maze_Cell::setLink(int cellside, CLS_Maze_Cell* addr)
{

	this->LinkedCells[cellside] = addr;

}
void CLS_Maze_Cell::setFood(bool value, int amount)
{

	this->containsFood = value;
	this->foodAmount = amount;

}
void CLS_Maze_Cell::setPhero(float value)
{
	this->pheromoneLevel += value;
}
void CLS_Maze_Cell::removeFood()
{
	if (this->foodAmount > 1)
		this->foodAmount -= 1;
	else if (this->foodAmount == 1)
	{
		this->containsFood = false;
		this->foodAmount = 0;
	}
}

CoOrd3D<int> CLS_Maze_Cell::getPosistion()
{

	return this->position;

}
CLS_Maze_Cell* CLS_Maze_Cell::getAdjacent(side value)
{

	return this->AdjacentCells[value];

}
CLS_Maze_Cell* CLS_Maze_Cell::getAdjacent(int value)
{

	return this->AdjacentCells[value];

}
CLS_Maze_Cell* CLS_Maze_Cell::getLink(side value)
{

	return this->LinkedCells[value];

}
CLS_Maze_Cell* CLS_Maze_Cell::getLink(int value)
{

	return this->LinkedCells[value];

}
bool CLS_Maze_Cell::getFood()
{

	return this->containsFood;

}
float CLS_Maze_Cell::getPhero()
{
	return this->pheromoneLevel;
}
int CLS_Maze_Cell::getFoodAmount()
{
	return this->foodAmount;
}

CLS_Maze_Cell::side CLS_Maze_Cell::getReverse(CLS_Maze_Cell::side direc)
{
	switch (direc)
	{
		case TOP:
			return BOTTOM;
		case BOTTOM:
			return TOP;
		case LEFT:
			return RIGHT;
		case RIGHT:
			return LEFT;
		case FRONT:
			return BACK;
		case BACK:
			return FRONT;
	}
	
	return FRONT;

}
int CLS_Maze_Cell::getReverse(int direc)
{
	switch (direc)
	{
		case TOP:
			return BOTTOM;
		case BOTTOM:
			return TOP;
		case LEFT:
			return RIGHT;
		case RIGHT:
			return LEFT;
		case FRONT:
			return BACK;
		case BACK:
			return FRONT;
	}
	
	return FRONT;
}
