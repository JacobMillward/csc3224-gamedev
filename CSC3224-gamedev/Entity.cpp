#include "Entity.h"
#include "EntityManager.h"

Entity::Entity(uint32_t id)
{
	id_ = id;
}

Entity::~Entity()
{
	EntityManager::getInstance()->destroyEntity(id_);
}

unsigned int Entity::getID() const
{
	return id_;
}

void Entity::addComponent(const Component& c) const
{
	EntityManager::getInstance()->addComponent(id_, c);
}

void Entity::removeComponent(Component& c) const
{
	EntityManager::getInstance()->removeComponent(id_, c);
}
