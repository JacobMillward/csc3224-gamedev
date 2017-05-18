#include <string>
#include "EntityManager.h"
#include <typeindex>
#include <algorithm>
#include <iostream>
#include <EASTL/hash_set.h>
#include "Components/IComponent.h"
using namespace std;

EntityManager::EntityManager() : entityMap_(), entityID_(0), entityComponents_()
{
	/* Initiaslise map with lists of all component types to save checks for creation later on */
	for (auto i = 0; i < static_cast<int>(ComponentType::TYPE_END); ++i)
	{
		entityMap_.emplace(i, ComponentVector());
	}
}

uint32_t EntityManager::getNextID()
{
	return entityID_++;
}

EntityManager::~EntityManager()
{
	auto eList = eastl::hash_set<uint32_t>();
	for (auto comType : entityMap_)
	{
		for (auto it = comType.second.begin(); it != comType.second.end(); ++it)
		{
			delete it->first;
			if (eList.find(it->second->getID()) != eList.end())
			{
				eList.insert(it->second->getID());
				delete it->second;
			}
		}
	}
}

/*
 * Creates an entity at position (0, 0, 0)
 */
Entity* EntityManager::createEntity(std::string textureID, sf::IntRect rect)
{
	auto s = new Sprite(textureID, rect);
	return createEntity(s);
}

Entity* EntityManager::createEntity(Sprite* sprite)
{
	auto e = new Entity(getNextID(), *this, *sprite);
	std::cout << "Creating Entity#" << e->getID() << endl;
	entityMap_.find(static_cast<int>(ComponentType::SPRITE))->second.push_back(make_pair(sprite, e));
	entityComponents_.emplace(e->getID(), eastl::vector<Component*>{sprite});
	return e;
}

/*
 * Destroys all components that belong to the specified entity. Also deletes the entity.
 */
void EntityManager::destroyEntity(Entity* entity)
{
	entity->isDeleted = true;
	for (auto comType : entityMap_)
	{
		pair<Component*, Entity*>* matches[MAX_COMPONENTS];
		auto numMatches = 0;
		for (auto it = comType.second.begin(); it != comType.second.end(); ++it)
		{
			if (entity == it->second)
			{
				matches[numMatches++] = it;
			}
		}

		for (auto e : matches)
		{
			delete e->first;
			comType.second.erase(e);
		}
	}
	entityComponents_.erase(entity->getID());
	std::cout << "Destroyed Entity#" << entity->getID() << endl;
	delete entity;
}

/*
 * Adds the specifed component to the entity.
 */
void EntityManager::addComponent(Entity& e, Component& c)
{
	std::cout << "Adding Component type " << c.getTypeValue() << " to Entity#" << e.getID() << endl;
	entityMap_.find(c.getTypeValue())->second.push_back(make_pair(&c, &e));
	entityComponents_.find(e.getID())->second.push_back(&c);
}

/*
 * Removes the specified component from the entity.
 */
void EntityManager::removeComponent(Entity& e, Component& c)
{
	auto list = entityMap_.find(c.getTypeValue())->second;
	auto it = eastl::find_if(list.begin(), list.end(), [&e, &c](pair<Component*, Entity*> p)
	                         {
		                         return (e == *(p.second)) && (&c == p.first);
	                         });
	if (it != list.end())
	{
		std::cout << "Deleting " << typeid(it->first).name() << " Component from Entity#" << it->second->getID() << endl;
		delete it->first;
		list.erase(it);
	}
	else
	{
		throw "No such component on Entity";
	}
	auto comList = entityComponents_.find(e.getID())->second;
	auto comListIt = eastl::find_if(comList.begin(), comList.end(), [&c](Component* p)
	{
		return (&c == p);
	});
	comList.erase(comListIt);
}

eastl::vector<Component*>* EntityManager::getComponentList(uint32_t eID)
{
	return &entityComponents_.find(eID)->second;
}

uint32_t EntityManager::getMaxIdUsed() const
{
	return entityID_;
}

ComponentVector* EntityManager::getComponentList(ComponentType type)
{
	return &(entityMap_.find(static_cast<int>(type))->second);
}
