#pragma once
#include <SFML/System/Clock.hpp>
#include "../World.h"

class ISystem
{
public:
	ISystem(World& w) : world_(&w) {}
	virtual ~ISystem() {};

	virtual void step(sf::Time dt) = 0;

private:
	World *world_;
};
