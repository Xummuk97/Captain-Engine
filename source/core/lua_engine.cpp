#include <core/lua_engine.h>

LuaEngine::LuaEngine()
    : luaState(luaL_newstate())
{
    luaL_openlibs(luaState);
}

bool LuaEngine::include(const string& file)
{
    return luaL_dofile(luaState, file.c_str()) == 0;
}

Namespace LuaEngine::getNamespace()
{
    return getGlobalNamespace(luaState);
}

LuaRef LuaEngine::getVariable(const string& name)
{
    LuaRef luaRef = getGlobal(luaState, name.c_str());

    if (luaRef.isNil())
    {
        cout << "Variable '" << name << "' was not found!" << endl;
    }
    
    return luaRef;
}

LuaRef LuaEngine::createTable()
{
    return newTable(luaState);
}
