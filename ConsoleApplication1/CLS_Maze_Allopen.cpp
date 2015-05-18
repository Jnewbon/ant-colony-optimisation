#include "CLS_Maze_Allopen.h"


CLS_Maze_Allopen::CLS_Maze_Allopen(void)
{
}


CLS_Maze_Allopen::~CLS_Maze_Allopen(void)
{
}

void CLS_Maze_Allopen::generate(CLS_Maze_Cell* grid, int maxSize, bool perfect)
{

	for (int i = 0; i <= maxSize; i++)
	{

		for (int j = 0; j < 6; j++)
		{

			grid[i].setLink(j,grid[i].getAdjacent(j));

		}

	}

}