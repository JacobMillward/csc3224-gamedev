#pragma once
#include <string>
#include "IntentHandler.h"

enum class State
{
	PRESSED,
	DOWN,
	RELEASED,
	UP
};

struct IntentEvent
{
	int type;
	std::string name;
	State state;
	sf::Vector2i pos;
};

class IntentObserver
{
public:
	explicit IntentObserver(IntentHandler& intentHandler) : intentHandler_(&intentHandler) { intentHandler_->addObserver(this); };
	virtual ~IntentObserver() { intentHandler_->removeObserver(this); };
	virtual void onNotify(IntentEvent intent) = 0;

protected:
	IntentHandler* intentHandler_;
};

/* Compile-time string hashing */
constexpr unsigned int str2int(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}
