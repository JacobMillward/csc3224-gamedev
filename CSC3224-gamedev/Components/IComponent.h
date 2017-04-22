#pragma once

#define MAX_COMPONENTS 1024

struct IComponent
{
public:
	enum class Type
	{
		TRANSFORM,
		RENDERABLE,
		TAG,
		RIGIDBODY,
		TYPE_END
	};

	virtual Type getType() = 0;
	virtual int getTypeValue() = 0;

	virtual ~IComponent()
	{
	}
};
