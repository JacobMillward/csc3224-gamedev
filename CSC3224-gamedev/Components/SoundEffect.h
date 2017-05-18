#pragma once

#include "IComponent.h"
#include "../Systems/AudioSystem.h"
#include "../json/json.h"
#include <iostream>

class SoundEffect : public IComponent<SoundEffect>
{
public:
	static const ComponentType typeID = ComponentType::AUDIO;
	ComponentType getType() override { return typeID; }
	int getTypeValue() override { return static_cast<int>(typeID); }

	static SoundEffect* buildFromJson(Json::Value componentRoot, ...);
	Json::Value toJson() override;
	explicit SoundEffect(std::string soundID) : soundId_(soundID) {}

	std::string getSoundID() const { return soundId_; }
	void play() { play_ = true; };

protected:
	friend void AudioSystem::step(const sf::Time& dt);
	bool play_ = false;
	std::string soundId_;
};

inline SoundEffect* SoundEffect::buildFromJson(Json::Value componentRoot, ...)
{
	std::string soundName = componentRoot.get("SoundID", "").asString();
	if (soundName.empty())
	{
		throw "Invalid SoundID";
	}
	return new SoundEffect(soundName);
}

inline Json::Value SoundEffect::toJson()
{
	Json::Value root;
	root["ComType"] = static_cast<int>(this->getType());
	root["SoundID"] = this->getSoundID();
	return root;
}
