#pragma once
#include "IntentObserver.h"
#include <EASTL\vector_map.h>
#include <string>
#include <SFML\Window\Keyboard.hpp>
#include <SFML\Window\Mouse.hpp>

class IntentHandler
{
public:
	IntentHandler();
	~IntentHandler();
	void loadIntentsFromFile(std::string filePath);
	void printKeyMaps();

protected:
	eastl::vector_map<sf::Keyboard::Key, std::string> keyboardMap;
	eastl::vector_map<sf::Mouse::Button, std::string> mouseMap;
};

