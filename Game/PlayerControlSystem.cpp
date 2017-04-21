#include "PlayerControlSystem.h"
#include "Components\IComponent.h"
#include "Components\Tag.h"
#include "World.h"
#include <iostream>

PlayerControlSystem::PlayerControlSystem(World & world, IntentHandler & intentHandler) : ISystem(world)
{
	this->intentHandler = &intentHandler;
	intentHandler.addObserver(this);
}

PlayerControlSystem::~PlayerControlSystem()
{
	this->intentHandler->removeObserver(this);
}

void PlayerControlSystem::step(const sf::Time & dt)
{
	auto list = this->world_->getEntityManager().getComponentList(IComponent::Type::TAG);
	/* Scale the movement with deltatime and move the entity */
	//TODO: Limit movement to only the player object!
	//std::cout << '\r' << moveX * dt.asSeconds();
	for (auto pair : *list)
	{
		auto component = static_cast<Tag*>(pair.first);
		if (component->getTag() == "player") {
			pair.second->getTransform()->move(moveX * dt.asSeconds(), moveY * dt.asSeconds());
		}
	}
	moveX = moveY = 0;
}

void PlayerControlSystem::onNotify(IntentEvent intent)
{
	switch (str2int(intent.name.c_str()))
	{
	case str2int("Left"):
		if (intent.isDown) {
			moveX -= moveSpeed;
		}
		break;

	case str2int("Right"):
		if (intent.isDown) {
			moveX += moveSpeed;
		}
		break;

	case str2int("Up"):
		if (intent.isDown) {
			moveY -= moveSpeed;
		}
		break;

	case str2int("Down"):
		if (intent.isDown) {
			moveY += moveSpeed;
		}
		break;

	default:
		break;
	}
}
