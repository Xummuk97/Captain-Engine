#pragma once
#include <core/includes.h>

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

private:
	string name;
};

class ComponentDrawable : Component
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