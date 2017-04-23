#pragma once
#include <string>

#define MAX_COMPONENTS 1024

enum class ComponentType
{
	TRANSFORM,
	RENDERABLE,
	TAG,
	PHYSICSBODY,
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
		/* Here we use the curiously recurring template pattern to achieve static polymorphism. */
		/* XXX: We're going to want to implement buildFromJson as static in derived classes. Whilst this works on my platform (Win10, MSVC2015v140) it certainly isn't guaranteed to be portable. - Jacob Millward 23/04/17 */
		jsonBuild = &T::buildFromJson;
	};

	virtual ~IComponent()
	{
	}

	virtual std::string toJson() = 0;

protected:
	T* (*jsonBuild)(std::string);
};
