#include "Entity.h"

Entity::Entity(uint32_t id, EntityManager& entityManager) : id_(id), entityManager_(&entityManager)
{
}

Entity::~Entity()
{
	entityManager_->destroyEntity(id_);
}

uint32_t Entity::getID() const
{
	return id_;
}

void Entity::addComponent(const Component& c) const
{
	entityManager_->addComponent(id_, c);
}

void Entity::removeComponent(Component& c) const
{
	entityManager_->removeComponent(id_, c);
}
