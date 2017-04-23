#pragma once
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Intents/IntentHandler.h"
#include "TextureManager.h"
#include "World.h"

class GameBase
{
public:

	explicit GameBase(sf::RenderWindow* window);

	virtual ~GameBase();;

	void run();

protected:
	sf::Clock gameClock_;
	sf::RenderWindow* window_;
	IntentHandler intentHandler_;
	TextureManager textureManager_;
	World* world_;

	virtual void init()
	{
	};

	virtual void quit()
	{
	};

	void shutdown() const;
};
