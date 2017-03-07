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

void World::draw(sf::RenderWindow & w)
{
	w.draw(vertexArray_);
}

EntityManager & World::getEntityManager()
{
	return entityManager_;
}

void World::setVertexArray(sf::VertexArray & v)
{
	this->vertexArray_ = v;
}
