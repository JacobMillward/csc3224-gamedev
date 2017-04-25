#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "EASTL/fixed_map.h"

#define MAX_TEXTURES 128
#define MAX_SOUNDS 512;

class ResourceManager
{
protected:
	// The textures_ that are loaded
	eastl::fixed_map<std::string, sf::Texture*, MAX_TEXTURES> textures_;
	eastl::fixed_map<std::string, sf::SoundBuffer*, MAX_TEXTURES> sounds_;
	
public:

	ResourceManager();
	// Destructor which deletes the textures_ previously loaded
	~ResourceManager();

	// Get texture by id
	sf::Texture* getTexture(std::string name);
	sf::SoundBuffer* getSound(std::string name);

	// Loads the texture and returns a pointer to it and its id
	// If it is already loaded, this function just returns it
	sf::Texture* loadTexture(std::string name, std::string path);

	//Loads the sound and returns a pointer to it and it's id
	// If it is already loaded, this function just returns it
	sf::SoundBuffer* loadSound(std:: string name, std::string path);
};
