#pragma once
#include <string>

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