#pragma once
#include <core/includes.h>
#include <core/lua_engine.h>
#include <core/level.h>
#include <core/window.h>

using namespace std;
using namespace sf;

namespace captain
{
	const string LUA_MAIN_FILE = "resources/scripts/main.lua";

	class Core
	{
	public:
		Core();
		~Core();

		bool isKeyPressed(int key);

		void loadTexture(const string& name, const string& file);
		void loadLevel(const string& file);

		static Core* core;
		static captain::Window window;
		static LuaEngine luaEngine;
		static map<string, Texture*> textures;
		static Clock clock;
		static float deltaTime;
		static Level level;

	private:
		void initLua();
		void initLuaNamespaces();

		Time time;
	};
}