#pragma once
#include <string>

#define MAX_COMPONENTS 1024

enum class ComponentType
{
	TRANSFORM,
	RENDERABLE,
	TAG,
	RIGIDBODY,
	TYPE_END
};

class ComponentBase
{
public:
	virtual ~ComponentBase() = default;
	virtual ComponentType getType() = 0;
	virtual int getTypeValue() = 0;
};

template <typename T>
class IComponent : public ComponentBase
{
public:
	
	IComponent()
	{
		jsonBuild = &T::buildFromJson;
	};

	virtual ~IComponent()
	{
	}

protected:
	T* (*jsonBuild)(std::string);
};
