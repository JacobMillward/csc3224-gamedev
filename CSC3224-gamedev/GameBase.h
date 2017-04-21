#pragma once
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Intents/IntentHandler.h"

class GameBase
{
public:

	explicit GameBase(sf::RenderWindow* window) : gameClock_(sf::Clock()), window_(window), intentHandler_()
	{
	};

	virtual ~GameBase()
	{
		delete window_;
	};

	virtual void run()
	{
	};

protected:
	sf::Clock gameClock_;
	sf::RenderWindow* window_;
	IntentHandler intentHandler_;

	virtual void init()
	{
	};

	virtual void shutdown()
	{
	};
};
