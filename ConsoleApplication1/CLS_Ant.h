#pragma once
#include "CLS_Maze_Cell.h"
#include "CLS_MovableObject.h"
#include "CLS_AI_AntSuperCL.h"
#include "ostream"

#include <vector>

class CLS_Ant :
	public CLS_MovableObject
{
public:

	CLS_Ant();
	~CLS_Ant();

	void setAI(CLS_AI_AntSuperCL::antAItypes);
	void setHome(CLS_Maze_Cell*);
	void move();
	void draw(float screenWidth, int gridSize);

//private:

	bool foundFood;
	
	CLS_Maze_Cell* homeLocation;
	CLS_Maze_Cell* currentLocation;
	CLS_Maze_Cell* lastLocation;
	std::vector<CLS_Maze_Cell*> history;

	CLS_AI_AntSuperCL* antAI;

	void pheroEvap(CLS_Maze_Cell*, int);

	friend std::ostream& operator<<(std::ostream& out, const CLS_Ant& a);

};

