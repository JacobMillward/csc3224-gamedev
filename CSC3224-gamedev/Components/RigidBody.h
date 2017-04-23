#pragma once
#include "IComponent.h"
#include "Box2D/Dynamics/b2Body.h"
#include "../Systems/PhysicsSystem.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Fixture.h"

class RigidBody : public IComponent<RigidBody>
{
public:
	static const ComponentType typeID = ComponentType::RIGIDBODY;
	ComponentType getType() override { return typeID; }
	int getTypeValue() override { return static_cast<int>(typeID); }

	static RigidBody* buildFromJson(std::string jsonString);

	explicit RigidBody(PhysicsSystem* physicsSystem, float X = 0.f, float Y = 0.f)
	{
		b2BodyDef def;
		def.position = b2Vec2(X / PIXELS_TO_UNITS_SCALE, Y / PIXELS_TO_UNITS_SCALE);
		def.type = b2_dynamicBody;
		body_ = physicsSystem->createBody(def);
	};

	b2Body* getBody() const { return body_; }

	void addBoxCollider(b2FixtureDef& fixturedef, float width, float height) const
	{
		b2PolygonShape shape;
		shape.SetAsBox((width / 2) / PIXELS_TO_UNITS_SCALE, (height / 2) / PIXELS_TO_UNITS_SCALE);
		fixturedef.shape = &shape;
		body_->CreateFixture(&fixturedef);
	}

protected:
	b2Body* body_;
};

inline RigidBody* RigidBody::buildFromJson(std::string jsonString)
{
	//TODO: Implement buildFromJson
	return nullptr;
}
