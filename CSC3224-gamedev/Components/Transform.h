#pragma once
#include "IComponent.h"
#include <SFML/System/Vector3.hpp>

class Transform : public IComponent
{
public:
	/* The IComponent::Type of this component. */
	static const IComponent::Type typeID = IComponent::Type::TRANSFORM;
	Type getType() override { return typeID; }
	const int getTypeValue() override { return static_cast<int>(typeID); }

	Transform(sf::Vector3f& pos) : transform_(pos) {}
	Transform(float x, float y, float z) : transform_(sf::Vector3f(x, y, z)) {}
	~Transform() {}
	sf::Vector3f& get() { return transform_; }

protected:
	sf::Vector3f transform_;
};
