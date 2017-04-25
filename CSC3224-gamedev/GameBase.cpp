#include "GameBase.h"
#include "World.h"
#include <iostream>

GameBase::GameBase(sf::RenderWindow* window): gameClock_(sf::Clock()), window_(window), intentHandler_(), resourceManager_(), world_(new World(resourceManager_))
{
}

GameBase::~GameBase()
{
	delete window_;

	/* Destroy world (Mwahaha) */
	delete world_;
}

void GameBase::run()
{
	auto loop = true;
	while (loop)
	{
		// Deal with window events
		sf::Event event;
		while (window_->pollEvent(event))
		{
			// "close requested" event: Change the world state to quitting
			if (event.type == sf::Event::Closed)
				world_->changeState(World::State::Quitting);
		}

		auto dt = gameClock_.restart();

		// Move the world state machine forward
		switch (world_->getState())
		{
		case World::State::Init:
			//Game init
			cout << "Game Initialising\n";
			init();
			world_->changeState(World::State::Running);
			cout << "Game Initialisation Complete\n";
			break;

		case World::State::Running:
			//Main loop
			intentHandler_.processIntents();
			update(dt);
			world_->step(dt);
			window_->clear(sf::Color::Cyan);
			world_->draw(*window_, resourceManager_);
			window_->display();
			break;

		case World::State::Quitting:
			//Cleanup
			quit();
			world_->changeState(World::State::Shutdown);
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

void GameBase::shutdown() const
{
	cout << "Shutting down" << endl;
	window_->close();
}
