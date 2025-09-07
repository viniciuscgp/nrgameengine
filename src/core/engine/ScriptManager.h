#pragma once
#include <lua5.3/lua.hpp>
#include <string>

class Game;
class IInput;
class IAudio;
class Instance;

class ScriptManager {
    lua_State* L;

public:
    ScriptManager();
    ~ScriptManager();

    void registerAPI(Game* game, IInput* input, IAudio* audio);

    void registerFunction(const std::string& name, lua_CFunction fn, void* userdata = nullptr);

    bool runCode(const std::string& code);
    bool runInstanceCode(Instance* instance, const std::string& code);
};
