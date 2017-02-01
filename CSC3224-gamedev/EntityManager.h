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
	static EntityManager* getInstance();
	static void destroyInstance();
	~EntityManager();

	Entity createEntity(vector<Component>* components = new vector<Component>());
	void destroyEntity(uint32_t id);
	void addComponent(uint32_t id, const Component& c);
	void removeComponent(uint32_t id, const Component& c);

private:
	static EntityManager* entityManager_;
	EntityManager();

	map<uint32_t, vector<Component>*> entityMap_;
	unsigned int entityID_;

	unsigned int getNextID();
};
