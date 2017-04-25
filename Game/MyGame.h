#pragma once
#include "GameBase.h"

class MyGame : public GameBase
{
public:
	MyGame();
	~MyGame();

protected:
	void init() override;
	void update(sf::Time dt) override;
	void quit() override;

	sf::Time elapsedTime;
};
