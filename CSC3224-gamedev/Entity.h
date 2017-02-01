#pragma once
#include <vector>
#include "Component.h"

using namespace std;

class Entity
{
public:
	Entity(uint32_t id);
	~Entity();

	uint32_t getID() const;
	void addComponent(const Component& c) const;
	void removeComponent(Component& c) const;

private:
	uint32_t id_;
};
