#pragma once
#include <string>

struct IntentEvent {
	std::string Intent;

};
class IntentObserver
{
public:
	virtual ~IntentObserver() {}
	virtual void onNotify(IntentEvent event) = 0;
};