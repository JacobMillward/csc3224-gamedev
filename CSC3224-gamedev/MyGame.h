#pragma once
#include "GameBase.h"

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
	World world_;
};

