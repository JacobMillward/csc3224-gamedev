#include "RenderableBuildSystem.h"
#include "../World.h"
#include "../Components/Sprite.h"
#include <EASTL/sort.h>

RenderableBuildSystem::RenderableBuildSystem(World& w) : ISystem(w)
{
}

RenderableBuildSystem::~RenderableBuildSystem()
{
}

/* At the moment this just assumes every sprite is using the same texture. */
//TODO: Fix this to use multiple textures
void RenderableBuildSystem::step(const sf::Time& dt)
{
	auto list = this->world_->getEntityManager().getComponentList(ComponentType::SPRITE);
	/* Sort list by z layering */
	eastl::quick_sort(list->begin(), list->end(), [](ComponentVector::value_type a, ComponentVector::value_type b)
	                  {
		                  return a.second->getSprite()->getZOrder() < b.second->getSprite()->getZOrder();
	                  });

	for (auto pair : *list)
	{
		auto sprite = static_cast<Sprite*>(pair.first);
		this->world_->drawables_.push_back(sprite);
	}
}