#pragma once
#include <SFML\System\Clock.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\VertexArray.hpp>
#include <SFML\Graphics\Texture.hpp>
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
	void addDrawables(vector<pair<sf::VertexArray, sf::Texture>> &drawableList);
	void clearDrawables();

protected:
	State state_;
	EntityManager entityManager_;
	vector<ISystem*> systemList_;
	vector<pair<sf::VertexArray, sf::Texture>> drawables_;
	float timeScale_;
};

