#pragma once
#include <EASTL/vector_map.h>
#include <EASTL/slist.h>
#include <string>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

enum class State;
struct IntentEvent;
class IntentObserver;

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
	eastl::vector_map<sf::Keyboard::Key, State> keyboardState;
	eastl::vector_map<sf::Mouse::Button, std::string> mouseIntentMap;
	eastl::vector_map<sf::Mouse::Button, State> mouseState;
	eastl::slist<IntentObserver*> observerList;
	static State advanceState(State current, bool isPressed);
	void sendIntent(IntentEvent intent);
};
