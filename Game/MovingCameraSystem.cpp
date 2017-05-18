#include "MovingCameraSystem.h"
#include "World.h"
#include "Components/Tag.h"
#include <iostream>
#include "Components/PhysicsBody.h"

MovingCameraSystem::MovingCameraSystem(World& w, sf::RenderWindow* window, Json::Value platformConfig) : ISystem(w), window_(window), camera_(window->getDefaultView()), playerEntity(nullptr), platformConfig(platformConfig)
{
	for (int i = 0; i < ceil(camera_.getSize().y / maxVerticalDistance / PIXELS_TO_UNITS_SCALE) + 1; ++i)
	{
		platformConfig["Sprite"]["PosX"] = fmod(platformConfig["Sprite"]["PosX"].asFloat() + RandomFloat(-maxHorixzontalDistance, maxHorixzontalDistance) * PIXELS_TO_UNITS_SCALE, camera_.getSize().x);
		platformConfig["Sprite"]["PosY"] = fmod(platformConfig["Sprite"]["PosY"].asFloat() + RandomFloat(-minVerticalDistance, -maxVerticalDistance) * PIXELS_TO_UNITS_SCALE, camera_.getSize().y);
		auto e = Entity::buildFromJson(w.getEntityManager(), w.getPhysicsSystem(), platformConfig);
		platformBuffer.push_back(e->getComponent<PhysicsBody>()->getBody());
	}
}

MovingCameraSystem::~MovingCameraSystem()
{
}

void MovingCameraSystem::moveClouds() const
{
	auto list = this->world_->getEntityManager().getComponentList(ComponentType::TAG);
	for (auto pair : *list)
	{
		auto component = static_cast<Tag*>(pair.first);
		if (component->getTag() == "cloud")
		{
			auto sprite = pair.second->getSprite();
			auto pos = sprite->getPosition();
			auto offsetY = sprite->getOrigin().y;
			if(isBelowView(pos.y - offsetY))
			{
				sprite->move(0, camera_.getSize().y - offsetY);
			}
		}
	}
}

void MovingCameraSystem::step(const sf::Time& dt)
{
	if(!gameover)
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

		auto pos = playerEntity->getSprite()->getPosition();
		/* Shift highscore text depending on side */
		auto leftSide = (pos.x > camera_.getSize().x / 3);
		world_->DebugText.setPosition((leftSide ? 10 : 600), pos.y - world_->DebugText.getCharacterSize());

		/* Move Camera */
		//Starting delay
		currentdelay += dt.asMilliseconds();
		if (currentdelay > delayInMilliseconds)
		{
			auto finalSpeed = -moveSpeed * dt.asMilliseconds();
			finalSpeed = eastl::clamp(finalSpeed * currentdelay / 20000, -7.f, -1.f);
			auto difference = pos.y - camera_.getCenter().y;
			if (difference < 0)
			{
				finalSpeed += difference;
			}
			camera_.move(0, finalSpeed);

		}
		/* If after moving we're still behind the player then we want to match the players speed */
		auto difference = pos.y - camera_.getCenter().y;
		if (difference < 0)
		{
			camera_.move(0, difference);
		}
		window_->setView(camera_);

		advancePlatforms();
		moveClouds();

		/* Update player status */
		if (isBelowView(pos.y))
		{
			world_->sendSystemMessage({ "gameover" });
		}
	}
	
}

void MovingCameraSystem::advancePlatforms()
{
	/* Move platforms */
	//Get platform at front
	auto nextPlatform = platformBuffer.front();

	//If it is below the screen
	/* We add the offset manualy here because hacks */
	if (isBelowView((nextPlatform->GetPosition().y * PIXELS_TO_UNITS_SCALE) - 25))
	{
		cout << "Moving from (" << nextPlatform->GetPosition().x << ", " << nextPlatform->GetPosition().y << ") to (";

		// Get the position of the platform at the end of the queue 
		auto lastPlatformPos = platformBuffer.back()->GetPosition();

		//Calculate offsets from the last position and clamp within screen bounds
		auto offsetX = eastl::clamp(lastPlatformPos.x + RandomFloat(-maxHorixzontalDistance, maxHorixzontalDistance),
			2.f, //Hard code the boundries in because I've been fucking about with the maths for too long and I'm seeing falling blocks everywhere
			36.f);
		auto offsetY = lastPlatformPos.y - RandomFloat(minVerticalDistance, maxVerticalDistance);

		//Set the new position
		nextPlatform->SetTransform(b2Vec2(offsetX, offsetY), nextPlatform->GetAngle());
		cout << nextPlatform->GetPosition().x << ", " << nextPlatform->GetPosition().y << ")" << endl;

		//Move the platform at the front to the back
		platformBuffer.pop_front();
		platformBuffer.push_back(nextPlatform);
	}
}

void MovingCameraSystem::recieveMessage(const SystemMessage& m)
{
	if(m.name == "gameover")
	{
		gameover = true;
	}
}