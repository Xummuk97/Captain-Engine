#include "imgui_engine.h"
#include <core/core.h>

void ImGuiEngine::beginWindow(const string& text)
{
	ImGui::Begin(text.c_str());
}

bool ImGuiEngine::button(const string& text)
{
	return ImGui::Button(text.c_str());
}

void ImGuiEngine::label(const string& text)
{
	ImGui::Text(text.c_str());
}

void ImGuiEngine::colorEdit4(const string& text, LuaRef value)
{
	float arr[4];
	arr[0] = value[1];
	arr[1] = value[2];
	arr[2] = value[3];
	arr[3] = value[4];
	ImGui::ColorEdit4(text.c_str(), arr);

	value[1] = arr[0];
	value[2] = arr[1];
	value[3] = arr[2];
	value[4] = arr[3];
}