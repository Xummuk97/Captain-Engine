#include <core/object.h>
#include <core/core.h>

using namespace captain;

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
	for (pair<string, Component*> component : components)
	{
		delete component.second;
	}
	components.clear();

	for (Component* component : customComponents)
	{
		delete component;
	}
	customComponents.clear();

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
		components[name] = new ComponentDrawable;
	}
	else
	{
		customComponents.push_back(new Component(name));
	}
}

LuaRef Object::getComponent(const string& name)
{
	if (name == "componentDrawable")
	{
		return Core::luaEngine.createVariable((ComponentDrawable*)components[name]);
	}

	cout << "Component name '" << name << "' was not found!" << endl;
	return Core::luaEngine.createVariable(INVALID_OBJECT);
}

bool Object::hasComponent(const string& name)
{
	return components.find(name) != components.end();
}

bool Object::hasCustomComponent(const string& name)
{
	for (Component* component : customComponents)
	{
		if (component->getName() == name)
		{
			return true;
		}
	}

	return false;
}

void Object::update()
{
	for (Component* component : customComponents)
	{
		component->update(this, ComponentType_Object);
	}
}

void Object::draw()
{
	if (hasComponent("componentDrawable"))
	{
		((ComponentDrawable*)components["componentDrawable"])->draw();
	}
}

void Object::setVariable(const string& name, LuaRef value)
{
	variables[name] = new LuaRef(value);
}

LuaRef& Object::getVariable(const string& name)
{
	return *variables[name];
}
