#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "IComponent.h"
#include <string>
#include "../json/json.h"
#include "../ResourceManager.h"

class Sprite : public IComponent<Sprite>, public sf::Sprite
{
public:
	/* The ComponentType of this component. */
	static const ComponentType typeID = ComponentType::SPRITE;
	ComponentType getType() override { return typeID; }
	int getTypeValue() override { return static_cast<int>(typeID); }

	static Sprite*buildFromJson(Json::Value componentRoot);
	Json::Value toJson() override;

	Sprite(std::string textureID, sf::IntRect rect) : textureID_(textureID)
	{
		setTextureRect(rect);
	};

	void setZOrder(int order) { zOrder_ = order; };
	int getZOrder() const { return zOrder_; };

	std::string getTextureID() const { return textureID_; }
	

private:
	int zOrder_;
	std::string textureID_;
};

inline Sprite* Sprite::buildFromJson(Json::Value componentRoot)
{
	//TODO: Implement buildFromJson
	return nullptr;
}

inline Json::Value Sprite::toJson()
{
	Json::Value root;
	root["TextureID"] = textureID_;
	root["posX"] = getPosition().x;
	root["posY"] = getPosition().y;
	root["scaleX"] = getScale().x;
	root["scaleY"] = getScale().y;

	return root;
}
