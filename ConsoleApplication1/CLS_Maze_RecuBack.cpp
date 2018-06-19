#include "debugOptions.h"

#include "CLS_Maze_RecuBack.h"
#include "CLS_Maze.h"
#include "CLS_Simulator.h"
#include <stack>
#include <Windows.h>

#include <iostream>

using namespace std;

CLS_Maze_RecuBack::CLS_Maze_RecuBack()
{

}

CLS_Maze_RecuBack::~CLS_Maze_RecuBack()
{

}

void CLS_Maze_RecuBack::generate(CLS_Maze_Cell* grid, int maxSize, bool perfect)
{
	//this will store the history of the algorithm so we can backtrack through the maze
	stack<CLS_Maze_Cell*> backTrace;

	//get a random cell from the grid and set it as the first cell
	CLS_Maze_Cell* currentCell = &grid[rand() % maxSize];
#ifdef DEBUG_MAZE_GEN
	CLS_Simulator::getScreen()->getConsole()->clear();
#endif
	backTrace.push(currentCell);

	currentCell->beenVisited = true;

	while(!backTrace.empty())
	{

		bool deadEnd[6];

		for (int i = 0; i<6; i++)
		{
			deadEnd[i] = false;
		}


		while((!deadEnd[0] || !deadEnd[1] || !deadEnd[2] || !deadEnd[3] || !deadEnd[4] || !deadEnd[5]))
		{

			//Chose a direction between 0 - 5
			int direction = rand() % 6;
			//Must check if the cell i null before any other evaluation
			if (backTrace.top()->getAdjacent(direction) != NULL)
			{
				if(backTrace.top()->getAdjacent(direction)->beenVisited != true)
				{
					//Set the link to new cell
					backTrace.top()->setLink(direction,backTrace.top()->getAdjacent(direction));

					//set the link from the new cell
					backTrace.top()->getAdjacent(direction)->setLink(CLS_Maze_Cell::getReverse(direction),backTrace.top());

					//set the cell as visited
					backTrace.top()->getAdjacent(direction)->beenVisited = true;

					//Push the newcell into the stack
					backTrace.push(backTrace.top()->getAdjacent(direction));

#ifdef DEBUG_MAZE_GEN_3D
					CLS_Simulator::rotateDisplay(1.0f, 1.f);
					CLS_Simulator::display();
#endif
#ifdef DEBUG_MAZE_GEN //So the the grid is output to the console as it gernerates if the dubug define is set

					CLS_Screen* output = CLS_Simulator::getScreen();
					
					output->getConsole()->setColour(output->getConsole()->WHITE,output->getConsole()->BLUE);

					//output->getConsole()->clear();

					int size[3] = {10,10,2};

					
					for (int i = 0; i < size[2]; i++)
					{

						for(int j = 0; j < size[1]; j++)
						{
							for(int k = 0; k < size[0]; k++)
							{
								
								if (grid[CLS_Maze::getCellPos(CoOrd3D<int>(k,j,i),size)].beenVisited)
								{
									if (grid[CLS_Maze::getCellPos(CoOrd3D<int>(k,j,i),size)].getLink(CLS_Maze_Cell::BACK)!=NULL &&
										grid[CLS_Maze::getCellPos(CoOrd3D<int>(k,j,i),size)].getLink(CLS_Maze_Cell::FRONT)==NULL)
										output->getConsole()->setColour(output->getConsole()->LIGHT_YELLOW,output->getConsole()->GREEN);
									else if (grid[CLS_Maze::getCellPos(CoOrd3D<int>(k,j,i),size)].getLink(CLS_Maze_Cell::BACK)==NULL &&
											 grid[CLS_Maze::getCellPos(CoOrd3D<int>(k,j,i),size)].getLink(CLS_Maze_Cell::FRONT)!=NULL)
										output->getConsole()->setColour(output->getConsole()->LIGHT_YELLOW,output->getConsole()->LIGHT_RED);
									else if (grid[CLS_Maze::getCellPos(CoOrd3D<int>(k,j,i),size)].getLink(CLS_Maze_Cell::BACK)!=NULL &&
											 grid[CLS_Maze::getCellPos(CoOrd3D<int>(k,j,i),size)].getLink(CLS_Maze_Cell::FRONT)!=NULL )
										output->getConsole()->setColour(output->getConsole()->LIGHT_YELLOW,output->getConsole()->LIGHT_PURPLE);
									else
										output->getConsole()->setColour(output->getConsole()->LIGHT_YELLOW,output->getConsole()->LIGHT_YELLOW);
									output->outputPos(1+ k*2,(1+ j*2)+21*i," ");
									output->getConsole()->setColour(output->getConsole()->WHITE,output->getConsole()->BLUE);
								}
								if (grid[CLS_Maze::getCellPos(CoOrd3D<int>(k,j,i),size)].getLink(CLS_Maze_Cell::RIGHT) != NULL)
								{
									output->getConsole()->setColour(output->getConsole()->LIGHT_YELLOW,output->getConsole()->LIGHT_YELLOW);
									output->outputPos(2+ k*2,(1+ j*2)+21*i," ");
									output->getConsole()->setColour(output->getConsole()->WHITE,output->getConsole()->BLUE);
								}
								if (grid[CLS_Maze::getCellPos(CoOrd3D<int>(k,j,i),size)].getLink(CLS_Maze_Cell::TOP) != NULL)
								{
									output->getConsole()->setColour(output->getConsole()->LIGHT_YELLOW,output->getConsole()->LIGHT_YELLOW);
									output->outputPos(1+ k*2, (2+ j*2)+21*i," ");
									output->getConsole()->setColour(output->getConsole()->WHITE,output->getConsole()->BLUE);
								}
							}
						}
					}

					//Sleep(100);
#endif
				}
				else
					deadEnd[direction] = true;

			}
			else
				deadEnd[direction] = true;
				
		}

		backTrace.pop();

	}

	if (!perfect)
	{
		for (int i = 0; i < (maxSize / 10); i++)
		{
			int randNum = rand() % maxSize;
			int randSide = rand() % 6;
			while(grid[randNum].getAdjacent(randSide) == nullptr)
				randSide = rand() % 6;
			//Set the Link to
			grid[randNum].setLink(randSide,grid[randNum].getAdjacent(randSide));
			//Set the link from
			grid[randNum].getAdjacent(randSide)->setLink(CLS_Maze_Cell::getReverse(randSide),&(grid[randNum]));
		}
	}
}
