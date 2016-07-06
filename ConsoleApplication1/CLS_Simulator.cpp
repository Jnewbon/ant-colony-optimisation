#include "debugOptions.h"
#include "CLS_Simulator.h"
#include "CLS_Maze.h"
#include "CLS_Factory.h"
#include "CLS_Ant.h"
#include "CLS_Flock.h"
#include "CLS_AI_Rank.h"
#include "CLS_AI_Rank_Food.h"

#include <time.h>
#include <sstream>
#include <fstream>

using namespace std;
//using namespace CoreStructures;

const int SCREEN_X = 800;
const int SCREEN_Y = 800;
CLS_Screen CLS_Simulator::screen;
long long CLS_Simulator::lastTimePoint = 0;
std::vector<float> CLS_Simulator::timePoints;
int CLS_Simulator::argc = 0;
char **CLS_Simulator::argv = NULL;
CLS_Maze* CLS_Simulator::baseGrid = NULL;
CoOrd3D<int> CLS_Simulator::mousePos = CoOrd3D<int>(0,0,0);
//GUPivotCamera *CLS_Simulator::camera = new GUPivotCamera();
vector<CLS_MovableObject*> CLS_Simulator::movableObjects; 
long CLS_Simulator::itterations = 0;
long CLS_Simulator::shortest = -1;
long CLS_Simulator::shortestItor = -1;
bool CLS_Simulator::quit = false;

#ifdef DEBUG_ANT_AI
	CLS_MovableObject* CLS_Simulator::debugAnt = nullptr;
#endif
void CLS_Simulator::simulatorDestruct(void)
{		
	while(!movableObjects.empty()) delete movableObjects.back(), movableObjects.pop_back();
	delete baseGrid;
	delete argv;
}

void CLS_Simulator::simulationInit(int argc, char **argv) {

	glutInit(&argc,argv);

	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	glutInitWindowSize(SCREEN_X,SCREEN_Y);
	glutInitWindowPosition(800,0);
	glutCreateWindow("Computing Individual Project");
	
	//as the display function is a static this call is made very easy.
	glutDisplayFunc(CLS_Simulator::display);
	glutKeyboardFunc(CLS_Simulator::keyHandler);
	glutSpecialFunc(CLS_Simulator::specialKeyHandler);
	glutPassiveMotionFunc(CLS_Simulator::activeMouseHandler);
	glutMotionFunc(CLS_Simulator::activeMouseHandler);
	glutMouseFunc(CLS_Simulator::mouseButtonDown);

	//Initilized glew and output if successful
	GLenum err = glewInit();

#ifdef DEBUG_GRAPHICS
	screen.output("GLEW Setup..");
	if (err == GLEW_OK)
	{	screen.outputNL("SUCCEEDED");	}
	else
	{	screen.outputNL("FAILED");	}
#endif

	glClearColor(0.0,0.0,0.0,1.0);
	glOrtho(-(SCREEN_X/2),(SCREEN_X/2),-(SCREEN_Y/2),(SCREEN_Y/2),-400,400);

#ifdef DEBUG_GRAPHICS

	screen.outputPos(0,5,"SPF:");
	screen.outputPos(0,6,"FPS:");
	screen.outputPos(0,7,"ITR:");
#endif
	
	//bool vSync = wglSwapIntervalEXT(1);
	
	shortest = -1;

}

void CLS_Simulator::mainLoop() {

	
#ifdef DEBUG_GRAPHICS
	lastTimePoint = CLS_Simulator::elapsedTime();
#endif
	ofstream outFile;
	outFile.open("test.txt");
	glRotatef(30.0f,1.0f,1.0f,-1.0f);
	while(glutGetWindow() != 0 && quit == false)
	{
		glutMainLoopEvent();

		//As apprently the window can close between the last line and this line of cdoe, lect check again if the window still exsits
		if(glutGetWindow() != 0)
			glutPostRedisplay();
		else
			break;

		for (unsigned int i = 0; i < movableObjects.size(); i++)
			movableObjects[i]->move();

		baseGrid->applyEvapRule();

		itterations++;

		ostringstream stream;

		long long elapsed = CLS_Simulator::elapsedTime() - lastTimePoint;

		stream.str("");
		//stream << "optimal path is " << baseGrid->shortestPath << " moves long.";
		//screen.outputPos(0,5, stream.str());
		if (itterations % 20 == 0)
		{
			stream.str("");
			stream << "Itorations: " << itterations << "\t" << int(1000.0f / float(elapsed)) * 20 << "p/s    "; 
			lastTimePoint = CLS_Simulator::elapsedTime();
			//screen.outputPos(20,6, stream.str());
		}
		
         
 		if ((shortest == -1 || shortest > CLS_AI_AntSuperCL::shortestPath) && CLS_AI_AntSuperCL::shortestPath > 0)
		{
			shortest = CLS_AI_AntSuperCL::shortestPath;
			shortestItor = itterations;
			stream << "New shortest path: " << shortest << " Found in " << shortestItor << " Iterations";
			screen.outputNL(stream.str());
		}

		stream.str("");
		//stream << "Current shortest path: " << shortest << " Found in " << shortestItor << " Iterations       ";
		//screen.outputPos(0,7, stream.str());
		
		//screen.outputPos(0,8, "");

		if (shortest == baseGrid->shortestPath && baseGrid->shortestPath > 0 && shortest > 0)
		{
			outFile << "Current shortest path: " << shortest << " Found in " << shortestItor << " Iterations\n Test Ended";
			break;
		}
		if (itterations >= 10000)
		{
			cout << "Iteration Limit met." << endl;
			break;
		}
#ifdef DEBUG_GRAPHICS
		timePoints.push_back(float(CLS_Simulator::elapsedTime() - lastTimePoint));

		if (timePoints.size() > 10)
		{

			long long tempTimePoint = 0;

			for(int i = 0; i < (int)timePoints.size(); i++) //mp added (float)
			{
				tempTimePoint += (long long)timePoints[i]; //mp added (long long)
			}

			
			stream << (CLS_Simulator::elapsedTime() - lastTimePoint)/1000.0f;
			//stream << (float(tempTimePoint)/float(timePoints.size()))/1000.0f;

			screen.outputPos(6,5, "             ");
			screen.outputPos(6,5, stream.str());
			
			stream.str("");
			
			stream << 1000.0f/(CLS_Simulator::elapsedTime() - lastTimePoint);
			
			screen.outputPos(6,6, "             ");
			screen.outputPos(6,6, stream.str());
			
			stream.str("");
			stream << itterations;
			
			screen.outputPos(6,7, "             ");
			screen.outputPos(6,7, stream.str());
			
timePoints.clear();
		}
		


		
#endif
#ifdef DEBUG_ANT_AI
			
			for (int i = 0; i < movableObjects.size(); i++)
			{
				stream.str("");

				CLS_Ant* tempAnt = (CLS_Ant*) movableObjects[i];

				stream << *tempAnt;
			
				screen.outputPos(6,8+i, "                                                                                          ");
				screen.outputPos(6,8+i, stream.str());
	
				
			}
#endif		


	}
	
	cout << "Simulation terminated at " << itterations << " Iterations" << endl;

}

void CLS_Simulator::display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA); 
	glEnable(GL_BLEND); 
	CLS_Maze_Cell* current;

	float width, height; //mp changed int to float.  Removed 10+ warnings for mixing the int width and int height with lots of floating point values

	//this is so the grid will fil 90% of the screen
	width = SCREEN_X * 0.5;
	height = SCREEN_Y * 0.5;
	
	//glRotatef(0.4f,0.0f,1.0f,0.0f);

	glPointSize(3.0f);

	for (int z = 0; z < baseGrid->getGridSize()[2]; z++)
	{
		for (int y = 0; y < baseGrid->getGridSize()[1]; y++)
		{
			for (int x = 0; x < baseGrid->getGridSize()[0]; x++)
			{
				//Get the location of the cell to work with and assign it to a temp variable so we dont have ta call so many functions each time
				current = &baseGrid->getGrid()[CLS_Maze::getCellPos(CoOrd3D<int>(x,y,z),baseGrid->getGridSize())];
				float R, G, B, A;
				
					R = 1.0f;
					G = 0.0f;
					B = 0.0f;
					A = 0.75f;

				if (baseGrid->getHomeLoc() == current)
					glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
				else if (current->getFood())
					glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
				else 
					glColor4f(R, G, B, A);

				if (current->getFood())
					glPointSize(3.0f + ((20.0f / 200.0f) * float(current->getFoodAmount())));
				else if (current->getPhero() > 20.0f)
					glPointSize(3.0f + 20.0f);
				else
					glPointSize(3.0f + current->getPhero());

				
				glBegin(GL_POINTS);

				//All the axis are divided by the X axis so the grid will aprear Square rather then elongated.
				glVertex3f(((width / (baseGrid->getGridSize()[0]-1)) * current->getPosistion().x) - (width /2),
						   ((width / (baseGrid->getGridSize()[0]-1)) * current->getPosistion().y) - (width /2),
						   ((width / (baseGrid->getGridSize()[0]-1)) * current->getPosistion().z) - (width /2));

				glEnd();

				R = 1.0f;
				G = 1.0f;
				B = 1.0f;
				A = 0.75f;
				glBegin(GL_LINES);
				glColor4f(R, G, B, A);
				//3 if staments that will check the Right Top and Back of each cell as it loops through. This will draw
				if(current->getLink(CLS_Maze_Cell::RIGHT) != NULL)
				{
				
					glVertex3f(((width / (baseGrid->getGridSize()[0]-1)) * current->getPosistion().x) - (width /2),
								((width / (baseGrid->getGridSize()[0]-1)) * current->getPosistion().y) - (width /2),
								((width / (baseGrid->getGridSize()[0]-1)) * current->getPosistion().z)- (width /2));

					glVertex3f(((width / (baseGrid->getGridSize()[0]-1)) * current->getLink(CLS_Maze_Cell::RIGHT)->getPosistion().x) - (width /2),
								((width / (baseGrid->getGridSize()[0]-1)) * current->getLink(CLS_Maze_Cell::RIGHT)->getPosistion().y) - (width /2),
								((width / (baseGrid->getGridSize()[0]-1)) * current->getLink(CLS_Maze_Cell::RIGHT)->getPosistion().z)- (width /2));
				}
				if(current->getLink(CLS_Maze_Cell::TOP) != NULL)
				{
				
					glVertex3f(((width / (baseGrid->getGridSize()[0]-1)) * current->getPosistion().x) - (width /2),
								((width / (baseGrid->getGridSize()[0]-1)) * current->getPosistion().y) - (width /2),
								((width / (baseGrid->getGridSize()[0]-1)) * current->getPosistion().z)- (width /2));

					glVertex3f(((width / (baseGrid->getGridSize()[0]-1)) * current->getLink(CLS_Maze_Cell::TOP)->getPosistion().x) - (width /2),
								((width / (baseGrid->getGridSize()[0]-1)) * current->getLink(CLS_Maze_Cell::TOP)->getPosistion().y) - (width /2),
								((width / (baseGrid->getGridSize()[0]-1)) * current->getLink(CLS_Maze_Cell::TOP)->getPosistion().z)- (width /2));
				}
				if(current->getLink(CLS_Maze_Cell::BACK) != NULL)
				{
					
					glVertex3f(((width / (baseGrid->getGridSize()[0]-1)) * current->getPosistion().x) - (width /2),
								((width / (baseGrid->getGridSize()[0]-1)) * current->getPosistion().y) - (width /2),
								((width / (baseGrid->getGridSize()[0]-1)) * current->getPosistion().z)- (width /2));

					glVertex3f(((width / (baseGrid->getGridSize()[0]-1)) * current->getLink(CLS_Maze_Cell::BACK)->getPosistion().x) - (width /2),
								((width / (baseGrid->getGridSize()[0]-1)) * current->getLink(CLS_Maze_Cell::BACK)->getPosistion().y) - (width /2),
								((width / (baseGrid->getGridSize()[0]-1)) * current->getLink(CLS_Maze_Cell::BACK)->getPosistion().z)- (width /2));
				}
				
				glEnd();

			}
		}
	}

	for (unsigned int i = 0 ; i < movableObjects.size(); i++)
	{
		movableObjects[i]->draw(width,baseGrid->getGridSize()[0]-1);
	}

	glutSwapBuffers();
}

void CLS_Simulator::keyHandler(unsigned char key, int x, int y)
{
	if (key == 27)
		quit = true;
}

void CLS_Simulator::specialKeyHandler(int key , int x, int y)
{
	if (key == VK_ESCAPE)
		quit = true;
}

void CLS_Simulator::activeMouseHandler(int x, int y)
{
	if (CLS_Simulator::mousePos.z == 1) {

		int dx = x - CLS_Simulator::mousePos.x;
		int dy = y - CLS_Simulator::mousePos.y;

		
		glRotatef(1.0f,float(dx),float(dy),0.0f);

	}
}

void CLS_Simulator::mouseButtonDown(int button_id, int state, int x, int y)
{
	if (button_id==GLUT_LEFT_BUTTON) {
		
		if (state==GLUT_DOWN) {

			CLS_Simulator::mousePos.x = x;
			CLS_Simulator::mousePos.y = y;

			CLS_Simulator::mousePos.z = 1;

		} else if (state == GLUT_UP) {
			
			CLS_Simulator::mousePos.z = 0;
		}
	}
}

long long CLS_Simulator::elapsedTime() {
	static LARGE_INTEGER s_frequency;
    static BOOL s_use_qpc = QueryPerformanceFrequency(&s_frequency);
    if (s_use_qpc) {
        LARGE_INTEGER now;
        QueryPerformanceCounter(&now);
        return (1000LL * now.QuadPart) / s_frequency.QuadPart;
    } else {
        return GetTickCount();
    }
}

CLS_Screen* CLS_Simulator::getScreen()
{
	return &screen;
}

void CLS_Simulator::simulationGridInit(int x, int y, int z, int seed, CLS_MazeGenAlgorithm::algorithms mazeGen)
{
	baseGrid = new CLS_Maze(x, y, z, seed, mazeGen);

	//Call the function to populate and generate the maze
	baseGrid->start();

}

void CLS_Simulator::simulationAIInit(int numOfAnts, CLS_AI_AntSuperCL::antAItypes aiType)
{
	
	if (aiType == CLS_AI_AntSuperCL::RANK)
		baseGrid->pheroEvapRule = CLS_AI_Rank::pheroEvapRule;
	if (aiType == CLS_AI_AntSuperCL::RANK_FOOD)
		baseGrid->pheroEvapRule = CLS_AI_Rank_Food::pheroEvapRule;


	if (numOfAnts >=1 && numOfAnts <= 10)
	{	for (int i = 0; i < numOfAnts; i++)
		{

			CLS_MovableObject* antTemp = CLS_Factory::createObj(CLS_MovableObject::ANT);
			((CLS_Ant*)antTemp)->setAI(aiType);
			((CLS_Ant*)antTemp)->setHome(baseGrid->getHomeLoc());
			movableObjects.push_back(antTemp);
		}
	}
	else if(numOfAnts <= 0)
		throw 0;
	else
	{
		CLS_MovableObject* flockTemp = CLS_Factory::createObj(CLS_MovableObject::FLOCK);
		for (int i = 0; i < numOfAnts; i++)
		{

			CLS_MovableObject* antTemp = CLS_Factory::createObj(CLS_MovableObject::ANT);
			((CLS_Ant*)antTemp)->setAI(aiType);
			((CLS_Ant*)antTemp)->setHome(baseGrid->getHomeLoc());
			((CLS_Flock*)flockTemp)->addObject(antTemp);

#ifdef DEBUG_ANT_AI
			if ( i == 0 )
				debugAnt = antTemp;
#endif
		}
		movableObjects.push_back(flockTemp);

	}

}

void CLS_Simulator::simulationAddFood(int number)
{

	baseGrid->setFood(CoOrd3D<int>(baseGrid->getGridSize()[0]-1,baseGrid->getGridSize()[1]-1,baseGrid->getGridSize()[2]-1));

	for (int i = 1; i <= number - 1; i++)
	{
		int x, y, z;
		if (baseGrid->getGridSize()[0] == 1)
			x = 0;
		else
			x = (rand() % (baseGrid->getGridSize()[0] / 2)) + (baseGrid->getGridSize()[0] / 2);	
		if (baseGrid->getGridSize()[1] == 1)
			y = 0;
		else
			y = (rand() % (baseGrid->getGridSize()[1] / 2)) + (baseGrid->getGridSize()[1] / 2);
		if (baseGrid->getGridSize()[2] == 1)
			z = 0;
		else
			z = (rand() % (baseGrid->getGridSize()[2] / 2)) + (baseGrid->getGridSize()[2] / 2);
		
		baseGrid->setFood(CoOrd3D<int>(x,y,z));

	}

}

