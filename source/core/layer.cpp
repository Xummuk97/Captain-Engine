#include "layer.h"
#include <core/core.h>

using namespace captain;

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
	size_t size = objects.size();

	for (size_t i = 0; i < size;)
	{
		objects[i]->update();

		if (objects[i]->getIsKill())
		{
			removeObject(i);
			size--;
		}
		else
		{
			i++;
		}
	}
}

void Layer::draw()
{
	for (Object* object : objects)
	{
		object->draw();
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

	return INVALID_OBJECT;
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

	return INVALID_OBJECT;
}

void Layer::swapObjectLayer(int objectIndex, Layer* layer)
{
	Object* object = new Object;
	swap(objects[objectIndex], object);
	layer->objects.push_back(object);
	removeObject(objectIndex);
}