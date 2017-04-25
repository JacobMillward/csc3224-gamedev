#pragma once
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "EntityManager.h"
#include "Systems/ISystem.h"
#include "Systems/PhysicsSystem.h"
#include "Systems/RenderableBuildSystem.h"


class World
{
public:
	enum State
	{
		Init,
		Running,
		Quitting,
		Shutdown
	};

	explicit World(float timeScale = 1);
	~World();
	void changeState(State s) { state_ = s; };
	State getState() const { return state_; };
	void addSystem(ISystem* system);
	void step(const sf::Time& gameDelta);
	void draw(sf::RenderWindow& w);

	EntityManager& getEntityManager();
	PhysicsSystem* getPhysicsSystem() const;

protected:
	State state_;
	EntityManager entityManager_;
	PhysicsSystem* physics_system_;
	eastl::fixed_vector<ISystem*, MAX_SYSTEMS> systemList_;

	/* Let the render system access the list of drawables */
	friend void RenderableBuildSystem::step(const sf::Time& dt);
	eastl::vector<Sprite*> drawables_;

	float timeScale_;
};
