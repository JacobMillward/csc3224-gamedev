#pragma once
#include "ISystem.h"
#include "Box2D/Dynamics/b2World.h"

class PhysicsSystem : public ISystem
{
public:
	explicit PhysicsSystem(World& w, b2Vec2 gravity);
	void step(const sf::Time& dt) override;

protected:
	b2World physicsWorld_;
};
