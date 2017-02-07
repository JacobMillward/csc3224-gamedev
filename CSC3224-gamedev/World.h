#pragma once
#include <SFML\System\Clock.hpp>
#include "EntityManager.h"

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
	World(float timeScale = 1);
	~World();
	void changeState(State s) { state_ = s; };
	State getState() const { return state_; };
	void step(const sf::Time& gameDelta);

private:
	State state_;
	EntityManager entityManager_;
	float timeScale_;
};

