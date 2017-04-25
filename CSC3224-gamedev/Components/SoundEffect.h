#pragma once

#include "IComponent.h"
#include "../Systems/AudioSystem.h"

class SoundEffect : public IComponent<SoundEffect>
{
public:
	static const ComponentType typeID = ComponentType::TAG;
	ComponentType getType() override { return typeID; }
	int getTypeValue() override { return static_cast<int>(typeID); }

	static SoundEffect* buildFromJson(std::string jsonString);
	std::string toJson() override;
	explicit SoundEffect(std::string soundID) : soundId_(soundID) {}

	std::string getSoundID() const { return soundId_; }
	void play() { play_ = true; };

protected:
	friend void AudioSystem::step(const sf::Time& dt);
	bool play_ = false;
	std::string soundId_;
};

inline SoundEffect* SoundEffect::buildFromJson(std::string jsonString)
{
	//TODO: Implement buildFromJson
	return nullptr;
}

inline std::string SoundEffect::toJson()
{
	return {};
}
