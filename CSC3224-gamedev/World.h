#pragma once
#include <SFML\System\Clock.hpp>
#include <SFML\Graphics.hpp>
#include "EntityManager.h"
#include "Systems/ISystem.h"

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
	void addSystem(ISystem& system);
	void step(const sf::Time& gameDelta);
	void draw(sf::RenderWindow& w);

	EntityManager& getEntityManager();
	void setVertexArray(sf::VertexArray& v);

protected:
	State state_;
	EntityManager entityManager_;
	vector<ISystem*> systemList_;
	sf::VertexArray vertexArray_;
	float timeScale_;
};

