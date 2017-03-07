#pragma once
#include "GameBase.h"
#include "World.h"
#include "Components\Sprite.h"

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
	World world_ = NULL;

	sf::Texture playerTexture;
	Entity* player;
	Sprite* playerSprite;
};

