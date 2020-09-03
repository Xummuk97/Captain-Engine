#include <core/scripts/lua_engine.h>

/*void printMessage(const string& message)
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
}*/

#include <SFML/Graphics.hpp>
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
}