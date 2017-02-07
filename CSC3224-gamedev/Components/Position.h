#pragma once
#include "IComponent.h"
#include <SFML/System/Vector3.hpp>

class Position : public IComponent
{
public:
	/* The IComponent::Type of this component. */
	static const IComponent::Type typeID = IComponent::Type::Position;

	Position(sf::Vector3f& pos) : position_(&pos) {}
	Position(float x, float y, float z) : position_(new sf::Vector3f(x, y, z)) {}
	~Position()
	{
		delete position_;
	}
	sf::Vector3f& getPosition() const { return *position_; }
	const float& X() const { return position_->x; }
	const float& Y() const { return position_->y; }
	const float& Z() const { return position_->z; }

private:
	sf::Vector3f *position_;
};
