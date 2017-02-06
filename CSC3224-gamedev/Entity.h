#pragma once
#include <cstdint>
#include "IComponent.h"

class EntityManager;

class Entity
{
public:
	Entity(uint32_t id, EntityManager& entityManager);
	~Entity();
	uint32_t getID() const;
	void addComponent(IComponent& c) const;
	void removeComponent(IComponent& c) const;

private:
	uint32_t id_;
	EntityManager* entityManager_;
};
