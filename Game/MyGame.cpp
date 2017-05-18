#include "MyGame.h"
#include "PlayerControlSystem.h"
#include <iostream>
#include "Components/PhysicsBody.h"
#include <sstream>
#include "Components/SoundEffect.h"
#include "Components/Tag.h"
#include "FileLoader.h"
#include "ScoreSystem.h"
#include "MovingCameraSystem.h"


MyGame::MyGame() : GameBase(new sf::RenderWindow(sf::VideoMode(800, 600), "Woo!"))
{
}


MyGame::~MyGame()
{
}

void MyGame::init()
{

	window_->setFramerateLimit(60);
	/* Load intents from file */
	cout << "Loading keymap" << endl;
	intentHandler_.loadIntentsFromFile("KeyMap.txt");
	intentHandler_.printKeyMaps();

	/* Read in platform config */
	auto platformConfig = FileLoader::ReadFileToJsonValue("platform.json");

	/* Load other entities from file */
	FileLoader::LoadGameAssetsFromFile(world_->getEntityManager(), world_->getPhysicsSystem(), resourceManager_, "ExampleLevel.json");

	/* Set up world subsystems */
	this->world_->addSystem(new PlayerControlSystem(*this->world_, intentHandler_));
	this->world_->addSystem(new ScoreSystem(*this->world_));
	this->world_->addSystem(new MovingCameraSystem(*this->world_, window_, platformConfig));

	
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
}
