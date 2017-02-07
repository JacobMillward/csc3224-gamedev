#include <string>
#include "EntityManager.h"
#include <typeindex>
#include "Components/Position.h"

using namespace std;

EntityManager::EntityManager() : entityMap_(EntityMap()), entityID_(0)
{
}

uint32_t EntityManager::getNextID()
{
	return entityID_++;
}

EntityManager::~EntityManager()
{
}

Entity EntityManager::createEntity(sf::Vector3f& pos)
{
	Entity e = Entity(getNextID(), *this);
	Position *p = new Position(pos);
	if(!entityMap_.try_emplace(Position::typeID, vector<pair<IComponent*, uint32_t>> { make_pair(p, e.getID()) }).second)
	{
		throw "Error creating new Entity";
	}
	return e;
}



void EntityManager::destroyEntity(uint32_t id)
{
	/*auto it = entityMap_.find(id);
	if (it != entityMap_.end())
	{
		for (auto ent1 : it->second)
		{
			for (auto ent2 : ent1.second)
			{
				delete ent2;
			}
		}
		entityMap_.erase(it);
		return;
	}
	throw "Error destroying non-existent entity#" + to_string(id);*/
}

void EntityManager::addComponent(uint32_t id, IComponent& c)
{
	//auto it = entityMap_.find(id);
	//if (it != entityMap_.end())
	//{
	//	//Try and emplace it
	//	auto result = it->second.try_emplace(typeid(c), vector<IComponent*> { &c });
	//	if (!result.second)
	//	{
	//		//If we haven't placed it in, add it to the existing list
	//		result.first->second.push_back(&c);
	//		return;
	//	}
	//}
	//throw "Error adding component to a non-existent entity#" + to_string(id);
}

void EntityManager::removeComponent(uint32_t id, IComponent& c)
{
	////Try and find the entity
	//auto it1 = entityMap_.find(id);
	//if (it1 != entityMap_.end())
	//{
	//	//Find the list of this components type
	//	auto it2 = it1->second.find(typeid(c));
	//	if (it2 != it1->second.end())
	//	{
	//		//We've found the list, so lets find the correct component and erase
	//		for (auto it3 = it2->second.begin(); it3 != it2->second.end(); ++it3) {
	//			if (*it3 == &c)
	//			{
	//				delete *it3;
	//				it2->second.erase(it3);
	//				return;
	//			}
	//		}
	//	}
	//	throw "Error removing non-existent component from entity#" + to_string(id);
	//}
	//throw "Error removing component from non-existent entity#" + to_string(id);
}
