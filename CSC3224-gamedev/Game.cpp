#include "Game.h"
#include "EntityManager.h"

Game::Game() : state_(State::Init)
{
}


Game::~Game()
{
	EntityManager::destroyInstance();
}

void Game::changeState(State s)
{
	state_ = s;
}

Game::State Game::getState() const
{
	return state_;
}

void Game::init()
{
}

void Game::processInput()
{
}

void Game::update()
{
}
