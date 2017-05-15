#pragma once
#include "IComponent.h"
#include "../json/json.h"

class Tag : public IComponent<Tag>
{
public:
	static const ComponentType typeID = ComponentType::TAG;
	ComponentType getType() override { return typeID; }
	int getTypeValue() override { return static_cast<int>(typeID); }

	static Tag* buildFromJson(Json::Value componentRoot, ...);

	explicit Tag(std::string tagName) : tagName(tagName)
	{
	};

	std::string getTag() const { return tagName; };
	void setTag(std::string& name) { tagName = name; };

	Json::Value toJson() override;

protected:
	std::string tagName;
};

inline Tag* Tag::buildFromJson(Json::Value componentRoot, ...)
{
	std::string tagName = componentRoot.get("TagName", "").asString();
	if (tagName.empty())
	{
		throw "Invalid TagName";
	}
	return new Tag(tagName);
}

inline Json::Value Tag::toJson()
{
	Json::Value tag;
	tag["TagName"] = this->getTag();
	return tag;
}
