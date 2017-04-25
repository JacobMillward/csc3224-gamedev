#pragma once
#include "IComponent.h"
#include "Box2D/Dynamics/b2Body.h"
#include "../Systems/PhysicsSystem.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "../json/json.h"

class PhysicsBody : public IComponent<PhysicsBody>
{
public:
	static const ComponentType typeID = ComponentType::PHYSICSBODY;
	ComponentType getType() override { return typeID; }
	int getTypeValue() override { return static_cast<int>(typeID); }

	static PhysicsBody* buildFromJson(Json::Value componentRoot);

	explicit PhysicsBody(PhysicsSystem* physicsSystem, Sprite* sprite, b2BodyType bodyType)
	{
		b2BodyDef def;
		def.position = b2Vec2( (sprite->getPosition().x + sprite->getOrigin().x) / PIXELS_TO_UNITS_SCALE, (sprite->getPosition().y + sprite->getOrigin().y) / PIXELS_TO_UNITS_SCALE);
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

	Json::Value toJson() override;

protected:
	b2Body* body_;
};

inline PhysicsBody* PhysicsBody::buildFromJson(Json::Value componentRoot)
{
	//TODO: Implement buildFromJson
	return nullptr;
}

inline Json::Value PhysicsBody::toJson()
{
	throw "Not Yet Implemented";
}
