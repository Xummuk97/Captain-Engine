#include <core/scripts/lua_engine.h>

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

int main() 
{
	LuaEngine l;

	l.getNamespace()
		.beginClass<Player>("Player")
			.addConstructor <void (*) (void)> ()
			.addFunction("show", &Player::show)
		.endClass();

	l.include("scripts/main.lua");

	return 0;
}