#pragma once
#include <string>
#include "IComponent.h"

class Tag : public IComponent
{
public:
	static const IComponent::Type typeID = IComponent::Type::TAG;
	Type getType() override { return typeID; }
	int getTypeValue() override { return static_cast<int>(typeID); }

	explicit Tag(std::string tagName) : tagName(tagName)
	{
	};

	std::string getTag() const { return tagName; };
	void setTag(std::string& name) { tagName = name; };

protected:
	std::string tagName;
};
