#pragma once
#include "ISystem.h"
#include "Box2D/Dynamics/b2World.h"
#include "Box2D/Dynamics/b2Body.h"

#define PIXELS_TO_UNITS_SCALE 30.f

class PhysicsSystem : public ISystem
{
public:
	explicit PhysicsSystem(World& w, b2Vec2 gravity);
	void step(const sf::Time& dt) override;

	b2Body* createBody(b2BodyDef& bodydef)
	{
		return physicsWorld_.CreateBody(&bodydef);
	};

	void setContactListener(b2ContactListener* listener);

protected:
	b2World physicsWorld_;
};
