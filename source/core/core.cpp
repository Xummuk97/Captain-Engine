#include <core/core.h>
#include <core/imgui_engine.h>
#include <core/types.h>

using namespace captain;

Core*					Core::core;
captain::Window			Core::window;
LuaEngine				Core::luaEngine;
map<string, Texture*>	Core::textures;
Clock					Core::clock;
float					Core::deltaTime;
Level					Core::level;

Core::Core()
{
	Core::core = this;

	initLua();
	
	Core::luaEngine.getVariable("onEngineSetup")();

	Core::window.startWindow();
}

Core::~Core()
{
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

void captain::Core::initLua()
{
	initLuaNamespaces();

	if (!Core::luaEngine.include(LUA_MAIN_FILE))
	{
		cout << "File '" << LUA_MAIN_FILE << "' was not found!" << endl;
	}

	Core::luaEngine.setVariable("core", this);
	Core::luaEngine.setVariable("level", &Core::level);
	Core::luaEngine.setVariable("window", &Core::window);

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
}

void Core::initLuaNamespaces()
{
	Core::luaEngine.getNamespace()
		.beginClass<captain::Window>("Window")
			.addConstructor<void (*) (void)>()
			.addFunction("create", &captain::Window::create)
			.addFunction("setTitle", &captain::Window::setTitle)
			.addFunction("setFPS", &captain::Window::setFPS)
			.addFunction("setVerticalSync", &captain::Window::setVerticalSync)
			.addFunction("setPosition", &captain::Window::setPosition)
			.addFunction("setSize", &captain::Window::setSize)
			.addFunction("getPosition", &captain::Window::getPosition)
			.addFunction("getSize", &captain::Window::getSize)
		.endClass()
		.beginClass<Core>("Core")
			.addConstructor<void (*) (void)>()
			.addFunction("loadTexture", &Core::loadTexture)
			.addFunction("isKeyPressed", &Core::isKeyPressed)
		.endClass()
		.beginClass<Point<int>>("IntPoint")
			.addConstructor<void (*) (int, int)>()
			.addFunction("setX", &Point<int>::setX)
			.addFunction("getX", &Point<int>::getX)
			.addFunction("setY", &Point<int>::setY)
			.addFunction("getY", &Point<int>::getY)
			.addFunction("getTable", &Point<int>::getTable)
		.endClass()
		.beginClass<Point<float>>("FloatPoint")
			.addConstructor<void (*) (float, float)>()
			.addFunction("setX", &Point<float>::setX)
			.addFunction("getX", &Point<float>::getX)
			.addFunction("setY", &Point<float>::setY)
			.addFunction("getY", &Point<float>::getY)
			.addFunction("getTable", &Point<float>::getTable)
		.endClass()
		.beginClass<Point<unsigned int>>("UnsignedPoint")
			.addConstructor<void (*) (unsigned int, unsigned int)>()
			.addFunction("setX", &Point<unsigned int>::setX)
			.addFunction("getX", &Point<unsigned int>::getX)
			.addFunction("setY", &Point<unsigned int>::setY)
			.addFunction("getY", &Point<unsigned int>::getY)
			.addFunction("getTable", &Point<unsigned int>::getTable)
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
			.addFunction("isContainsTable", &Rectangle<int>::isContainsTable)
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
			.addFunction("isContainsTable", &Rectangle<float>::isContainsTable)
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
		.beginNamespace("ImGUI")
			.addFunction("beginWindow", &ImGuiEngine::beginWindow)
			.addFunction("endWindow", &ImGui::End)
			.addFunction("beginGroup", &ImGui::BeginGroup)
			.addFunction("endGroup", &ImGui::EndGroup)
			.addFunction("button", &ImGuiEngine::button)
			.addFunction("label", &ImGuiEngine::label)
			.addFunction("colorEdit4", &ImGuiEngine::colorEdit4)
		.endNamespace();
}