#pragma once
#include "Systems/ISystem.h"
#include "Intents/IntentObserver.h"
#include "Intents/IntentHandler.h"

class PlayerControlSystem : public ISystem, public IntentObserver
{
public:
	PlayerControlSystem(World& world, IntentHandler& intentHandler);

	// Inherited via ISystem
	void step(const sf::Time& dt) override;

	// Inherited via IntentObserver
	void onNotify(IntentEvent event) override;

protected:
	float moveForce = 25.0f;
	float moveX = 0;
	float moveY = 0;
};
