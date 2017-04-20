#include "MyGame.h"
#include <iostream>

int main()
{
	MyGame* app = new MyGame();
	app->run();

	delete app;
	return 0;
}