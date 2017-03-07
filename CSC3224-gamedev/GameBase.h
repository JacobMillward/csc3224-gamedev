#pragma once
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "FreeListAllocator.h"

class GameBase
{
public:
	
	GameBase(sf::RenderWindow* window, FreeListAllocator* memAllocator) : memAllocator_(memAllocator), gameClock_(sf::Clock()), window_(window) {};
	virtual ~GameBase()
	{
		delete window_;
	};

	virtual void run() {};

protected:
	FreeListAllocator* memAllocator_;
	sf::Clock gameClock_;
	sf::RenderWindow* window_;

	virtual void init() {};
	virtual void shutdown() {};
};