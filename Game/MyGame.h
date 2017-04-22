#pragma once
#include "GameBase.h"

class MyGame : public GameBase
{
public:
	MyGame();
	~MyGame();

protected:
	void init() override;
	void quit() override;

private:
	Entity* wheel;
};
