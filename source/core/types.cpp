#include <core/types.h>

namespace captain
{
	// Класс Vector2 //////////////////////////////////////////////////////
	Vector2::Vector2(double x, double y) : x(x), y(y)
	{
	}

	Vector2::operator Vector2i()
	{
		return Vector2i(x, y);
	}

	Vector2::operator Vector2f()
	{
		return Vector2f(x, y);
	}

	Vector2::operator Vector2u()
	{
		return Vector2u(x, y);
	}



/*	// Класс Vector3 //////////////////////////////////////////////////////
	Vector3::Vector3(double x, double y, double z) : x(x), y(y), z(z)
	{
	}

	Vector3::operator Vector3i()
	{
		return Vector3i(x, y);
	}

	Vector3::operator Vector3f()
	{
		return Vector3f(x, y);
	}

	Vector3::operator Vector3u()
	{
		return Vector3u(x, y);
	}*/
}
