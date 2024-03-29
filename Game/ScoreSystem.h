#pragma once
#include "Systems/ISystem.h"
#include "Entity.h"

class ScoreSystem : public ISystem
{
public:
	ScoreSystem(World& w);
	~ScoreSystem();
	void step(const sf::Time& dt) override;
	void recieveMessage(const SystemMessage& m) override;
protected:
	Entity* playerEntity;
	const float baseline = 500.f;
	int highScore;
	bool gameOver = false;
};

