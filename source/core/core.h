#pragma once

#include <SFML/Graphics.hpp>
#include <core/lua_engine.h>

using namespace sf;

#define LUA_MAIN_FILE "resources/scripts/main.lua"

class Core
{
public:
	Core();
	~Core();



private:
	void loadLuaNamespaces();

	LuaEngine luaEngine;
};