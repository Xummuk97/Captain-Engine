#pragma once
#include <core/includes.h>
#include <core/object.h>

class Layer
{
public:
	Layer(const string& name);
	~Layer();

	LuaRef getName();

	int spawnObject(const string& name, const string& tag = "default");
	void removeObject(int objectIndex);

	void update();
	void draw();

	void clear();

	int getObjectIdFromTag(const string& tag);
	int getObjectIdFromUniqueId(int uniqueId);

private:
	string name;
	vector<Object*> objects;
};