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

VisualObject::VisualObject()
	: AbstractObject("VisualObject")
{
}

VisualObject::~VisualObject()
{
}

void VisualObject::update()
{
}

void VisualObject::draw()
{
	Core::renderWindow->draw(sprite);
}

void VisualObject::setTexture(const string& name)
{
	sprite.setTexture(Core::textures[name]);
}

void VisualObject::setTextureRect(int x, int y, int width, int height)
{
	sprite.setTextureRect({ x, y, width, height });
}
