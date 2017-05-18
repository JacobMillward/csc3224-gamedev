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
	sf::IntRect textureRect = sf::IntRect(componentRoot.get("textureRectLeft", 0).asInt(),
	                                       componentRoot.get("textureRectTop", 0).asInt(),
	                                       componentRoot.get("textureRectWidth", 32).asInt(),
	                                       componentRoot.get("textureRectHeight", 32).asInt());
	float posX = componentRoot.get("posX", 0).asFloat();
	float posY = componentRoot.get("posY", 0).asFloat();
	float scaleX = componentRoot.get("scaleX", 1).asFloat();
	float scaleY = componentRoot.get("scaleY", 1).asFloat();
	int zOrder = componentRoot.get("z-order", 0).asInt();

	Sprite* s = new Sprite(textureID, textureRect);
	s->setPosition(posX, posY);
	s->setScale(scaleX, scaleY);
	s->setZOrder(zOrder);

	return s;
}

inline Json::Value Sprite::toJson()
{
	Json::Value root;
	root["ComType"] = static_cast<int>(this->getType());
	root["TextureID"] = textureID_;
	root["textureRectLeft"] = getTextureRect().left;
	root["textureRectTop"] = getTextureRect().top;
	root["textureRectWidth"] = getTextureRect().width;
	root["textureRectHeight"] = getTextureRect().height;
	root["posX"] = getPosition().x;
	root["posY"] = getPosition().y;
	root["scaleX"] = getScale().x;
	root["scaleY"] = getScale().y;
	root["z-order"] = getZOrder();

	return root;
}
