#pragma once
#include "GameBase.h"
#include "World.h"

class MyGame : public GameBase
{
public:
	MyGame();
	~MyGame();

	void run() override;

protected:
	void init() override;
	void shutdown() override;

private:
	World* world_;

	Entity* wheel;
};
