#pragma once
#include "CLS_MazeGenAlgorithm.h"
class CLS_Maze_Primms :
	public CLS_MazeGenAlgorithm
{
public:
	CLS_Maze_Primms();
	~CLS_Maze_Primms();

	void generate(CLS_Maze_Cell*, int,bool);

};

