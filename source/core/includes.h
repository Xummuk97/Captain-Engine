#pragma once
// SFML-includes
#include <SFML\Main.hpp>
#include <SFML/Graphics.hpp>

// STD-includes
#include <string>
#include <list>
#include <vector>
#include <iostream>

// Lua-includes
extern "C"
{
#include "lua/lua.h"
#include "lua/lauxlib.h"
#include "lua/lualib.h"
}
#include <LuaBridge/LuaBridge.h>

// ImGUI-includes
#include <imgui.h>
#include <imgui-SFML.h>

// Namespaces
using namespace luabridge;
using namespace std;
using namespace sf;