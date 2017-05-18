#include "World.h"
#include "Systems/RenderableBuildSystem.h"
#include "Box2D/Common/b2Math.h"
#include "Systems/AudioSystem.h"
#include "Components/Sprite.h"
#include <iostream>

World::World(ResourceManager& resourceManager, float timeScale) : state_(Init), entityManager_(EntityManager()), physics_system_(new PhysicsSystem(*this, b2Vec2(0.f, 15.f))), systemList_(eastl::fixed_vector<ISystem*, MAX_SYSTEMS>()), timeScale_(timeScale)
{
	addSystem(physics_system_);
	addSystem(new RenderableBuildSystem(*this));
	addSystem(new AudioSystem(*this, resourceManager));

	/* Lets use Arial, as it's probably always available */
	if (!debugFont.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
	{
		std::cout << "Failed to load debug font" << std::endl;
	}
	DebugText.setFont(debugFont);
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

void World::sendSystemMessage(const SystemMessage& m)
{
	for (auto system : systemList_)
	{
		system->recieveMessage(m);
	}
}

void World::step(const sf::Time& gameDelta)
{
	for (auto system : systemList_)
	{
		system->step(gameDelta);
	}
}

void World::draw(sf::RenderWindow& w, ResourceManager& resourceManager)
{
	for (auto sprite : drawables_)
	{
		sprite->setTexture(*(resourceManager.getTexture(sprite->getTextureID())));
		w.draw(*sprite);
	}
	if(debug)
	{
		w.draw(DebugText);
	}
}

EntityManager& World::getEntityManager()
{
	return entityManager_;
}

PhysicsSystem& World::getPhysicsSystem() const
{
	return *physics_system_;
}
