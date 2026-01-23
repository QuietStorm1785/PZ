
#include "LuaBinder.h"


namespace zombie {


// Register a C++ class and its methods with Lua under the given name.
void LuaBinder::RegisterClass(lua_State* L, const char* name, const luaL_Reg* methods) {
    luaL_newmetatable(L, name);
    luaL_setfuncs(L, methods, 0);
    lua_pushvalue(L, -1);
    lua_setfield(L, -1, "__index");
    lua_setglobal(L, name);
}


// Register a global C++ function with Lua under the given name.
void LuaBinder::RegisterFunction(lua_State* L, const char* name, lua_CFunction fn) {
    lua_register(L, name, fn);
}


// Register an enum or integer constant with Lua under the given name.
void LuaBinder::RegisterConstant(lua_State* L, const char* name, int value) {
    lua_pushinteger(L, value);
    lua_setglobal(L, name);
}

} // namespace zombie
