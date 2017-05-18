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

	static Sprite* buildFromJson(Json::Value componentRoot, ...);
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

inline Sprite* Sprite::buildFromJson(Json::Value componentRoot, ...)
{
	//TODO: Implement buildFromJson
	std::string textureID = componentRoot.get("TextureID", "").asString();
	sf::IntRect textureRect = sf::IntRect(componentRoot.get("TextureRectLeft", 0).asInt(),
	                                       componentRoot.get("TextureRectTop", 0).asInt(),
	                                       componentRoot.get("TextureRectWidth", 32).asInt(),
	                                       componentRoot.get("TextureRectHeight", 32).asInt());
	float posX = componentRoot.get("PosX", 0).asFloat();
	float posY = componentRoot.get("PosY", 0).asFloat();
	auto originX = componentRoot.get("OriginX", 0).asFloat();
	auto originY = componentRoot.get("OriginY", 0).asFloat();
	float scaleX = componentRoot.get("ScaleX", 1).asFloat();
	float scaleY = componentRoot.get("ScaleY", 1).asFloat();
	int zOrder = componentRoot.get("z-Order", 0).asInt();

	Sprite* s = new Sprite(textureID, textureRect);
	s->setPosition(posX, posY);
	s->setOrigin(originX, originY);
	s->setScale(scaleX, scaleY);
	s->setZOrder(zOrder);

	return s;
}

inline Json::Value Sprite::toJson()
{
	Json::Value root;
	root["ComType"] = static_cast<int>(this->getType());
	root["TextureID"] = textureID_;
	root["TextureRectLeft"] = getTextureRect().left;
	root["TextureRectTop"] = getTextureRect().top;
	root["TextureRectWidth"] = getTextureRect().width;
	root["TextureRectHeight"] = getTextureRect().height;
	root["PosX"] = getPosition().x;
	root["PosY"] = getPosition().y;
	root["OriginX"] = getOrigin().x;
	root["OriginY"] = getOrigin().y;
	root["ScaleX"] = getScale().x;
	root["ScaleY"] = getScale().y;
	root["Z-Order"] = getZOrder();

	return root;
}
