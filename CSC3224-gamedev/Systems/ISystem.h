#pragma once
#include <SFML/System/Clock.hpp>

#define MAX_SYSTEMS 1024

class World;

class ISystem
{
public:
	explicit ISystem(World& w) : world_(&w)
	{
	}

	virtual ~ISystem()
	{
	};

	virtual void step(const sf::Time& dt) = 0;

protected:
	World* world_;
};
