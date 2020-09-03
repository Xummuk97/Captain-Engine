#include "core.h"

void printMessage(const string& message)
{
	cout << message << endl;
}

struct Player
{
	Player()
	{

	}

	void show(const string& name)
	{
		cout << "Hello, " << name << "!" << endl;
	}
};

Core::Core()
{
	loadLuaNamespaces();
	
	if (!luaEngine.include(LUA_MAIN_FILE))
	{
		cout << "File '" << LUA_MAIN_FILE << "' was not found!" << endl;
	}
}

Core::~Core()
{
}

void Core::loadLuaNamespaces()
{
	luaEngine.getNamespace()
		.beginClass<Player>("Player")
			.addConstructor <void (*) (void)> ()
			.addFunction("show", &Player::show)
		.endClass();
}

