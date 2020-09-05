#include "core.h"
#include <core/object.h>
#include <conio.h>
Core*					Core::core;
RenderWindow*			Core::renderWindow;
LuaEngine				Core::luaEngine;
map<string, Texture*>	Core::textures;
list<Object*>			Core::objects;
Clock					Core::clock;
float					Core::deltaTime;

Core::Core()
{
	Core::core = this;

	loadLuaNamespaces();
	
	if (!Core::luaEngine.include(LUA_MAIN_FILE))
	{
		cout << "File '" << LUA_MAIN_FILE << "' was not found!" << endl;
	}

	Core::renderWindow = new RenderWindow(VideoMode(windowWidth, windowHeight), windowTitle);
	Core::renderWindow->setFramerateLimit(windowFPS);
	Core::renderWindow->setVerticalSyncEnabled(windowVerticalSyncEnabled);

	Core::luaEngine.setVariable("core", this);

	vector<string> buttons =
	{
		"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",

		"Num0","Num1", "Num2", "Num3", "Num4","Num5", "Num6", "Num7", "Num8", "Num9",

		"Escape", "LControl", "LShift","LAlt", "LSystem", "RControl", "RShift", "RAlt", "RSystem", "Menu", "LBracket",
		"RBracket", "Semicolon", "Comma", "Period","Quote", "Slash", "Backslash", "Tilde", "Equal", "Hyphen", "Space",
		"Enter","Backspace", "Tab", "PageUp", "PageDown","End", "Home", "Insert", "Delete",	"Add", "Subtract", "Multiply", "Divide",

		"Left", "Right", "Up", "Down",

		"Numpad0", "Numpad1", "Numpad2", "Numpad3", "Numpad4", "Numpad5", "Numpad6", "Numpad7","Numpad8", "Numpad9",

		"F1", "F2","F3", "F4", "F5", "F6","F7", "F8", "F9", "F10","F11", "F12", "F13", "F14","F15",

		"Pause"
	};

	for (size_t i = 0; i < buttons.size(); i++)
	{
		transform(buttons[i].begin(), buttons[i].end(), buttons[i].begin(), ::toupper);

		buttons[i].insert(0, "KB_");

		Core::luaEngine.setVariable(buttons[i], i);
	}
	
	Core::luaEngine.getVariable("setup")();

	startWindow();
}

Core::~Core()
{
	Core::renderWindow->close();
}

void Core::setParam(const string& name, LuaRef value)
{
	if (name == "window_title")
	{
		windowTitle = value.cast<string>();
		Core::renderWindow->setTitle(windowTitle);
	}
	else if (name == "window_fps")
	{
		windowFPS = value.cast<unsigned int>();
		Core::renderWindow->setFramerateLimit(windowFPS);
	}
	else if (name == "window_vertical_sync")
	{
		windowVerticalSyncEnabled = value.cast<bool>();
		Core::renderWindow->setVerticalSyncEnabled(windowVerticalSyncEnabled);
	}
	else if (name == "window_position")
	{
		Vector2i windowPosition = value.cast<Vector2i>();
		Core::renderWindow->setPosition(windowPosition);
	}
	else if (name == "window_size")
	{
		Vector2u windowSize = value.cast<Vector2u>();
		Core::renderWindow->setSize(windowSize);
	}
	
}

LuaRef Core::getParam(const string& name)
{
	if (name == "window_title")
	{
		return Core::luaEngine.createVariable(windowTitle);
	}
	else if (name == "window_fps")
	{
		return Core::luaEngine.createVariable(windowFPS);
	}
	else if (name == "window_vertical_sync")
	{
		return Core::luaEngine.createVariable(windowVerticalSyncEnabled);
	}
	else if (name == "window_position")
	{
		return Core::luaEngine.createVariable(Core::renderWindow->getPosition());
	}
	else if (name == "window_size")
	{
		return Core::luaEngine.createVariable(Core::renderWindow->getSize());
	}
	
	cout << "Param '" << name << "' was not found!" << endl;
	return Core::luaEngine.createVariable(0);
}

void Core::loadTexture(const string& name, const string& file)
{
	Texture* texture = new Texture;
	texture->loadFromFile("resources/textures/" + file);
	Core::textures[name] = texture;
}

void Core::addObject(const string& name)
{
	Core::objects.push_back(new Object(name));
}

bool Core::isKeyPressed(int key)
{
	return sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key);
}

void Core::loadLuaNamespaces()
{
	Core::luaEngine.getNamespace()
		.beginClass<Core>("Core")
			.addConstructor<void (*) (void)>()
			.addFunction("setParam", &Core::setParam)
			.addFunction("getParam", &Core::getParam)
			.addFunction("loadTexture", &Core::loadTexture)
			.addFunction("addObject", &Core::addObject)
			.addFunction("isKeyPressed", &Core::isKeyPressed)
		.endClass()
		.beginClass<Vector2i>("Vector2i")
			.addConstructor<void (*) (void)>()\
			.addProperty("x", &Vector2i::x)
			.addProperty("y", &Vector2i::y)
		.endClass()
		.beginClass<Vector2u>("Vector2u")
			.addConstructor<void (*) (void)>()\
			.addProperty("x", &Vector2u::x)
			.addProperty("y", &Vector2u::y)
		.endClass()
		.beginClass<Vector2f>("Vector2f")
			.addConstructor<void (*) (void)>()\
			.addProperty("x", &Vector2f::x)
			.addProperty("y", &Vector2f::y)
		.endClass()
		.beginClass<IntRect>("IntRect")
			.addConstructor<void (*) (void)>()\
			.addProperty("left", &IntRect::left)
			.addProperty("top", &IntRect::top)
			.addProperty("width", &IntRect::width)
		.endClass()
		.beginClass<FloatRect>("FloatRect")
			.addConstructor<void (*) (void)>()\
			.addProperty("left", &FloatRect::left)
			.addProperty("top", &FloatRect::top)
			.addProperty("width", &FloatRect::width)
		.endClass()
		.beginClass<Object>("Object")
			.addConstructor<void (*) (const string&)>()
			.addFunction("getType", &Object::getType)
			.addFunction("setTexture", &Object::setTexture)
			.addFunction("setTextureRect", &Object::setTextureRect)
			.addFunction("drawSprite", &Object::drawSprite)
			.addFunction("setPosition", &Object::setPosition)
			.addFunction("move", &Object::move)
		.endClass();
}

void Core::startWindow()
{
	while (Core::renderWindow->isOpen())
	{
		eventProcess();
		gameProcess();
	}
}

void Core::eventProcess()
{
	sf::Event event;
	while (Core::renderWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			Core::renderWindow->close();
		}
	}
}

void Core::gameProcess()
{
	Core::deltaTime = clock.getElapsedTime().asSeconds();
	Core::clock.restart();

	for (Object* obj : objects)
	{
		Core::luaEngine.getVariable("update")(obj);
	}

	Core::renderWindow->clear();

	for (Object* obj : objects)
	{
		Core::luaEngine.getVariable("draw")(obj);
	}

	Core::renderWindow->display();

	Core::luaEngine.free();
}