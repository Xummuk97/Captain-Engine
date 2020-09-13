#include <core/object.h>
#include <core/core.h>

using namespace captain;

Object::Object()
{
}

Object::Object(const string& type, const string& tag)
	: type(type)
	, tag(tag)
	, components(new Components(this))
{
	static int _uniqueId = 0;
	_uniqueId++;
	uniqueId = _uniqueId;

	Core::luaEngine.getVariable("onObjectCreate")(this);
}

Object::~Object()
{
	for (pair<string, LuaRef*> variable : variables)
	{
		delete variable.second;
	}
	variables.clear();
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
		components->addCustomComponent(name, new ComponentDrawable);
	}
	else
	{
		components->addComponent(new ComponentLua(name));
	}
}

LuaRef Object::getComponent(const string& name)
{
	if (name == "componentDrawable")
	{
		return Core::luaEngine.createVariable(components->getCustomComponent<ComponentDrawable>(name));
	}
}

void Object::update()
{
	components->updateComponents();
}

void Object::draw()
{
	components->updateCustomComponent("componentDrawable");
}

void Object::setVariable(const string& name, LuaRef value)
{
	variables[name] = new LuaRef(value);
}

LuaRef& Object::getVariable(const string& name)
{
	return *variables[name];
}

void Object::setKill(bool isKill)
{
	this->isKill = isKill;
}

bool Object::getIsKill()
{
	return isKill;
}
