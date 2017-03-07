#include "MyGame.h"

int main()
{
	MyGame* app = new MyGame();
	app->run();
	delete app;

	return 0;
}