#include "MyGame.h"
#include "Systems\RenderableBuildSystem.h"
#include "Components\Sprite.h"
#include <iostream>
#include <SFML\Window\Event.hpp>


MyGame::MyGame() : GameBase(new sf::RenderWindow(sf::VideoMode(800, 600), "Woo!"))
{
	world_ = new World();
}


MyGame::~MyGame()
{
	/* Destroy world (Mwahaha) */
	delete world_;
}

void MyGame::init()
{
	/* Set up world */
	//TODO: Load world setup from file

	sf::IntRect rect(0, 0, 160, 160);
	playerTexture.loadFromFile("player.png");
	Sprite* playerSprite = new Sprite(playerTexture, rect);
	world_->getEntityManager().createEntity()->addComponent(*playerSprite);

	/* Set up world subsystems */
	auto r = new RenderableBuildSystem(*this->world_);
	this->world_->addSystem(*r);
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
			world_->step(gameClock_.getElapsedTime());
			window_->clear(sf::Color::Cyan);
			world_->draw(*window_);
			window_->display();
			break;

		case World::State::Quitting:
			//Cleanup
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

void MyGame::shutdown()
{
	cout << "Shutting down" << endl;
	window_->close();
}
