#include "Game.h"
#include <iostream>

using namespace std;

int main()
{
	Game* app = new Game();

	bool loop = true;
	while (loop)
	{
		switch (app->getState())
		{
		case Game::Init:
			cout << "Game Initialising\n";
			app->init();
			app->changeState(Game::State::Running);
			cout << "Game Initialisation Complete\n";
			break;

		case Game::Running:
			app->processInput();
			app->update();
			break;

		case Game::Shutdown:
			delete app;
			loop = false;
			break;

		default:
			throw "Erroroneous Game State";
		}
	}
}
