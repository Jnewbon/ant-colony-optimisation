#pragma once
#include "CLS_MovableObject.h"
#include "CLS_AI_AntSuperCL.h"
#include "CLS_MazeGenAlgorithm.h"
#include "list"

class CLS_Factory
{
private:
	//No point for the facotry to be instaniated so, prevent that from happening
	CLS_Factory(void);
	//As the Factory will not be instantiated there is no need for a destructor

public:

	static void DestoryAllObjects();

	static CLS_MovableObject* createObj(CLS_MovableObject::objectType);
	static CLS_AI_AntSuperCL* createObj(CLS_AI_AntSuperCL::antAItypes);
	static CLS_MazeGenAlgorithm* createObj(CLS_MazeGenAlgorithm::algorithms);
	static std::list<CLS_MovableObject*> allObjMV;
	static std::list<CLS_AI_AntSuperCL*> allObjAI;
	static std::list<CLS_MazeGenAlgorithm*> allObjMG;
};

