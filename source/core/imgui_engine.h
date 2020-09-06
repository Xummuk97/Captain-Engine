#pragma once

#include "imgui.h"
#include "imgui-SFML.h"

#include <string>

extern "C"
{
#include "lua/lua.h"
#include "lua/lauxlib.h"
#include "lua/lualib.h"
}

#include <LuaBridge/LuaBridge.h>

using namespace luabridge;
using namespace std;

class ImGuiEngine
{
public:
	static void beginWindow(const string& text);
	static bool button(const string& text);
	static void label(const string& text);
	static void colorEdit4(const string& text, LuaRef value);
};