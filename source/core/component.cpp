#include "component.h"
#include <core/core.h>
#include <core/object.h>

using namespace captain;

Object* objCast(void* obj)
{
	return (Object*)obj;
}

Component::Component()
{}

Component::~Component()
{}

void captain::Component::setLuaCallbackName(const string& name)
{
	luaCallbackName = name;
}

string captain::Component::getLuaCallbackName()
{
	return luaCallbackName;
}

captain::Components::Components(void* obj)
	: obj(obj)
{
}

captain::Components::~Components()
{
	for (Component* component : components)
	{
		delete component;
	}
	components.clear();

	for (pair<string, Component*> customComponent : customComponents)
	{
		delete customComponent.second;
	}
	customComponents.clear();
}

void captain::Components::addComponent(Component* component)
{
	components.push_back(component);
}

void captain::Components::addCustomComponent(const string& name, Component* component)
{
	customComponents[name] = component;
}

void captain::Components::updateComponents()
{
	string luaCallbackName;

	for (Component* component : components)
	{
		luaCallbackName = component->getLuaCallbackName();

		if (luaCallbackName != "-")
		{
			Core::luaEngine.getVariable(luaCallbackName)(objCast(obj));
		}
		else
		{
			component->update();
		}
	}
}

void captain::Components::updateCustomComponent(const string& name)
{
	Component* customComponent = customComponents[name];

	if (customComponent)
	{
		string luaCallbackName = customComponent->getLuaCallbackName();

		if (luaCallbackName != "-")
		{
			Core::luaEngine.getVariable(luaCallbackName)(objCast(obj));
		}
		else
		{
			customComponent->update();
		}
	}
}

captain::ComponentLua::ComponentLua(const string& luaCallbackName)
{
	setLuaCallbackName(luaCallbackName);
}

captain::ComponentLua::~ComponentLua()
{
}

void captain::ComponentLua::update()
{
}

captain::ComponentDrawable::ComponentDrawable()
{
}

captain::ComponentDrawable::~ComponentDrawable()
{
}

void captain::ComponentDrawable::update()
{
	Core::window.draw(sprite);
}

void captain::ComponentDrawable::setTexture(const string& name)
{
	sprite.setTexture(*Core::textures[name]);
}

void captain::ComponentDrawable::setTextureRect(int x, int y, int width, int height)
{
	sprite.setTextureRect({ x, y, width, height });
}

Sprite* captain::ComponentDrawable::getSprite()
{
	return &sprite;
}
