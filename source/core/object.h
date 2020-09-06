#pragma once
#include <core/includes.h>

using namespace std;
using namespace sf;
using namespace luabridge;

class Object
{
public:
	Object(const string& type, const string& tag = "default");
	~Object();

	LuaRef getType();
	LuaRef getTag();

	void setTag(const string& tag);

	void setTexture(const string& name);
	void setTextureRect(int x, int y, int width, int height);

	void drawSprite();

	void setPosition(float x, float y);
	void move(float x, float y);

	int getUniqueId();

private:
	int uniqueId;
	string type, tag;
	Sprite* sprite = nullptr;
};