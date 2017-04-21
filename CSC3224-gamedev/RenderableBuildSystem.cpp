#include "Systems/RenderableBuildSystem.h"
#include "World.h"
#include "Components/Sprite.h"
#include <EASTL\sort.h>
#define _USE_MATH_DEFINES
#include <math.h>

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
	/* Sort list by z layering */
	eastl::quick_sort(list->begin(), list->end(), [](ComponentVector::value_type a, ComponentVector::value_type b) {
		return a.second->getTransform()->getZOrder() < b.second->getTransform()->getZOrder();
	});
	vArray_.resize(list->size() * 4);

	/* Create quads */
	int quadIndex = 0;
	for (auto pair : *list)
	{
		auto transform = pair.second->getTransform();
		auto rect = static_cast<Sprite*>(pair.first)->getRect();
		auto pos = transform->getPosition();
		auto origin = transform->getOrigin();
		auto rotation = transform->getRotation();
		auto scale = transform->getScale();

		/* Calculate positions*/
		auto topLeft = sf::Vector2f(pos.x + rect.left,
			pos.y + rect.top) - origin;
		auto topRight = sf::Vector2f(pos.x + rect.left + rect.width,
			pos.y + rect.top) - origin;
		auto bottomLeft = sf::Vector2f(pos.x + rect.left + rect.width,
			pos.y + rect.top + rect.height) - origin;
		auto bottomRight = sf::Vector2f(pos.x + rect.left,
			pos.y + rect.top + rect.height) - origin;
		
		auto absoluteOrigin = topLeft + origin;

		/* Apply scaling */
		topLeft = sf::Vector2f((absoluteOrigin.x + topLeft.x)*scale.x, (absoluteOrigin.y + topLeft.y)*scale.y);
		topRight = sf::Vector2f((absoluteOrigin.x + topRight.x)*scale.x, (absoluteOrigin.y + topRight.y)*scale.y);
		bottomLeft = sf::Vector2f((absoluteOrigin.x + bottomLeft.x)*scale.x, (absoluteOrigin.y + bottomLeft.y)*scale.y);
		bottomRight = sf::Vector2f((absoluteOrigin.x + bottomRight.x)*scale.x, (absoluteOrigin.y + bottomRight.y)*scale.y);

		/* Create quad vertices and rotate points if needed*/
		vArray_[quadIndex].position = rotatePoint(topLeft, absoluteOrigin, rotation);
		vArray_[quadIndex + 1].position = rotatePoint(topRight, absoluteOrigin, rotation);
		vArray_[quadIndex + 2].position = rotatePoint(bottomLeft, absoluteOrigin, rotation);
		vArray_[quadIndex + 3].position = rotatePoint(bottomRight, absoluteOrigin, rotation);

		/* Create quad texture coordinates (non-normalised) */
		vArray_[quadIndex].texCoords = sf::Vector2f(rect.left, rect.top);
		vArray_[quadIndex + 1].texCoords = sf::Vector2f(rect.left + rect.width, rect.top);
		vArray_[quadIndex + 2].texCoords = sf::Vector2f(rect.left + rect.width, rect.top + rect.height);
		vArray_[quadIndex + 3].texCoords = sf::Vector2f(rect.left, rect.top + rect.height);

		/* To the next quad! */
		quadIndex += 4;
	}
	
	/* Replace drawables list with new one */
	//TODO: Optimise all this copying every frame
	this->world_->clearDrawables();
	vector<pair<sf::VertexArray, sf::Texture>> m;
	m.push_back(make_pair(vArray_, static_cast<Sprite*>(list->at(0).first)->getTexture()));
	this->world_->addDrawables(m);
}

sf::Vector2f RenderableBuildSystem::rotatePoint(sf::Vector2f & point, sf::Vector2f & origin, float angle)
{
	if (angle == 0)
	{
		return point;
	}

	angle = angle * (M_PI / 180.0f); // Convert to radians
	auto rotatedX = cosf(angle) * (point.x - origin.x) - sinf(angle) * (point.y - origin.y) + origin.x;
	auto rotatedY = sinf(angle) * (point.x - origin.x) + cosf(angle) * (point.y - origin.y) + origin.y;

	return sf::Vector2f(rotatedX, rotatedY);
}
