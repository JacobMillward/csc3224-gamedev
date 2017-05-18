#include "PlayerControlSystem.h"
#include "Components/IComponent.h"
#include "Components/Tag.h"
#include "World.h"
#include "Components/PhysicsBody.h"
#include "Components/SoundEffect.h"
#include "Box2D/Dynamics/Contacts/b2Contact.h"
#include "ScoreSystem.h"

PlayerControlSystem::PlayerControlSystem(World& world, IntentHandler& intentHandler) : ISystem(world), IntentObserver(intentHandler), playerEntity(nullptr)
{
	world.getPhysicsSystem().setContactListener(this);
}

void PlayerControlSystem::step(const sf::Time& dt)
{
	/* Grab a reference to the player */
	if (!playerEntity)
	{
		auto list = this->world_->getEntityManager().getComponentList(ComponentType::TAG);
		for (auto pair : *list)
		{
			auto component = static_cast<Tag*>(pair.first);
			if (component->getTag() == "player")
			{
				playerEntity = pair.second;
				playerPhysics = playerEntity->getComponent<PhysicsBody>();
				playerPhysics->getBody()->SetGravityScale(1.5f);
				break;
			}
		}
	}
	else if (playerEntity->getComponent<Tag>()->getTag() == "dead") return;

	/* Move the player */
	auto body = playerEntity->getComponent<PhysicsBody>()->getBody();
	float velChange = desiredVel - body->GetLinearVelocity().x;
	float impulse = body->GetMass() * velChange;
	body->ApplyLinearImpulseToCenter(b2Vec2(impulse, 0), true);

	if (jump)
	{
		body->ApplyLinearImpulseToCenter(b2Vec2(0, -(body->GetMass() * (jumpVel - body->GetLinearVelocity().y))), true);
		jump = false;
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

	//Jump
	if (intent.name == "Jump" && intent.state == State::PRESSED && grounded)
	{
		jump = true;
	}
}

void PlayerControlSystem::BeginContact(b2Contact* contact)
{
	//check if either fixture was the player
	auto fixA = contact->GetFixtureA();
	auto fixB = contact->GetFixtureB();
	void* bodyAUserData = fixA->GetBody()->GetUserData();
	void* bodyBUserData = fixB->GetBody()->GetUserData();
	if (bodyAUserData && bodyBUserData)
	{
		
		auto udA = static_cast<PhysicsBody*>(bodyAUserData);
		auto udB = static_cast<PhysicsBody*>(bodyBUserData);
		if (udA == playerPhysics || udB == playerPhysics)
		{
			grounded = true;
		}
	}
}

void PlayerControlSystem::EndContact(b2Contact* contact)
{
	//check if either fixture was the player
	auto fixA = contact->GetFixtureA();
	auto fixB = contact->GetFixtureB();
	void* bodyAUserData = fixA->GetBody()->GetUserData();
	void* bodyBUserData = fixB->GetBody()->GetUserData();
	if (bodyAUserData && bodyBUserData)
	{
		auto udA = static_cast<PhysicsBody*>(bodyAUserData);
		auto udB = static_cast<PhysicsBody*>(bodyBUserData);
		if (udA == playerPhysics || udB == playerPhysics)
		{
			grounded = false;
		}
	}
}

void PlayerControlSystem::recieveMessage(const SystemMessage& m)
{

}
