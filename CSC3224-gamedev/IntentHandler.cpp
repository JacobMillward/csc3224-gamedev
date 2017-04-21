#include "IntentHandler.h"
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
	int lineNum = 0;
	while (std::getline(infile, line))
	{
		lineNum++;
		if (!line.empty())
		{
			std::stringstream ss(line);
			//We only care about the first 3 tokens - lets attempt to parse them into the correct format
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
				keyboardStateMap.emplace(sf::Keyboard::Key(keyCode), KeyState::UP);
				break;
			
			/* Mouse */
			case 1:
				if (keyCode > sf::Mouse::ButtonCount || keyCode < 0)
				{
					std::cout << "IntentMap: Mouse code out of range. Line ("  << lineNum << ")" << std::endl;
					continue;
				}
				mouseIntentMap.erase(sf::Mouse::Button(keyCode));
				mouseIntentMap.emplace(sf::Mouse::Button(keyCode), intent);
				mouseStateMap.emplace(sf::Mouse::Button(keyCode), KeyState::UP);
				break;

			/* Invalid mapNumber */
			default:
				std::cout << "IntentMap: Invalid map number. Line (" << lineNum << ")" << std::endl;
				continue;
			}
		}
	}
}

void IntentHandler::printKeyMaps()
{
	std::cout << "Keyboard" << std::endl;
	std::cout << "KeyCode\tIntent" << std::endl;
	for (auto key : keyboardIntentMap)
	{
		std::cout << key.first << "\t" << key.second << std::endl;
	}

	std::cout << "\nMouse" << std::endl;
	std::cout << "KeyCode\tIntent" << std::endl;
	for (auto key : mouseIntentMap)
	{
		std::cout << key.first << "\t" << key.second << std::endl;
	}
}

void IntentHandler::addObserver(IntentObserver * observer)
{
	observerList.push_front(observer);
}

void IntentHandler::removeObserver(IntentObserver * observer)
{
	observerList.remove(observer);
}

void IntentHandler::processIntents()
{
	updateState();

	/* Notify observers of state */
	std::cout << keyboardStateMap.find(sf::Keyboard::Space)->second << std::endl;
}

void IntentHandler::updateState()
{
	/* Update state of bound keys */
	for (auto pair : keyboardIntentMap)
	{
		sf::Keyboard::Key key = pair.first;
		KeyState currentState = keyboardStateMap.find(key)->second;
		KeyState newState;
		if (sf::Keyboard::isKeyPressed(key))
		{
			switch (currentState)
			{
			case KeyState::RELEASED:
			case KeyState::UP:
				newState = KeyState::PRESSED;
				break;
			case KeyState::DOWN:
			case KeyState::PRESSED:
				newState = KeyState::DOWN;
				break;
			}
		}
		else
		{
			switch (currentState)
			{
			case KeyState::DOWN:
			case KeyState::PRESSED:
				newState = KeyState::RELEASED;
				break;
			case KeyState::RELEASED:
			case KeyState::UP:
				newState = KeyState::UP;
				break;
			
			}
		}
		
		keyboardStateMap.erase(key);
		keyboardStateMap.emplace(key, newState);
	}

	/* And again for mouse buttons */
	for (auto pair : mouseIntentMap)
	{
		sf::Mouse::Button key = pair.first;
		KeyState currentState = mouseStateMap.find(key)->second;
		KeyState newState;
		if (sf::Mouse::isButtonPressed(key))
		{
			switch (currentState)
			{
			case KeyState::RELEASED:
			case KeyState::UP:
				newState = KeyState::PRESSED;
				break;
			case KeyState::DOWN:
			case KeyState::PRESSED:
				newState = KeyState::DOWN;
				break;
			}
		}
		else
		{
			switch (currentState)
			{
			case KeyState::DOWN:
			case KeyState::PRESSED:
				newState = KeyState::RELEASED;
				break;
			case KeyState::RELEASED:
			case KeyState::UP:
				newState = KeyState::UP;
				break;

			}
		}
		mouseStateMap.erase(key);
		mouseStateMap.emplace(key, newState);
	}
}
