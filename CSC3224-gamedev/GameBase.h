#pragma once
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Intents/IntentHandler.h"
#include "TextureManager.h"

class GameBase
{
public:

	explicit GameBase(sf::RenderWindow* window) : gameClock_(sf::Clock()), window_(window), intentHandler_(), textureManager_()
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
	TextureManager textureManager_;

	virtual void init()
	{
	};

	virtual void shutdown()
	{
	};
};
