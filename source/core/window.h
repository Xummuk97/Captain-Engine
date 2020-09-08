#pragma once
#include <core/includes.h>

namespace captain
{
	class Window
	{
	public:
		Window();
		~Window();

		void create(const string& title, int width, int height);
		void draw(const Sprite& sprite);

		void startWindow();

		void setTitle(const string& title);
		void setFPS(unsigned int fps);
		void setVerticalSync(bool isEnabled);
		void setPosition(int x, int y);
		void setSize(unsigned int x, unsigned int y);

		LuaRef getPosition();
		LuaRef getSize();

	private:
		void initImGUI();

		void processEvent();
		void processGame();

		RenderWindow* renderWindow = nullptr;
		Time time;
	};
}