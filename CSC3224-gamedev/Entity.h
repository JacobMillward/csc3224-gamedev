#pragma once
#include <cstdint>
#include <SFML/System/Vector3.hpp>
#include "Components/IComponent.h"
#include "Components/Transform.h"

#define MAX_ENTITIES 1024

class EntityManager;

class Entity
{
public:
	Entity(uint32_t id, EntityManager& entityManager, Transform& pos);
	~Entity();
	uint32_t getID() const;
	void addComponent(IComponent& c);
	void removeComponent(IComponent& c);
	Transform* getTransform() const;

	bool operator==(const Entity& other) const;
private:
	uint32_t id_;
	EntityManager* entityManager_;
	Transform* transform_;

	friend class EntityManager;
	bool isDeleted = false;
};
