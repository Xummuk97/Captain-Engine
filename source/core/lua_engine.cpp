#include "lua_engine.h"

LuaEngine::LuaEngine()
    : luaState(luaL_newstate())
{
    luaL_openlibs(luaState);
}

bool LuaEngine::include(const char* file)
{
    return luaL_dofile(luaState, file) == 0;
}

Namespace LuaEngine::getNamespace()
{
    return getGlobalNamespace(luaState);
}

LuaRef LuaEngine::getVariable(const char* name)
{
    LuaRef luaRef = getGlobal(luaState, name);

    if (luaRef.isNil())
    {
        cout << "Variable '" << name << "' was not found!" << endl;
    }

    return luaRef;
}