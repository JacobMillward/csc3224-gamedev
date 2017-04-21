#include "MyGame.h"
#include "Systems\RenderableBuildSystem.h"
#include "Components\Sprite.h"
#include "Components\Tag.h"
#include "PlayerControlSystem.h"
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
	/* Load intents from file */
	std::cout << "Loading keymap" << std::endl;
	intentHandler_.loadIntentsFromFile("KeyMap.txt");
	intentHandler_.printKeyMaps();

	/* Create objects */
	sf::IntRect rect(0, 0, 600, 600);
	playerTexture.loadFromFile("player.png");
	Sprite* playerSprite = new Sprite(playerTexture, rect);
	wheel = this->world_->getEntityManager().createEntity();
	wheel->addComponent(*playerSprite);
	wheel->addComponent(*(new Tag("player")));
	auto transform = wheel->getTransform();
	transform->move(300, 300);
	transform->setOrigin(300, 300);
	transform->setScale(0.5, 0.5);


	/* Set up world subsystems */
	this->world_->addSystem(new PlayerControlSystem(*this->world_, intentHandler_));
	this->world_->addSystem(new RenderableBuildSystem(*this->world_));
}

void MyGame::run()
{
	sf::Time dt;
	sf::Time totalTime;
	int frameCount = 0;
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
			intentHandler_.processIntents();
			dt = gameClock_.restart();
			++frameCount;
			totalTime += dt;
			if (totalTime.asSeconds() > 1) {
				std::cout << "\r\t\t\r" << frameCount / totalTime.asSeconds() << " FPS";
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
