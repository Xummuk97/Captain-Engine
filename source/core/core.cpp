#include "core.h"

Core*					Core::core;
RenderWindow*			Core::renderWindow;

Core::Core()
{
	Core::core = this;

	loadLuaNamespaces();
	
	if (!luaEngine.include(LUA_MAIN_FILE))
	{
		cout << "File '" << LUA_MAIN_FILE << "' was not found!" << endl;
	}

	Core::renderWindow = new RenderWindow(VideoMode(windowWidth, windowHeight), windowTitle);
	Core::renderWindow->setFramerateLimit(windowFPS);
	Core::renderWindow->setVerticalSyncEnabled(false);

	LuaRef setup = luaEngine.getVariable("setup");
	LuaRef core = luaEngine.createRef(this);
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
}

LuaRef Core::getParam(const string& name)
{
	if (name == "window_title")
	{
		return luaEngine.createRef(windowTitle);
	}
	else if (name == "window_fps")
	{
		return luaEngine.createRef(windowFPS);
	}
	else if (name == "window_vertical_sync")
	{
		return luaEngine.createRef(windowVerticalSyncEnabled);
	}

	cout << "Param '" << name << "' was not found!" << endl;
	return LuaRef(0);
}

void Core::loadLuaNamespaces()
{
	luaEngine.getNamespace()
		.beginClass<Core>("Core")
			.addConstructor<void (*) (void)>()
			.addFunction("setParam", &Core::setParam)
			.addFunction("getParam", &Core::getParam)
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
				Core::renderWindow->close();
		}
		Core::renderWindow->clear();
		Core::renderWindow->display();
	}
}

