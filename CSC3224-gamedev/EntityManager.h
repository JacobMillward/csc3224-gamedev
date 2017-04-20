#pragma once
#include <EASTL\fixed_hash_map.h>
#include <EASTL\fixed_vector.h>
#include <vector>
#include <typeindex>
#include "Entity.h"

using namespace std;

typedef eastl::fixed_vector<pair<IComponent*, Entity*>, MAX_COMPONENTS> ComponentVector;
//TODO: Consider a multimap here instead
typedef eastl::fixed_hash_map<int, ComponentVector, static_cast<int>(IComponent::Type::TYPE_END) + 1> EntityMap;

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	Entity* createEntity();
	void destroyEntity(Entity* entity);
	void addComponent(Entity& e, IComponent& c);
	void removeComponent(Entity& e, IComponent& c);
	ComponentVector* getComponentList(IComponent::Type type);

private:
	EntityMap entityMap_;
	uint32_t entityID_;

	uint32_t getNextID();
};