#pragma once
#include <core/includes.h>

namespace captain
{
	class Component
	{
	public:
		Component();
		~Component();

		virtual void update() = 0;

		string getLuaCallbackName();

	protected:
		void setLuaCallbackName(const string& name);

	private:
		string luaCallbackName = "-";
	};

	class Components
	{
	public:
		Components(void* obj);
		~Components();

		void addComponent(Component* component);
		void addCustomComponent(const string& name, Component* component);

		void updateComponents();
		void updateCustomComponent(const string& name);

		template<class T>
		T* getCustomComponent(const string& name)
		{
			return (T*)customComponents[name];
		}

	private:
		void* obj;
		list<Component*> components;
		map<string, Component*> customComponents;
	};

	class ComponentLua : public Component
	{
	public:
		ComponentLua(const string& luaCallbackName);
		~ComponentLua();

		void update();
	};

	class ComponentDrawable : public Component
	{
	public:
		ComponentDrawable();
		~ComponentDrawable();

		void update();

		void setTexture(const string& name);
		void setTextureRect(int x, int y, int width, int height);
		
		Sprite* getSprite();

	private:
		Sprite sprite;
	};

	class ComponentPhysix : public Component
	{
	public:
		ComponentPhysix(Sprite* sprite);
		~ComponentPhysix();

		void update();

	private:
		Sprite* sprite;
		b2BodyDef bodyDef;
		b2Body* body;
		b2PolygonShape* shape;
		b2FixtureDef fixture;
	};
}