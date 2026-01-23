
#pragma once
#include <string>
#include <vector>
#include "lua.hpp"


namespace zombie {


// LuaBinder provides static helpers for binding C++ classes, functions, and constants to Lua.
class LuaBinder {
public:
    // Register a C++ class and its methods with Lua under the given name.
    static void RegisterClass(lua_State* L, const char* name, const luaL_Reg* methods);

    // Register a global C++ function with Lua under the given name.
    static void RegisterFunction(lua_State* L, const char* name, lua_CFunction fn);

    // Register an enum or integer constant with Lua under the given name.
    static void RegisterConstant(lua_State* L, const char* name, int value);
};


} // namespace zombie
