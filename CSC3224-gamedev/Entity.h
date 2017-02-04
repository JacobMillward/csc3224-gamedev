#pragma once
#include <vector>
#include "Component.h"
#include "EntityManager.h"

using namespace std;

class Entity
{
public:
	~Entity();
	uint32_t getID() const;
	void addComponent(const Component& c) const;
	void removeComponent(Component& c) const;

private:
	Entity(uint32_t id, EntityManager& entityManager);
	uint32_t id_;
	EntityManager* entityManager_;

	friend class EntityManager;
};
