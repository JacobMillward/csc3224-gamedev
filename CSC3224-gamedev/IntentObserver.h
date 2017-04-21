#pragma once
#include <string>
#include <SFML\System\Vector2.hpp>

struct IntentEvent {
	int type;
	std::string name;
	bool isDown;
	sf::Vector2i pos;
};

class IntentObserver
{
public:
	virtual ~IntentObserver() {}
	virtual void onNotify(IntentEvent event) = 0;
};