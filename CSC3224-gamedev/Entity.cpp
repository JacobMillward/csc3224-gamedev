#include "Entity.h"
#include "EntityManager.h"
#include "Components/SoundEffect.h"
#include "Components/PhysicsBody.h"
#include "Components/Tag.h"
#include <iostream>

Entity::Entity(uint32_t id, EntityManager& entityManager, Sprite& pos)
{
	id_ = id;
	entityManager_ = &entityManager;
	sprite_ = &pos;
}

Entity::~Entity()
{
	if (!isDeleted)
	{
		entityManager_->destroyEntity(this);
	}
}

uint32_t Entity::getID() const
{
	return id_;
}

void Entity::addComponent(Component& c)
{
	entityManager_->addComponent(*this, c);
}

void Entity::removeComponent(Component& c)
{
	entityManager_->removeComponent(*this, c);
}

Sprite* Entity::getSprite() const
{
	return sprite_;
}

Entity* Entity::buildFromJson(EntityManager& entityManager, PhysicsSystem& physicsSystem, Json::Value root)
{
	auto entity = entityManager.createEntity(Sprite::buildFromJson(root["Sprite"]));
	//Loop though components
	for (auto jsonComponent : root["Components"])
	{
		auto type = jsonComponent.get("ComType", -1).asInt();
		if (type < 0)
		{
			cout << "Invalid component type" << endl;
			break;
		}
		auto comType = static_cast<ComponentType>(type);

		//Build component based on type
		Component* component = nullptr;
		switch (comType)
		{
		case ComponentType::TAG:
		{
			component = Tag::buildFromJson(jsonComponent);
			break;
		}
		case ComponentType::PHYSICSBODY:
		{
			component = PhysicsBody::buildFromJson(jsonComponent, &physicsSystem, entity->getSprite());
			break;
		}
		case ComponentType::AUDIO:
		{
			component = SoundEffect::buildFromJson(jsonComponent);
			break;
		}

		//We must have a sprite, so don't bother creating additional ones (undefined behaviour)
		case ComponentType::SPRITE: break;
		case ComponentType::TYPE_END:
		default:;
		}
		if (component)
		{
			entity->addComponent(*component);
		}
	}
	return entity;
}

bool Entity::operator==(const Entity& other) const
{
	return this->id_ == other.getID();
}
