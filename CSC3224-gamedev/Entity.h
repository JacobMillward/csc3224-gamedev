#pragma once
#include <cstdint>
#include "Components/IComponent.h"
#include "Components/Sprite.h"

#define MAX_ENTITIES 1024

class PhysicsSystem;
class EntityManager;

class Entity
{
public:
	~Entity();
	uint32_t getID() const;
	void addComponent(Component& c);
	void removeComponent(Component& c);
	Sprite* getSprite() const;
	template <typename T>
	T* getComponent();
	static Entity* buildFromJson(EntityManager& entityManager, PhysicsSystem& physicsSystem, Json::Value root);

	bool operator==(const Entity& other) const;
private:
	friend class EntityManager;
	Entity(uint32_t id, EntityManager& entityManager, Sprite& sprite);
	uint32_t id_;
	EntityManager* entityManager_;
	Sprite* sprite_;

	friend class EntityManager;
	bool isDeleted = false;
};

template <typename T>
T* Entity::getComponent()
{
	return entityManager_->getComponent<T>(this);
}
