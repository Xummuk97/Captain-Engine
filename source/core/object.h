#pragma once

#include <SFML/Graphics.hpp>
#include <string>

extern "C" {
# include "lua/lua.h"
# include "lua/lauxlib.h"
# include "lua/lualib.h"
}

#include <LuaBridge/LuaBridge.h>

using namespace std;
using namespace sf;
using namespace luabridge;

class AbstractObject
{
public:
	AbstractObject(const string& type);
	~AbstractObject();

	virtual void update();
	virtual void draw();

	LuaRef getType();

private:
	string type;
};

class VisualObject : public AbstractObject
{
public:
	VisualObject();
	~VisualObject();

	void update();
	void draw();

	void setTexture(const string& name);
	void setTextureRect(int x, int y, int width, int height);

private:
	Sprite sprite;
};