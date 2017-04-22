#include "MyGame.h"
#include "Components/Sprite.h"
#include "Components/Tag.h"
#include "PlayerControlSystem.h"
#include <iostream>
#include <SFML/Window/Event.hpp>
#include "Components/RigidBody.h"


MyGame::MyGame() : GameBase(new sf::RenderWindow(sf::VideoMode(800, 600), "Woo!"))
{
	world_ = new World();
	wheel = this->world_->getEntityManager().createEntity();
}


MyGame::~MyGame()
{
	/* Destroy world (Mwahaha) */
	delete world_;
}

void MyGame::init()
{
	/* Load intents from file */
	cout << "Loading keymap" << endl;
	intentHandler_.loadIntentsFromFile("KeyMap.txt");
	intentHandler_.printKeyMaps();

	/* Create object */
	playerTexture.loadFromFile("player.png");
	wheel->addComponent(*(new Sprite(playerTexture, sf::IntRect(0, 0, 600, 600))));
	wheel->addComponent(*(new Tag("player")));
	auto transform = wheel->getTransform();
	transform->setOrigin(300, 300);
	transform->setScale(0.5, 0.5);
	auto rigidbody = new RigidBody(world_->getPhysicsSystem(), transform->getPosition().x, transform->getPosition().y);
	wheel->addComponent(*rigidbody);
	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.f;
	fixtureDef.friction = 0.7f;
	rigidbody->addBoxCollider(fixtureDef, 150, 150);

	/* Set up world subsystems */
	this->world_->addSystem(new PlayerControlSystem(*this->world_, intentHandler_));
}

void MyGame::run()
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
