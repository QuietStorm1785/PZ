
#pragma once
#include <string>
#include <unordered_map>
#include <typeindex>
#include <functional>
#include "lua.hpp"

namespace zombie {

// LuaObjectMapper maps C++ objects and types to Lua tables/classes and vice versa.
// Provides helpers for registering types, pushing/pulling objects, and global registration.
class LuaObjectMapper {
public:
    // Get the singleton instance of LuaObjectMapper.
    static LuaObjectMapper& Instance();

    // Register a C++ type with a Lua metatable and constructor.
    // luaName: name of the Lua metatable/class
    // methods: array of Lua methods for the type
    // ctor: function to construct a C++ object from Lua
    template<typename T>
    void RegisterType(const std::string& luaName, const luaL_Reg* methods, std::function<T*(lua_State*)> ctor);

    // Push a C++ object to Lua as userdata (with metatable).
    template<typename T>
    void Push(lua_State* L, T* obj);

    // Get a C++ object from the Lua stack (by metatable/type).
    template<typename T>
    T* Get(lua_State* L, int idx);

    // Register a global C++ object as a Lua table/global.
    template<typename T>
    void RegisterGlobal(const std::string& luaName, T* obj);

private:
    LuaObjectMapper();
    ~LuaObjectMapper();
    // Map from C++ type_index to Lua metatable name for type safety.
    std::unordered_map<std::type_index, std::string> typeToMetatable;
};

} // namespace zombie
