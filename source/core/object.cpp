#include <core/object.h>
#include <core/core.h>

Object::Object(const string& type, const string& tag)
	: type(type)
	, tag(tag)
{
	static int _uniqueId = 0;
	_uniqueId++;
	uniqueId = _uniqueId;

	Core::luaEngine.getVariable("onObjectCreate")(this);
}

Object::~Object()
{
	if (sprite)
	{
		delete sprite;
	}
}

LuaRef Object::getType()
{
	return Core::luaEngine.createVariable(type);
}

LuaRef Object::getTag()
{
	return Core::luaEngine.createVariable(tag);
}

void Object::setTag(const string& tag)
{
	this->tag = tag;
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

int Object::getUniqueId()
{
	return uniqueId;
}
