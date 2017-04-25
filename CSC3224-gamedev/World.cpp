#include "World.h"
#include "Systems/RenderableBuildSystem.h"
#include "Box2D/Common/b2Math.h"

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

void World::draw(sf::RenderWindow& w, TextureManager& textureManager)
{
	sf::RenderStates states;
	for (auto sprite : drawables_)
	{
		sprite->setTexture(*textureManager.getTexture(sprite->getTextureID()));
		w.draw(*sprite);
	}
}

EntityManager& World::getEntityManager()
{
	return entityManager_;
}

PhysicsSystem* World::getPhysicsSystem() const
{
	return physics_system_;
}
