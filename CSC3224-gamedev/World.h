#pragma once
#include "EntityManager.h"
#include "SystemManager.h"

class World
{
public:
	World();
	~World();

private:
	EntityManager entityManager_;
	SystemManager systemManager_;
};

