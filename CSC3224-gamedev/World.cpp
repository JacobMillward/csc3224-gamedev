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
	sf::RenderStates states;
	for (auto vArray : drawables_)
	{
		states.texture = &vArray.second;
		w.draw(vArray.first, states);
	}
}

EntityManager & World::getEntityManager()
{
	return entityManager_;
}

void World::addDrawables(vector<pair<sf::VertexArray, sf::Texture>> &drawableList)
{
	for (auto drawable : drawableList)
	{
		drawables_.push_back(drawable);
	}
}

void World::clearDrawables()
{
	drawables_.clear();
}

