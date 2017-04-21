#pragma once
#include "ISystem.h"
#include <SFML/Graphics/VertexArray.hpp>

class RenderableBuildSystem : public ISystem
{
public:
	explicit RenderableBuildSystem(World& w);
	~RenderableBuildSystem();

	void step(const sf::Time& dt) override;

protected:
	sf::VertexArray vArray_;

	static sf::Vector2f rotatePoint(sf::Vector2f& point, sf::Vector2f& origin, float angle);
};
