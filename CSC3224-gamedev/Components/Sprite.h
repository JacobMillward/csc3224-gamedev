#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "IComponent.h"
#include <string>

class Sprite : public IComponent<Sprite>, public sf::Sprite
{
public:
	/* The ComponentType of this component. */
	static const ComponentType typeID = ComponentType::SPRITE;
	ComponentType getType() override { return typeID; }
	int getTypeValue() override { return static_cast<int>(typeID); }

	static Sprite* buildFromJson(std::string jsonString);
	std::string toJson() override;

	Sprite(sf::Texture& texture, sf::IntRect rect)
	{
		setTexture(texture);
		setTextureRect(rect);
	};

	void setZOrder(int order) { zOrder_ = order; };
	int getZOrder() const { return zOrder_; };

	

private:
	int zOrder_;
};

inline Sprite* Sprite::buildFromJson(std::string jsonString)
{
	//TODO: Implement buildFromJson
	return nullptr;
}

inline std::string Sprite::toJson()
{
	return {};
}
