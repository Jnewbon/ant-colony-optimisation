#pragma once
#include "CLS_MazeGenAlgorithm.h"
class CLS_Maze_Allopen:
	public CLS_MazeGenAlgorithm
{
public:
	CLS_Maze_Allopen(void);
	~CLS_Maze_Allopen(void);

	void generate(CLS_Maze_Cell*, int,bool);
};

