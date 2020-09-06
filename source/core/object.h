#pragma once
#include <core/includes.h>

using namespace std;
using namespace sf;
using namespace luabridge;

class Object
{
public:
	Object(const string& type);
	~Object();

	LuaRef getType();

	void setTexture(const string& name);
	void setTextureRect(int x, int y, int width, int height);

	void drawSprite();

	void setPosition(float x, float y);
	void move(float x, float y);

private:
	string type;
	Sprite* sprite;
};