#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem(World& w, b2Vec2 gravity) : ISystem(w), physicsWorld_(gravity)
{
}

void PhysicsSystem::step(const sf::Time& dt)
{
}
