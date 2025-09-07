#include "core/engine/LuaApi.h"
#include <iostream>
#include "core/model/Game.h"
#include "ports/IInput.h"
#include "ports/IAudio.h"
#include "ports/KeyCode.h"

#define LUA_SET_KEY(name, alias)                                 \
    lua_pushinteger(L, static_cast<lua_Integer>(KeyCode::name)); \
    lua_setglobal(L, alias)

 
constexpr int MOUSE_LEFT = 1;
constexpr int MOUSE_MIDDLE = 2;
constexpr int MOUSE_RIGHT = 3;

// ----------------- CONSTANTES DE TECLAS -----------------
void registerKeyConstants(lua_State *L)
{
// Letras A–Z
LUA_SET_KEY(VK_A, "VK_A");
LUA_SET_KEY(VK_B, "VK_B");
LUA_SET_KEY(VK_C, "VK_C");
LUA_SET_KEY(VK_D, "VK_D");
LUA_SET_KEY(VK_E, "VK_E");
LUA_SET_KEY(VK_F, "VK_F");
LUA_SET_KEY(VK_G, "VK_G");
LUA_SET_KEY(VK_H, "VK_H");
LUA_SET_KEY(VK_I, "VK_I");
LUA_SET_KEY(VK_J, "VK_J");
LUA_SET_KEY(VK_K, "VK_K");
LUA_SET_KEY(VK_L, "VK_L");
LUA_SET_KEY(VK_M, "VK_M");
LUA_SET_KEY(VK_N, "VK_N");
LUA_SET_KEY(VK_O, "VK_O");
LUA_SET_KEY(VK_P, "VK_P");
LUA_SET_KEY(VK_Q, "VK_Q");
LUA_SET_KEY(VK_R, "VK_R");
LUA_SET_KEY(VK_S, "VK_S");
LUA_SET_KEY(VK_T, "VK_T");
LUA_SET_KEY(VK_U, "VK_U");
LUA_SET_KEY(VK_V, "VK_V");
LUA_SET_KEY(VK_W, "VK_W");
LUA_SET_KEY(VK_X, "VK_X");
LUA_SET_KEY(VK_Y, "VK_Y");
LUA_SET_KEY(VK_Z, "VK_Z");

// Números 0–9
LUA_SET_KEY(VK_0, "VK_0");
LUA_SET_KEY(VK_1, "VK_1");
LUA_SET_KEY(VK_2, "VK_2");
LUA_SET_KEY(VK_3, "VK_3");
LUA_SET_KEY(VK_4, "VK_4");
LUA_SET_KEY(VK_5, "VK_5");
LUA_SET_KEY(VK_6, "VK_6");
LUA_SET_KEY(VK_7, "VK_7");
LUA_SET_KEY(VK_8, "VK_8");
LUA_SET_KEY(VK_9, "VK_9");

// Especiais
LUA_SET_KEY(VK_ESCAPE, "VK_ESCAPE");
LUA_SET_KEY(VK_SPACE,  "VK_SPACE");
LUA_SET_KEY(VK_RETURN, "VK_RETURN");
LUA_SET_KEY(VK_TAB,    "VK_TAB");
LUA_SET_KEY(VK_SHIFT,  "VK_SHIFT");
LUA_SET_KEY(VK_CTRL,   "VK_CTRL");
LUA_SET_KEY(VK_ALT,    "VK_ALT");

// Setas
LUA_SET_KEY(VK_LEFT,  "VK_LEFT");
LUA_SET_KEY(VK_RIGHT, "VK_RIGHT");
LUA_SET_KEY(VK_UP,    "VK_UP");
LUA_SET_KEY(VK_DOWN,  "VK_DOWN");
}

// ----------------- FUNÇÕES LUA -----------------
int l_print(lua_State *L)
{
    const char *msg = lua_tostring(L, 1);
    if (msg)
        std::cout << "[Lua] " << msg << std::endl;
    return 0;
}

int l_quit(lua_State *L)
{
    std::cout << "[Lua] quit chamado" << std::endl;
    return 0;
}

int l_mouse_button_pressed(lua_State *L)
{
    auto input = static_cast<IInput *>(lua_touserdata(L, lua_upvalueindex(1)));

    int button = MOUSE_LEFT;
    if (lua_gettop(L) >= 1 && lua_isnumber(L, 1))
    {
        button = lua_tointeger(L, 1);
    }

    bool pressed = input->isMouseButtonPressed(button);
    lua_pushboolean(L, pressed);
    return 1;
}

int l_scene_goto_next(lua_State *L)
{
    auto game = static_cast<Game *>(lua_touserdata(L, lua_upvalueindex(1)));
    game->nextScene();
    return 0;
}

int l_sound_play(lua_State *L)
{
    auto audio = static_cast<IAudio *>(lua_touserdata(L, lua_upvalueindex(1)));
    if (lua_gettop(L) >= 1 && lua_isstring(L, 1))
    {
        std::string soundName = lua_tostring(L, 1);
        std::cout << "[Lua] tocar som: " << soundName << std::endl;
    }
    return 0;
}

int l_key_pressed(lua_State *L)
{
    auto input = static_cast<IInput *>(lua_touserdata(L, lua_upvalueindex(1)));
    int key = luaL_checkinteger(L, 1);
    bool pressed = input->isKeyPressed(static_cast<KeyCode>(key));
    lua_pushboolean(L, pressed);
    return 1;
}

int l_key_released(lua_State *L)
{
    auto input = static_cast<IInput *>(lua_touserdata(L, lua_upvalueindex(1)));
    int key = luaL_checkinteger(L, 1);
    bool released = input->isKeyReleased(static_cast<KeyCode>(key));
    lua_pushboolean(L, released);
    return 1;
}

int l_key_held(lua_State *L)
{
    auto input = static_cast<IInput *>(lua_touserdata(L, lua_upvalueindex(1)));
    int key = luaL_checkinteger(L, 1);
    bool held = input->isKeyHeld(static_cast<KeyCode>(key));
    lua_pushboolean(L, held);
    return 1;
}
