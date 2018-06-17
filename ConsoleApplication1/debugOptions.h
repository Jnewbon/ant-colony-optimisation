#pragma once
//Will output Infomation to the console during the Maze Generation Algorithm
//#define DEBUG_MAZE_GEN

//OutPut stats from the Grpahical code to the console
//#define DEBUG_GRAPHICS

//Debug for the ants
//#define DEBUG_ANT_AI
#include <string>


class debug {
public:
	static std::string getErrorCode(int code)
	{
		std::string errors[] = { 
							"An invalid number of ants was given to the AI initilization",		// Error 0
							"Current Location of an ant is set to NULL",						// Error 1
							"There was no ant AI initilized"									// Error 2
		};

		return errors[code];
	}
};