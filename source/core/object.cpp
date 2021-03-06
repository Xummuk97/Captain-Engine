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

int Object::getUniqueId()
{
	return uniqueId;
}

void Object::addComponent(const string& name)
{
	if (name == "componentDrawable")
	{
		componentDrawable = new ComponentDrawable;
	}
	else
	{
		components.push_back(new Component(name));
	}
}

LuaRef Object::getComponentDrawable()
{
	return Core::luaEngine.createVariable(componentDrawable);
}

void Object::update()
{
	for (Component* component : components)
	{
		component->update(this, ComponentType_Object);
	}
}

void Object::draw()
{
	if (componentDrawable)
	{
		componentDrawable->draw();
	}
}
