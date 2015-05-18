#pragma once
#include "CLS_AI_AntSuperCL.h"
class CLS_AI_Rank_Food :
	public CLS_AI_AntSuperCL
{
public:
	CLS_AI_Rank_Food(void);
	~CLS_AI_Rank_Food(void);

	CLS_Maze_Cell* move(CLS_Maze_Cell*);
	
	void returnMove(std::vector<CLS_Maze_Cell*>);

	static void pheroEvapRule(CLS_Maze_Cell*, int);
};

