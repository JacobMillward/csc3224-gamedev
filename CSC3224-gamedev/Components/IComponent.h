#pragma once

#define MAX_COMPONENTS 1024

struct IComponent
{
public:
	enum class Type { TRANSFORM, RENDERABLE, TAG, TYPE_END };
	virtual Type getType() = 0;
	virtual const int getTypeValue() = 0;
	virtual ~IComponent() {}
};
