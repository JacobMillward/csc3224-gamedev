#include "World.h"
#include "Systems/RenderableBuildSystem.h"

World::World(float timeScale) : state_(Init), entityManager_(EntityManager()), physics_system_(new PhysicsSystem(*this, b2Vec2(0.f, 9.8f))), systemList_(eastl::fixed_vector<ISystem*, MAX_SYSTEMS>()), timeScale_(timeScale)
{
	addSystem(physics_system_);
	addSystem(new RenderableBuildSystem(*this));
}


World::~World()
{
	for (auto system : systemList_)
	{
		delete system;
	}
}

void World::addSystem(ISystem* system)
{
	systemList_.push_back(system);
}

void World::step(const sf::Time& gameDelta)
{
	for (auto system : systemList_)
	{
		system->step(gameDelta);
	}
}

void World::draw(sf::RenderWindow& w)
{
	sf::RenderStates states;
	for (auto vArray : drawables_)
	{
		states.texture = &vArray.second;
		w.draw(vArray.first, states);
	}
}

EntityManager& World::getEntityManager()
{
	return entityManager_;
}

PhysicsSystem* World::getPhysicsSystem()
{
	return physics_system_;
}

void World::addDrawables(vector<pair<sf::VertexArray, sf::Texture>>& drawableList)
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
