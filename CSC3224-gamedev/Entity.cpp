#include "Entity.h"
#include "EntityManager.h"

Entity::Entity(uint32_t id, EntityManager & entityManager, sf::Vector3f& pos)
{
	id_ = id_;
	entityManager_ = &entityManager;
	position_ = &pos;
}

Entity::~Entity()
{
	entityManager_->destroyEntity(id_);
	delete position_;
}

uint32_t Entity::getID() const
{
	return id_;
}

void Entity::addComponent(IComponent& c) const
{
	entityManager_->addComponent(id_, c);
}

void Entity::removeComponent(IComponent& c) const
{
	entityManager_->removeComponent(id_, c);
}

sf::Vector3f * Entity::getPosition()
{
	return position_;
}
