#include <core/window.h>
#include <core/core.h>

captain::Window::Window()
{}

captain::Window::~Window()
{
	delete renderWindow;
}

void captain::Window::create(const string& title, int width, int height)
{
	renderWindow = new RenderWindow(VideoMode(width, height), title);
}

void captain::Window::draw(const Sprite& sprite)
{
	renderWindow->draw(sprite);
}

void captain::Window::initImGUI()
{
	ImGui::SFML::Init(*renderWindow);
}

void captain::Window::startWindow()
{
	initImGUI();

	while (renderWindow->isOpen())
	{
		processEvent();
		processGame();
	}

	ImGui::SFML::Shutdown();
}

void captain::Window::setTitle(const string& title)
{
	renderWindow->setTitle(title);
}

void captain::Window::setFPS(unsigned int fps)
{
	renderWindow->setFramerateLimit(fps);
}

void captain::Window::setVerticalSync(bool isEnabled)
{
	renderWindow->setVerticalSyncEnabled(isEnabled);
}

void captain::Window::setPosition(int x, int y)
{
	renderWindow->setPosition({ x, y });
}

void captain::Window::setSize(unsigned int x, unsigned int y)
{
	renderWindow->setSize({ x, y });
}

LuaRef captain::Window::getPosition()
{
	Vector2i position = renderWindow->getPosition();

	LuaRef value = Core::luaEngine.createTable();
	value["x"] = position.x;
	value["y"] = position.y;
	return value;
}

LuaRef captain::Window::getSize()
{
	Vector2u size = renderWindow->getSize();

	LuaRef value = Core::luaEngine.createTable();
	value["x"] = size.x;
	value["y"] = size.y;
	return value;
}

void captain::Window::processEvent()
{
	sf::Event event;
	while (renderWindow->pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(event);

		if (event.type == sf::Event::Closed)
		{
			renderWindow->close();
		}
	}
}

void captain::Window::processGame()
{
	time = Core::clock.restart();
	Core::deltaTime = time.asSeconds();

	Core::worldPhysix->Step(1 / 60.0f, 1, 1);

	Core::level.update();
	ImGui::SFML::Update(*renderWindow, time);
	Core::luaEngine.getVariable("onGUI")();

	renderWindow->clear();
	Core::level.draw();
	ImGui::SFML::Render(*renderWindow);
	renderWindow->display();

	Core::luaEngine.free();
}
