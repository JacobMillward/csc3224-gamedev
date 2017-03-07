#pragma once
#include <unordered_map>
#include <vector>
#include <typeindex>
#include "Entity.h"

using namespace std;

typedef unordered_map<IComponent::Type, vector<pair<IComponent*, uint32_t>>> EntityMap;

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	Entity* createEntity();
	void destroyEntity(Entity* entity);
	void addComponent(Entity& e, IComponent& c);
	void removeComponent(Entity& e, IComponent& c);
	template <class T>
	vector<pair<IComponent*, uint32_t>> getComponentList(T comClass);

private:
	EntityMap entityMap_;
	uint32_t entityID_;

	uint32_t getNextID();
};

template <class T>
vector<pair<IComponent*, uint32_t>> EntityManager::getComponentList(T comClass)
{
	
}
