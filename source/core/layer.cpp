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

int Layer::spawnObject(const string& name, const string& tag)
{
	Object* obj = new Object(name, tag);
	objects.push_back(obj);
	return obj->getUniqueId();
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

int Layer::getObjectIdFromTag(const string& tag)
{
	size_t size = objects.size();

	for (size_t i = 0; i < size; i++)
	{
		if (objects[i]->getTag() == tag)
		{
			return i;
		}
	}

	return -1;
}

int Layer::getObjectIdFromUniqueId(int uniqueId)
{
	size_t size = objects.size();

	for (size_t i = 0; i < size; i++)
	{
		if (objects[i]->getUniqueId() == uniqueId)
		{
			return i;
		}
	}

	return -1;
}
