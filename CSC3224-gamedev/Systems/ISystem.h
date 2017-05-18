#pragma once
#include <SFML/System/Clock.hpp>
#include <string>

#define MAX_SYSTEMS 1024

struct SystemMessage
{
	std::string name;
};

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
	virtual void recieveMessage(const SystemMessage& m) = 0;

protected:
	World* world_;
};
