
#include "LuaObjectMapper.h"
#include <stdexcept>

namespace zombie {

// Singleton accessor for LuaObjectMapper.
LuaObjectMapper& LuaObjectMapper::Instance() {
    static LuaObjectMapper instance;
    return instance;
}

// Constructor/Destructor for LuaObjectMapper. No special initialization needed.
LuaObjectMapper::LuaObjectMapper() {}
LuaObjectMapper::~LuaObjectMapper() {}

// Example: RegisterType for IsoObject (mirroring MapObjects)
// Registers a C++ type with a Lua metatable and constructor.
template<typename T>
void LuaObjectMapper::RegisterType(const std::string& luaName, const luaL_Reg* methods, std::function<T*(lua_State*)> ctor) {
    typeToMetatable[typeid(T)] = luaName;
    lua_State* L = nullptr; // Should be set to your Lua state
    luaL_newmetatable(L, luaName.c_str());
    luaL_setfuncs(L, methods, 0);
    lua_pushvalue(L, -1);
    lua_setfield(L, -1, "__index");
    lua_setglobal(L, luaName.c_str());
    // Optionally store ctor for later
}

// Push a C++ object to Lua as userdata (with metatable).
template<typename T>
void LuaObjectMapper::Push(lua_State* L, T* obj) {
    if (!obj) { lua_pushnil(L); return; }
    T** udata = static_cast<T**>(lua_newuserdata(L, sizeof(T*))); *udata = obj;
    luaL_getmetatable(L, typeToMetatable[typeid(T)].c_str());
    lua_setmetatable(L, -2);
}

// Get a C++ object from the Lua stack (by metatable/type).
template<typename T>
T* LuaObjectMapper::Get(lua_State* L, int idx) {
    T** udata = static_cast<T**>(luaL_checkudata(L, idx, typeToMetatable[typeid(T)].c_str()));
    if (!udata) throw std::runtime_error("Invalid userdata type for LuaObjectMapper::Get");
    return *udata;
}

// Register a global C++ object as a Lua table/global.
template<typename T>
void LuaObjectMapper::RegisterGlobal(const std::string& luaName, T* obj) {
    lua_State* L = nullptr; // Should be set to your Lua state
    Push(L, obj);
    lua_setglobal(L, luaName.c_str());
}

// Explicit instantiations for common types (example)
// These lines ensure the template methods are instantiated for IsoObject.
template void LuaObjectMapper::RegisterType<class IsoObject>(const std::string&, const luaL_Reg*, std::function<IsoObject*(lua_State*)>);
template void LuaObjectMapper::Push<class IsoObject>(lua_State*, IsoObject*);
template IsoObject* LuaObjectMapper::Get<class IsoObject>(lua_State*, int);
template void LuaObjectMapper::RegisterGlobal<class IsoObject>(const std::string&, IsoObject*);

} // namespace zombie
