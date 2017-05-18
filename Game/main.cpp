#include "MyGame.h"
#include <iostream>

int main()
{
	srand(time(0));
	auto app = new MyGame();
	app->run();

	delete app;
	return 0;
}
