#include "PlayerControlSystem.h"
#include "Components/IComponent.h"
#include "Components/Tag.h"
#include "World.h"
#include "Components/RigidBody.h"

PlayerControlSystem::PlayerControlSystem(World& world, IntentHandler& intentHandler) : ISystem(world)
{
	this->intentHandler = &intentHandler;
	intentHandler.addObserver(this);
}

PlayerControlSystem::~PlayerControlSystem()
{
	this->intentHandler->removeObserver(this);
}

void PlayerControlSystem::step(const sf::Time& dt)
{
	auto list = this->world_->getEntityManager().getComponentList(IComponent::Type::TAG);
	for (auto pair : *list)
	{
		/* Scale the movement with deltatime and move the entity */

		auto component = static_cast<Tag*>(pair.first);
		if (component->getTag() == "player")
		{
			auto body = pair.second->getComponent<RigidBody>()->getBody();
			body->ApplyLinearImpulseToCenter(b2Vec2(moveX, moveY), true);
		}
	}
	moveX = moveY = 0;
}

void PlayerControlSystem::onNotify(IntentEvent intent)
{
	switch (str2int(intent.name.c_str()))
	{
	case str2int("Left"):
		if (intent.isDown)
		{
			moveX -= moveForce;
		}
		break;

	case str2int("Right"):
		if (intent.isDown)
		{
			moveX += moveForce;
		}
		break;

	case str2int("Up"):
		if (intent.isDown)
		{
			moveY -= moveForce;
		}
		break;

	case str2int("Down"):
		if (intent.isDown)
		{
			moveY += moveForce;
		}
		break;

	default:
		break;
	}
}
