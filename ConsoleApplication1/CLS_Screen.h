#pragma once

#include <string>

#include "CLS_ConsoleInterface.h"
class CLS_Screen
{
public:
	CLS_Screen(void);
	~CLS_Screen(void);

	void output(std::string);
	void outputNL(std::string);
	void outputPos(int, int, std::string);

	CLS_ConsoleInterface* getConsole();

private:

	CLS_ConsoleInterface console;

};

