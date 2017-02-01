#pragma once



class Component
{
public:
	enum Type { Position };

	Component(Type t) { _type = t; }
	virtual ~Component() = 0;

private:
	Type _type;
};

