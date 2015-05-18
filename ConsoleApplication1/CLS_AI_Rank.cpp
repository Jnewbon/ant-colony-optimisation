#include "CLS_AI_Rank.h"
#include <vector>

CLS_AI_Rank::CLS_AI_Rank(void)
{
}


CLS_AI_Rank::~CLS_AI_Rank(void)
{
}

CLS_Maze_Cell* CLS_AI_Rank::move(CLS_Maze_Cell* currentCell)
{

	float path[6];

	for (int i = 0; i < 6; i++)
	{

		if (currentCell->getLink(i) != nullptr)
			path[i] = (currentCell->getLink(i)->getPhero() + 1.0f) * (float(rand() % 100)+1.0f);
		else
			path[i] = 0;

	}

	int highestSide = 7;

	for (int i = 0; i < 6; i++)
	{
		if (highestSide != 7)
		{
			if ( path[highestSide] < path[i] )
				highestSide = i;
		}
		else
			highestSide = i;
	}

	if (currentCell->getLink(highestSide) == nullptr)
		throw 1;

	return currentCell->getLink(highestSide);

	/*std::vector<int> tempList;
	for (int i = 0; i < 6; i++)
	{
		if (currentCell->getLink(i) != nullptr)
		{
			for (int j = 0; j < (currentCell->getLink(i)->getPhero() * 40) + 1; j++)
				tempList.push_back(i);
		}
	}
	
	return currentCell->getLink(tempList[rand() % tempList.size()]);
	*/
}

void CLS_AI_Rank::returnMove(std::vector<CLS_Maze_Cell*> history)
{
	if (shortestPath == 0 || shortestPath > history.size())
	{
		shortestPath = history.size();
	}
	const float PHERO_DEPO_CONT = 100; //The base number the phromones depositied.
	int startSize = history.size();
	//Loop elimination

	bool lElimFin = false;
	while(!lElimFin)
	{
		bool Break = false;
		for (std::vector<CLS_Maze_Cell*>::iterator i = history.begin(); i != history.end(); i++)
		{

			if (Break)
				break;

			for (std::vector<CLS_Maze_Cell*>::iterator j = i +1; j != history.end(); j++)
			{

				if ((*i)== (*j))
				{
					if((*i+1) == (*j))
					{
						//Then thewre is only one element to remove
					}
					history.erase(i+1,j+1);
					Break = true;
					break;
				}
				
			}

			//Rechaed the end of the loop so set the variable to break the while
			if (i+1 == history.end())
				lElimFin = true;
		}
	}

	//Lay the pheromones down on the path.
	while (!history.empty())
	{
		history.back()->setPhero(PHERO_DEPO_CONT/startSize);
		history.pop_back();
	}

}
void CLS_AI_Rank::pheroEvapRule(CLS_Maze_Cell* theGrid, int sizeOfGrid)
{

	for (int i = 0; i < sizeOfGrid; i ++)
	{
		theGrid[i].setPhero(-(theGrid[i].getPhero()*0.00005f));
	}

}

