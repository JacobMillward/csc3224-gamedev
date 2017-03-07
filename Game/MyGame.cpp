#include "MyGame.h"
#include <iostream>


MyGame::MyGame() : world_(World()), GameBase(new sf::Window(sf::VideoMode(800, 600), "My Game"))
{
}


MyGame::~MyGame()
{
	/* Destroy world (Mwahaha) */
	//TODO: Construct world destroying function
}

void MyGame::init()
{
	/* Set up world */
	//TODO: Load world setup from file

	auto e = this->world_.getEntityManager().createEntity();
	auto e2 = this->world_.getEntityManager().createEntity();
	this->world_.getEntityManager().destroyEntity(e);
	this->world_.getEntityManager().destroyEntity(e2);
	/* Set up world subsystems */
	//TODO: Add subsystems
}

void MyGame::run()
{
	bool loop = true;
	while (loop)
	{
		// Deal with window events
		sf::Event event;
		while (window_->pollEvent(event))
		{
			// "close requested" event: Change the world state to quitting
			if (event.type == sf::Event::Closed)
				world_.changeState(World::State::Quitting);
		}

		// Move the world state machine forward
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
			world_.step(gameClock_.getElapsedTime());
			break;

		case World::State::Quitting:
			//Cleanup
			world_.changeState(World::State::Shutdown);
			break;

		case World::State::Shutdown:
			//Final game cleanup and window shutdown
			shutdown();
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
	window_->close();
}
