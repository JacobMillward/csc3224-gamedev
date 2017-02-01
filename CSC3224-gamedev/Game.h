#pragma once
#include "SystemManager.h"

class Game
{
public:
	enum State
	{
		Init,
		Running,
		Shutdown
	};
	Game();
	~Game();
	void changeState(State s);
	State getState() const;

	void init();
	void processInput();
	void update();

private:
	State state_;
};
