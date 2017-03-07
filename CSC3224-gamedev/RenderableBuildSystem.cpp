#include "Systems/RenderableBuildSystem.h"
#include "World.h"
#include "Components/Sprite.h"

RenderableBuildSystem::RenderableBuildSystem(World & w) : ISystem(w)
{
	vArray_ = sf::VertexArray(sf::Quads);
}

RenderableBuildSystem::~RenderableBuildSystem()
{
	//delete vArray_;
}

void RenderableBuildSystem::step(const sf::Time & dt)
{
	auto list = this->world_->getEntityManager().getComponentList(IComponent::Type::Renderable);
	vArray_.resize(list->size() * 4);

	int quadIndex = 0;
	for (auto pair : *list)
	{
		auto rect = static_cast<Sprite*>(pair.first)->getRect();
		auto pos = pair.second->getPosition();
		/* Create quad vertices */
		vArray_[quadIndex].position = sf::Vector2f(pos->X() + rect.left, pos->Y() + rect.top);
		vArray_[quadIndex + 1].position = sf::Vector2f(pos->X() + rect.left + rect.width, pos->Y() + rect.top);
		vArray_[quadIndex + 2].position = sf::Vector2f(pos->X() + rect.left + rect.width, pos->Y() + rect.top + rect.height);
		vArray_[quadIndex + 3].position = sf::Vector2f(pos->X() + rect.left, pos->Y() + rect.top + rect.height);

		/* Create quad texture coordinates (non-normalised) */
		vArray_[quadIndex].texCoords = sf::Vector2f(rect.left, rect.top);
		vArray_[quadIndex + 1].texCoords = sf::Vector2f(rect.left + rect.width, rect.top);
		vArray_[quadIndex + 2].texCoords = sf::Vector2f(rect.left + rect.width, rect.top + rect.height);
		vArray_[quadIndex + 3].texCoords = sf::Vector2f(rect.left, rect.top + rect.height);

		/* To the next quad! */
		quadIndex += 4;
	}
	

	this->world_->setVertexArray(vArray_);
}
