#pragma once
#include "CLS_AI_AntSuperCL.h"
class CLS_AI_ACO: public CLS_AI_AntSuperCL
{
public:
	CLS_AI_ACO(void);
	~CLS_AI_ACO(void);

	CLS_Maze_Cell* move(CLS_Maze_Cell*);
	void returnMove(std::vector<CLS_Maze_Cell*>);

};

