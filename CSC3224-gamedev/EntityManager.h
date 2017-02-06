#pragma once
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <typeinfo>
#include "Entity.h"

using namespace std;
typedef unordered_map<uint32_t, unordered_map<type_index, vector<IComponent*>>> EntityMap;

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	Entity createEntity();
	void destroyEntity(uint32_t id);
	void addComponent(uint32_t id, IComponent& c);
	void removeComponent(uint32_t id, IComponent& c);

private:
	EntityMap entityMap_;
	uint32_t entityID_;

	uint32_t getNextID();
};
