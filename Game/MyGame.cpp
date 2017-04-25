#include "MyGame.h"
#include "Components/Sprite.h"
#include "PlayerControlSystem.h"
#include <iostream>
#include "Components/PhysicsBody.h"
#include <sstream>
#include "Components/SoundEffect.h"


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

	/* Create boxes */
	auto texture = resourceManager_.loadTexture("box", "box.png");

	auto e = world_->getEntityManager().createEntity("box", sf::IntRect(0, 0, 32, 32));
	e->getSprite()->move(60, 0);
	e->getSprite()->setOrigin(16, 16);
	auto r = new PhysicsBody(world_->getPhysicsSystem(), e->getSprite(), b2_dynamicBody);
	b2FixtureDef f;
	f.density = 1.f;
	f.friction = 0.7f;
	r->addBoxCollider(f, 32, 32);
	e->addComponent(*r);

	auto beeps = resourceManager_.loadSound("beeps", "sms-alert-4.wav");
	e->addComponent(*(new SoundEffect("beeps")));
	e->getComponent<SoundEffect>()->play();
	/* Create box 2 */
	auto e2 = world_->getEntityManager().createEntity("box", sf::IntRect(0, 0, 32, 32));
	e2->getSprite()->setOrigin(16, 16);
	e2->getSprite()->setPosition(400, 500);
	e2->getSprite()->setScale(22.f, 1.f);
	r = new PhysicsBody(world_->getPhysicsSystem(), e2->getSprite(), b2_staticBody);
	f.density = 0.0f;
	r->addBoxCollider(f, 704, 32);
	e2->addComponent(*r);

	/* Set up world subsystems */
	this->world_->addSystem(new PlayerControlSystem(*this->world_, intentHandler_));
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
