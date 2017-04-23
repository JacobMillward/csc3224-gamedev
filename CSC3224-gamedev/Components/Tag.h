#pragma once
#include <string>
#include "IComponent.h"

class Tag : public IComponent<Tag>
{
public:
	static const ComponentType typeID = ComponentType::TAG;
	ComponentType getType() override { return typeID; }
	int getTypeValue() override { return static_cast<int>(typeID); }

	static Tag* buildFromJson(std::string jsonString);

	explicit Tag(std::string tagName) : tagName(tagName)
	{
	};

	std::string getTag() const { return tagName; };
	void setTag(std::string& name) { tagName = name; };

	std::string toJson() override;

protected:
	std::string tagName;
};

inline Tag* Tag::buildFromJson(std::string jsonString)
{
	//TODO: Implement buildFromJson
	return nullptr;
}

inline std::string Tag::toJson()
{
	return {};
}
