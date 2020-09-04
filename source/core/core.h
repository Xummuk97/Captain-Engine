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

	void loadTexture(const string& name, const string& file);

	static Core* core;
	static RenderWindow* renderWindow;
	static LuaEngine luaEngine;
	static map<string, Texture> textures;

private:
	void loadLuaNamespaces();
	void startWindow();

	string windowTitle = "Captain Engine 1.0";
	int windowWidth = 800;
	int windowHeight = 600;
	int windowFPS = 60;
	bool windowVerticalSyncEnabled = false;
};