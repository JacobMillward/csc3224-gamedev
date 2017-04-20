#pragma once
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class GameBase
{
public:
	
	GameBase(sf::RenderWindow* window) : gameClock_(sf::Clock()), window_(window) {};
	virtual ~GameBase()
	{
		delete window_;
	};

	virtual void run() {};

protected:
	sf::Clock gameClock_;
	sf::RenderWindow* window_;

	virtual void init() {};
	virtual void shutdown() {};
};