#pragma once
#include "ISystem.h"
#include <SFML/Audio/SoundBuffer.hpp>
#include "EASTL/fixed_vector.h"

class SoundEffect;
class ResourceManager;

class AudioSystem : public ISystem
{
public:
	AudioSystem(World& w, ResourceManager& resourceManager);
	~AudioSystem();
	void step(const sf::Time& dt) override;

	void recieveMessage(const SystemMessage& m) override
	{
	};

protected:
	ResourceManager* resourcemanager_;
	/* We're only allowing 20 concurrent sounds by default */
	eastl::fixed_vector<std::pair<sf::Sound*, SoundEffect*>, 20> playingSounds_;
};

