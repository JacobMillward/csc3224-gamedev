#include "TextureManager.h"

TextureManager::TextureManager() : textures()
{
}

// Get Length of Textures Array
int TextureManager::getLength() const
{
	return textures.size();
}

// Get Texture by Name
sf::Texture* TextureManager::getTexture(unsigned int id)
{
	auto textureIt = textures.find(id);
	// See if we have already loaded this texture
	if (textureIt != textures.end())
	{
		return textureIt->second;
	}
	throw "No such texture exists";
}

// Assign a Texture a Name (for accessing via get) and path (to load from)
unsigned int TextureManager::loadTexture(string path)
{
	// Haven't loaded it yet, time to create it
	auto texture = new sf::Texture();

	if (texture->loadFromFile(path))
	{
		auto id = textureID++;
		textures.emplace(id, texture);
		return id;
	}

	// Could not load the file
	delete texture;
	throw "Error creating texture";
}

TextureManager::~TextureManager()
{
	for (auto pair : textures)
	{
		delete pair.second;
	}
}
