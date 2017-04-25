#include "ResourceManager.h"
#include <SFML/Audio/Sound.hpp>

ResourceManager::ResourceManager() : textures_()
{
}

// Get Texture by Name
sf::Texture* ResourceManager::getTexture(std::string name)
{
	auto textureIt = textures_.find(name);
	// See if we have already loaded this texture
	if (textureIt != textures_.end())
	{
		return textureIt->second;
	}
	throw "No such texture exists";
}

//Get soundbuffer by name
sf::SoundBuffer* ResourceManager::getSound(std::string name)
{
	auto soundIt = sounds_.find(name);
	// See if we have already loaded this sound
	if (soundIt != sounds_.end())
	{
		return soundIt->second;
	}
	throw "No such sound exists";
}

// Assign a Texture a Name (for accessing via get) and path (to load from)
sf::Texture* ResourceManager::loadTexture(std::string name, std::string path)
{
	auto t = textures_.find(name);
	if (t != textures_.end())
	{
		return t->second;
	}

	// Haven't loaded it yet, time to create it
	auto texture = new sf::Texture();
	if (texture->loadFromFile(path))
	{
		textures_.emplace(name, texture);
		return texture;
	}

	// Could not load the file
	delete texture;
	throw "Error creating texture";
}

sf::SoundBuffer* ResourceManager::loadSound(std::string name, std::string path)
{
	auto s = sounds_.find(name);
	if (s != sounds_.end())
	{
		return s->second;
	}

	// Haven't loaded it yet, time to create it
	auto soundBuffer = new sf::SoundBuffer();
	if (soundBuffer->loadFromFile(path))
	{
		sounds_.emplace(name, soundBuffer);
		return soundBuffer;
	}

	// Could not load the file
	delete soundBuffer;
	throw "Error creating SoundBuffer";
}

ResourceManager::~ResourceManager()
{
	for (auto pair : textures_)
	{
		delete pair.second;
	}
}
