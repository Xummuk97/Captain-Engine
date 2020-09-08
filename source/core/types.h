#pragma once
#include <core/includes.h>
#include <core/core.h>

namespace captain
{
	template<class T>
	class Rectangle
	{
	public:
		Rectangle(T x, T y, T width, T height)
			: rect(x, y, width, height)
		{}

		~Rectangle() {}

		void setX(T x) { rect.left = x; }
		T getX() { return rect.left; }

		void setY(T y) { rect.top = y; }
		T getY() { return rect.top; }
		
		void setWidth(T width) { rect.width = width; }
		T getWidth() { return rect.width; }

		void setHeight(T height) { rect.height = height; }
		T getHeight() { return rect.height; }

		bool isContains(T x, T y)
		{
			return rect.contains(x, y);
		}

		bool isIntersects(T x, T y, T width, T height)
		{
			return rect.intersects({ x, y, width, height });
		}

		bool isIntersectsTable(LuaRef value)
		{
			return rect.intersects({ value["x"].cast<T>(), value["y"].cast<T>(), value["width"].cast<T>(), value["height"].cast<T>() });
		}

		LuaRef getTable()
		{
			LuaRef value = Core::luaEngine.createTable();
			value["x"] = rect.left;
			value["y"] = rect.top;
			value["width"] = rect.width;
			value["height"] = rect.height;
			return value;
		}

	private:
		Rect<T> rect;
	};
}