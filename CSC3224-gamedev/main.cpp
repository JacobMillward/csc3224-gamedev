#include "Game.h"
#include <iostream>

using namespace std;

int main()
{
	Game* app = new Game();
	app->run();
	delete app;
}
