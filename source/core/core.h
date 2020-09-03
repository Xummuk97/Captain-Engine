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

	void setParam(const string& name, LuaRef value);
	LuaRef getParam(const string& name);

	static Core* core;
	static RenderWindow* renderWindow;

private:
	void loadLuaNamespaces();
	void startWindow();

	LuaEngine luaEngine;

	string windowTitle = "Captain Engine 1.0";
	int windowWidth = 800;
	int windowHeight = 600;
	int windowFPS = 60;
	bool windowVerticalSyncEnabled = false;
};