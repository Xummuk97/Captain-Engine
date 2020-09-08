#include "level.h"
#include <core/core.h>

using namespace captain;

Level::Level()
{
}

Level::~Level()
{
	// Serialize levels
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

LuaRef Level::getObjectInfoFromTag(const string& tag)
{
	int index;
	size_t size = layers.size();

	for (size_t i = 0; i < size; i++)
	{
		index = layers[i]->getObjectIdFromTag(tag);

		if (index != INVALID_OBJECT)
		{
			return getObjectInfoFromObjectId(i, index);
		}
	}

	return Core::luaEngine.createVariable(INVALID_OBJECT);
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

	return INVALID_OBJECT;
}

LuaRef Level::getObjectInfoFromUniqueId(int uniqueId)
{
	size_t size = layers.size();
	int index;

	for (size_t i = 0; i < size; i++)
	{
		index = layers[i]->getObjectIdFromUniqueId(uniqueId);

		if (index != INVALID_OBJECT)
		{
			return getObjectInfoFromObjectId(i, index);
		}
	}

	return Core::luaEngine.createVariable(INVALID_OBJECT);
}

void Level::load(const string& path, int type)
{
	this->path = "resources/levels/" + path;

	Level::TypeLoader enumType = static_cast<Level::TypeLoader>(type);

	switch (enumType)
	{
	case Level::TypeLoader::Tiled:
		loadFromTiled();
		break;
	}
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

void Level::swapObjectLayer(int objectIndex, int layerIndex1, int layerIndex2)
{
	layers[layerIndex1]->swapObjectLayer(objectIndex, layers[layerIndex2]);
}

void Level::loadFromTiled()
{
}

LuaRef Level::getObjectInfoFromObjectId(int layer, int object)
{
	LuaRef value = Core::luaEngine.createTable();
	value["layer"] = layer;
	value["object"] = object;
	return value;
}
