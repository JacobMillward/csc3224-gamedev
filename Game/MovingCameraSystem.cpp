#include "MovingCameraSystem.h"
#include "World.h"

MovingCameraSystem::MovingCameraSystem(World& w, sf::RenderWindow* window) : ISystem(w), window_(window), camera_(window->getDefaultView())
{
}

MovingCameraSystem::~MovingCameraSystem()
{
}

void MovingCameraSystem::step(const sf::Time& dt)
{
	currentdelay += dt.asMilliseconds();
	if(currentdelay > delayInMilliseconds)
	{
		auto move = -moveSpeed * dt.asMilliseconds();
		camera_.move(0, move);
		world_->DebugText.move(0, move);
		window_->setView(camera_);
	}
}
