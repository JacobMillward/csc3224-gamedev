#pragma once
#include "IComponent.h"
#include "Box2D/Dynamics/b2Body.h"
#include "../Systems/PhysicsSystem.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "../json/json.h"
#include <stdarg.h> 

class PhysicsBody : public IComponent<PhysicsBody>
{
public:
	static const ComponentType typeID = ComponentType::PHYSICSBODY;
	ComponentType getType() override { return typeID; }
	int getTypeValue() override { return static_cast<int>(typeID); }

	static PhysicsBody* buildFromJson(Json::Value componentRoot, ...);

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

/* Expects a pointer to a sprite to be passed in, as well as a pointer to the PhysicsSystem.
 * Usage: buildFromJson(componentRoot, PhysicsSystem*, Sprite*)
 */
inline PhysicsBody* PhysicsBody::buildFromJson(Json::Value componentRoot, ...)
{
	va_list vl;
	va_start(vl, componentRoot);
	PhysicsSystem* p = va_arg(vl, PhysicsSystem*);
	Sprite* s = va_arg(vl, Sprite*);
	va_end(vl);

	//TODO: Fix this checking here
	if (p == nullptr) throw "No PhysicsSystem passed in";
	if (s == nullptr) throw "No Sprite passed in";

	// Default to 2 (Dynamic body) on failure
	b2BodyType type = b2BodyType(componentRoot.get("type", 2).asInt());
	auto b = new PhysicsBody(p, s, type);

	//TODO: Add fictures
	return b;
}

inline Json::Value PhysicsBody::toJson()
{
	Json::Value root;
	root["type"] = body_->GetType();

	return root;
}
