#pragma once
#include <SFML/System/Clock.hpp>

class World;

class ISystem
{
public:
	ISystem(World& w) : world_(&w) {}
	virtual ~ISystem() {};

	virtual void step(const sf::Time& dt) = 0;

protected:
	World *world_;
};
