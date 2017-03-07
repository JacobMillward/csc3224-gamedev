#pragma once
#include <SFML\Graphics\Texture.hpp>
#include "IComponent.h"

class Sprite : public IComponent
{
public:
	/* The IComponent::Type of this component. */
	static const IComponent::Type typeID = IComponent::Type::Renderable;
	Type getType() override { return typeID; }

	Sprite(sf::Texture texture, sf::IntRect rect) : texture_(texture), rect_(rect) {};
	sf::Texture& getTexture() { return texture_; };
	sf::IntRect& getRect() { return rect_; };

private:
	sf::Texture texture_;
	sf::IntRect rect_;
};