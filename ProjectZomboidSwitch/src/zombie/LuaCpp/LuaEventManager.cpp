
#include "LuaEventManager.h"
#include "LuaManager.h"


namespace zombie {


// Singleton accessor for LuaEventManager.
LuaEventManager& LuaEventManager::Instance() {
    static LuaEventManager instance;
    return instance;
}


// Constructor/Destructor for LuaEventManager. No special initialization needed.
LuaEventManager::LuaEventManager() {}
LuaEventManager::~LuaEventManager() {}


// Register a C++ function as an event handler (exposed to Lua).
void LuaEventManager::RegisterEvent(const std::string& eventName, lua_CFunction handler) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_register(L, eventName.c_str(), handler);
    // Optionally store ref for later
}


// Register a Lua function as an event handler by name.
void LuaEventManager::RegisterLuaEvent(const std::string& eventName, const std::string& luaFuncName) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_getglobal(L, luaFuncName.c_str());
    if (lua_isfunction(L, -1)) {
        int ref = luaL_ref(L, LUA_REGISTRYINDEX);
        eventRefs[eventName] = ref;
    } else {
        lua_pop(L, 1);
    }
}


// Trigger an event by name, passing arguments (nargs: #args, nresults: #results).
bool LuaEventManager::TriggerEvent(const std::string& eventName, int nargs, int nresults) {
    lua_State* L = LuaManager::Instance().GetState();
    auto it = eventRefs.find(eventName);
    if (it == eventRefs.end()) return false;
    lua_rawgeti(L, LUA_REGISTRYINDEX, it->second);
    if (!lua_isfunction(L, -1)) {
        lua_pop(L, 1);
        return false;
    }
    if (lua_pcall(L, nargs, nresults, 0) != LUA_OK) {
        const char* err = lua_tostring(L, -1);
        // Optionally log error
        lua_pop(L, 1);
        return false;
    }
    return true;
}

} // namespace zombie
