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

	Sprite(unsigned int textureID, sf::IntRect rect) : textureID_(textureID)
	{
		setTextureRect(rect);
	};

	unsigned int getTextureID() const { return textureID_; };
	void setZOrder(int order) { zOrder_ = order; };
	int getZOrder() const { return zOrder_; };

	std::string toJson() override;

private:
	unsigned int textureID_;
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
