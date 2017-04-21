#pragma once
#include "IntentObserver.h"
#include <EASTL\vector_map.h>
#include <EASTL\hash_map.h>
#include <EASTL\slist.h>
#include <string>
#include <SFML\Window\Keyboard.hpp>
#include <SFML\Window\Mouse.hpp>

class IntentHandler
{
public:
	enum KeyState { PRESSED, DOWN, RELEASED, UP };
	IntentHandler();
	~IntentHandler();
	void loadIntentsFromFile(std::string filePath);
	void printKeyMaps();

	void addObserver(IntentObserver* observer);
	void removeObserver(IntentObserver* observer);

	void processIntents();

protected:
	eastl::vector_map<sf::Keyboard::Key, std::string> keyboardIntentMap;
	eastl::hash_map<int, KeyState> keyboardStateMap;
	eastl::vector_map<sf::Mouse::Button, std::string> mouseIntentMap;
	eastl::hash_map<int, KeyState> mouseStateMap;
	eastl::slist<IntentObserver*> observerList;

	void updateState();
};
