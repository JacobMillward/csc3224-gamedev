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

	explicit PhysicsBody(PhysicsSystem* physicsSystem, Sprite* sprite, b2BodyType bodyType) : fixtureSizes()
	{
		b2BodyDef def;
		def.position = b2Vec2( (sprite->getPosition().x + sprite->getOrigin().x) / PIXELS_TO_UNITS_SCALE, (sprite->getPosition().y + sprite->getOrigin().y) / PIXELS_TO_UNITS_SCALE);
		def.type = bodyType;
		body_ = physicsSystem->createBody(def);
		body_->SetUserData(this);
	};

	b2Body* getBody() const { return body_; }

	void addBoxCollider(b2FixtureDef& fixturedef, float width, float height)
	{
		b2PolygonShape shape;
		shape.SetAsBox((width / 2) / PIXELS_TO_UNITS_SCALE, (height / 2) / PIXELS_TO_UNITS_SCALE);
		fixturedef.shape = &shape;
		body_->CreateFixture(&fixturedef);

		fixtureSizes.push_back(eastl::make_pair(width, height));
	}
	
	Json::Value toJson() override;

protected:
	b2Body* body_;
	eastl::vector<eastl::pair<float, float>> fixtureSizes;
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
	b2BodyType type = b2BodyType(componentRoot.get("BodyType", 2).asInt());
	auto b = new PhysicsBody(p, s, type);
	b->getBody()->SetFixedRotation(componentRoot.get("FixedRotation", false).asBool());

	auto fixtures = componentRoot.get("Fixtures", "");
	for(auto f : fixtures)
	{
		b2FixtureDef def;
		def.density = f.get("Density", 1).asFloat();
		def.friction = f.get("Friction", 0.5).asFloat();
		def.restitution = f.get("Restitution", 0.0).asFloat();
		auto width = f.get("Width", 1).asFloat();
		auto height = f.get("Height", 1).asFloat();

		b->addBoxCollider(def, width, height);
	}
	return b;
}

inline Json::Value PhysicsBody::toJson()
{
	Json::Value root;
	root["ComType"] = static_cast<int>(this->getType());
	root["BodyType"] = body_->GetType();
	root["FixedRotation"] = body_->IsFixedRotation();

	auto index = 0;
	for (b2Fixture* f = body_->GetFixtureList(); f; f = f->GetNext())
	{
		Json::Value data;
		data["Density"] = f->GetDensity();
		data["Friction"] = f->GetFriction();
		data["Restitution"] = f->GetRestitution();
		data["Width"] = fixtureSizes.at(index).first;
		data["Height"] = fixtureSizes.at(index).second;

		root["Fixtures"].append(data);

		++index;
	}

	return root;
}
