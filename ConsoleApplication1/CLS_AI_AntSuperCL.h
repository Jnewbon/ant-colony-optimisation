#pragma once
#include "CLS_Maze_Cell.h"
#include <vector>

/*
This class will contain the basic ACO algorithm. Any dirrived classes will override the basic algortihm
*/

class CLS_AI_AntSuperCL
{

public:

	
	enum antAItypes { BASIC , RANK , RANK_FOOD };

	CLS_AI_AntSuperCL(void);
	virtual ~CLS_AI_AntSuperCL(void);

	virtual CLS_Maze_Cell* move(CLS_Maze_Cell*) = 0;
	virtual void returnMove(std::vector<CLS_Maze_Cell*>) = 0;
	
	static int shortestPath;


};

