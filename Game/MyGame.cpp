#include "MyGame.h"
#include "PlayerControlSystem.h"
#include <iostream>
#include "Components/PhysicsBody.h"
#include <sstream>
#include "Components/SoundEffect.h"
#include "Components/Tag.h"
#include "FileLoader.h"


MyGame::MyGame() : GameBase(new sf::RenderWindow(sf::VideoMode(800, 600), "Woo!"))
{
}


MyGame::~MyGame()
{
}

void MyGame::init()
{
	/* Load intents from file */
	cout << "Loading keymap" << endl;
	intentHandler_.loadIntentsFromFile("KeyMap.txt");
	intentHandler_.printKeyMaps();

	/* Create resources */
	resourceManager_.loadTexture("box", "box.png");
	resourceManager_.loadSound("beeps", "sms-alert-4.wav");

	/* Set up world subsystems */
	this->world_->addSystem(new PlayerControlSystem(*this->world_, intentHandler_));

	/* Load entities from file */
	FileLoader::LoadEntitiesFromFile(world_->getEntityManager(), world_->getPhysicsSystem(), "ExampleLevel.json");
}

void MyGame::update(sf::Time dt)
{
	elapsedTime += dt;
	stringstream ss;
	ss << "FPS: " << 1 / dt.asSeconds();
	if (elapsedTime.asSeconds() > 1)
	{
		window_->setTitle(ss.str());
		elapsedTime = sf::Time::Zero;
	}
}

void MyGame::quit()
{
	cout << "Cleaning up resources" << endl;

	/* World cleans up it's resources automatically, so we don't need to delete any pointers here */
}
