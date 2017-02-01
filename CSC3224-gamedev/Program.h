#pragma once
#include "SystemManager.h"

class Program
{
private:
	bool isRunning;
public:
	Program();
	~Program();
	
	bool isRunning() { return isRunning; }
	SystemManager * getSystemManager();
	void processInput();
	void update();
};

int main();
