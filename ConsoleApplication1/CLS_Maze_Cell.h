#pragma once
#include "CoOrd3D.h"



class CLS_Maze_Cell
{
public:

	enum side { TOP, BOTTOM, FRONT, BACK, LEFT, RIGHT, null };
	//enum cellType { WALL, PASSAGE };
	CLS_Maze_Cell(void);
	~CLS_Maze_Cell(void);

	void setPosition(CoOrd3D<int>);
	void setAdjacent(side, CLS_Maze_Cell*);
	void setFood(bool,int);
	void setLink(side, CLS_Maze_Cell*);
	void setLink(int, CLS_Maze_Cell*);
	void setPhero(float);
	void removeFood();
	//void setCellAttrib(cellType);

	CoOrd3D<int> getPosistion();
	CLS_Maze_Cell* getAdjacent(side);
	CLS_Maze_Cell* getAdjacent(int);
	CLS_Maze_Cell* getLink(side);
	CLS_Maze_Cell* getLink(int);
	float getPhero();
	int getFoodAmount();

	static side getReverse(side);
	static int getReverse(int);


	bool getFood();
	//cellType getCellAttrib();

	bool beenVisited;

private:
	 
	// The position of the cell in relation to other cells
	CoOrd3D<int> position;

	//This shall contain the memory loaction of the adjacent cells
	CLS_Maze_Cell *AdjacentCells[6];

	//this will set if the cell contains the food/destination
	bool containsFood;

	//This is for Showing realtime path updates
	int foodAmount;

	//Thiss wil contain the value of what the cell is, either a wall or a passage
	//cellType cellAttribute;
	
	//Links Cells This will contain the nodes that are travalable to from this cell
	CLS_Maze_Cell *LinkedCells[6];

	//this will contain the phromone level of the cell.
	float pheromoneLevel;
};

