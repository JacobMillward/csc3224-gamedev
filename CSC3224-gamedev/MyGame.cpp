#include "MyGame.h"
#include <iostream>


MyGame::MyGame()
{
}


MyGame::~MyGame()
{
	/* Destroy world (Mwahaha) */
}

void MyGame::init()
{
	/* Set up world */
	//TODO: Load world setup from file
	this->world_ = World();

	/* Set up world subsystems */
	//TODO: Add subsystems
}

void MyGame::run()
{
	bool loop = true;
	while (loop)
	{
		sf::Time currentTime = gameClock.getElapsedTime();
		sf::Time dt = currentTime - lastTime;
		lastTime = currentTime;

		switch (world_.getState())
		{
		case World::State::Init:
			//Game init
			cout << "Game Initialising\n";
			init();
			world_.changeState(World::State::Running);
			cout << "Game Initialisation Complete\n";
			break;

		case World::State::Running:
			//Main loop
			world_.step(dt);
			break;

		case World::State::Quitting:
			//Cleanup
			world_.changeState(World::State::Shutdown);
			break;

		case World::State::Shutdown:
			//Final game cleanup and window shutdown
			loop = false;
			break;

		default:
			throw "Erroroneous Game State";
		}
	}
}

void MyGame::shutdown()
{
	cout << "Shutting down" << endl;
}
