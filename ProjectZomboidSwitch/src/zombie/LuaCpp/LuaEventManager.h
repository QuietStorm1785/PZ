
#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "lua.hpp"

namespace zombie {

// LuaEventManager manages registration and triggering of C++ and Lua event handlers.
// Allows C++ and Lua functions to be registered as event handlers and triggered by name.
class LuaEventManager {
public:
    // Register a C++ function as an event handler (exposed to Lua).
    void RegisterEvent(const std::string& eventName, lua_CFunction handler);
    // Register a Lua function as an event handler by name.
    void RegisterLuaEvent(const std::string& eventName, const std::string& luaFuncName);

    // Trigger an event by name, passing arguments (nargs: #args, nresults: #results).
    bool TriggerEvent(const std::string& eventName, int nargs = 0, int nresults = 0);

    // Singleton access to the LuaEventManager instance.
    static LuaEventManager& Instance();

private:
    LuaEventManager();
    ~LuaEventManager();
    // Map of event name to Lua registry reference for handler.
    std::unordered_map<std::string, int> eventRefs;
};

} // namespace zombie
