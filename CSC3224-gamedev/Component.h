#pragma once
#include <cstdint>


class Component
{
public:
	enum Type
	{
		Position
	};

	Component(Type t);
	virtual ~Component() = 0;
	uint32_t getID() const { return id_; }

private:
	Type type_;
	static uint32_t nextID_;
	uint32_t id_;
};
