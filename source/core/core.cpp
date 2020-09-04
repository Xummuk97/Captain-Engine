#include "core.h"

Core*					Core::core;
RenderWindow*			Core::renderWindow;
LuaEngine				Core::luaEngine;

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

	LuaRef setup = Core::luaEngine.getVariable("setup");
	LuaRef core = Core::luaEngine.createVariable(this);
	setup(core);

	startWindow();
}

Core::~Core()
{
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

void Core::loadLuaNamespaces()
{
	Core::luaEngine.getNamespace()
		.beginClass<Core>("Core")
			.addConstructor<void (*) (void)>()
			.addFunction("setParam", &Core::setParam)
			.addFunction("getParam", &Core::getParam)
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
		.endClass();
}

void Core::startWindow()
{
	while (Core::renderWindow->isOpen())
	{
		sf::Event event;
		while (Core::renderWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				Core::renderWindow->close();
			}
		}
		Core::renderWindow->clear();
		Core::renderWindow->display();
	}
}

