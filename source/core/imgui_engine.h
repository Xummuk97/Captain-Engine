#pragma once
#include <core/includes.h>

namespace captain
{
	class ImGuiEngine
	{
	public:
		static void beginWindow(const string& text);
		static bool button(const string& text);
		static void label(const string& text);
		static void colorEdit4(const string& text, LuaRef value);
	};
}