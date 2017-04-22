#include "MyGame.h"
#include "Components/Sprite.h"
#include "Components/Tag.h"
#include "PlayerControlSystem.h"
#include "Components/RigidBody.h"
#include <iostream>


MyGame::MyGame() : GameBase(new sf::RenderWindow(sf::VideoMode(800, 600), "Woo!"))
{
	world_ = new World();
	wheel = this->world_->getEntityManager().createEntity();
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

	/* Create object */
	auto texture = textureManager_.loadTexture("wheel", "player.png");

	wheel->addComponent(*(new Sprite(*texture, sf::IntRect(0, 0, 600, 600))));
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

void MyGame::quit()
{
}
