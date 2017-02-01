#include <algorithm>
#include "EntityManager.h"

using namespace std;

EntityManager::EntityManager() : entityID_(0)
{
}

unsigned int EntityManager::getNextID()
{
	return entityID_++;
}

EntityManager* EntityManager::getInstance()
{
	if (!entityManager_)
	{
		entityManager_ = new EntityManager();
	}

	return entityManager_;
}

void EntityManager::destroyInstance()
{
	delete entityManager_;
	entityManager_ = nullptr;
}

EntityManager::~EntityManager()
{
	for(auto entry : entityMap_)
	{
		delete entry.second;
	}
}

Entity EntityManager::createEntity(vector<Component>* components)
{
	Entity e = Entity(getNextID());
	entityMap_.insert(pair<uint32_t, vector<Component>*>(e.getID(), components));
	return e;
}



void EntityManager::destroyEntity(uint32_t id)
{
	auto it = entityMap_.find(id);
	if (it != entityMap_.end())
	{
		delete it->second;
		entityMap_.erase(it);
	}
	else
	{
		throw "Tried to destroy non-existent entity#" + to_string(id);
	}
}

void EntityManager::addComponent(uint32_t id, const Component& c)
{
	auto it = entityMap_.find(id);
	if (it != entityMap_.end())
	{
		it->second->push_back(c);
	}
	else
	{
		throw "Tried to add component to a non-existent entity#" + to_string(id);
	}
}

void EntityManager::removeComponent(uint32_t id, const Component& c)
{
	auto it = entityMap_.find(id);
	if (it != entityMap_.end())
	{
		auto componentIt = find(it->second->begin(), it->second->end(), c);
		if (componentIt != it->second->end())
		{
			it->second->erase(componentIt);
			return;
		}
	}
	throw "Error removing component#" + std::to_string(c.getID()) + " from entity#" + to_string(id);
}
