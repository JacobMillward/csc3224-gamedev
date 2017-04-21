#pragma once
#include <EASTL/fixed_hash_map.h>
#include <EASTL/fixed_vector.h>
#include <type_traits>
#include "Entity.h"

using namespace std;

typedef eastl::fixed_vector<pair<IComponent*, Entity*>, MAX_COMPONENTS> ComponentVector;
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
	template <typename T>
	T* getComponent(Entity* e);

private:
	EntityMap entityMap_;
	uint32_t entityID_;

	uint32_t getNextID();
};

template <typename T>
T* EntityManager::getComponent(Entity* e)
{
	static_assert(std::is_base_of<IComponent, T>::value, "T must inherit from IComponent");
	auto comType = static_cast<int>(T::typeID);
	auto list = entityMap_.find(comType)->second;
	auto it = eastl::find_if(list.begin(), list.end(), [e](pair<IComponent*, Entity*> p)
	                         {
		                         return (e == p.second);
	                         });
	if (it != list.end())
	{
		return static_cast<T*>(it->first);
	}
	throw "No such component on entity.";
}
