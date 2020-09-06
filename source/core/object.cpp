#include <core/object.h>
#include <core/core.h>

Object::Object(const string& type)
	: type(type)
{
	Core::luaEngine.getVariable("init")(this);
}

Object::~Object()
{
}

LuaRef Object::getType()
{
	return Core::luaEngine.createVariable(type);
}

void Object::setTexture(const string& name)
{
	sprite = new Sprite();
	sprite->setTexture(*Core::textures[name]);
}

void Object::setTextureRect(int x, int y, int width, int height)
{
	if (sprite)
	{
		sprite->setTextureRect({ x, y, width, height });
	}
}

void Object::drawSprite()
{
	if (sprite)
	{
		Core::renderWindow->draw(*sprite);
	}
}

void Object::setPosition(float x, float y)
{
	if (sprite)
	{
		sprite->setPosition(x, y);
	}
}

void Object::move(float x, float y)
{
	if (sprite)
	{
		sprite->move(x * Core::deltaTime * 100.0f, y * Core::deltaTime * 100.0f);
	}
}
