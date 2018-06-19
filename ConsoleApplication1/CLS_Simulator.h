#if !defined(_CLS_SIMULATOR_H)
#define _CLS_SIMULATOR_H

#include <vector>


#include "GL\glew\glew.h"
#include "GL\glut.h"
#include "GL\freeglut.h"
#include "GL\glew\wglew.h"
//#include "CoreStructures\CoreStructures.h"

#include "CLS_Screen.h"
#include "CLS_Maze.h"
#include "CLS_Maze_Cell.h"
#include "CLS_MazeGenAlgorithm.h"
#include "CLS_AI_AntSuperCL.h"
#include "CLS_MovableObject.h"


class CLS_Simulator {
public:

	
	static void simulationInit(int, char**);
	static void simulationGridInit(int, int, int, int, CLS_MazeGenAlgorithm::algorithms);
	static void simulationAIInit(int, CLS_AI_AntSuperCL::antAItypes);
	static void simulationAddFood(int);
	static void simulatorDestruct(void);
	static void mainLoop();
	static CLS_Screen* getScreen();
	static void display();

	static void rotateDisplay(float left, float up);
	
private:

#ifdef DEBUG_ANT_AI
	static CLS_MovableObject* debugAnt;
#endif


	static CLS_Screen screen;
	static long long lastTimePoint;
	static std::vector<float> timePoints;
	static long itterations;
	static long shortest;
	static long shortestItor;


	static void keyHandler(unsigned char, int, int);
	static void specialKeyHandler(int, int, int);
	static void activeMouseHandler(int, int);
	static void mouseButtonDown(int, int, int, int);

	static long long elapsedTime();
	static bool quit;
	static int argc;
	static char **argv;
	static CLS_Maze *baseGrid;

	//This will contain the mouse position as well as the state on the left button
	//x,y will be the position and z will be the state of the button 0 for up 1 for down.
	static CoOrd3D<int> mousePos;

	//will contain a list of all the movable objects (either all the ants or a flock containing all the ants)
	static std::vector<CLS_MovableObject*> movableObjects; 

	static void restockAnts();

	//static CoreStructures::GUPivotCamera* camera;
};


#endif  //_CLS_SIMULATOR_H
