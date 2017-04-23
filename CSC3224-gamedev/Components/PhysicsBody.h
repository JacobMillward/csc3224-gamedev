#pragma once
#include "IComponent.h"
#include "Box2D/Dynamics/b2Body.h"
#include "../Systems/PhysicsSystem.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Fixture.h"

class PhysicsBody : public IComponent<PhysicsBody>
{
public:
	static const ComponentType typeID = ComponentType::PHYSICSBODY;
	ComponentType getType() override { return typeID; }
	int getTypeValue() override { return static_cast<int>(typeID); }

	static PhysicsBody* buildFromJson(string jsonString);

	explicit PhysicsBody(PhysicsSystem* physicsSystem, Transform* transform, b2BodyType bodyType)
	{
		b2BodyDef def;
		def.position = b2Vec2( (transform->getPosition().x + transform->getOrigin().x) / PIXELS_TO_UNITS_SCALE, (transform->getPosition().y + transform->getOrigin().y) / PIXELS_TO_UNITS_SCALE);
		def.type = bodyType;
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

	string toJson() override;

protected:
	b2Body* body_;
};

inline PhysicsBody* PhysicsBody::buildFromJson(string jsonString)
{
	//TODO: Implement buildFromJson
	return nullptr;
}

inline string PhysicsBody::toJson()
{
	return {};
}
