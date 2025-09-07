#pragma once
#include <lua5.3/lua.hpp>

// forward declarations para poder usar ponteiros
class Game;
class IInput;
class IAudio;

// funções que a Lua pode chamar
int l_print(lua_State* L);
int l_quit(lua_State* L);
int l_mouse_button_pressed(lua_State* L);
int l_scene_goto_next(lua_State* L);
int l_sound_play(lua_State* L);

int l_key_pressed(lua_State* L);
int l_key_released(lua_State* L);
int l_key_held(lua_State* L);

void registerKeyConstants(lua_State* L);
