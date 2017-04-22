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
	eastl::fixed_map<string, sf::Texture*, MAX_TEXTURES> textures;

	// Manually keep track of the order in which textures were loaded, so you can get by index.
	eastl::fixed_vector<string, MAX_TEXTURES> order;
	
public:

	TextureManager();
	// Destructor which deletes the textures previously loaded
	~TextureManager();

	int getLength() const;

	// Get texture by name specified in loadTexture
	sf::Texture* getTexture(string name);

	// Get texutre by index in map
	sf::Texture* getTexture(int index);

	// Loads the texture and returns a pointer to it
	// If it is already loaded, this function just returns it
	// If it cannot find the file, returns nullptr
	sf::Texture* loadTexture(string name, string path);
};
