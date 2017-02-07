#pragma once

struct IComponent
{
public:
	enum class Type { Position };
	virtual ~IComponent() {}
};
