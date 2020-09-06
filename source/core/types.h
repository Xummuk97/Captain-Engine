#pragma once
#include <core/includes.h>

namespace captain
{
	class Vector2
	{
	public:
		Vector2(double x = 0, double y = 0);
		~Vector2() = default;

		// Non lua methods
		operator Vector2i();
		operator Vector2f();
		operator Vector2u();

	private:
		double x = 0, y = 0;
	};

	class Rect
	{
	public:
		Rect(double left = 0, double right = 0, double width = 0, double height = 0);
		~Rect() = default;

		// Non lua methods
		operator IntRect();
		operator FloatRect();

	private:
		double left, right, width, height;
	};
};
