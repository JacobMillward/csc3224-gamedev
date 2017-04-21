#pragma once
#include <SFML\Graphics\Texture.hpp>
#include "IComponent.h"

class Sprite : public IComponent
{
public:
	/* The IComponent::Type of this component. */
	static const IComponent::Type typeID = IComponent::Type::RENDERABLE;
	Type getType() override { return typeID; }
	const int getTypeValue() override { return static_cast<int>(typeID); }

	Sprite(sf::Texture texture, sf::IntRect rect) : texture_(texture), rect_(rect) {};
	sf::Texture& getTexture() { return texture_; };
	sf::FloatRect& getRect() { return rect_; };

private:
	sf::Texture texture_;
	sf::FloatRect rect_;
};