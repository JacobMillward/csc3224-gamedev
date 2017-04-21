#pragma once
#include "Systems\ISystem.h"
#include "IntentHandler.h"

class PlayerControlSystem : public ISystem, public IntentObserver
{
public:
	PlayerControlSystem(World& world, IntentHandler& intentHandler);
	~PlayerControlSystem();

	// Inherited via ISystem
	virtual void step(const sf::Time & dt) override;

	// Inherited via IntentObserver
	virtual void onNotify(IntentEvent event) override;

protected:
	IntentHandler* intentHandler;
	float moveSpeed = 100.0f;
	float moveX = 0;
	float moveY = 0;
};
