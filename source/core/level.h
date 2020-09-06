#pragma once

#include <core/includes.h>
#include <core/layer.h>

#define LEVEL_TILED 0
#define LEVEL_CAPTAIN 1

class Level
{
public:
	Level();
	~Level();

	int addLayer(const string& name);
	void removeLayer(int layerIndex);
	LuaRef getLayer(int layerIndex);

	void spawnObject(int layerIndex, const string& objectName);

	void load(const string& path, int type);

	void clear();

	void update();
	void draw();

private:
	void loadFromTiled();

	string path;
	vector<Layer*> layers;
};