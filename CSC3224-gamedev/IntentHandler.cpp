#include "IntentHandler.h"
#include <fstream>
#include <sstream>
#include <iostream>

IntentHandler::IntentHandler()
{
	/* Set up intent maps */
	keyboardMap.reserve(sf::Keyboard::KeyCount);
	mouseMap.reserve(sf::Mouse::ButtonCount);

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
				keyboardMap.erase(sf::Keyboard::Key(keyCode));
				keyboardMap.emplace(sf::Keyboard::Key(keyCode), intent);
				break;
			
			/* Mouse */
			case 1:
				if (keyCode > sf::Mouse::ButtonCount || keyCode < 0)
				{
					std::cout << "IntentMap: Mouse code out of range. Line ("  << lineNum << ")" << std::endl;
					continue;
				}
				mouseMap.erase(sf::Mouse::Button(keyCode));
				mouseMap.emplace(sf::Mouse::Button(keyCode), intent);
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
	for (auto key : keyboardMap)
	{
		std::cout << key.first << "\t" << key.second << std::endl;
	}

	std::cout << "\nMouse" << std::endl;
	std::cout << "KeyCode\tIntent" << std::endl;
	for (auto key : mouseMap)
	{
		std::cout << key.first << "\t" << key.second << std::endl;
	}
}