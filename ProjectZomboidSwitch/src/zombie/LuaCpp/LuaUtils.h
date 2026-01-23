
// LuaUtils.h
#pragma once
#include <string>
#include "lua.hpp"

namespace zombie {

// LuaUtils provides advanced utilities for Lua table manipulation, serialization,
// pretty-printing, type-safe conversion, and error/logging for C++/Lua interop.
class LuaUtils {
public:
    // --- Additional serialization formats ---
#ifdef YAML_CPP_VERSION_MAJOR
    // Convert a Lua table at idx to a YAML node.
    static YAML::Node TableToYaml(lua_State* L, int idx);
    // Convert a YAML node to a Lua table.
    static void YamlToTable(lua_State* L, const YAML::Node& node);
#endif
#ifdef TOML11_VERSION
    // Convert a Lua table at idx to a TOML value.
    static toml::value TableToToml(lua_State* L, int idx);
    // Convert a TOML value to a Lua table.
    static void TomlToTable(lua_State* L, const toml::value& v);
#endif

    // --- Shallow table comparison ---
    // Compare two Lua tables for shallow (non-recursive) equality.
    static bool TablesShallowEqual(lua_State* L, int idx1, int idx2);

    // --- Advanced error/logging ---
    enum LogLevel { LOG_ERROR, LOG_WARN, LOG_INFO, LOG_DEBUG };
    // Log a message with a given log level (to stderr).
    static void Log(const std::string& msg, LogLevel level = LOG_INFO);

    // --- Pretty-printing and cycle-safe serialization ---
    // Serialize a Lua table to a pretty-printed string (cycle-safe, handles cycles).
    static std::string SerializeTablePretty(lua_State* L, int idx, int indent = 0, std::unordered_set<const void*>* seen = nullptr);

    // --- Table serialization ---
    // Serialize a Lua table at idx to a Lua code string.
    static std::string SerializeTable(lua_State* L, int idx);
#ifdef NLOHMANN_JSON_VERSION_MAJOR
    // Serialize a Lua table at idx to JSON (requires nlohmann/json).
    static nlohmann::json TableToJson(lua_State* L, int idx);
    // Convert a JSON object to a Lua table.
    static void JsonToTable(lua_State* L, const nlohmann::json& j);
#endif

    // --- Table deserialization (from Lua code string) ---
    // Deserialize a Lua table from a Lua code string.
    static void DeserializeTable(lua_State* L, const std::string& luaCode);

    // --- Table deep copy ---
    // Deep copy a Lua table from one index to another.
    static void DeepCopyTable(lua_State* L, int fromIdx, int toIdx);

    // --- Table deep equality ---
    // Compare two Lua tables for deep (recursive) equality.
    static bool TablesEqual(lua_State* L, int idx1, int idx2);

    // --- Type-safe conversion helpers ---
    static int ToInt(lua_State* L, int idx) { return (int)lua_tointeger(L, idx); }
    static double ToDouble(lua_State* L, int idx) { return lua_tonumber(L, idx); }
    static bool ToBool(lua_State* L, int idx) { return lua_toboolean(L, idx) != 0; }
    static std::string ToString(lua_State* L, int idx) {
        const char* s = lua_tostring(L, idx);
        return s ? std::string(s) : std::string();
    }

    // --- Type-safe push to Lua stack ---
    template<typename T>
    static void Push(lua_State* L, const T& value);
};

    // --- Template specializations for Push<T> ---
    template<>
    inline void LuaUtils::Push<int>(lua_State* L, const int& value) { Push(L, value); }
    template<>
    inline void LuaUtils::Push<float>(lua_State* L, const float& value) { Push(L, (double)value); }
    template<>
    inline void LuaUtils::Push<double>(lua_State* L, const double& value) { Push(L, value); }
    template<>
    inline void LuaUtils::Push<bool>(lua_State* L, const bool& value) { Push(L, value); }
    template<>
    inline void LuaUtils::Push<std::string>(lua_State* L, const std::string& value) { Push(L, value); }
    // Type-safe conversion from Lua stack
    template<typename T>
    static T To(lua_State* L, int idx);
};

// --- Template specializations for To<T> ---
template<>
inline int LuaUtils::To<int>(lua_State* L, int idx) { return ToInt(L, idx); }
template<>
inline float LuaUtils::To<float>(lua_State* L, int idx) { return (float)ToDouble(L, idx); }
template<>
inline double LuaUtils::To<double>(lua_State* L, int idx) { return ToDouble(L, idx); }
template<>
inline bool LuaUtils::To<bool>(lua_State* L, int idx) { return ToBool(L, idx); }
template<>
inline std::string LuaUtils::To<std::string>(lua_State* L, int idx) { return ToString(L, idx); }
public:
    // Stack helpers
    static inline void Push(lua_State* L, int value) noexcept { lua_pushinteger(L, value); }
    static inline void Push(lua_State* L, double value) noexcept { lua_pushnumber(L, value); }
    static inline void Push(lua_State* L, const std::string& value) noexcept { lua_pushlstring(L, value.c_str(), value.size()); }
    static inline void Push(lua_State* L, bool value) noexcept { lua_pushboolean(L, value); }
    static inline void Push(lua_State* L, const char* value) noexcept { lua_pushstring(L, value); }

    // Type checking
    static inline bool IsTable(lua_State* L, int idx) noexcept { return lua_istable(L, lua_absindex(L, idx)); }
    static inline bool IsFunction(lua_State* L, int idx) noexcept { return lua_isfunction(L, lua_absindex(L, idx)); }
    static inline bool IsString(lua_State* L, int idx) noexcept { return lua_isstring(L, lua_absindex(L, idx)); }
    static inline bool IsNumber(lua_State* L, int idx) noexcept { return lua_isnumber(L, lua_absindex(L, idx)); }

    // Conversion
    static inline std::string ToString(lua_State* L, int idx) {
        size_t len;
        const char* str = lua_tolstring(L, lua_absindex(L, idx), &len);
        return str ? std::string(str, len) : std::string();
    }
    static inline int ToInt(lua_State* L, int idx) noexcept { return static_cast<int>(lua_tointeger(L, lua_absindex(L, idx))); }
    static inline double ToDouble(lua_State* L, int idx) noexcept { return lua_tonumber(L, lua_absindex(L, idx)); }
    static inline bool ToBool(lua_State* L, int idx) noexcept { return lua_toboolean(L, lua_absindex(L, idx)) != 0; }
};

} // namespace zombie
