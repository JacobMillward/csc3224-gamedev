#pragma once
#include "Systems/ISystem.h"
#include "Systems/PhysicsSystem.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


class MovingCameraSystem : public ISystem
{
public:
	MovingCameraSystem(World& w, sf::RenderWindow* window);
	~MovingCameraSystem();
	void step(const sf::Time& dt) override;

protected:
	sf::RenderWindow* window_;
	sf::View camera_;
	const float delayInMilliseconds = 800;
	float currentdelay = 0;
	const float moveSpeed = 1 / PIXELS_TO_UNITS_SCALE;
	;
};

