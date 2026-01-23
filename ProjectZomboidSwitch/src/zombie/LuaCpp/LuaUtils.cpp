
#include "LuaUtils.h"

namespace zombie {

bool LuaUtils::TablesShallowEqual(lua_State* L, int idx1, int idx2) {
    if (!lua_istable(L, idx1) || !lua_istable(L, idx2)) return false;
    lua_pushnil(L);
    while (lua_next(L, idx1 < 0 ? idx1 - 1 : idx1) != 0) {
        lua_pushvalue(L, -2); // duplicate key
        lua_gettable(L, idx2 < 0 ? idx2 - 2 : idx2);
        if (!lua_compare(L, -2, -1, LUA_OPEQ)) {
            lua_pop(L, 2);
            return false;
        }
        lua_pop(L, 2);
    }
    return true;
}

// Compare two Lua tables for shallow (non-recursive) equality.
// Returns true if all key-value pairs in idx1 exist and are equal in idx2.

void LuaUtils::Log(const std::string& msg, LogLevel level) {
    const char* prefix = "[INFO] ";
    if (level == LOG_ERROR) prefix = "[ERROR] ";
    else if (level == LOG_WARN) prefix = "[WARN] ";
    else if (level == LOG_DEBUG) prefix = "[DEBUG] ";
    fprintf(stderr, "%s%s\n", prefix, msg.c_str());
}

// Log a message with a given log level (to stderr).

std::string LuaUtils::SerializeTablePretty(lua_State* L, int idx, int indent, std::unordered_set<const void*>* seen) {
    if (!lua_istable(L, idx)) return "nil";
    if (!seen) {
        std::unordered_set<const void*> localSeen;
        return SerializeTablePretty(L, idx, indent, &localSeen);
    }
    const void* ptr = lua_topointer(L, idx);
    if (seen->count(ptr)) return "<cycle>";
    seen->insert(ptr);
    std::string pad(indent, ' ');
    std::string result = "{\n";
    lua_pushnil(L);
    bool first = true;
    while (lua_next(L, idx < 0 ? idx - 1 : idx) != 0) {
        if (!first) result += ",\n";
        first = false;
        result += pad + "  ";
        // Key
        if (lua_type(L, -2) == LUA_TSTRING) {
            result += "[\"" + ToString(L, -2) + "\"] = ";
        } else if (lua_type(L, -2) == LUA_TNUMBER) {
            result += "[" + ToString(L, -2) + "] = ";
        } else {
            result += "[?] = ";
        }
        // Value
        if (lua_istable(L, -1)) {
            result += SerializeTablePretty(L, -1, indent + 2, seen);
        } else if (lua_type(L, -1) == LUA_TSTRING) {
            result += '"' + ToString(L, -1) + '"';

// Serialize a Lua table to a pretty-printed string (cycle-safe, handles cycles).
        } else if (lua_type(L, -1) == LUA_TNUMBER) {
            result += ToString(L, -1);
        } else if (lua_type(L, -1) == LUA_TBOOLEAN) {
            result += lua_toboolean(L, -1) ? "true" : "false";
        } else if (lua_isnil(L, -1)) {
            result += "nil";
        } else {
            result += "?";
        }
        lua_pop(L, 1);
    }
    result += "\n" + pad + "}";
    return result;
}

// --- Table serialization to Lua code string ---
std::string LuaUtils::SerializeTable(lua_State* L, int idx) {
    if (!lua_istable(L, idx)) return "nil";
    std::string result = "{";
    lua_pushnil(L);
    bool first = true;
    while (lua_next(L, idx < 0 ? idx - 1 : idx) != 0) {
        if (!first) result += ", ";
        first = false;
        // Key
        if (lua_type(L, -2) == LUA_TSTRING) {
            result += "[\"" + ToString(L, -2) + "\"]=";
        } else if (lua_type(L, -2) == LUA_TNUMBER) {
            result += "[" + ToString(L, -2) + "]=";
        } else {
            result += "[?]=";
        }
        // Value
        if (lua_istable(L, -1)) {
            result += SerializeTable(L, -1);
        } else if (lua_type(L, -1) == LUA_TSTRING) {
            result += "\"" + ToString(L, -1) + "\"";
        } else if (lua_type(L, -1) == LUA_TNUMBER) {
            result += ToString(L, -1);
        } else if (lua_type(L, -1) == LUA_TBOOLEAN) {
            result += lua_toboolean(L, -1) ? "true" : "false";
        } else if (lua_isnil(L, -1)) {
            result += "nil";
        } else {
            result += "?";
        }
        lua_pop(L, 1);
    }
    result += "}";
    return result;
}

#ifdef NLOHMANN_JSON_VERSION_MAJOR
// JSON serialization/deserialization stubs (implement if nlohmann/json is available)
nlohmann::json LuaUtils::TableToJson(lua_State* L, int idx) {
    return nlohmann::json();
}
void LuaUtils::JsonToTable(lua_State* L, const nlohmann::json& j) {}
#endif

// --- Table deserialization from Lua code string ---
void LuaUtils::DeserializeTable(lua_State* L, const std::string& luaCode) {
    std::string chunk = "return " + luaCode;
    if (luaL_loadstring(L, chunk.c_str()) == LUA_OK) {
        lua_call(L, 0, 1); // leaves table on stack
    } else {
        lua_pushnil(L);
    }
}

// --- Table deep copy ---
void LuaUtils::DeepCopyTable(lua_State* L, int fromIdx, int toIdx) {
    if (!lua_istable(L, fromIdx) || !lua_istable(L, toIdx)) return;
    lua_pushnil(L);
    while (lua_next(L, fromIdx < 0 ? fromIdx - 1 : fromIdx) != 0) {
        lua_pushvalue(L, -2); // duplicate key
        if (lua_istable(L, -2)) {
            lua_newtable(L);
            DeepCopyTable(L, -2, -1);
            lua_settable(L, toIdx < 0 ? toIdx - 3 : toIdx);
        } else {
            lua_pushvalue(L, -2); // duplicate value
            lua_settable(L, toIdx < 0 ? toIdx - 3 : toIdx);
        }
        lua_pop(L, 1); // pop value
    }
}

// --- Table deep equality ---
bool LuaUtils::TablesEqual(lua_State* L, int idx1, int idx2) {
    if (!lua_istable(L, idx1) || !lua_istable(L, idx2)) return false;
    lua_pushnil(L);
    while (lua_next(L, idx1 < 0 ? idx1 - 1 : idx1) != 0) {
        lua_pushvalue(L, -2); // duplicate key
        lua_gettable(L, idx2 < 0 ? idx2 - 2 : idx2);
        if (lua_type(L, -2) == LUA_TTABLE && lua_type(L, -1) == LUA_TTABLE) {
            if (!TablesEqual(L, -2, -1)) {
                lua_pop(L, 2);
                return false;
            }
        } else if (!lua_compare(L, -2, -1, LUA_OPEQ)) {
            lua_pop(L, 2);
            return false;
        }
        lua_pop(L, 2);
    }
    return true;
}

void LuaUtils::Push(lua_State* L, int value) {
    lua_pushinteger(L, value);
}
void LuaUtils::Push(lua_State* L, double value) {
    lua_pushnumber(L, value);
}
void LuaUtils::Push(lua_State* L, const std::string& value) {
    lua_pushlstring(L, value.c_str(), value.size());
}
void LuaUtils::Push(lua_State* L, bool value) {
    lua_pushboolean(L, value);
}
void LuaUtils::Push(lua_State* L, const char* value) {
    lua_pushstring(L, value);
}

bool LuaUtils::IsTable(lua_State* L, int idx) {
    return lua_istable(L, idx);
}
bool LuaUtils::IsFunction(lua_State* L, int idx) {
    return lua_isfunction(L, idx);
}
bool LuaUtils::IsString(lua_State* L, int idx) {
    return lua_isstring(L, idx);
}
bool LuaUtils::IsNumber(lua_State* L, int idx) {
    return lua_isnumber(L, idx);
}

std::string LuaUtils::ToString(lua_State* L, int idx) {
    size_t len;
    const char* str = lua_tolstring(L, idx, &len);
    return str ? std::string(str, len) : std::string();
}
int LuaUtils::ToInt(lua_State* L, int idx) {
    return static_cast<int>(lua_tointeger(L, idx));
}
double LuaUtils::ToDouble(lua_State* L, int idx) {
    return lua_tonumber(L, idx);
}
bool LuaUtils::ToBool(lua_State* L, int idx) {
    return lua_toboolean(L, idx) != 0;
}

} // namespace zombie
