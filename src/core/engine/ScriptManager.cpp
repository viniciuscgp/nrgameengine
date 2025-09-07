#include "ScriptManager.h"
#include "core/model/Game.h"
#include "core/model/Instance.h"
#include "core/engine/LuaApi.h" 
#include <iostream>

ScriptManager::ScriptManager() {
    L = luaL_newstate();
    luaL_openlibs(L);
}

ScriptManager::~ScriptManager() {
    if (L) lua_close(L);
}

void ScriptManager::registerAPI(Game* game, IInput* input, IAudio* audio) {
    registerFunction("print", l_print);
    registerFunction("quit", l_quit);

    registerFunction("mouse_button_pressed", l_mouse_button_pressed, input);
    registerFunction("scene_goto_next", l_scene_goto_next, game);
    registerFunction("sound_play", l_sound_play, audio);

    registerFunction("key_pressed", l_key_pressed, input);
    registerFunction("key_released", l_key_released, input);
    registerFunction("key_held", l_key_held, input);    

    registerKeyConstants(L);    
}

bool ScriptManager::runCode(const std::string& code) {
    if (luaL_dostring(L, code.c_str()) != LUA_OK) {
        std::cerr << "Erro Lua: " << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
        return false;
    }
    return true;
}

bool ScriptManager::runInstanceCode(Instance* instance, const std::string& code) {
    // expõe variáveis da instância
    lua_newtable(L);
    lua_pushnumber(L, instance->x); lua_setfield(L, -2, "x");
    lua_pushnumber(L, instance->y); lua_setfield(L, -2, "y");
    lua_pushnumber(L, instance->force_x); lua_setfield(L, -2, "force_x");
    lua_pushnumber(L, instance->force_y); lua_setfield(L, -2, "force_y");
    lua_pushnumber(L, instance->friction); lua_setfield(L, -2, "friction");

    lua_setglobal(L, "self"); // em Lua: acessar via self.x, self.y

    bool ok = runCode(code);

    // depois de rodar, atualizar os valores de volta
    lua_getglobal(L, "self");
    if (lua_istable(L, -1)) {
        lua_getfield(L, -1, "x");        if (lua_isnumber(L, -1)) instance->x = lua_tonumber(L, -1); lua_pop(L,1);
        lua_getfield(L, -1, "y");        if (lua_isnumber(L, -1)) instance->y = lua_tonumber(L, -1); lua_pop(L,1);
        lua_getfield(L, -1, "force_x");  if (lua_isnumber(L, -1)) instance->force_x = lua_tonumber(L, -1); lua_pop(L,1);
        lua_getfield(L, -1, "force_y");  if (lua_isnumber(L, -1)) instance->force_y = lua_tonumber(L, -1); lua_pop(L,1);
        lua_getfield(L, -1, "friction"); if (lua_isnumber(L, -1)) instance->friction = lua_tonumber(L, -1); lua_pop(L,1);
    }
    lua_pop(L, 1);

    return ok;
}

void ScriptManager::registerFunction(const std::string& name, lua_CFunction fn, void* userdata) {
    if (userdata) {
        lua_pushlightuserdata(L, userdata);
        lua_pushcclosure(L, fn, 1); // 1 upvalue = ponteiro
    } else {
        lua_pushcfunction(L, fn);
    }
    lua_setglobal(L, name.c_str());
}

