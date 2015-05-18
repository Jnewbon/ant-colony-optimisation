#include "CLS_Factory.h"
#include "CLS_Ant.h"
#include "CLS_AI_ACO.h"

#include "CLS_Flock.h"
#include "CLS_Maze_Primms.h"
#include "CLS_Maze_RecuBack.h"
#include "CLS_Maze_Allopen.h"


std::list<CLS_MovableObject*> CLS_Factory::allObjMV;
std::list<CLS_AI_AntSuperCL*> CLS_Factory::allObjAI;
std::list<CLS_MazeGenAlgorithm*> CLS_Factory::allObjMG;

CLS_Factory::CLS_Factory(void)
{

}


CLS_MovableObject* CLS_Factory::createObj(CLS_MovableObject::objectType type)
{
	CLS_MovableObject* retrunObj;
	switch (type)
	{
	case CLS_MovableObject::ANT:
		retrunObj = new CLS_Ant();
		break;

	case CLS_MovableObject::FLOCK:
		retrunObj = new CLS_Flock();
		break;

	}

	allObjMV.push_back(retrunObj);

	return retrunObj;
}

CLS_AI_AntSuperCL* CLS_Factory::createObj(CLS_AI_AntSuperCL::antAItypes type)
{
		CLS_AI_AntSuperCL* retrunObj;
	switch (type)
	{
	case CLS_AI_AntSuperCL::BASIC:
		retrunObj = new CLS_AI_ACO();
		break;


	}

	allObjAI.push_back(retrunObj);
	return retrunObj;
}

CLS_MazeGenAlgorithm* CLS_Factory::createObj(CLS_MazeGenAlgorithm::algorithms type)
{
		CLS_MazeGenAlgorithm* retrunObj;
	switch (type)
	{
	case CLS_MazeGenAlgorithm::PRIMMS:
		retrunObj = new CLS_Maze_Primms();
		break;

	case CLS_MazeGenAlgorithm::RECUBACK:
		retrunObj = new CLS_Maze_RecuBack();
		break;
	case CLS_MazeGenAlgorithm::ALLOPEN:
		retrunObj = new CLS_Maze_Allopen();
		break;
		
	}
	allObjMG.push_back(retrunObj);
	return retrunObj;
}

void CLS_Factory::DestoryAllObjects()
{

	
}