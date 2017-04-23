#pragma once
#include <SFML/Graphics/Texture.hpp>
#include "IComponent.h"

class Sprite : public IComponent<Sprite>
{
public:
	/* The ComponentType of this component. */
	static const ComponentType typeID = ComponentType::RENDERABLE;
	ComponentType getType() override { return typeID; }
	int getTypeValue() override { return static_cast<int>(typeID); }

	static Sprite* buildFromJson(std::string jsonString);

	Sprite(sf::Texture texture, sf::IntRect rect) : texture_(texture), rect_(rect)
	{
	};
	sf::Texture& getTexture() { return texture_; };
	sf::FloatRect& getRect() { return rect_; };

private:
	sf::Texture texture_;
	sf::FloatRect rect_;
};

inline Sprite* Sprite::buildFromJson(std::string jsonString)
{
	//TODO: Implement buildFromJson
	return nullptr;
}
