#pragma once
#include "CLS_Maze_Cell.h"
class CLS_MazeGenAlgorithm
{
public:
	//Will list all the algorithms
	enum algorithms { PRIMMS , RECUBACK, ALLOPEN};
	
	/*
	This function will run through a grid and generate the paths of the maze
	As there is no default algorithm the function will not be have a definition.
	That will be done in any derived classes
	Third option is if the algoritm will generate a perfect maze or not
	*/
	virtual void generate(CLS_Maze_Cell*, int,bool) = 0;

};

