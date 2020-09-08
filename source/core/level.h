#pragma once

#include <core/includes.h>
#include <core/layer.h>

namespace captain
{
	class Level
	{
	public:
		enum class TypeLoader
		{
			Tiled,
			Captain
		};

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

		void update();
		void draw();

		void swapObjectLayer(int objectIndex, int layerIndex1, int layerIndex2);

	private:
		void loadFromTiled();

		LuaRef getObjectInfoFromObjectId(int layer, int object);

		string path;
		vector<Layer*> layers;
	};
}