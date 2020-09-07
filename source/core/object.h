#pragma once
#include <core/includes.h>
#include <core/component.h>

using namespace std;
using namespace sf;
using namespace luabridge;

#define INVALID_OBJECT -1

class Object
{
public:
	Object(const string& type, const string& tag = "default");
	~Object();

	LuaRef getType();
	LuaRef getTag();

	void setTag(const string& tag);

	int getUniqueId();

	void addComponent(const string& name);
	LuaRef getComponentDrawable();

	void update();
	void draw();

private:
	int uniqueId;
	string type, tag;
	Sprite* sprite = nullptr;

	list<Component*> components;
	ComponentDrawable* componentDrawable;
};