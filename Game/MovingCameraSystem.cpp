#include "MovingCameraSystem.h"
#include "World.h"
#include "Components/Tag.h"
#include <iostream>

MovingCameraSystem::MovingCameraSystem(World& w, sf::RenderWindow* window) : ISystem(w), window_(window), camera_(window->getDefaultView())
{
}

MovingCameraSystem::~MovingCameraSystem()
{
}

void MovingCameraSystem::step(const sf::Time& dt)
{
	/* Grab a reference to the player */
	if (!playerEntity)
	{
		auto list = this->world_->getEntityManager().getComponentList(ComponentType::TAG);
		for (auto pair : *list)
		{
			auto component = static_cast<Tag*>(pair.first);
			if (component->getTag() == "player")
			{
				playerEntity = pair.second;
				break;
			}
		}
	}
	currentdelay += dt.asMilliseconds();
	if(currentdelay > delayInMilliseconds)
	{
		auto move = -moveSpeed * dt.asMilliseconds();
		camera_.move(0, move);
		world_->DebugText.move(0, move);
		window_->setView(camera_);
	}

	auto pos = playerEntity->getSprite()->getPosition();
	auto bottom = camera_.getCenter().y + (camera_.getSize().y / 2);

	if(pos.y > bottom)
	{
		//player is dead
		playerEntity->getComponent<Tag>()->setTag("dead");
	}
}
