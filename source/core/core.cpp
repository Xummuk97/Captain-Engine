#include <core/core.h>
#include <core/imgui_engine.h>
#include <core/types.h>

using namespace captain;

Core*					Core::core;
RenderWindow*			Core::renderWindow;
LuaEngine				Core::luaEngine;
map<string, Texture*>	Core::textures;
Clock					Core::clock;
float					Core::deltaTime;
Level					Core::level;

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

	ImGui::SFML::Init(*Core::renderWindow);

	Core::luaEngine.setVariable("core", this);
	Core::luaEngine.setVariable("level", &Core::level);

	Core::luaEngine.setVariable("INVALID_OBJECT", INVALID_OBJECT);
	Core::luaEngine.setVariable("LEVEL_TYPELOADER_TILED", (int)Level::TypeLoader::Tiled);
	Core::luaEngine.setVariable("LEVEL_TYPELOADER_CAPTAIN", (int)Level::TypeLoader::Captain);

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
		buttons[i] = "KB_" + buttons[i];

		Core::luaEngine.setVariable(buttons[i], i);
	}
	
	Core::luaEngine.getVariable("onEngineSetup")();

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

bool Core::isKeyPressed(int key)
{
	return sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key);
}

void Core::loadLevel(const string& file)
{

}

void Core::loadLuaNamespaces()
{
	Core::luaEngine.getNamespace()
		.beginClass<Core>("Core")
			.addConstructor<void (*) (void)>()
			.addFunction("setParam", &Core::setParam)
			.addFunction("getParam", &Core::getParam)
			.addFunction("loadTexture", &Core::loadTexture)
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
		.beginClass<Rectangle<int>>("IntRect")
			.addConstructor<void (*) (int, int, int, int)> ()
			.addFunction("setX", &Rectangle<int>::setX)
			.addFunction("getX", &Rectangle<int>::getX)
			.addFunction("setY", &Rectangle<int>::setY)
			.addFunction("getY", &Rectangle<int>::getY)
			.addFunction("setWidth", &Rectangle<int>::setWidth)
			.addFunction("getWidth", &Rectangle<int>::getWidth)
			.addFunction("setHeight", &Rectangle<int>::setHeight)
			.addFunction("getHeight", &Rectangle<int>::getHeight)
			.addFunction("isContains", &Rectangle<int>::isContains)
			.addFunction("isIntersects", &Rectangle<int>::isIntersects)
			.addFunction("isIntersectsTable", &Rectangle<int>::isIntersectsTable)
			.addFunction("getTable", &Rectangle<int>::getTable)
		.endClass()
		.beginClass<Rectangle<float>>("FloatRect")
			.addConstructor<void (*) (float, float, float, float)> ()
			.addFunction("setX", &Rectangle<float>::setX)
			.addFunction("getX", &Rectangle<float>::getX)
			.addFunction("setY", &Rectangle<float>::setY)
			.addFunction("getY", &Rectangle<float>::getY)
			.addFunction("setWidth", &Rectangle<float>::setWidth)
			.addFunction("getWidth", &Rectangle<float>::getWidth)
			.addFunction("setHeight", &Rectangle<float>::setHeight)
			.addFunction("getHeight", &Rectangle<float>::getHeight)
			.addFunction("isContains", &Rectangle<float>::isContains)
			.addFunction("isIntersects", &Rectangle<float>::isIntersects)
			.addFunction("isIntersectsTable", &Rectangle<float>::isIntersectsTable)
			.addFunction("getTable", &Rectangle<float>::getTable)
		.endClass()
		.beginClass<ComponentDrawable>("ComponentDrawable")
			.addConstructor<void (*) (void)>()
			.addFunction("setTexture", &ComponentDrawable::setTexture)
			.addFunction("setTextureRect", &ComponentDrawable::setTextureRect)
			.addFunction("setPosition", &ComponentDrawable::setPosition)
			.addFunction("move", &ComponentDrawable::move)
		.endClass()
		.beginClass<Object>("Object")
			.addConstructor<void (*) (const string&)>()
			.addFunction("getType", &Object::getType)
			.addFunction("getTag", &Object::getTag)
			.addFunction("setTag", &Object::setTag)
			.addFunction("getUniqueId", &Object::getUniqueId)
			.addFunction("addComponent", &Object::addComponent)
			.addFunction("getComponent", &Object::getComponent)
			.addFunction("hasComponent", &Object::hasComponent)
			.addFunction("setVariable", &Object::setVariable)
			.addFunction("getVariable", &Object::getVariable)
			.addFunction("setKill", &Object::setKill)
			.addFunction("getIsKill", &Object::getIsKill)
		.endClass()
		.beginClass<Layer>("Layer")
			.addConstructor<void (*) (const string&)>()
			.addFunction("spawnObject", &Layer::spawnObject)
			.addFunction("removeObject", &Layer::removeObject)
			.addFunction("getName", &Layer::getName)
		.endClass()
		.beginClass<Level>("Level")
			.addConstructor<void (*) (void)>()
			.addFunction("addLayer", &Level::addLayer)
			.addFunction("removeLayer", &Level::removeLayer)
			.addFunction("getLayer", &Level::getLayer)
			.addFunction("spawnObject", &Level::spawnObject)
			.addFunction("spawnObjectTag", &Level::spawnObjectTag)
			.addFunction("getMapIdFromName", &Level::getMapIdFromName)
			.addFunction("getObjectInfoFromTag", &Level::getObjectInfoFromTag)
			.addFunction("getObjectInfoFromUniqueId", &Level::getObjectInfoFromUniqueId)
			.addFunction("swapObjectLayer", &Level::swapObjectLayer)
			.addFunction("load", &Level::load)
		.endClass()
		.beginNamespace("ImGui")
			.addFunction("beginWindow", &ImGuiEngine::beginWindow)
			.addFunction("endWindow", &ImGui::End)
			.addFunction("beginGroup", &ImGui::BeginGroup)
			.addFunction("endGroup", &ImGui::EndGroup)
			.addFunction("button", &ImGuiEngine::button)
			.addFunction("label", &ImGuiEngine::label)
			.addFunction("colorEdit4", &ImGuiEngine::colorEdit4)
		.endNamespace();
}

void Core::startWindow()
{
	while (Core::renderWindow->isOpen())
	{
		eventProcess();
		gameProcess();
	}

	ImGui::SFML::Shutdown();
}

void Core::eventProcess()
{
	sf::Event event;
	while (Core::renderWindow->pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(event);

		if (event.type == sf::Event::Closed)
		{
			Core::renderWindow->close();
		}
	}
}

void Core::gameProcess()
{
	time = Core::clock.restart();
	Core::deltaTime = time.asSeconds();

	Core::level.update();
	ImGui::SFML::Update(*Core::renderWindow, time);
	Core::luaEngine.getVariable("onGUI")();
	consoleProcess();

	Core::renderWindow->clear();
	Core::level.draw();
	ImGui::SFML::Render(*Core::renderWindow);
	Core::renderWindow->display();

	Core::luaEngine.free();
}

void Core::consoleProcess()
{
	static char command[256], log[1024];

	ImGui::Begin("Console");
	ImGui::InputTextMultiline("Log", log, sizeof(log));
	ImGui::InputText("Command", command, sizeof(command));
	if (ImGui::Button("Execute"))
	{
		Core::luaEngine.eval(command);
		sprintf_s(command, sizeof(command), "%s\n", command);
		strcat_s(log, command);
		command[0] = '\0';
	}
	ImGui::End();
}