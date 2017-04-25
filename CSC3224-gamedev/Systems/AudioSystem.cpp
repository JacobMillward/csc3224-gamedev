#include "AudioSystem.h"
#include "../World.h"
#include "../Components/SoundEffect.h"
#include "../ResourceManager.h"
#include <SFML/Audio/Sound.hpp>
#include <iostream>


AudioSystem::AudioSystem(World& w, ResourceManager& resourceManager) : ISystem(w), resourcemanager_(&resourceManager)
{
}


AudioSystem::~AudioSystem()
{
}

void AudioSystem::step(const sf::Time& dt)
{
	auto list = world_->getEntityManager().getComponentList(ComponentType::AUDIO);

	for (auto pair : *list)
	{
		
		auto soundEffect = static_cast<SoundEffect*>(pair.first);
		if (soundEffect->play_)
		{
			auto sound = new sf::Sound();
			sound->setBuffer(*resourcemanager_->getSound(soundEffect->getSoundID()));
			sound->play();
			soundEffect->play_ = false;
			playingSounds_.push_back(make_pair(sound, soundEffect));
		}
	}

	/* Clean up any sounds that are no longer playing */
	for (auto soundIt = playingSounds_.begin(), end = playingSounds_.end(); soundIt != end; ++soundIt)
	{
		if((*soundIt).first->getStatus() == sf::SoundSource::Stopped)
		{
			delete (*soundIt).first;
			playingSounds_.erase(soundIt);
		}
	}
}
