#include "GameBase.h"
#include "World.h"
#include <iostream>

GameBase::GameBase(sf::RenderWindow* window): gameClock_(sf::Clock()), window_(window), intentHandler_(), textureManager_(), world_()
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
	sf::Time dt;
	sf::Time totalTime;
	auto frameCount = 0;
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
			dt = gameClock_.restart();
			++frameCount;
			totalTime += dt;
			if (totalTime.asSeconds() > 1)
			{
				cout << "\r\t\t\r" << frameCount / totalTime.asSeconds() << " FPS";
				totalTime = sf::Time::Zero;
				frameCount = 0;
			}
			world_->step(dt);
			window_->clear(sf::Color::Cyan);
			world_->draw(*window_);
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
