#include "IntentHandler.h"
#include "IntentObserver.h"
#include <fstream>
#include <sstream>
#include <iostream>

IntentHandler::IntentHandler()
{
	/* Set up intent maps */
	keyboardIntentMap.reserve(sf::Keyboard::KeyCount);
	mouseIntentMap.reserve(sf::Mouse::ButtonCount);
}


IntentHandler::~IntentHandler()
{
}

void IntentHandler::loadIntentsFromFile(std::string filePath)
{
	std::ifstream infile(filePath);
	int mapNumber, keyCode;
	std::string intent;

	//Get Line from file
	std::string line;
	auto lineNum = 0;
	while (getline(infile, line))
	{
		lineNum++;
		if (!line.empty())
		{
			std::stringstream ss(line);
			//We only care about the first 4 tokens - lets attempt to parse them into the correct format
			if (((ss >> mapNumber).fail())
				|| (ss >> keyCode).fail()
				|| (ss >> intent).fail())
			{
				//Malformed line, do nothing
				std::cout << "IntentMap: Malformed line (" << lineNum << ")" << std::endl;
				continue;
			}

			//Turn keyCode into correct type
			switch (mapNumber)
			{
				/* Keyboard  */
			case 0:
				if (keyCode > sf::Keyboard::KeyCount || keyCode < 0)
				{
					std::cout << "IntentMap: Keyboard code out of range. Line (" << lineNum << ")" << std::endl;
					continue;
				}
				keyboardIntentMap.erase(sf::Keyboard::Key(keyCode));
				keyboardIntentMap.emplace(sf::Keyboard::Key(keyCode), intent);
				break;

				/* Mouse */
			case 1:
				if (keyCode > sf::Mouse::ButtonCount || keyCode < 0)
				{
					std::cout << "IntentMap: Mouse code out of range. Line (" << lineNum << ")" << std::endl;
					continue;
				}
				mouseIntentMap.erase(sf::Mouse::Button(keyCode));
				mouseIntentMap.emplace(sf::Mouse::Button(keyCode), intent);
				break;

				/* Invalid mapNumber */
			default:
				std::cout << "IntentMap: Invalid map number. Line (" << lineNum << ")" << std::endl;
			}
		}
	}
}

void IntentHandler::printKeyMaps()
{
	std::cout << "Keyboard" << std::endl;
	std::cout << "KeyCode\tIntent" << std::endl;
	for (auto pair : keyboardIntentMap)
	{
		std::cout << pair.first << "\t" << pair.second << std::endl;
	}

	std::cout << "\nMouse" << std::endl;
	std::cout << "KeyCode\tIntent" << std::endl;
	for (auto pair : mouseIntentMap)
	{
		std::cout << pair.first << "\t" << pair.second << std::endl;
	}
}

void IntentHandler::addObserver(IntentObserver* observer)
{
	observerList.push_front(observer);
}

void IntentHandler::removeObserver(IntentObserver* observer)
{
	observerList.remove(observer);
}

void IntentHandler::processIntents()
{
	/* Keyboard intents */
	for (auto pair : keyboardIntentMap)
	{
		auto key = pair.first;
		State currentState;
		//If we have a previous state
		if(keyboardState.count(key) > 0)
		{
			currentState = advanceState(keyboardState[key], sf::Keyboard::isKeyPressed(key));
		}
		//Otherwise we assume it was up
		else
		{
			currentState = advanceState(State::UP, sf::Keyboard::isKeyPressed(key));
		}
		keyboardState[key] = currentState;

		IntentEvent intent{0, pair.second, currentState};
		sendIntent(intent);
	}

	/* Mouse intents */
	for (auto pair : mouseIntentMap)
	{
		auto button = pair.first;
		State currentState;
		//If we have a previous state
		if (mouseState.count(button) > 0)
		{
			currentState = advanceState(mouseState[button], sf::Mouse::isButtonPressed(button));
		}
		//Otherwise we assume it was up
		else
		{
			currentState = advanceState(State::UP, sf::Mouse::isButtonPressed(button));
		}
		mouseState[button] = currentState;

		IntentEvent intent{ 1, pair.second, currentState, sf::Mouse::getPosition() };
		sendIntent(intent);
	}
}

State IntentHandler::advanceState(State current, bool isPressed)
{
	//Update new state based on old
	State newState;
	switch (current)
	{
	case State::PRESSED:
	case State::DOWN:
		{
			if (isPressed)
				newState = State::DOWN;
			else
				newState = State::RELEASED;
			break;
		}
	case State::RELEASED:
	case State::UP:
		{
			if (isPressed)
				newState = State::PRESSED;
			else
				newState = State::UP;
			break;
		}
	default:
		newState = State::UP;
	}

	return newState;
}

void IntentHandler::sendIntent(IntentEvent intent)
{
	for (auto it = observerList.begin(), end = observerList.end(); it != end; ++it)
	{
		(*it)->onNotify(intent);
	}
}
