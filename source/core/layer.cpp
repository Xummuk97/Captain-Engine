#include "layer.h"
#include <core/core.h>

Layer::Layer(const string& name)
	: name(name)
{
}

Layer::~Layer()
{
	clear();
}

LuaRef Layer::getName()
{
	return Core::luaEngine.createVariable(name);
}

int Layer::spawnObject(const string& name)
{
	int index = objects.size();
	objects.push_back(new Object(name));
	return index;
}

void Layer::removeObject(int objectIndex)
{
	delete objects[objectIndex];
	objects.erase(objects.begin() + objectIndex);
}

void Layer::update()
{
	for (Object* object : objects)
	{
		Core::luaEngine.getVariable("update")(this, object);
	}
}

void Layer::draw()
{
	for (Object* object : objects)
	{
		Core::luaEngine.getVariable("draw")(this, object);
	}
}

void Layer::clear()
{
	for (Object* object : objects)
	{
		delete object;
	}

	objects.clear();
}
