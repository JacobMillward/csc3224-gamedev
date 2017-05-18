#pragma once
#include "Systems/ISystem.h"
#include "Intents/IntentObserver.h"
#include "Intents/IntentHandler.h"
#include "Box2D/Dynamics/b2WorldCallbacks.h"
#include "Entity.h"

class PlayerControlSystem : public ISystem, public IntentObserver, public b2ContactListener
{
public:
	PlayerControlSystem(World& world, IntentHandler& intentHandler);

	// Inherited via ISystem
	void step(const sf::Time& dt) override;

	// Inherited via IntentObserver
	void onNotify(IntentEvent event) override;

	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
protected:
	Entity* playerEntity;
	const float jumpVel = 8;
	const float moveVel = 8;
	float desiredVel = 0;

	bool jump = false;
	bool grounded = false;
};
