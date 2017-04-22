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
	while (std::getline(infile, line))
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
		IntentEvent intent;
		intent.type = 0;
		intent.name = pair.second;
		intent.isDown = sf::Keyboard::isKeyPressed(pair.first);
		sendIntent(intent);
	}
	/* Mouse intents */
	for (auto pair : mouseIntentMap)
	{
		IntentEvent intent;
		intent.type = 1;
		intent.name = pair.second;
		intent.isDown = sf::Mouse::isButtonPressed(pair.first);
		intent.pos = sf::Mouse::getPosition();
		sendIntent(intent);
	}
}

void IntentHandler::sendIntent(IntentEvent intent)
{
	for (auto it = observerList.begin(), end = observerList.end(); it != end; ++it)
	{
		(*it)->onNotify(intent);
	}
}
