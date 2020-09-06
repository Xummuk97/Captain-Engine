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
