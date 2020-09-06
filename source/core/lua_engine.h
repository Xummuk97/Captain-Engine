#pragma once

extern "C" 
{
#include "lua/lua.h"
#include "lua/lauxlib.h"
#include "lua/lualib.h"
}

#include <LuaBridge/LuaBridge.h>
#include <iostream>

using namespace luabridge;
using namespace std;

class LuaEngine
{
public:
	LuaEngine();

	bool include(const string& file);
	Namespace getNamespace();

	LuaRef getVariable(const string& name);

	template <class T>
	void setVariable(const string& name, T value)
	{
		setGlobal(luaState, value, name.c_str());
	}

	template<class T>
	LuaRef createVariable(T value)
	{
		return LuaRef(luaState, value);
	}

	LuaRef createTable();

	void free()
	{
		lua_gc(luaState, LUA_GCCOLLECT);
	}

private:
	lua_State* luaState;
};