#include <core/scripts/lua_engine.h>

void printMessage(const string& message)
{
    cout << message << endl;
}

int main() 
{
    LuaEngine l;

    l.getNamespace().beginNamespace("game")
        .addFunction("message", &printMessage).
        endNamespace();

    l.include("scripts/main.lua");

    return 0;
}