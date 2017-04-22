#include "MyGame.h"
#include <iostream>

/*
 * Depending on the video drivers, the ouput framerate may be limited by the screen refresh rate. There doesn't seem to be anything that can fix this at the moment within SFML.
 */
int main()
{
	auto app = new MyGame();
	app->run();

	delete app;
	return 0;
}
