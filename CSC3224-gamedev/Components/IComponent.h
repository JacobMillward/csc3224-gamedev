#pragma once

struct IComponent
{
public:
	enum class Type { Position, Test, TYPE_END };
	virtual Type getType() = 0;
	virtual ~IComponent() {}
};
