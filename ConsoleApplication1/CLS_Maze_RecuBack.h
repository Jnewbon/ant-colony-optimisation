#pragma once
#include "CLS_MazeGenAlgorithm.h"

class CLS_Maze_RecuBack :
	public CLS_MazeGenAlgorithm
{
public:
	CLS_Maze_RecuBack(void);
	~CLS_Maze_RecuBack(void);

	void generate(CLS_Maze_Cell*, int,bool);

};

