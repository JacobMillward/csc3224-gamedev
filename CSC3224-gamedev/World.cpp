#include "World.h"
#include <iostream>

World::World(float timeScale) : state_(State::Init), entityManager_(EntityManager()), timeScale_(timeScale)
{
}


World::~World()
{
}

void World::step(const sf::Time & gameDelta)
{
}

EntityManager & World::getEntityManager()
{
	return entityManager_;
}
