#pragma once
#include <SFML/System/Clock.hpp>
#include <SFML/Window.hpp>

class GameBase
{
public:
	
	GameBase(sf::Window* window) : gameClock_(sf::Clock()), window_(window) {};
	virtual ~GameBase()
	{
		delete window_;
	};

	virtual void run() {};

protected:
	sf::Clock gameClock_;
	sf::Window* window_;

	virtual void init() {};
	virtual void shutdown() {};
};