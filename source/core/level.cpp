#include "level.h"
#include <core/core.h>

Level::Level()
{
}

Level::~Level()
{
}

int Level::addLayer(const string& name)
{
	int index = layers.size();
	layers.push_back(new Layer(name));
	return index;
}

void Level::removeLayer(int layerIndex)
{
	delete layers[layerIndex];
	layers.erase(layers.begin() + layerIndex);
}

LuaRef Level::getLayer(int layerIndex)
{
	return Core::luaEngine.createVariable(layers[layerIndex]);
}

int Level::spawnObject(int layerIndex, const string& objectName)
{
	return layers[layerIndex]->spawnObject(objectName);
}

int Level::spawnObjectTag(int layerIndex, const string& objectName, const string& tag)
{
	return layers[layerIndex]->spawnObject(objectName, tag);
}

int Level::getObjectIdFromTag(const string& tag)
{
	int index;

	for (Layer* layer : layers)
	{
		index = layer->getObjectIdFromTag(tag);

		if (index != -1)
		{
			return index;
		}
	}

	return -1;
}

int Level::getMapIdFromName(const string& name)
{
	size_t size = layers.size();

	for (size_t i = 0; i < size; i++)
	{
		if (layers[i]->getName() == name)
		{
			return i;
		}
	}

	return -1;
}

LuaRef Level::getObjectInfoFromUniqueId(int uniqueId)
{
	LuaRef info = Core::luaEngine.createTable();

	size_t size = layers.size();
	int index;

	for (size_t i = 0; i < size; i++)
	{
		index = layers[i]->getObjectIdFromUniqueId(uniqueId);

		if (index != -1)
		{
			info["layer"] = i;
			info["object"] = index;
			return info;
		}
	}

	return info;
}

void Level::load(const string& path, int type)
{
	this->path = "resources/levels/" + path;

	switch (type)
	{
	case LEVEL_TILED:
		loadFromTiled();
		break;
	}
}

void Level::clear()
{
	for (Layer* layer : layers)
	{
		delete layer;
	}

	layers.clear();
}

void Level::update()
{
	for (Layer* layer : layers)
	{
		layer->update();
	}
}

void Level::draw()
{
	for (Layer* layer : layers)
	{
		layer->draw();
	}
}

void Level::loadFromTiled()
{
}
