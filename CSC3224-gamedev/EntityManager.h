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

	Entity createEntity(sf::Vector3f& pos);
	void destroyEntity(uint32_t id);
	void addComponent(uint32_t id, IComponent& c);
	void removeComponent(uint32_t id, IComponent& c);

private:
	EntityMap entityMap_;
	uint32_t entityID_;

	uint32_t getNextID();
};
