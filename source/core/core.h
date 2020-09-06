#pragma once
#include <core/includes.h>
#include <core/lua_engine.h>
#include <core/level.h>

using namespace std;
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

	bool isKeyPressed(int key);

	static Core* core;
	static RenderWindow* renderWindow;
	static LuaEngine luaEngine;
	static map<string, Texture*> textures;
	static Clock clock;
	static float deltaTime;
	static Level level;

private:
	void loadLuaNamespaces();
	void startWindow();

	void eventProcess();
	void gameProcess();

	string windowTitle = "Captain Engine 1.0";
	int windowWidth = 800;
	int windowHeight = 600;
	int windowFPS = 300;
	bool windowVerticalSyncEnabled = false;

	Time time;
};