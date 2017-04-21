#include "Entity.h"
#include "EntityManager.h"
#include <iostream>

Entity::Entity(uint32_t id, EntityManager & entityManager, Transform& pos)
{
	id_ = id;
	entityManager_ = &entityManager;
	transform_ = &pos;
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

void Entity::addComponent(IComponent& c)
{
	entityManager_->addComponent(*this, c);
}

void Entity::removeComponent(IComponent& c)
{
	entityManager_->removeComponent(*this, c);
}

Transform * Entity::getTransform() const
{
	return transform_;
}

bool Entity::operator==(const Entity & other) const
{
	return this->id_ == other.getID();
}
