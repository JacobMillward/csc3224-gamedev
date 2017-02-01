#pragma once
#include <map>
class EntityManager
{
private:
	static EntityManager *_entityManager;
	EntityManager();
public:
	static EntityManager * getInstance();
	static void destroyInstance();
};

