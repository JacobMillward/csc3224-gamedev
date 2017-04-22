#pragma once
#include "IComponent.h"
#include "Box2D/Dynamics/b2Body.h"
#include "../Systems/PhysicsSystem.h"

#define PIXELS_TO_UNITS_SCALE 30.f

class RigidBody : public IComponent
{
public:
	static const Type typeID = Type::RIGIDBODY;
	Type getType() override { return typeID; }
	int getTypeValue() override { return static_cast<int>(typeID); }

	explicit RigidBody(PhysicsSystem* physicsSystem, float X = 0.f, float Y = 0.f)
	{
		b2BodyDef def;
		def.position = b2Vec2(X / PIXELS_TO_UNITS_SCALE, Y / PIXELS_TO_UNITS_SCALE);
		def.type = b2_dynamicBody;
		body_ = physicsSystem->createBody(def);
	};

	b2Body* getBody() const { return body_; }

protected:
	b2Body* body_;
};
