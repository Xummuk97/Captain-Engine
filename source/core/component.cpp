#include "component.h"
#include <core/core.h>
#include <core/object.h>

using namespace captain;

Component::Component()
{}

Component::Component(const string& name)
	: name(name)
{}

Component::~Component()
{
}

void Component::update(void* obj, const Component::Type& type)
{
	switch (type)
	{
	case Component::Type::Object:
		Core::luaEngine.getVariable(name)(static_cast<Object*>(obj));
		break;
	}
}

string Component::getName()
{
	return name;
}

ComponentDrawable::ComponentDrawable()
{
}

ComponentDrawable::~ComponentDrawable()
{
}

void ComponentDrawable::setTexture(const string& name)
{
	sprite.setTexture(*Core::textures[name]);
}

void ComponentDrawable::setTextureRect(int x, int y, int width, int height)
{
	sprite.setTextureRect({ x, y, width, height });
}

void ComponentDrawable::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
}

void ComponentDrawable::move(float x, float y)
{
	sprite.move(x * Core::deltaTime * 100.0f, y * Core::deltaTime * 100.0f);
}

void ComponentDrawable::draw()
{
	Core::window.draw(sprite);
}