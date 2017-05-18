#pragma once
#include "Systems/ISystem.h"
#include "Systems/PhysicsSystem.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include "Entity.h"
#include <queue>
#include <iostream>

/*
 * Possibly the most inefficient class I've ever made, with hacks galore. I am ashamed to call this my work :(
 */
class MovingCameraSystem : public ISystem
{
public:
	MovingCameraSystem(World& w, sf::RenderWindow* window, Json::Value platformConfig);
	~MovingCameraSystem();
	void moveClouds() const;
	void step(const sf::Time& dt) override;
	void advancePlatforms();
protected:
	sf::RenderWindow* window_;
	sf::View camera_;
	Entity* playerEntity;
	const float delayInMilliseconds = 2000;
	float currentdelay = 0;
	const float moveSpeed = 1/ PIXELS_TO_UNITS_SCALE;
	Json::Value platformConfig;
	bool gameover = false;
	/* eastl::queue is broken right now */
	std::deque<b2Body*> platformBuffer;

	const float maxVerticalDistance = 85.f / PIXELS_TO_UNITS_SCALE;
	const float minVerticalDistance = 75.f / PIXELS_TO_UNITS_SCALE;
	const float maxHorixzontalDistance = 100.f / PIXELS_TO_UNITS_SCALE;
	const float minHorixzontalDistance = 40.f / PIXELS_TO_UNITS_SCALE;

	bool isBelowView(float y) const
	{
		auto bottom = camera_.getCenter().y + (camera_.getSize().y / 2);
		return (y-bottom) > 0;
	}

public:
	void recieveMessage(const SystemMessage& m) override;
};

/* Generates a random float between a and b. Assumes a < b */
inline float RandomFloat(float a, float b)
{
	float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	float diff = b - a;
	float r = random * diff;
	return a + r;
}