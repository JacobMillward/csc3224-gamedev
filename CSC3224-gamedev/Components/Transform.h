#pragma once
#include "IComponent.h"
#include <SFML/System/Vector3.hpp>
#include <SFML\Graphics\Transformable.hpp>

class Transform : public IComponent, public sf::Transformable
{
public:
	/* The IComponent::Type of this component. */
	static const IComponent::Type typeID = IComponent::Type::TRANSFORM;
	Type getType() override { return typeID; }
	const int getTypeValue() override { return static_cast<int>(typeID); }

	Transform(sf::Vector2f& pos = sf::Vector2f(0.0f,0.0f), float rotation = 0.0f, sf::Vector2f& scale = sf::Vector2f(1.0f, 1.0f), sf::Vector2f& origin = sf::Vector2f(0.0f, 0.0f)) {
		setPosition(pos);
		setRotation(rotation);
		setScale(scale);
		setOrigin(origin);
		zorder_ = 0;
	}
	~Transform() {}
	int getZOrder() { return zorder_; }
	void setZOrder(int z) { zorder_ = z; }

protected:
	int zorder_;
};
