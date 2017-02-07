#pragma once
#include <cstdint>
#include <SFML\System\Vector3.hpp>
#include "IComponent.h"

class EntityManager;

class Entity
{
public:
	Entity(uint32_t id, EntityManager& entityManager, sf::Vector3f& pos);
	~Entity();
	uint32_t getID() const;
	void addComponent(IComponent& c) const;
	void removeComponent(IComponent& c) const;
	sf::Vector3f* getPosition();

private:
	uint32_t id_;
	EntityManager* entityManager_;
	/* Position is inherent to all entities, thus not a seperate component */
	sf::Vector3f *position_;
};
