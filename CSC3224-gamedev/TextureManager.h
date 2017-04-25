#pragma once
#include <SFML/Graphics.hpp>
#include "EASTL/fixed_map.h"
#include "EASTL/fixed_vector.h"

#define MAX_TEXTURES 128
using namespace std;

/* Based on the texture manager provided at https://github.com/netpoetica/sfml-texture-manager by Keith Rosenberg */
class TextureManager
{
protected:
	// The textures that are loaded
	eastl::fixed_map<unsigned int, sf::Texture*, MAX_TEXTURES> textures;

	unsigned int textureID = 0;
	
public:

	TextureManager();
	// Destructor which deletes the textures previously loaded
	~TextureManager();

	int getLength() const;

	// Get texture by name specified in loadTexture
	sf::Texture* getTexture(unsigned int id);

	// Loads the texture and returns a pointer to it
	// If it is already loaded, this function just returns it
	// If it cannot find the file, returns nullptr
	unsigned int loadTexture(string path);
};
