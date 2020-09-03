#include <core/lua_engine.h>

#define LUA_MAIN_FILE "resources/scripts/main.lua"

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

void loadLuaNamespaces(LuaEngine& l)
{
	l.getNamespace()
		.beginClass<Player>("Player")
			.addConstructor <void (*) (void)> ()
			.addFunction("show", &Player::show)
		.endClass();
}

int main() 
{
	LuaEngine l;

	loadLuaNamespaces(l);

	if (!l.include(LUA_MAIN_FILE))
	{
		cout << "File '" << LUA_MAIN_FILE << "' was not found!" << endl;
	}

	return 0;
}

/*#include <SFML/Graphics.hpp>
int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "Lesson 1. kychka-pc.ru");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(shape);
		window.display();
	}
	return 0;
}*/

/*#include <tinyxml2/tinyxml2.h>

using namespace tinyxml2;

int main()
{
	XMLDocument doc;
	doc.LoadFile("resources/configs/test.xml");
	doc.Print();
	return 0;
}*/