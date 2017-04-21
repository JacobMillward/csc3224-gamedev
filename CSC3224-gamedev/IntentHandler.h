#pragma once
#include "IntentObserver.h"
#include <EASTL/vector_map.h>
#include <EASTL/slist.h>
#include <string>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

class IntentHandler
{
public:
	IntentHandler();
	~IntentHandler();
	void loadIntentsFromFile(std::string filePath);
	void printKeyMaps();

	void addObserver(IntentObserver* observer);
	void removeObserver(IntentObserver* observer);

	void processIntents();

protected:
	eastl::vector_map<sf::Keyboard::Key, std::string> keyboardIntentMap;
	eastl::vector_map<sf::Mouse::Button, std::string> mouseIntentMap;
	eastl::slist<IntentObserver*> observerList;
	void sendIntent(IntentEvent intent);
};
