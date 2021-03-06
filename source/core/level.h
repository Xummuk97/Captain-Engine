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

	int spawnObject(int layerIndex, const string& objectName);
	int spawnObjectTag(int layerIndex, const string& objectName, const string& tag);

	int getMapIdFromName(const string& name);
	LuaRef getObjectInfoFromTag(const string& tag);
	LuaRef getObjectInfoFromUniqueId(int uniqueId);

	void load(const string& path, int type);

	void clear();

	void update();
	void draw();

private:
	void loadFromTiled();

	void getObjectInfoFromObjectId(LuaRef& value, int layer, int object);

	string path;
	vector<Layer*> layers;
};