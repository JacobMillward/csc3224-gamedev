#include "PlayerControlSystem.h"
#include "Components/IComponent.h"
#include "Components/Tag.h"
#include "World.h"
#include "Components/PhysicsBody.h"
#include <iostream>
#include "Components/SoundEffect.h"

PlayerControlSystem::PlayerControlSystem(World& world, IntentHandler& intentHandler) : ISystem(world), IntentObserver(intentHandler)
{
}

void PlayerControlSystem::step(const sf::Time& dt)
{
	auto list = this->world_->getEntityManager().getComponentList(ComponentType::TAG);
	for (auto pair : *list)
	{
		/* Scale the movement with deltatime and move the entity */

		auto component = static_cast<Tag*>(pair.first);
		if (component->getTag() == "player")
		{
			auto body = pair.second->getComponent<PhysicsBody>()->getBody();
			body->ApplyForceToCenter(b2Vec2(moveX, moveY), true);
			if (play)
			{
				pair.second->getComponent<SoundEffect>()->play();
				play = false;
			}
		}
	}
	moveX = moveY = 0;
}

void PlayerControlSystem::onNotify(IntentEvent intent)
{
	if (intent.state == State::PRESSED || intent.state == State::DOWN)
	{
		switch (str2int(intent.name.c_str()))
		{
		case str2int("Left"):
			{
				moveX -= moveForce;

				break;
			}

		case str2int("Right"):
			{
				moveX += moveForce;

				break;
			}

		case str2int("Up"):
			{
				moveY -= moveForce;

				break;
			}

		case str2int("Down"):
			{
				moveY += moveForce;

				break;
			}
		default:
			break;
		}
	}

	//Play sound
	if(intent.name == "Jump" && intent.state == State::RELEASED)
	{
		play = true;
	}
}
