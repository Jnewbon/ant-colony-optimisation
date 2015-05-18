#pragma once
#include "CLS_Maze_Cell.h"
#include "CLS_MazeGenAlgorithm.h"

typedef void (*CallbackType)(CLS_Maze_Cell*, int);  

class CLS_Maze
{
public:
	CLS_Maze();
	CLS_Maze(int, int, int, long, CLS_MazeGenAlgorithm::algorithms);
	~CLS_Maze(void);
	static int getCellPos(CoOrd3D<int>,int*);
	CLS_Maze_Cell* getGrid();
	int* getGridSize();
	void setHome(CLS_Maze_Cell*);
	void setFood(CoOrd3D<int>);
	CLS_Maze_Cell* getHomeLoc();

	int shortestPath;

	void applyEvapRule();

	CallbackType pheroEvapRule;

	void start();

private:

	//Stores the size of the grid
	int gridSize[3];

	//Store all the cells of the grid
	CLS_Maze_Cell *grid;

	CLS_Maze_Cell* homeLoc;

	//As there could be many maze generation algorithms 
	//using the comand pattern this will allow the diffrent 
	//algorithms to be chosen at run time
	CLS_MazeGenAlgorithm* maze_Gen;

	//generates the CLS_Maze from the grid using a seed
	void populateMazeArray();
	void generateMazePaths(long);
	void solveMaze();
	
	int seed;


};

