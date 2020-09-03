#pragma once

extern "C" {
# include "lua/lua.h"
# include "lua/lauxlib.h"
# include "lua/lualib.h"
}

#include <LuaBridge/LuaBridge.h>
#include <iostream>

using namespace luabridge;
using namespace std;

class LuaEngine
{
public:
	LuaEngine();

	bool include(const char* file);
	Namespace getNamespace();

	LuaRef getVariable(const char* name);

	template <class T>
	void setVariable(const char* name, T value)
	{
		setGlobal(luaState, value, name);
	}

	template<class T>
	LuaRef createRef(T value)
	{
		return LuaRef(luaState, value);
	}

private:
	lua_State* luaState;
};