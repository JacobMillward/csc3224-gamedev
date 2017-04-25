#include "PhysicsSystem.h"
#include "../World.h"
#include "../Components/PhysicsBody.h"

PhysicsSystem::PhysicsSystem(World& w, b2Vec2 gravity) : ISystem(w), physicsWorld_(gravity)
{
}

void PhysicsSystem::step(const sf::Time& dt)
{
	physicsWorld_.Step(dt.asSeconds(), 8, 3);

	auto list = world_->getEntityManager().getComponentList(ComponentType::PHYSICSBODY);
	for (auto pair : *list)
	{
		auto body = static_cast<PhysicsBody*>(pair.first)->getBody();

		auto sprite = pair.second->getSprite();
		sprite->setPosition(body->GetPosition().x * PIXELS_TO_UNITS_SCALE, body->GetPosition().y * PIXELS_TO_UNITS_SCALE);
		sprite->setRotation((180.f / b2_pi) * body->GetAngle());
	}
}
