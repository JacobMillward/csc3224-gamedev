#include "Entity.h"
#include "EntityManager.h"

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

bool Entity::operator==(const Entity& other) const
{
	return this->id_ == other.getID();
}
