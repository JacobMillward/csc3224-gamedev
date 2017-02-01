#pragma once
#include <vector>
#include "Component.h"

using namespace std;

class Entity
{
public:
	Entity(unsigned int id);
	~Entity();

private:
	unsigned int _id;
	
};

