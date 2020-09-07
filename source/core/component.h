#pragma once
#include <core/includes.h>

namespace captain
{
	enum
	{
		ComponentType_Object
	};

	class Component
	{
	public:
		Component(const string& name = "");
		~Component();

		virtual void update(void* obj, int componentType);

		string getName();

	private:
		string name;
	};

	class ComponentDrawable : public Component
	{
	public:
		ComponentDrawable();
		~ComponentDrawable();

		void setTexture(const string& name);
		void setTextureRect(int x, int y, int width, int height);

		void setPosition(float x, float y);
		void move(float x, float y);

		void draw();

	private:
		Sprite sprite;
	};
}