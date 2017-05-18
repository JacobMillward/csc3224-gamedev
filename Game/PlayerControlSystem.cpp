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
			float velChange = desiredVel - body->GetLinearVelocity().x;
			float impulse = body->GetMass() * velChange;
			body->ApplyLinearImpulseToCenter(b2Vec2(impulse, 0), true);
			if (jump)
			{
				body->ApplyLinearImpulseToCenter(b2Vec2(0, body->GetMass() * (-jumpVel - body->GetLinearVelocity().y)), true);
				jump = false;
			}
		}
	}
	desiredVel = 0;
}

void PlayerControlSystem::onNotify(IntentEvent intent)
{
	if (intent.state == State::PRESSED || intent.state == State::DOWN)
	{
		switch (str2int(intent.name.c_str()))
		{
		case str2int("Left"):
			{
				desiredVel -= moveVel;
				break;
			}

		case str2int("Right"):
			{
				desiredVel += moveVel;
				break;
			}
		default:
			break;
		}
	}

	//Play sound
	if (intent.name == "Jump" && intent.state == State::PRESSED)
	{
		jump = true;
	}
}
