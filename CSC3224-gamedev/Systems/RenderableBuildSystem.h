#pragma once
#include "ISystem.h"

class RenderableBuildSystem : public ISystem
{
public:
	explicit RenderableBuildSystem(World& w);
	~RenderableBuildSystem();

	void step(const sf::Time& dt) override;

	void recieveMessage(const SystemMessage& m) override
	{
	};
};
