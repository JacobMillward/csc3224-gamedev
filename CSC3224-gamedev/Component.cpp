#include "Component.h"

Component::Component(Type t) : type_(t), id_(nextID_++)
{
}
