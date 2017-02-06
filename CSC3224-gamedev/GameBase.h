#pragma once
#include <SFML\System\Clock.hpp>
#include "World.h"

class GameBase
{
public:
	
	GameBase() : gameClock(sf::Clock()), lastTime(sf::Time()) {};
	virtual ~GameBase() {};

	virtual void run() {};

protected:
	sf::Clock gameClock;
	sf::Time lastTime;

	virtual void init() {};
	virtual void shutdown() {};
};