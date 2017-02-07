#pragma once
#include <SFML\System\Clock.hpp>

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