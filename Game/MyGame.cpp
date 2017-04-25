#include "MyGame.h"
#include "Components/Sprite.h"
#include "PlayerControlSystem.h"
#include <iostream>
#include "Components/PhysicsBody.h"
#include <sstream>


MyGame::MyGame() : GameBase(new sf::RenderWindow(sf::VideoMode(800, 600), "Woo!"))
{
	world_ = new World();
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
	auto texture = textureManager_.loadTexture("box.png", "box.png");

	for (int i = 0; i < 10; ++i)
	{
		auto e = world_->getEntityManager().createEntity();
		e->addComponent(*(new Sprite(*texture, sf::IntRect(0, 0, 32, 32))));
		e->getTransform()->move((i + 1) * 10, 50);
		e->getTransform()->setOrigin(16, 16);
		//e->getTransform()->setScale(0.2, 0.2);
		auto r = new PhysicsBody(world_->getPhysicsSystem(), e->getTransform(), b2_dynamicBody);
		e->addComponent(*r);
		b2FixtureDef f;
		f.density = .1f;
		f.friction = 1.f;
		r->addBoxCollider(f, 16, 16);
	}

	/* Create ground */
	auto ground = world_->getEntityManager().createEntity();
	ground->addComponent(*(new Sprite(*texture, sf::IntRect(0, 0, 32, 32))));
	ground->getTransform()->setScale(1.f, 1.f);
	ground->getTransform()->setOrigin(0, 0);
	ground->getTransform()->setPosition(10, 250);
	auto r = new PhysicsBody(world_->getPhysicsSystem(), ground->getTransform(), b2_staticBody);
	b2FixtureDef f;
	f.density = 0.f;
	r->addBoxCollider(f, 320, 16);

	/* Set up world subsystems */
	this->world_->addSystem(new PlayerControlSystem(*this->world_, intentHandler_));
}

void MyGame::update(sf::Time dt)
{
	elapsedTime += dt;
	std::stringstream ss;
	ss << "FPS: " << 1 / dt.asSeconds();
	if (elapsedTime.asSeconds() > 1)
	{
		window_->setTitle(ss.str());
		elapsedTime = sf::Time::Zero;
	}
}

void MyGame::quit()
{
	std::cout << "Cleaning up resources" << std::endl;
}
