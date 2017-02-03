#pragma once
#include <map>
#include <vector>
#include <string>
#include "Entity.h"
#include "Component.h"
using namespace std;

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	Entity createEntity(vector<Component>* components = new vector<Component>());
	void destroyEntity(uint32_t id);
	void addComponent(uint32_t id, const Component& c);
	void removeComponent(uint32_t id, const Component& c);

private:
	map<uint32_t, vector<Component>*> entityMap_;
	unsigned int entityID_;

	unsigned int getNextID();
};
