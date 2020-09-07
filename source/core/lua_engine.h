#pragma once
#include <core/includes.h>

namespace captain
{
	class LuaEngine
	{
	public:
		LuaEngine();

		bool include(const string& file);
		Namespace getNamespace();

		LuaRef getVariable(const string& name);

		template <class T>
		void setVariable(const string& name, T value)
		{
			setGlobal(luaState, value, name.c_str());
		}

		template<class T>
		LuaRef createVariable(T value)
		{
			return LuaRef(luaState, value);
		}

		LuaRef createTable();

		void free();
		void eval(const string& text);

	private:
		lua_State* luaState;
	};
}