#include "Entity.h"
#include "EntityManager.h"
#include <iostream>

Entity::Entity(uint32_t id, EntityManager & entityManager, Position& pos)
{
	id_ = id;
	entityManager_ = &entityManager;
	position_ = &pos;
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

Position * Entity::getPosition() const
{
	return position_;
}

bool Entity::operator==(const Entity & other) const
{
	return this->id_ == other.getID();
}
