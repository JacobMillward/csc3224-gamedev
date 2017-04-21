#include "MyGame.h"
#include <iostream>

int main()
{
	auto app = new MyGame();
	app->run();

	delete app;
	return 0;
}
