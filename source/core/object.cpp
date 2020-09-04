#include "object.h"
#include <core/core.h>

AbstractObject::AbstractObject(const string& type)
	: type(type)
{
}

AbstractObject::~AbstractObject()
{
}

void AbstractObject::update()
{
}

void AbstractObject::draw()
{
}

LuaRef AbstractObject::getType()
{
	return Core::luaEngine.createVariable(type);
}
