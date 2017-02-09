#include <string>
#include "EntityManager.h"
#include <typeindex>
#include "Components/Position.h"
#include <algorithm>
#include <iostream>

using namespace std;

EntityManager::EntityManager() : entityMap_(EntityMap()), entityID_(0)
{
	/* Initiaslise map with lists of all component types to save checks for creation later on */
	for(int i = 0; i < static_cast<int>(IComponent::Type::TYPE_END); ++i)
	{
		entityMap_.try_emplace(IComponent::Type(i), vector<pair<IComponent*, uint32_t>>());
	}
}

uint32_t EntityManager::getNextID()
{
	return entityID_++;
}

EntityManager::~EntityManager()
{
	//TODO: Actually fix this huge ass leak here.
}

/*
 * Creates an entity at position (0, 0, 0)
 */
Entity* EntityManager::createEntity()
{
	Position *p = new Position(0, 0, 0);
	Entity *e = new Entity(getNextID(), *this, *p);
	cout << "Creating Entity#" << e->getID() << endl;
	entityMap_.find(IComponent::Type::Position)->second.push_back(make_pair(p, e->getID()));
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
		vector<vector<pair<IComponent*, uint32_t>>::iterator> matches;
		for (auto it = comType.second.begin(); it != comType.second.end(); ++it)
		{
			if (entity->getID() == it->second)
			{
				matches.push_back(it);
			}
		}
		// Might need to loop in reverse here - UNIT TEST
		for (auto e : matches)
		{
			delete e->first;
			comType.second.erase(e);
		}
		
	}
	cout << "Destroyed Entity#" << entity->getID() << endl;
	delete entity;
}

/*
 * Adds the specifed component to the entity.
 */
void EntityManager::addComponent(Entity& e, IComponent& c)
{
	cout << "Adding Component type " << static_cast<int>(c.getType()) << " to Entity#" << e.getID() << endl;
	entityMap_.find(c.getType())->second.push_back(make_pair(&c, e.getID()));
}

/*
 * Removes the specified component from the entity.
 */
void EntityManager::removeComponent(Entity& e, IComponent& c)
{
	auto list = entityMap_.find(c.getType())->second;
	auto it = find_if(list.begin(), list.end(), [&e, &c](pair<IComponent*, uint32_t> p){
		return (e.getID() == p.second) && (&c == p.first);
	});
	if (it != list.end())
	{
		cout << "Deleting " << typeid(it->first).name() << " Component from Entity#" << it->second << endl;
		delete it->first;
		list.erase(it);
	}
	else
	{
		throw "No such component on Entity";
	}
}
