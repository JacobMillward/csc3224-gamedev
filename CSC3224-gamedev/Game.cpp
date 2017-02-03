#include <iostream>
#include "Game.h"
#include "EntityManager.h"

Game::Game() : state_(State::Init)
{
}


Game::~Game()
{
}

void Game::changeState(State s)
{
	state_ = s;
}

Game::State Game::getState() const
{
	return state_;
}

void Game::run()
{

}

void Game::init()
{
}

void Game::processInput()
{
}

void Game::update()
{
	bool loop = true;
	while (loop)
	{
		switch (state_)
		{
		case Game::Init:
			cout << "Game Initialising\n";
			init();
			changeState(Game::State::Running);
			cout << "Game Initialisation Complete\n";
			break;

		case Game::Running:
			processInput();
			update();
			break;

		case Game::Shutdown:
			loop = false;
			break;

		default:
			throw "Erroroneous Game State";
		}
	}
}
