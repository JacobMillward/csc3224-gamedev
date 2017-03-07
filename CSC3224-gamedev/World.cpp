#include "World.h"
#include <iostream>

World::World(float timeScale) : state_(State::Init), entityManager_(EntityManager()), systemList_(vector<ISystem*>()),timeScale_(timeScale)
{
}


World::~World()
{
}

void World::addSystem(ISystem& system)
{
	systemList_.push_back(&system);
}

void World::step(const sf::Time & gameDelta)
{
	for(auto system : systemList_)
	{
		system->step(gameDelta);
	}
}

EntityManager & World::getEntityManager()
{
	return entityManager_;
}
