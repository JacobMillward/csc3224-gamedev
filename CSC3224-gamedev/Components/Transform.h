#pragma once
#include "IComponent.h"
#include <SFML/Graphics/Transformable.hpp>

class Transform : public IComponent<Transform>, public sf::Transformable
{
public:
	/* The ComponentType of this component. */
	static const ComponentType typeID = ComponentType::TRANSFORM;
	ComponentType getType() override { return typeID; }
	int getTypeValue() override { return static_cast<int>(typeID); }

	static Transform* buildFromJson(std::string jsonString);

	explicit Transform(sf::Vector2f& pos = sf::Vector2f(0.0f, 0.0f), float rotation = 0.0f, sf::Vector2f& scale = sf::Vector2f(1.0f, 1.0f), sf::Vector2f& origin = sf::Vector2f(0.0f, 0.0f))
	{
		setPosition(pos);
		setRotation(rotation);
		setScale(scale);
		setOrigin(origin);
		zorder_ = 0;
	}

	~Transform()
	{
	}

	int getZOrder() const { return zorder_; }
	void setZOrder(int z) { zorder_ = z; }

	std::string toJson() override;

protected:
	int zorder_;
};

inline Transform* Transform::buildFromJson(std::string jsonString)
{
	//TODO: Implement buildFromJson
	return nullptr;
}

inline std::string Transform::toJson()
{
	return {};
}
