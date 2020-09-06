#pragma once
#include <core/includes.h>
#include <core/object.h>

class Layer
{
public:
	Layer(const string& name);
	~Layer();

	LuaRef getName();

	int spawnObject(const string& name);
	void removeObject(int objectIndex);

	void update();
	void draw();

	void clear();

private:
	string name;
	vector<Object*> objects;
};