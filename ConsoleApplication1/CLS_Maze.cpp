#include "CLS_Maze.h"
#include "CLS_Simulator.h"
#include "CLS_Factory.h"
#include <cstdlib>
#include <stack>

#include <iostream>
#include <time.h>

using namespace std;

CLS_Maze::CLS_Maze(int width, int height, int depth, long seed, CLS_MazeGenAlgorithm::algorithms mz_gen)
{

	this->gridSize[0]	=	width;
	this->gridSize[1]	=	height;
	this->gridSize[2]	=	depth;

	this->maze_Gen = CLS_Factory::createObj(mz_gen);

	this->seed = seed;

	this->shortestPath = -1;
	

	//Lets start the graphics before creating the maze so the user can see it while its being made
	//CLS_Simulator::setGrid(this->grid, this->gridSize);

	//this->GraphicsThread = new std::thread(CLS_Simulator::simulationInit);

	



/*
	for (int i = 0; i < depth; i++)
	{

		for(int j = 0; j < height; j++)
		{
			for(int k = 0; k < width; k++)
			{
				std::cout << this->grid[this->getCellPos(CoOrd3D<int>(k,j,i))].getCellAttrib() << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	*/


}

void CLS_Maze::populateMazeArray()
{

	// set the internal width height and depth modifier

	this->grid = new CLS_Maze_Cell[this->gridSize[0] * this->gridSize[1] * this->gridSize[2]];

	//we Want the for loops to run in revers to how we are setting them so if wedealing with x first that will be the last loop coded
	// So as we want X, Y then Z the for loops will be  Z, Y then X
	for( int z = 0; z < this->gridSize[2]; z++)
	{
		for( int y = 0; y < this->gridSize[1]; y++)
		{
			for( int x = 0; x < this->gridSize[0]; x++)
			{

				//The combination of X,Y and Z give the position of the cell in the array.
				//As the array is only one dimestion, we shall use the function getCellPosition 
				//to return the location in the array that coordinate is.
				//As we will need this number lots of times lets store it tempoarally
				int cellnumber = this->getCellPos(CoOrd3D<int>(x,y,z),this->gridSize);

				//Set the current position in the grid
				this->grid[cellnumber].setPosition(CoOrd3D<int>(x,y,z));

				//To make navigating the grid simple each cell will know it neighbours
				//Here we will set each neighbour for each cell.
				if(x == 0)//If the cell is at the leading Far Left
				{
					this->grid[cellnumber].setAdjacent(CLS_Maze_Cell::LEFT, nullptr);
					this->grid[cellnumber].setAdjacent(CLS_Maze_Cell::RIGHT, &this->grid[this->getCellPos(CoOrd3D<int>(x+1,y,z),this->gridSize)]);
				}
				else if(x == this->gridSize[0] - 1)//If the cell is at the Far Right
				{
					this->grid[cellnumber].setAdjacent(CLS_Maze_Cell::LEFT, &this->grid[this->getCellPos(CoOrd3D<int>(x-1,y,z),this->gridSize)]);
					this->grid[cellnumber].setAdjacent(CLS_Maze_Cell::RIGHT, nullptr);
				}
				else //If the ceel is in the middle somewhere
				{
					this->grid[cellnumber].setAdjacent(CLS_Maze_Cell::LEFT, &this->grid[this->getCellPos(CoOrd3D<int>(x-1,y,z),this->gridSize)]);
					this->grid[cellnumber].setAdjacent(CLS_Maze_Cell::RIGHT, &this->grid[this->getCellPos(CoOrd3D<int>(x+1,y,z),this->gridSize)]);
				}

				if(y == 0)//Repeat for Y as above
				{
					this->grid[cellnumber].setAdjacent(CLS_Maze_Cell::BOTTOM, nullptr);
					this->grid[cellnumber].setAdjacent(CLS_Maze_Cell::TOP, &this->grid[this->getCellPos(CoOrd3D<int>(x,y+1,z),this->gridSize)]);
				}
				else if(y == this->gridSize[1] - 1)
				{
					this->grid[cellnumber].setAdjacent(CLS_Maze_Cell::BOTTOM, &this->grid[this->getCellPos(CoOrd3D<int>(x,y-1,z),this->gridSize)]);
					this->grid[cellnumber].setAdjacent(CLS_Maze_Cell::TOP, nullptr);
				}
				else
				{
					this->grid[cellnumber].setAdjacent(CLS_Maze_Cell::BOTTOM, &this->grid[this->getCellPos(CoOrd3D<int>(x,y-1,z),this->gridSize)]);
					this->grid[cellnumber].setAdjacent(CLS_Maze_Cell::TOP, &this->grid[this->getCellPos(CoOrd3D<int>(x,y+1,z),this->gridSize)]);
				}
				if (this->gridSize[2] == 1)
				{
					//Special case if only a 2d maze is made
					this->grid[cellnumber].setAdjacent(CLS_Maze_Cell::FRONT, nullptr);
					this->grid[cellnumber].setAdjacent(CLS_Maze_Cell::BACK, nullptr );
				}
				else if(z == 0)//Repeat for Z as above
				{
					this->grid[cellnumber].setAdjacent(CLS_Maze_Cell::FRONT, nullptr);
					this->grid[cellnumber].setAdjacent(CLS_Maze_Cell::BACK, &this->grid[this->getCellPos(CoOrd3D<int>(x,y,z+1),this->gridSize)]);
				}
				else if(z == this->gridSize[2] - 1)
				{
					this->grid[cellnumber].setAdjacent(CLS_Maze_Cell::FRONT, &this->grid[this->getCellPos(CoOrd3D<int>(x,y,z-1),this->gridSize)]);
					this->grid[cellnumber].setAdjacent(CLS_Maze_Cell::BACK, nullptr );
				}
				else
				{
					this->grid[cellnumber].setAdjacent(CLS_Maze_Cell::BACK, &this->grid[this->getCellPos(CoOrd3D<int>(x,y,z+1),this->gridSize)]);
					this->grid[cellnumber].setAdjacent(CLS_Maze_Cell::FRONT, &this->grid[this->getCellPos(CoOrd3D<int>(x,y,z-1),this->gridSize)]);
				}

			}
		}
		
	}

}

CLS_Maze::~CLS_Maze(void)
{
	std::cout << "\nMaze Destructor:\n";

	/*for (int i = 0; i < this->gridSize[0] * this->gridSize[1] * this->gridSize[2]; i++)
	{
		this->grid[i];
	}*/

	delete[] this->grid;
	delete this->maze_Gen;
}

void CLS_Maze::generateMazePaths(long seed)
{

	srand(seed);

	this->maze_Gen->generate(this->grid,this->getCellPos(CoOrd3D<int>(this->gridSize[0]-1,this->gridSize[1]-1,this->gridSize[2]-1),this->gridSize),false);

	this->homeLoc = &this->grid[0];

	//Reset the rand to actual random
	srand(time(NULL));

	/*this->foodLoc = &this->grid[this->getCellPos(CoOrd3D<int>(this->gridSize[0]-1,this->gridSize[1]-1,this->gridSize[2]-1),this->gridSize)];

	this->foodLoc->setFood(true,);*/

}

int CLS_Maze::getCellPos(CoOrd3D<int> pos,int* size)
{
	return ((pos.z) * (size[0] * size[1])) + ((pos.y) * size[0]) + pos.x;
}

void CLS_Maze::start()
{
	this->populateMazeArray();

	this->generateMazePaths(this->seed);

	//this->solveMaze();
}

CLS_Maze_Cell* CLS_Maze::getGrid()
{
	return this->grid;
}

int* CLS_Maze::getGridSize()
{
	return this->gridSize;
}

void  CLS_Maze::setHome(CLS_Maze_Cell* home)
{
	 homeLoc = home;
}

CLS_Maze_Cell* CLS_Maze::getHomeLoc()
{
	return homeLoc;
}

void CLS_Maze::applyEvapRule()
{
	pheroEvapRule(this->grid, this->gridSize[0] * this->gridSize[1] * this->gridSize[2]);
}

void CLS_Maze::solveMaze()
{
	//this will store the history of the algorithm so we can backtrack through the maze
	stack<CLS_Maze_Cell*> backTrace;

	//start from the home cell
	CLS_Maze_Cell* currentCell = this->getHomeLoc();

	backTrace.push(currentCell);

	//As this is the second time the maze has been run thrue we will work with the oppisite of true/false
	currentCell->beenVisited = false;

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
			if (backTrace.top()->getLink(direction) != NULL && backTrace.top()->getLink(direction) != nullptr)
			{
				//if the cell has not been (!visited) before 
				if(backTrace.top()->getLink(direction)->beenVisited != false)
				{
					//Set the link to new cell
					backTrace.top()->setLink(direction,backTrace.top()->getLink(direction));

					//set the link from the new cell
					backTrace.top()->getLink(direction)->setLink(CLS_Maze_Cell::getReverse(direction),backTrace.top());

					//set the cell as (!visited)
					backTrace.top()->getLink(direction)->beenVisited = false;

					//Push the newcell into the stack
					backTrace.push(backTrace.top()->getLink(direction));

					for (int i = 0; i<6; i++)
					{
						deadEnd[i] = false;
					}

				}
				else
					deadEnd[direction] = true;

			}
			else
				deadEnd[direction] = true;
				
		}
		//if the current cell has food then break as the stack will contain the "only" path to the food
		//The nature of the algorithm means that in a perfect maze the stack will always contain the shortest path to the food
		if (backTrace.top()->getFood())
			break; 
		backTrace.pop();

	}
	//as the home isnt counted as a "move" -1 as size() dosent start from 0
	this->shortestPath = backTrace.size()-1;
}

void CLS_Maze::setFood(CoOrd3D<int> loc)
{
	grid[getCellPos(loc, this->getGridSize())].setFood(true,200);
}
