#include "TextureManager.h"

TextureManager::TextureManager() : textures(), order()
{
}

// Get Length of Textures Array
int TextureManager::getLength() const
{
	return textures.size();
}

// Get Texture by Name
sf::Texture* TextureManager::getTexture(string name)
{
	auto textureIt = textures.find(name);
	// See if we have already loaded this texture
	if (textureIt != textures.end())
	{
		return textureIt->second;
	}
	throw "No such texture exists";
}

// Get Texture by Index
sf::Texture* TextureManager::getTexture(int index)
{
	// Stay DRY and reuse get by name, but get string name from vector with index
	return getTexture(order.at(index));
}

// Assign a Texture a Name (for accessing via get) and path (to load from)
sf::Texture* TextureManager::loadTexture(string name, string path)
{
	// Haven't loaded it yet, time to create it
	auto texture = new sf::Texture();

	if (texture->loadFromFile(path))
	{
		textures.emplace(name, texture);

		// Push to vector the order in which items were loaded into map, for accessing via index.
		order.push_back(name);
		return texture;
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
