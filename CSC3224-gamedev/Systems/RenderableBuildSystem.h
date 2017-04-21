#pragma once
#include "ISystem.h"
#include <SFML\Graphics\VertexArray.hpp>

class RenderableBuildSystem : public ISystem
{
public:
	RenderableBuildSystem(World& w);
	~RenderableBuildSystem();

	void step(const sf::Time& dt) override;

protected:
	sf::VertexArray vArray_;

	sf::Vector2f rotatePoint(sf::Vector2f& point, sf::Vector2f& origin, float angle);
};