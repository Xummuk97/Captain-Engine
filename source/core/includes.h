#pragma once
// SFML-includes
#include <SFML\Main.hpp>
#include <SFML/Graphics.hpp>

// STD-includes
#include <string>
#include <list>
#include <vector>
#include <iostream>

// Lua-includes
extern "C"
{
#include "lua/lua.h"
#include "lua/lauxlib.h"
#include "lua/lualib.h"
}
#include <LuaBridge/LuaBridge.h>

// ImGUI-includes
#include <imgui.h>
#include <imgui-SFML.h>

// Box2D-includes
#include <box2d/b2_block_allocator.h>
#include <box2d/b2_body.h>
#include <box2d/b2_broad_phase.h>
#include <box2d/b2_chain_shape.h>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_collision.h>
#include <box2d/b2_contact.h>
#include <box2d/b2_contact_manager.h>
#include <box2d/b2_distance.h>
#include <box2d/b2_distance_joint.h>
#include <box2d/b2_draw.h>
#include <box2d/b2_dynamic_tree.h>
#include <box2d/b2_edge_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_friction_joint.h>
#include <box2d/b2_gear_joint.h>
#include <box2d/b2_growable_stack.h>
#include <box2d/b2_joint.h>
#include <box2d/b2_math.h>
#include <box2d/b2_motor_joint.h>
#include <box2d/b2_mouse_joint.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_prismatic_joint.h>
#include <box2d/b2_pulley_joint.h>
#include <box2d/b2_revolute_joint.h>
#include <box2d/b2_rope.h>
#include <box2d/b2_settings.h>
#include <box2d/b2_shape.h>
#include <box2d/b2_stack_allocator.h>
#include <box2d/b2_time_of_impact.h>
#include <box2d/b2_time_step.h>
#include <box2d/b2_timer.h>
#include <box2d/b2_weld_joint.h>
#include <box2d/b2_wheel_joint.h>
#include <box2d/b2_world.h>
#include <box2d/b2_world_callbacks.h>
#include <box2d/box2d.h>

// Namespaces
using namespace luabridge;
using namespace std;
using namespace sf;