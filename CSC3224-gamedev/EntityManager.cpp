#include "EntityManager.h"



EntityManager::EntityManager()
{
}


EntityManager::~EntityManager()
{
}

EntityManager * EntityManager::getInstance()
{
	if (!_entityManager) {
		_entityManager = new EntityManager();
	}
	
	return _entityManager;
}

void EntityManager::destroyInstance()
{
	delete _entityManager;
	_entityManager = nullptr;
}
