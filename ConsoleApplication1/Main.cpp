//#ifdef _DEBUG 
//	#ifndef DGB_NEW
//		#define DBG_NEW new ( _NORMAL_BLOCK, __FILE__ , __LINE__ )
//		#define new DBG_NEW
//		#define _CRTDBG_MAP_ALLOC
//	#endif
//#endif
//
//#define DEBUG
	
#include "debugOptions.h"
#include "CLS_Maze.h"
#include "CLS_Maze_Cell.h"
#include "CoOrd3D.h"
#include "CLS_MovableObject.h"
#include "CLS_Factory.h"
#include "CLS_Simulator.h"

#include <iostream>
#include <time.h>
#include <string>
#include <iostream>

using namespace std;



int main(int argc, char **argv)
{
	//gu_memory_report();
	////_CrtSetBreakAlloc(186); 

	////Used to check for Memory leaks
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//
	int Grid_X, Grid_Y, Grid_Z, Num_ants;
	Grid_X = 20;
	Grid_Y = 20;
	Grid_Z = 2;
	Num_ants = 100;
	cout << "Test 1" << endl;
	cout << "ACO Algorithm: Rank ACO" << endl;
	cout << "Pheromone deposition amount 100" << endl;
	cout << "Pheromone Evap Rate 0.5% per iteration" << endl;
	cout << "Grid Type: Recursive Back" << endl;
	cout << "Grid Size: { " << Grid_X << " , " << Grid_Y << " , " << Grid_Z << " }" << endl
		 << "Number of Ants: " << Num_ants << endl;

	system("PAUSE");

	try
	{

		CLS_Simulator::simulationInit(argc,argv);
		CLS_Simulator::simulationGridInit(Grid_X,Grid_Y,Grid_Z,0,CLS_MazeGenAlgorithm::RECUBACK);
		CLS_Simulator::simulationAIInit(Num_ants,CLS_AI_AntSuperCL::RANK);
		CLS_Simulator::simulationAddFood(1);
		CLS_Simulator::mainLoop();
	}
	catch(int errorCode)
	{
		cout << endl << debug::getErrorCode(errorCode) << "     " << endl;
	}
	
	system("PAUSE");
	system("CLS");
	CLS_Simulator::simulatorDestruct();
	CLS_Factory::DestoryAllObjects(); //MWAHAHAHAHA
	//gu_memory_report();
	_CrtDumpMemoryLeaks();
	system("PAUSE");
	//_CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_DEBUG );
	return 0;
}