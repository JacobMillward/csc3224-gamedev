#include "PhysicsSystem.h"
#include "../World.h"
#include "../Components/RigidBody.h"

PhysicsSystem::PhysicsSystem(World& w, b2Vec2 gravity) : ISystem(w), physicsWorld_(gravity)
{
}

void PhysicsSystem::step(const sf::Time& dt)
{
	physicsWorld_.Step(dt.asSeconds(), 8, 3);

	auto list = world_->getEntityManager().getComponentList(IComponent::Type::RIGIDBODY);
	for (auto pair : *list)
	{
		auto transform = pair.second->getTransform();
		auto body = static_cast<RigidBody*>(pair.first)->getBody();

		transform->setPosition(body->GetPosition().x * PIXELS_TO_UNITS_SCALE, body->GetPosition().y * PIXELS_TO_UNITS_SCALE);
		transform->setRotation(body->GetAngle() * 180.f / b2_pi);
	}
}
