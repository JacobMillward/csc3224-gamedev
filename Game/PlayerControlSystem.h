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
	const float jumpVel = 8;
	const float moveVel = 8;
	float desiredVel = 0;

	bool jump = false;
};
