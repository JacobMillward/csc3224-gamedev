#include <string>
#include "EntityManager.h"
#include <typeindex>
#include "Components/Transform.h"
#include <algorithm>
#include <iostream>
#include <EASTL\hash_set.h>
using namespace std;

EntityManager::EntityManager() : entityMap_(EntityMap()), entityID_(0)
{
	/* Initiaslise map with lists of all component types to save checks for creation later on */
	for(int i = 0; i < static_cast<int>(IComponent::Type::TYPE_END); ++i)
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
Entity* EntityManager::createEntity()
{
	Transform *p = new Transform();
	Entity *e = new Entity(getNextID(), *this, *p);
	std::cout << "Creating Entity#" << e->getID() << endl;
	entityMap_.find(static_cast<int>(IComponent::Type::TRANSFORM))->second.push_back(make_pair(p, e));
	return e;
}

/*
 * Destroys all components that belong to the specified entity. Also deletes the entity.
 */
void EntityManager::destroyEntity(Entity *entity)
{
	entity->isDeleted = true;
	for (auto comType : entityMap_)
	{
		pair<IComponent*, Entity*>* matches[MAX_COMPONENTS];
		int numMatches = 0;
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
	std::cout << "Destroyed Entity#" << entity->getID() << endl;
	delete entity;
}

/*
 * Adds the specifed component to the entity.
 */
void EntityManager::addComponent(Entity& e, IComponent& c)
{
	std::cout << "Adding Component type " << c.getTypeValue() << " to Entity#" << e.getID() << endl;
	entityMap_.find(c.getTypeValue())->second.push_back(make_pair(&c, &e));
}

/*
 * Removes the specified component from the entity.
 */
void EntityManager::removeComponent(Entity& e, IComponent& c)
{
	auto list = entityMap_.find(c.getTypeValue())->second;
	auto it = eastl::find_if(list.begin(), list.end(), [&e, &c](pair<IComponent*, Entity*> p){
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
}

ComponentVector* EntityManager::getComponentList(IComponent::Type type)
{
	return &(entityMap_.find(static_cast<int>(type))->second);
}
