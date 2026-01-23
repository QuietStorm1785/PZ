
// --- Signal-slot/observer pattern for C++/Lua ---
// Implements a signal/slot (observer) system for C++/Lua integration.
// Allows registering, connecting, and emitting named signals to decouple event producers and consumers.
#include "LuaManager.h"
#include "ExampleObject.h"
#include <unordered_map>
#include <vector>
#include <memory>
#include <iostream>
#include <filesystem>

// --- Signal-slot/observer pattern for C++/Lua ---
// Implements a signal/slot (observer) system for C++/Lua integration.
// Allows registering, connecting, and emitting named signals to decouple event producers and consumers.
#include "LuaManager.h"
#include "ExampleObject.h"
#include <unordered_map>
#include <vector>
#include <memory>
#include <iostream>
#include <filesystem>

// --- Signal-slot/observer pattern for C++/Lua ---
void LuaManager::RegisterSignal(const std::string& name) {
    signals.emplace(name, LuaCpp::LuaSignal());
// Emit a named signal, calling all connected slots
}

void LuaManager::ConnectSignal(const std::string& name, LuaCpp::LuaSignal::Slot slot) {
    auto it = signals.find(name);
    if (it != signals.end()) {
        it->second.connect(slot);

// --- LuaBackendClass event listener management ---
// Static map of event listeners for LuaBackendClass
    }
}
// Register a new Lua event by name

void LuaManager::EmitSignal(const std::string& name) {
    auto it = signals.find(name);
    if (it != signals.end()) {
// Add a Lua function reference as an event listener
        it->second.emit();
    }
}
std::unordered_map<std::string, std::vector<int>> LuaBackendClass::luaEventListeners;
// Remove a Lua function reference from event listeners

void LuaBackendClass::RegisterLuaEvent(const std::string& eventName) {
    luaEventListeners[eventName] = {};
}

// Trigger a Lua event, calling all registered listeners with nargs arguments
void LuaBackendClass::AddLuaEventListener(const std::string& eventName, int luaFuncRef) {
    luaEventListeners[eventName].push_back(luaFuncRef);
}

void LuaBackendClass::RemoveLuaEventListener(const std::string& eventName, int luaFuncRef) {
    auto& vec = luaEventListeners[eventName];
    vec.erase(std::remove(vec.begin(), vec.end(), luaFuncRef), vec.end());
}

void LuaBackendClass::TriggerLuaEvent(const std::string& eventName, int nargs) {
    lua_State* L = LuaManager::Instance().GetState();
    auto it = luaEventListeners.find(eventName);
    if (it == luaEventListeners.end()) return;
    for (int ref : it->second) {
        lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
        for (int i = 0; i < nargs; ++i)

// --- LuaManager event/callback registration and dispatch ---
// Register a new Lua event by name
            lua_pushvalue(L, -(nargs + 1)); // push args
        if (lua_pcall(L, nargs, 0, 0) != LUA_OK) {
            const char* err = lua_tostring(L, -1);

            // Register a named signal for the observer pattern.
            void LuaManager::RegisterSignal(const std::string& name) {
                signals.emplace(name, LuaCpp::LuaSignal());
            }

            // Connect a slot (callback) to a named signal.
    if (nargs > 0) lua_pop(L, nargs);
// Remove a Lua function reference from event listeners
}
// --- Lua-side event/callback registration and C++ event dispatch ---
}
// Trigger a Lua event, calling all registered listeners with nargs arguments

            // Emit a named signal, calling all connected slots.
void LuaManager::AddLuaEventListener(const std::string& eventName, int luaFuncRef) {
    luaEvents[eventName].listeners.push_back(luaFuncRef);
}
void LuaManager::RemoveLuaEventListener(const std::string& eventName, int luaFuncRef) {
    auto& listeners = luaEvents[eventName].listeners;
    listeners.erase(std::remove(listeners.begin(), listeners.end(), luaFuncRef), listeners.end());

            // --- LuaBackendClass event listener management ---
            // Static map of event listeners for LuaBackendClass
}

            // Register a new Lua event by name (C++ side, not LuaManager's own event system).
void LuaManager::TriggerLuaEvent(const std::string& eventName, int nargs) {
    lua_State* L = GetState();
    auto it = luaEvents.find(eventName);

            // Add a Lua function reference as an event listener for a named event.
    if (it == luaEvents.end()) return;

// --- Template-based type conversion utilities ---

            // Remove a Lua function reference from event listeners for a named event.
// Generic template for pushing C++ values to Lua (must specialize)
    for (int ref : it->second.listeners) {
        lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
        // Assumes nargs arguments are already on the stack

            // Trigger a Lua event, calling all registered listeners with nargs arguments.
        if (lua_pcall(L, nargs, 0, 0) != LUA_OK) {
            const char* err = lua_tostring(L, -1);
// Specializations for common types
            // Optionally log error
            lua_pop(L, 1);
        }
    }
template<typename T>
void LuaBackendClass::Push(lua_State* L, const T& value) {
    // Specialize for your types as needed
    static_assert(sizeof(T) == 0, "Push<T> not specialized for this type");
// Generic template for getting C++ values from Lua (must specialize)
template<>
inline void LuaBackendClass::Push(lua_State* L, const int& value) { lua_pushinteger(L, value); }
template<>
template<>
            }

            // --- Lua-side event/callback registration and C++ event dispatch ---
            // These manage events and listeners from the LuaManager side, for Lua-driven events.
inline void LuaBackendClass::Push(lua_State* L, const double& value) { lua_pushnumber(L, value); }
template<>
inline void LuaBackendClass::Push(lua_State* L, const bool& value) { lua_pushboolean(L, value); }

            // Add a Lua function reference as an event listener for a LuaManager event.
template<>
inline void LuaBackendClass::Push(lua_State* L, const std::string& value) { lua_pushstring(L, value.c_str()); }


            // Remove a Lua function reference from listeners for a LuaManager event.
template<typename T>
T LuaBackendClass::Get(lua_State* L, int idx) {
    // Specialize for your types as needed
    static_assert(sizeof(T) == 0, "Get<T> not specialized for this type");

            // Trigger a LuaManager event, calling all registered listeners with nargs arguments.
}
// --- Smart pointer support for Lua userdata ---
// Push a shared_ptr as Lua userdata
template<>
inline int LuaBackendClass::Get(lua_State* L, int idx) { return (int)lua_tointeger(L, idx); }
template<>
inline float LuaBackendClass::Get(lua_State* L, int idx) { return (float)lua_tonumber(L, idx); }
template<>
inline double LuaBackendClass::Get(lua_State* L, int idx) { return lua_tonumber(L, idx); }
template<>
// Get a shared_ptr from Lua userdata
inline bool LuaBackendClass::Get(lua_State* L, int idx) { return lua_toboolean(L, idx) != 0; }
template<>
inline std::string LuaBackendClass::Get(lua_State* L, int idx) { return lua_tostring(L, idx); }

            // --- Template-based type conversion utilities ---
            // Generic template for pushing C++ values to Lua (must specialize for each type).

// --- Smart pointer support ---
// Push a unique_ptr as Lua userdata
template<typename T>
void LuaBackendClass::PushSharedPtr(lua_State* L, std::shared_ptr<T> ptr, const std::string& metatableName) {
            // Specializations for common types (int, float, double, bool, std::string).
    auto** ud = (std::shared_ptr<T>**)lua_newuserdata(L, sizeof(std::shared_ptr<T>));
    new(ud) std::shared_ptr<T>(ptr);
    luaL_getmetatable(L, metatableName.c_str());
    lua_setmetatable(L, -2);
}
// Get a unique_ptr from Lua userdata
template<typename T>
std::shared_ptr<T> LuaBackendClass::GetSharedPtr(lua_State* L, int idx) {
    auto** ud = (std::shared_ptr<T>**)luaL_checkudata(L, idx, typeid(T).name());
    return *ud;

            // Generic template for getting C++ values from Lua (must specialize for each type).
}

// --- ExampleObject Lua binding ---
// Lua constructor for ExampleObject
template<typename T>
            // Specializations for common types (int, float, double, bool, std::string).
void LuaBackendClass::PushUniquePtr(lua_State* L, std::unique_ptr<T> ptr, const std::string& metatableName) {
    auto** ud = (std::unique_ptr<T>**)lua_newuserdata(L, sizeof(std::unique_ptr<T>));
    new(ud) std::unique_ptr<T>(std::move(ptr));
    luaL_getmetatable(L, metatableName.c_str());
    lua_setmetatable(L, -2);
}
template<typename T>
std::unique_ptr<T> LuaBackendClass::GetUniquePtr(lua_State* L, int idx) {

// Garbage collector for ExampleObject

            // --- Smart pointer support for Lua userdata ---
            // Push a shared_ptr as Lua userdata for Lua-side management.
    auto** ud = (std::unique_ptr<T>**)luaL_checkudata(L, idx, typeid(T).name());
    return std::move(*ud);
}
// --- ExampleObject Lua binding ---
static int ExampleObject_new(lua_State* L) {

// Get the name property from ExampleObject
            // Get a shared_ptr from Lua userdata.
    const char* name = luaL_checkstring(L, 1);
    int value = (int)luaL_checkinteger(L, 2);
    void* mem = lua_newuserdata(L, sizeof(zombie::LuaCpp::ExampleObject));
    new(mem) zombie::LuaCpp::ExampleObject(name, value);
    luaL_getmetatable(L, "ExampleObject");

            // Push a unique_ptr as Lua userdata for Lua-side management.

// Set the name property on ExampleObject
    lua_setmetatable(L, -2);
    return 1;
}

static int ExampleObject_gc(lua_State* L) {
            // Get a unique_ptr from Lua userdata.
    auto* obj = (zombie::LuaCpp::ExampleObject*)lua_touserdata(L, 1);

// Get the value property from ExampleObject
    obj->~ExampleObject();
    return 0;

            // --- ExampleObject Lua binding ---
            // Lua constructor for ExampleObject. Allocates and constructs a new ExampleObject in Lua.
}

static int ExampleObject_getName(lua_State* L) {

// Set the value property on ExampleObject
    auto* obj = (zombie::LuaCpp::ExampleObject*)luaL_checkudata(L, 1, "ExampleObject");
    lua_pushstring(L, obj->GetName().c_str());
    return 1;
}

            // Garbage collector for ExampleObject. Calls destructor when Lua collects the object.

static int ExampleObject_setName(lua_State* L) {

// Methods and meta-methods for ExampleObject
    auto* obj = (zombie::LuaCpp::ExampleObject*)luaL_checkudata(L, 1, "ExampleObject");

            // Get the name property from ExampleObject.
    const char* name = luaL_checkstring(L, 2);
    obj->SetName(name);
    return 0;
}


            // Set the name property on ExampleObject.
static int ExampleObject_getValue(lua_State* L) {

    auto* obj = (zombie::LuaCpp::ExampleObject*)luaL_checkudata(L, 1, "ExampleObject");
    lua_pushinteger(L, obj->GetValue());
    return 1;
}

            // Get the value property from ExampleObject.

// Register ExampleObject metatable and constructor in Lua

static int ExampleObject_setValue(lua_State* L) {
    auto* obj = (zombie::LuaCpp::ExampleObject*)luaL_checkudata(L, 1, "ExampleObject");

            // Set the value property on ExampleObject.
    int v = (int)luaL_checkinteger(L, 2);
    obj->SetValue(v);
    return 0;
}

static const luaL_Reg ExampleObject_methods[] = {

            // Methods and meta-methods for ExampleObject.

// --- Bytecode support for loading/dumping Lua functions ---
// Load Lua bytecode from a buffer
    {"getName", ExampleObject_getName},
    {"setName", ExampleObject_setName},
    {"getValue", ExampleObject_getValue},
    {"setValue", ExampleObject_setValue},

            static const luaL_Reg ExampleObject_meta[] = {
    {NULL, NULL}
};


            // Register ExampleObject metatable and constructor in Lua.
static const luaL_Reg ExampleObject_meta[] = {
    {"__gc", ExampleObject_gc},

// Writer callback for dumping Lua bytecode
    {NULL, NULL}
};

static void RegisterExampleObject(lua_State* L) {
    luaL_newmetatable(L, "ExampleObject");

            // --- Bytecode support for loading/dumping Lua functions ---
            // Load Lua bytecode from a buffer and push the function onto the stack.
    luaL_setfuncs(L, ExampleObject_meta, 0);

// Dump a Lua function to bytecode
    lua_newtable(L);
    luaL_setfuncs(L, ExampleObject_methods, 0);
    lua_setfield(L, -2, "__index");
    lua_pop(L, 1);
    lua_register(L, "ExampleObject", ExampleObject_new);
}

            // Writer callback for dumping Lua bytecode to a buffer.
// --- Bytecode support ---

// --- Type conversion utilities for Lua stack ---
// Convert Lua value to int
bool LuaBackendClass::LoadBytecode(lua_State* L, const std::vector<char>& bytecode, const std::string& chunkName) {
    if (luaL_loadbuffer(L, bytecode.data(), bytecode.size(), chunkName.c_str()) != LUA_OK) {

            // Dump a Lua function to bytecode and store in a buffer.
        const char* err = lua_tostring(L, -1);
// Convert Lua value to float
        LogError(err ? err : "Unknown error in LoadBytecode");
        lua_pop(L, 1);
        return false;
// Convert Lua value to bool
    }

            // --- Type conversion utilities for Lua stack ---
            // Convert Lua value to int.
    return true;
}
// Convert Lua value to string
            // Convert Lua value to float.

static int DumpWriter(lua_State*, const void* p, size_t sz, void* ud) {
    auto* out = static_cast<std::vector<char>*>(ud);
            // Convert Lua value to bool.
    const char* cp = static_cast<const char*>(p);
// Convert Lua value to pointer
    out->insert(out->end(), cp, cp + sz);
            // Convert Lua value to string.
    return 0;
}

// --- Push C++ values to Lua stack ---
            // Convert Lua value to pointer.

bool LuaBackendClass::DumpBytecode(lua_State* L, int funcIndex, std::vector<char>& outBytecode) {
    if (!lua_isfunction(L, funcIndex)) return false;

            // --- Push C++ values to Lua stack ---
    lua_pushvalue(L, funcIndex);
    int status = lua_dump(L, DumpWriter, &outBytecode, 0);
    lua_pop(L, 1);
    return status == 0;
}
// --- Type conversion utilities ---
int LuaBackendClass::ToInt(lua_State* L, int idx) {
    return (int)lua_tointeger(L, idx);
}
float LuaBackendClass::ToFloat(lua_State* L, int idx) {
    return (float)lua_tonumber(L, idx);
}

// --- Type-safe argument extraction from Lua stack ---
// Get string argument from Lua stack

            // --- Type-safe argument extraction from Lua stack ---
            // Get string argument from Lua stack.
bool LuaBackendClass::ToBool(lua_State* L, int idx) {
    return lua_toboolean(L, idx) != 0;
}
std::string LuaBackendClass::ToString(lua_State* L, int idx) {
            // Get int argument from Lua stack.
// Get int argument from Lua stack
    if (lua_isstring(L, idx)) return lua_tostring(L, idx);
    return std::string();
}
            // Get pointer argument from Lua stack.
void* LuaBackendClass::ToPtr(lua_State* L, int idx) {
// Get pointer argument from Lua stack
    return lua_touserdata(L, idx);
}
            // Get bool argument from Lua stack.

void LuaBackendClass::PushInt(lua_State* L, int value) {
// Get bool argument from Lua stack

            // --- Reference management for Lua registry ---
            // Create a reference to a Lua value in the registry.
    lua_pushinteger(L, value);
}
void LuaBackendClass::PushFloat(lua_State* L, float value) {

            // Release a reference from the Lua registry.
// --- Reference management for Lua registry ---
// Create a reference to a Lua value
    lua_pushnumber(L, value);

            // --- Scoped stack management for Lua ---
            // Guard to restore Lua stack to previous state on destruction (RAII).
}
void LuaBackendClass::PushBool(lua_State* L, bool value) {

            // --- Error reporting/logging ---
            // Log an error message from LuaBackendClass.
    lua_pushboolean(L, value);
// Release a reference from the Lua registry
}

            // --- Callback registration and dispatch ---
            // Register a C++ callback and expose it to Lua as a global function.
void LuaBackendClass::PushString(lua_State* L, const std::string& value) {
    lua_pushstring(L, value.c_str());

// --- Scoped stack management for Lua ---
// Guard to restore Lua stack to previous state
}
void LuaBackendClass::PushPtr(lua_State* L, void* value) {


            // Generic callback dispatcher for Lua->C++.
// --- Error reporting/logging ---
// Log an error message from LuaBackendClass
    lua_pushlightuserdata(L, value);
}
// --- Type-safe argument extraction ---

// --- Wrap a Lua function as a std::function ---
std::string LuaBackendClass::GetArgString(lua_State* L, int idx) {
    if (lua_isstring(L, idx)) return lua_tostring(L, idx);
    return std::string();
}
int LuaBackendClass::GetArgInt(lua_State* L, int idx) {
    if (lua_isinteger(L, idx)) return (int)lua_tointeger(L, idx);
    return 0;
}
void* LuaBackendClass::GetArgPtr(lua_State* L, int idx) {
    if (lua_islightuserdata(L, idx)) return lua_touserdata(L, idx);
    return nullptr;
}

            // --- Coroutine yield/resume with values ---
            // Yield from a Lua coroutine.
bool LuaBackendClass::GetArgBool(lua_State* L, int idx) {
    return lua_toboolean(L, idx) != 0;
}
            // Resume a Lua coroutine.

// --- Reference management ---

// --- Coroutine yield/resume with values ---
// Yield from a Lua coroutine

            // --- Userdata helpers for C++ pointer types ---
            // Push a raw pointer as Lua userdata.
int LuaBackendClass::Ref(lua_State* L, int idx) {
    lua_pushvalue(L, idx);
    return luaL_ref(L, LUA_REGISTRYINDEX);
// Resume a Lua coroutine
}
void LuaBackendClass::Unref(lua_State* L, int ref) {
    luaL_unref(L, LUA_REGISTRYINDEX, ref);

            // Get a raw pointer from Lua userdata.
}


// --- Automatic metatable registration for C++ types ---
// Register a metatable for a C++ type in Lua
// --- Scoped stack management ---
LuaBackendClass::StackGuard::StackGuard(lua_State* L) : L(L), top(lua_gettop(L)) {}

            // --- Table/metatable helpers for LuaBackendClass ---
            // Set the metatable for a Lua table by reference.
LuaBackendClass::StackGuard::~StackGuard() { lua_settop(L, top); }

// --- Error reporting/logging ---
void LuaBackendClass::LogError(const std::string& msg) {
    std::cerr << "[LuaBackendClass Error] " << msg << std::endl;
}


            // Get the metatable reference for a Lua table.

// --- Callback registration and dispatch ---
// Static map of callback functions
// --- Lua function as std::function ---

// Register a C++ callback and expose it to Lua
std::function<int(void*)> LuaBackendClass::MakeLuaFunction(int ref) {
    return [ref](void* arg) -> int {
        lua_State* L = LuaManager::Instance().GetState();
        lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
        lua_pushlightuserdata(L, arg);

            // Set a string field on a Lua table.
        if (lua_pcall(L, 1, 1, 0) != LUA_OK) {
            const char* err = lua_tostring(L, -1);
            LogError(err ? err : "Unknown error in MakeLuaFunction");

// Generic callback dispatcher for Lua->C++
            lua_pop(L, 1);
            return 0;

            // Set a pointer field on a Lua table.
        }
        int result = 0;
        if (lua_isinteger(L, -1)) result = (int)lua_tointeger(L, -1);
        lua_pop(L, 1);
        return result;
    };
}

            // Get all string keys from a Lua table.

// --- Coroutine yield/resume with values ---
int LuaBackendClass::Yield(lua_State* L, int nresults) {
    return lua_yield(L, nresults);
}
int LuaBackendClass::Resume(lua_State* co, int nargs, int* nresults) {
    int status = lua_resume(co, nullptr, nargs);
    if (nresults) *nresults = lua_gettop(co);
    return status;
}


            // Get a pointer field from a Lua table.
// --- Userdata helpers for C++ pointer types ---
// Push a raw pointer as Lua userdata

// --- Automatic metatable registration ---
template<typename T>
void LuaBackendClass::RegisterMetatable(const std::string& name, const luaL_Reg* methods) {
    lua_State* L = LuaManager::Instance().GetState();
    luaL_newmetatable(L, name.c_str());
    luaL_setfuncs(L, methods, 0);

// Get a raw pointer from Lua userdata

            // Set a pointer value at a numeric index in a Lua table.
    lua_pushvalue(L, -1);
    lua_setfield(L, -1, "__index");
    lua_setglobal(L, name.c_str());
}
#include <unordered_map>
std::unordered_map<std::string, LuaBackendClass::CallbackFn> LuaBackendClass::callbackMap;


            // Get a pointer value at a numeric index in a Lua table.

// --- Bind a C function to Lua global ---
int LuaBackendClass::RegisterCallback(const std::string& name, CallbackFn cb) {
    callbackMap[name] = cb;
    lua_State* L = LuaManager::Instance().GetState();
    lua_pushstring(L, name.c_str());

// --- Coroutine creation and management ---
// Create a Lua coroutine from a function name
    lua_pushcfunction(L, GenericCallback);
    lua_setglobal(L, name.c_str());

            // Check if a Lua table has a given key.
    return 0;
}

int LuaBackendClass::GenericCallback(lua_State* L) {
    // Get function name from stack (debug info)
    lua_Debug ar;
    if (lua_getstack(L, 0, &ar) && lua_getinfo(L, "n", &ar) && ar.name) {
        auto it = callbackMap.find(ar.name);

            // Get all string keys from a Lua table.
        if (it != callbackMap.end()) {
            return it->second(L);
        }
    }

// Resume a Lua coroutine by reference
    // Fallback: try global function name
    const char* fname = lua_tostring(L, lua_upvalueindex(1));
    if (fname) {
        auto it = callbackMap.find(fname);
        if (it != callbackMap.end()) {
            return it->second(L);
        }
    }

            // Clear all entries from a Lua table.

// --- Table/metatable helpers for LuaBackendClass ---
// Set the metatable for a Lua table by reference
    return 0;
}
void LuaBackendClass::PushUserdata(void* ptr, const std::string& metatableName) {
    lua_State* L = LuaManager::Instance().GetState();
    void** ud = (void**)lua_newuserdata(L, sizeof(void*));
    *ud = ptr;
    luaL_getmetatable(L, metatableName.c_str());

// Get the metatable reference for a Lua table

            namespace zombie {

            // --- LuaManager singleton and lifecycle ---
            // Singleton instance accessor for LuaManager.
    lua_setmetatable(L, -2);
}

void* LuaBackendClass::ToUserdata(int index) {

            // Constructor/Destructor for LuaManager. Initializes and shuts down Lua state.
    lua_State* L = LuaManager::Instance().GetState();
    if (lua_isuserdata(L, index)) {

            // Initialize Lua state and expose C++ types/classes to Lua.
        return *(void**)lua_touserdata(L, index);
    }
    return nullptr;
}


// Set a string field on a Lua table
void LuaBackendClass::BindFunction(const std::string& name, lua_CFunction fn) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_register(L, name.c_str(), fn);
}

int LuaBackendClass::CreateCoroutine(const std::string& funcName) {
    lua_State* L = LuaManager::Instance().GetState();

// Set a pointer field on a Lua table
    lua_getglobal(L, funcName.c_str());

            // Shutdown Lua state and free resources.
    if (!lua_isfunction(L, -1)) {
        lua_pop(L, 1);
        return LUA_NOREF;
    }
    lua_State* co = lua_newthread(L);
    lua_pushvalue(L, -2);

            // Get the current Lua state pointer.

// Get a string field from a Lua table
    lua_xmove(L, co, 1);

            // Load and execute a Lua script file.
    int ref = luaL_ref(L, LUA_REGISTRYINDEX);
    lua_pop(L, 1);
    return ref;
}

int LuaBackendClass::ResumeCoroutine(int coroutineRef, int nargs) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, coroutineRef);
    lua_State* co = lua_tothread(L, -1);
    int status = lua_resume(co, nullptr, nargs);

            // Recursively load all Lua scripts in a directory.

// Get a pointer field from a Lua table
    lua_pop(L, 1);
    return status;

            // Register a global C function in Lua.
}
void LuaBackendClass::SetMetatable(int metatableRef) {
    lua_State* L = LuaManager::Instance().GetState();

            // Register a C++ class and its methods in Lua.
    lua_rawgeti(L, LUA_REGISTRYINDEX, table);
    lua_rawgeti(L, LUA_REGISTRYINDEX, metatableRef);
    lua_setmetatable(L, -2);
    lua_pop(L, 1);
}


// Set a pointer value at a numeric index in a Lua table

            // Register a C++ event by name for C++/Lua event integration.
int LuaBackendClass::GetMetatable() {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, table);

            // Add a callback closure to a named event.
    if (lua_getmetatable(L, -1)) {
        int ref = luaL_ref(L, LUA_REGISTRYINDEX);
        lua_pop(L, 1);
        return ref;

            // Remove a callback closure from a named event.

// Get a pointer value at a numeric index in a Lua table
    }
    lua_pop(L, 1);

            // Trigger a named event, passing arguments to all registered callbacks.
    return LUA_NOREF;
}
void LuaBackendClass::SetField(const std::string& key, const std::string& value) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, table);
    lua_pushstring(L, value.c_str());

            // Call a global Lua function by name, with arguments and expected results.
    lua_setfield(L, -2, key.c_str());
    lua_pop(L, 1);
}

// Check if a Lua table has a given key

void LuaBackendClass::SetField(const std::string& key, void* value) {

            // Push a global Lua function onto the stack by name.
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, table);
    lua_pushlightuserdata(L, value);
    lua_setfield(L, -2, key.c_str());
    lua_pop(L, 1);

            // --- LuaGlobalObject implementation ---
            // Example: Load a vehicle model by name/path/type using ModelManager.
}

// Get all string keys from a Lua table

std::string LuaBackendClass::GetFieldString(const std::string& key) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, table);
            // Example: Load the default Zomboid model (male).
    lua_getfield(L, -1, key.c_str());
    std::string result;
    if (lua_isstring(L, -1)) {
        result = lua_tostring(L, -1);
    }
            // Example: Set metadata for a model by name.
    lua_pop(L, 2);
    return result;
}

void* LuaBackendClass::GetFieldPtr(const std::string& key) {
            // ...other static methods as needed...

            // --- LuaItemQuery implementation ---
            // Implementation of LuaItemQuery for async item operations and Lua callback integration.

// Clear all entries from a Lua table
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, table);
    lua_getfield(L, -1, key.c_str());
    void* result = nullptr;
    if (lua_islightuserdata(L, -1)) {
        result = lua_touserdata(L, -1);
    }
    lua_pop(L, 2);
    return result;
}

void LuaBackendClass::SetIndex(int idx, void* value) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, table);
    lua_pushlightuserdata(L, value);
    lua_rawseti(L, -2, idx);
    lua_pop(L, 1);
}

void* LuaBackendClass::GetIndex(int idx) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, table);
    lua_rawgeti(L, -1, idx);
    void* result = nullptr;
    if (lua_islightuserdata(L, -1)) {
        result = lua_touserdata(L, -1);
    }
    lua_pop(L, 2);
    return result;
}

bool LuaBackendClass::HasKey(const std::string& key) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, table);
    lua_getfield(L, -1, key.c_str());
    bool exists = !lua_isnil(L, -1);
    lua_pop(L, 2);
    return exists;
}

std::vector<std::string> LuaBackendClass::Keys() {
    lua_State* L = LuaManager::Instance().GetState();
    std::vector<std::string> keys;
    lua_rawgeti(L, LUA_REGISTRYINDEX, table);
    lua_pushnil(L);
    while (lua_next(L, -2) != 0) {
        if (lua_type(L, -2) == LUA_TSTRING) {
            keys.emplace_back(lua_tostring(L, -2));
        }
        lua_pop(L, 1);
    }
    lua_pop(L, 1);
    return keys;
}

void LuaBackendClass::Clear() {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, table);
    lua_pushnil(L);
    while (lua_next(L, -2) != 0) {
        lua_pop(L, 1);
        lua_pushvalue(L, -1);
        lua_pushnil(L);
        lua_settable(L, -3);
    }
    lua_pop(L, 1);
}

namespace zombie {

LuaManager& LuaManager::Instance() {
    static LuaManager instance;
    return instance;
}

LuaManager::LuaManager() : L(nullptr) {}
LuaManager::~LuaManager() { Shutdown(); }

void LuaManager::Init() {
    if (L) return;
    L = luaL_newstate();
    luaL_openlibs(L);

    // Expose all registered C++ types/classes to Lua
    static LuaExposer exposer;
    exposer.ExposeAll();

    // Register global objects, comparators, file writers, etc. as needed
    // Example: LuaGlobalObject::RegisterWithLua(L);
    // Example: LuaFileWriter writer("output.txt");
    // ...other integration logic...

    // Register ExampleObject binding
    RegisterExampleObject(L);
}

void LuaManager::Shutdown() {
    if (L) {
        lua_close(L);
        L = nullptr;
    }
}

lua_State* LuaManager::GetState() {
    return L;
}

bool LuaManager::LoadScript(const std::string& filename) {
    if (!L) return false;
    if (luaL_dofile(L, filename.c_str()) != LUA_OK) {
        const char* err = lua_tostring(L, -1);
        // Optionally log error
        lua_pop(L, 1);
        return false;
    }
    return true;
}

void LuaManager::LoadDirectory(const std::string& dirPath) {
    namespace fs = std::filesystem;
    for (const auto& entry : fs::recursive_directory_iterator(dirPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".lua") {
            LoadScript(entry.path().string());
        }
    }
}

void LuaManager::RegisterFunction(const std::string& name, lua_CFunction fn) {
    if (L) lua_register(L, name.c_str(), fn);
}

void LuaManager::RegisterClass(const std::string& name, const luaL_Reg* methods) {
    if (!L) return;
    luaL_newmetatable(L, name.c_str());
    luaL_setfuncs(L, methods, 0);
    lua_pushvalue(L, -1);
    lua_setfield(L, -1, "__index");
    lua_setglobal(L, name.c_str());
}

void LuaManager::RegisterEvent(const std::string& eventName) {
    events.emplace(eventName, LuaCpp::Event(eventName, static_cast<int>(events.size())));
}

void LuaManager::AddEventCallback(const std::string& eventName, LuaCpp::LuaClosure* closure) {
    auto it = events.find(eventName);
    if (it != events.end()) {
        it->second.addCallback(closure);
    }
}

void LuaManager::RemoveEventCallback(const std::string& eventName, LuaCpp::LuaClosure* closure) {
    auto it = events.find(eventName);
    if (it != events.end()) {
        it->second.removeCallback(closure);
    }
}

bool LuaManager::TriggerEvent(const std::string& eventName, std::vector<void*> args) {
    auto it = events.find(eventName);
    if (it == events.end()) return false;
    // You may want to pass LuaCaller, KahluaTable, etc. as needed
    return it->second.trigger(nullptr, nullptr, args);
}

bool LuaManager::CallGlobal(const std::string& funcName, int nargs, int nresults) {
    if (!L) return false;
    lua_getglobal(L, funcName.c_str());
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

bool LuaManager::PushFunction(const std::string& funcName) {
    if (!L) return false;
    lua_getglobal(L, funcName.c_str());
    return lua_isfunction(L, -1);
}

// --- LuaGlobalObject implementation ---
Model* LuaGlobalObject::LoadVehicleModel(const std::string& name, const std::string& path, const std::string& type) {
    // Use ModelManager to load or retrieve the vehicle model
    // name: mesh name, path: texture name, type: shader/type
    using zombie::core::skinnedmodel::ModelManager;
    Model* model = ModelManager::instance.getLoadedModel(name, path, false, type);
    return model;
}
Model* LuaGlobalObject::LoadZomboidModel() {
    // Return the default male model (could be extended to select by gender/type)
    using zombie::core::skinnedmodel::ModelManager;
    return &ModelManager::instance.m_maleModel;
}
void LuaGlobalObject::SetModelMetaData(const std::string& name, const std::string& meta1, const std::string& meta2, const std::string& meta3, bool flag) {
    // Set model metadata using ModelManager
    using zombie::core::skinnedmodel::ModelManager;
    ModelManager::instance.setModelMetaData(name, meta1, meta2, meta3, flag);
}
// ...other static methods as needed...

// --- LuaItemQuery implementation ---
LuaItemQuery::LuaItemQuery(const std::vector<std::string>& ids, int luaFuncRef, void* arg)
    : luaFuncRef(luaFuncRef), arg(arg), handle(0) {
    // Convert string IDs to Steam IDs
    std::vector<long> steamIDs;
    for (const auto& s : ids) {
        long id = zombie::core::znet::SteamUtils::convertStringToSteamID(s);
        if (id != -1L) steamIDs.push_back(id);
    }
    // Start a Steam Workshop query and register this as a callback
    handle = zombie::core::znet::SteamWorkshop::instance.CreateQueryUGCDetailsRequest(steamIDs, this);
    if (handle == 0L) {
        // Query failed, call Lua callback with NotCompleted
        lua_State* L = LuaManager::Instance().GetState();
        lua_rawgeti(L, LUA_REGISTRYINDEX, luaFuncRef);
        if (arg) {
            lua_pushlightuserdata(L, arg);
            lua_pushstring(L, "NotCompleted");
            lua_pcall(L, 2, 0, 0);
        } else {
            lua_pushstring(L, "NotCompleted");
            lua_pcall(L, 1, 0, 0);
        }
        luaL_unref(L, LUA_REGISTRYINDEX, luaFuncRef);
    }
}
void LuaItemQuery::OnItemCreated(long id, bool success) {
    // Example: call Lua callback for item created
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, luaFuncRef);
    lua_pushinteger(L, id);
    lua_pushboolean(L, success);
    lua_pcall(L, 2, 0, 0);
}
void LuaItemQuery::OnItemNotCreated(int id) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, luaFuncRef);
    lua_pushinteger(L, id);
    lua_pushstring(L, "NotCreated");
    lua_pcall(L, 2, 0, 0);
}
void LuaItemQuery::OnItemUpdated(bool success) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, luaFuncRef);
    lua_pushboolean(L, success);
    lua_pcall(L, 1, 0, 0);
}
void LuaItemQuery::OnItemNotUpdated(int id) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, luaFuncRef);
    lua_pushinteger(L, id);
    lua_pushstring(L, "NotUpdated");
    lua_pcall(L, 2, 0, 0);
}
void LuaItemQuery::OnItemSubscribed(long id) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, luaFuncRef);
    lua_pushinteger(L, id);
    lua_pushstring(L, "Subscribed");
    lua_pcall(L, 2, 0, 0);
}
void LuaItemQuery::OnItemNotSubscribed(long id, int code) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, luaFuncRef);
    lua_pushinteger(L, id);
    lua_pushstring(L, "NotSubscribed");
    lua_pushinteger(L, code);
    lua_pcall(L, 3, 0, 0);
}
void LuaItemQuery::OnItemDownloaded(long id) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, luaFuncRef);
    lua_pushinteger(L, id);
    lua_pushstring(L, "Downloaded");
    lua_pcall(L, 2, 0, 0);
}
void LuaItemQuery::OnItemNotDownloaded(long id, int code) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, luaFuncRef);
    lua_pushinteger(L, id);
    lua_pushstring(L, "NotDownloaded");
    lua_pushinteger(L, code);
    lua_pcall(L, 3, 0, 0);
}
void LuaItemQuery::OnItemQueryCompleted(long id, int count) {
    // Collect results from SteamUGCDetails and call Lua callback
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, luaFuncRef);
    lua_pushinteger(L, id);
    lua_pushstring(L, "Completed");
    lua_pushinteger(L, count);
    // Optionally, push more details as a Lua table here
    lua_pcall(L, 3, 0, 0);
    // Clean up Lua reference
    luaL_unref(L, LUA_REGISTRYINDEX, luaFuncRef);
}
void LuaItemQuery::OnItemQueryNotCompleted(long id, int code) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, luaFuncRef);
    lua_pushinteger(L, id);
    lua_pushstring(L, "NotCompleted");
    lua_pushinteger(L, code);
    lua_pcall(L, 3, 0, 0);
    luaL_unref(L, LUA_REGISTRYINDEX, luaFuncRef);
}

// --- LuaComparator implementation ---
LuaComparator::LuaComparator(int luaFuncRef) : luaFuncRef(luaFuncRef) {}
int LuaComparator::Compare(void* a, void* b) {
    // Call Lua function for comparison
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, luaFuncRef); // push Lua function
    lua_pushlightuserdata(L, a);
    lua_pushlightuserdata(L, b);
    if (lua_pcall(L, 2, 1, 0) != LUA_OK) {
        const char* err = lua_tostring(L, -1);
        // Optionally log error
        lua_pop(L, 1);
        return 0;
    }
    int result = 0;
    if (lua_isinteger(L, -1)) {
        result = (int)lua_tointeger(L, -1);
    }
    lua_pop(L, 1);
    return result;
}

// --- LuaFileWriter implementation ---
LuaFileWriter::LuaFileWriter(const std::string& filename) : writer(filename) {}
void LuaFileWriter::Write(const std::string& text) {
    writer << text;
}
void LuaFileWriter::Writeln(const std::string& text) {
    writer << text << std::endl;
}
void LuaFileWriter::Close() {
    writer.close();
}

// --- LuaExposer implementation ---
void LuaExposer::ExposeAll() {
    // Iterate all registered types/classes and expose them to Lua
    lua_State* L = LuaManager::Instance().GetState();
    // For each type in exposedTypes, call its static RegisterWithLua(L) if available
    for (const auto& typeIdx : exposedTypes) {
        // This requires that each type registered with SetExposed<T>()
        // also provides a static RegisterWithLua(lua_State*) method.
        // We use a registry of function pointers for each type.
        auto it = registerFuncs.find(typeIdx);
        if (it != registerFuncs.end() && it->second) {
            it->second(L);
        }
    }
}

template<typename T>
void LuaExposer::SetExposed() {
    exposedTypes.insert(std::type_index(typeid(T)));
}

template<typename T>
bool LuaExposer::ShouldExpose() {
    return exposedTypes.find(std::type_index(typeid(T))) != exposedTypes.end();
}

// --- LuaHookManager implementation ---
std::vector<LuaHookManager::Event> LuaHookManager::eventList;
std::unordered_map<std::string, LuaHookManager::Event*> LuaHookManager::eventMap;

bool LuaHookManager::TriggerHook(const std::string& name) {
    auto it = eventMap.find(name);
    if (it == eventMap.end()) return false;
    void* args[1] = {nullptr};
    return it->second->trigger(LuaManager::Instance().GetState(), args, 0);
}
bool LuaHookManager::TriggerHook(const std::string& name, void* arg1) {
    auto it = eventMap.find(name);
    if (it == eventMap.end()) return false;
    void* args[1] = {arg1};
    return it->second->trigger(LuaManager::Instance().GetState(), args, 1);
}
bool LuaHookManager::TriggerHook(const std::string& name, void* arg1, void* arg2) {
    auto it = eventMap.find(name);
    if (it == eventMap.end()) return false;
    void* args[2] = {arg1, arg2};
    return it->second->trigger(LuaManager::Instance().GetState(), args, 2);
}
bool LuaHookManager::TriggerHook(const std::string& name, void* arg1, void* arg2, void* arg3) {
    auto it = eventMap.find(name);
    if (it == eventMap.end()) return false;
    void* args[3] = {arg1, arg2, arg3};
    return it->second->trigger(LuaManager::Instance().GetState(), args, 3);
}
bool LuaHookManager::TriggerHook(const std::string& name, void* arg1, void* arg2, void* arg3, void* arg4) {
    auto it = eventMap.find(name);
    if (it == eventMap.end()) return false;
    void* args[4] = {arg1, arg2, arg3, arg4};
    return it->second->trigger(LuaManager::Instance().GetState(), args, 4);
}
bool LuaHookManager::TriggerHook(const std::string& name, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5) {
    auto it = eventMap.find(name);
    if (it == eventMap.end()) return false;
    void* args[5] = {arg1, arg2, arg3, arg4, arg5};
    return it->second->trigger(LuaManager::Instance().GetState(), args, 5);
}
bool LuaHookManager::TriggerHook(const std::string& name, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, void* arg6) {
    auto it = eventMap.find(name);
    if (it == eventMap.end()) return false;
    void* args[6] = {arg1, arg2, arg3, arg4, arg5, arg6};
    return it->second->trigger(LuaManager::Instance().GetState(), args, 6);
}

void LuaHookManager::AddEvent(const std::string& name) {
    if (eventMap.find(name) == eventMap.end()) {
        eventList.emplace_back(name);
        eventMap[name] = &eventList.back();
    }
}
void LuaHookManager::AddEvents() {
    AddEvent("AutoDrink");
    AddEvent("UseItem");
    AddEvent("Attack");
    AddEvent("CalculateStats");
    AddEvent("WeaponHitCharacter");
    AddEvent("WeaponSwing");
    AddEvent("WeaponSwingHitPoint");
}
void LuaHookManager::Clear() {
    eventList.clear();
    eventMap.clear();
}
void LuaHookManager::RegisterHooks() {
    // Register hooks with Lua: create Lua table and bind C++ hook functions
    lua_State* L = LuaManager::Instance().GetState();
    lua_newtable(L); // hooks table
    for (const auto& pair : eventMap) {
        const std::string& name = pair.first;
        // Register a C function for each hook event
        lua_pushstring(L, name.c_str());
        lua_pushcfunction(L, [](lua_State* L) -> int {
            // Get event name from upvalue
            const char* eventName = lua_tostring(L, lua_upvalueindex(1));
            // Collect arguments as void* array
            int nargs = lua_gettop(L);
            void* args[8] = {nullptr};
            for (int i = 0; i < nargs && i < 8; ++i) {
                if (lua_islightuserdata(L, i + 1))
                    args[i] = lua_touserdata(L, i + 1);
            }
            // Call the C++ hook
            bool result = false;
            switch (nargs) {
                case 0: result = LuaHookManager::TriggerHook(eventName); break;
                case 1: result = LuaHookManager::TriggerHook(eventName, args[0]); break;
                case 2: result = LuaHookManager::TriggerHook(eventName, args[0], args[1]); break;
                case 3: result = LuaHookManager::TriggerHook(eventName, args[0], args[1], args[2]); break;
                case 4: result = LuaHookManager::TriggerHook(eventName, args[0], args[1], args[2], args[3]); break;
                case 5: result = LuaHookManager::TriggerHook(eventName, args[0], args[1], args[2], args[3], args[4]); break;
                case 6: result = LuaHookManager::TriggerHook(eventName, args[0], args[1], args[2], args[3], args[4], args[5]); break;
                default: result = false; break;
            }
            lua_pushboolean(L, result);
            return 1;
        });
        lua_pushstring(L, name.c_str());
        lua_setupvalue(L, -2, 1); // set event name as upvalue
        lua_settable(L, -3);
    }
    lua_setglobal(L, "Hooks");
}
void LuaHookManager::Reset() {
    Clear();
}
bool LuaHookManager::Event::trigger(lua_State* L, void** args, int nargs) {
    bool anySuccess = false;
    for (int ref : callbacks) {
        lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
        for (int i = 0; i < nargs; ++i) {
            lua_pushlightuserdata(L, args ? args[i] : nullptr);
        }
        if (lua_pcall(L, nargs, 0, 0) == LUA_OK) {
            anySuccess = true;
        } else {
            const char* err = lua_tostring(L, -1);
            // Optionally log error
            lua_pop(L, 1);
        }
    }
    return anySuccess;
}

// --- LuaBackendClass Implementation ---

LuaBackendClass::LuaBackendClass(const std::string& typeName) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_getglobal(L, typeName.c_str());
    if (lua_istable(L, -1)) {
        table = luaL_ref(L, LUA_REGISTRYINDEX);
    } else {
        table = LUA_NOREF;
        lua_pop(L, 1);
    }
    typeTable = table;
}


std::string LuaBackendClass::GetString(const std::string& key) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, (int)table);
    lua_getfield(L, -1, key.c_str());
    std::string result;
    if (lua_isstring(L, -1)) {
        result = lua_tostring(L, -1);
    }
    lua_pop(L, 2);
    return result;
}

void LuaBackendClass::CallVoid(const std::string& func) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, (int)table);
    lua_getfield(L, -1, func.c_str());
    lua_pushvalue(L, -2); // push table as self
    if (lua_pcall(L, 1, 0, 0) != LUA_OK) {
        lua_pop(L, 1); // error
    }
    lua_pop(L, 1); // pop table
}
void LuaBackendClass::CallVoid(const std::string& func, void* arg1) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, (int)table);
    lua_getfield(L, -1, func.c_str());
    lua_pushvalue(L, -2); // push table as self
    lua_pushlightuserdata(L, arg1);
    if (lua_pcall(L, 2, 0, 0) != LUA_OK) {
        lua_pop(L, 1);
    }
    lua_pop(L, 1);
}
void LuaBackendClass::CallVoid(const std::string& func, void* arg1, void* arg2) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, (int)table);
    lua_getfield(L, -1, func.c_str());
    lua_pushvalue(L, -2);
    lua_pushlightuserdata(L, arg1);
    lua_pushlightuserdata(L, arg2);
    if (lua_pcall(L, 3, 0, 0) != LUA_OK) {
        lua_pop(L, 1);
    }
    lua_pop(L, 1);
}
void LuaBackendClass::CallVoid(const std::string& func, void* arg1, void* arg2, void* arg3) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, (int)table);
    lua_getfield(L, -1, func.c_str());
    lua_pushvalue(L, -2);
    lua_pushlightuserdata(L, arg1);
    lua_pushlightuserdata(L, arg2);
    lua_pushlightuserdata(L, arg3);
    if (lua_pcall(L, 4, 0, 0) != LUA_OK) {
        lua_pop(L, 1);
    }
    lua_pop(L, 1);
}
void LuaBackendClass::CallVoid(const std::string& func, void* arg1, void* arg2, void* arg3, void* arg4) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, (int)table);
    lua_getfield(L, -1, func.c_str());
    lua_pushvalue(L, -2);
    lua_pushlightuserdata(L, arg1);
    lua_pushlightuserdata(L, arg2);
    lua_pushlightuserdata(L, arg3);
    lua_pushlightuserdata(L, arg4);
    if (lua_pcall(L, 5, 0, 0) != LUA_OK) {
        lua_pop(L, 1);
    }
    lua_pop(L, 1);
}
void LuaBackendClass::CallVoid(const std::string& func, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, (int)table);
    lua_getfield(L, -1, func.c_str());
    lua_pushvalue(L, -2);
    lua_pushlightuserdata(L, arg1);
    lua_pushlightuserdata(L, arg2);
    lua_pushlightuserdata(L, arg3);
    lua_pushlightuserdata(L, arg4);
    lua_pushlightuserdata(L, arg5);
    if (lua_pcall(L, 6, 0, 0) != LUA_OK) {
        lua_pop(L, 1);
    }
    lua_pop(L, 1);
}
void LuaBackendClass::CallVoid(const std::string& func, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, void* arg6) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, (int)table);
    lua_getfield(L, -1, func.c_str());
    lua_pushvalue(L, -2);
    lua_pushlightuserdata(L, arg1);
    lua_pushlightuserdata(L, arg2);
    lua_pushlightuserdata(L, arg3);
    lua_pushlightuserdata(L, arg4);
    lua_pushlightuserdata(L, arg5);
    lua_pushlightuserdata(L, arg6);
    if (lua_pcall(L, 7, 0, 0) != LUA_OK) {
        lua_pop(L, 1);
    }
    lua_pop(L, 1);
}

void* LuaBackendClass::Call(const std::string& func) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, (int)table);
    lua_getfield(L, -1, func.c_str());
    lua_pushvalue(L, -2);
    if (lua_pcall(L, 1, 1, 0) != LUA_OK) {
        const char* err = lua_tostring(L, -1);
        // Log error
        lua_pop(L, 2);
        return nullptr;
    }
    void* result = nullptr;
    if (lua_islightuserdata(L, -1)) {
        result = lua_touserdata(L, -1);
    }
    lua_pop(L, 2);
    return result;
}
void* LuaBackendClass::Call(const std::string& func, void* arg1) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, (int)table);
    lua_getfield(L, -1, func.c_str());
    lua_pushvalue(L, -2);
    lua_pushlightuserdata(L, arg1);
    if (lua_pcall(L, 2, 1, 0) != LUA_OK) {
        const char* err = lua_tostring(L, -1);
        lua_pop(L, 2);
        return nullptr;
    }
    void* result = nullptr;
    if (lua_islightuserdata(L, -1)) {
        result = lua_touserdata(L, -1);
    }
    lua_pop(L, 2);
    return result;
}
void* LuaBackendClass::Call(const std::string& func, void* arg1, void* arg2) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, (int)table);
    lua_getfield(L, -1, func.c_str());
    lua_pushvalue(L, -2);
    lua_pushlightuserdata(L, arg1);
    lua_pushlightuserdata(L, arg2);
    if (lua_pcall(L, 3, 1, 0) != LUA_OK) {
        const char* err = lua_tostring(L, -1);
        lua_pop(L, 2);
        return nullptr;
    }
    void* result = nullptr;
    if (lua_islightuserdata(L, -1)) {
        result = lua_touserdata(L, -1);
    }
    lua_pop(L, 2);
    return result;
}
void* LuaBackendClass::Call(const std::string& func, void* arg1, void* arg2, void* arg3) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, (int)table);
    lua_getfield(L, -1, func.c_str());
    lua_pushvalue(L, -2);
    lua_pushlightuserdata(L, arg1);
    lua_pushlightuserdata(L, arg2);
    lua_pushlightuserdata(L, arg3);
    if (lua_pcall(L, 4, 1, 0) != LUA_OK) {
        const char* err = lua_tostring(L, -1);
        lua_pop(L, 2);
        return nullptr;
    }
    void* result = nullptr;
    if (lua_islightuserdata(L, -1)) {
        result = lua_touserdata(L, -1);
    }
    lua_pop(L, 2);
    return result;
}
void* LuaBackendClass::Call(const std::string& func, void* arg1, void* arg2, void* arg3, void* arg4) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, (int)table);
    lua_getfield(L, -1, func.c_str());
    lua_pushvalue(L, -2);
    lua_pushlightuserdata(L, arg1);
    lua_pushlightuserdata(L, arg2);
    lua_pushlightuserdata(L, arg3);
    lua_pushlightuserdata(L, arg4);
    if (lua_pcall(L, 5, 1, 0) != LUA_OK) {
        const char* err = lua_tostring(L, -1);
        lua_pop(L, 2);
        return nullptr;
    }
    void* result = nullptr;
    if (lua_islightuserdata(L, -1)) {
        result = lua_touserdata(L, -1);
    }
    lua_pop(L, 2);
    return result;
}
void* LuaBackendClass::Call(const std::string& func, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, (int)table);
    lua_getfield(L, -1, func.c_str());
    lua_pushvalue(L, -2);
    lua_pushlightuserdata(L, arg1);
    lua_pushlightuserdata(L, arg2);
    lua_pushlightuserdata(L, arg3);
    lua_pushlightuserdata(L, arg4);
    lua_pushlightuserdata(L, arg5);
    if (lua_pcall(L, 6, 1, 0) != LUA_OK) {
        const char* err = lua_tostring(L, -1);
        lua_pop(L, 2);
        return nullptr;
    }
    void* result = nullptr;
    if (lua_islightuserdata(L, -1)) {
        result = lua_touserdata(L, -1);
    }
    lua_pop(L, 2);
    return result;
}
void* LuaBackendClass::Call(const std::string& func, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, void* arg6) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, (int)table);
    lua_getfield(L, -1, func.c_str());
    lua_pushvalue(L, -2);
    lua_pushlightuserdata(L, arg1);
    lua_pushlightuserdata(L, arg2);
    lua_pushlightuserdata(L, arg3);
    lua_pushlightuserdata(L, arg4);
    lua_pushlightuserdata(L, arg5);
    lua_pushlightuserdata(L, arg6);
    if (lua_pcall(L, 7, 1, 0) != LUA_OK) {
        const char* err = lua_tostring(L, -1);
        lua_pop(L, 2);
        return nullptr;
    }
    void* result = nullptr;
    if (lua_islightuserdata(L, -1)) {
        result = lua_touserdata(L, -1);
    }
    lua_pop(L, 2);
    return result;
}

int LuaBackendClass::CallInt(const std::string& func) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, (int)table);
    lua_getfield(L, -1, func.c_str());
    lua_pushvalue(L, -2);
    if (lua_pcall(L, 1, 1, 0) != LUA_OK) {
        const char* err = lua_tostring(L, -1);
        lua_pop(L, 2);
        return 0;
    }
    int result = 0;
    if (lua_isinteger(L, -1)) {
        result = (int)lua_tointeger(L, -1);
    }
    lua_pop(L, 2);
    return result;
}
int LuaBackendClass::CallInt(const std::string& func, void* arg1) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, (int)table);
    lua_getfield(L, -1, func.c_str());
    lua_pushvalue(L, -2);
    lua_pushlightuserdata(L, arg1);
    if (lua_pcall(L, 2, 1, 0) != LUA_OK) {
        const char* err = lua_tostring(L, -1);
        lua_pop(L, 2);
        return 0;
    }
    int result = 0;
    if (lua_isinteger(L, -1)) {
        result = (int)lua_tointeger(L, -1);
    }
    lua_pop(L, 2);
    return result;
}
int LuaBackendClass::CallInt(const std::string& func, void* arg1, void* arg2) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, (int)table);
    lua_getfield(L, -1, func.c_str());
    lua_pushvalue(L, -2);
    lua_pushlightuserdata(L, arg1);
    lua_pushlightuserdata(L, arg2);
    if (lua_pcall(L, 3, 1, 0) != LUA_OK) {
        const char* err = lua_tostring(L, -1);
        lua_pop(L, 2);
        return 0;
    }
    int result = 0;
    if (lua_isinteger(L, -1)) {
        result = (int)lua_tointeger(L, -1);
    }
    lua_pop(L, 2);
    return result;
}
int LuaBackendClass::CallInt(const std::string& func, void* arg1, void* arg2, void* arg3) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, (int)table);
    lua_getfield(L, -1, func.c_str());
    lua_pushvalue(L, -2);
    lua_pushlightuserdata(L, arg1);
    lua_pushlightuserdata(L, arg2);
    lua_pushlightuserdata(L, arg3);
    if (lua_pcall(L, 4, 1, 0) != LUA_OK) {
        const char* err = lua_tostring(L, -1);
        lua_pop(L, 2);
        return 0;
    }
    int result = 0;
    if (lua_isinteger(L, -1)) {
        result = (int)lua_tointeger(L, -1);
    }
    lua_pop(L, 2);
    return result;
}
int LuaBackendClass::CallInt(const std::string& func, void* arg1, void* arg2, void* arg3, void* arg4) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, (int)table);
    lua_getfield(L, -1, func.c_str());
    lua_pushvalue(L, -2);
    lua_pushlightuserdata(L, arg1);
    lua_pushlightuserdata(L, arg2);
    lua_pushlightuserdata(L, arg3);
    lua_pushlightuserdata(L, arg4);
    if (lua_pcall(L, 5, 1, 0) != LUA_OK) {
        const char* err = lua_tostring(L, -1);
        lua_pop(L, 2);
        return 0;
    }
    int result = 0;
    if (lua_isinteger(L, -1)) {
        result = (int)lua_tointeger(L, -1);
    }
    lua_pop(L, 2);
    return result;
}
int LuaBackendClass::CallInt(const std::string& func, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, (int)table);
    lua_getfield(L, -1, func.c_str());
    lua_pushvalue(L, -2);
    lua_pushlightuserdata(L, arg1);
    lua_pushlightuserdata(L, arg2);
    lua_pushlightuserdata(L, arg3);
    lua_pushlightuserdata(L, arg4);
    lua_pushlightuserdata(L, arg5);
    if (lua_pcall(L, 6, 1, 0) != LUA_OK) {
        const char* err = lua_tostring(L, -1);
        lua_pop(L, 2);
        return 0;
    }
    int result = 0;
    if (lua_isinteger(L, -1)) {
        result = (int)lua_tointeger(L, -1);
    }
    lua_pop(L, 2);
    return result;
}
int LuaBackendClass::CallInt(const std::string& func, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, void* arg6) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, (int)table);
    lua_getfield(L, -1, func.c_str());
    lua_pushvalue(L, -2);
    lua_pushlightuserdata(L, arg1);
    lua_pushlightuserdata(L, arg2);
    lua_pushlightuserdata(L, arg3);
    lua_pushlightuserdata(L, arg4);
    lua_pushlightuserdata(L, arg5);
    lua_pushlightuserdata(L, arg6);
    if (lua_pcall(L, 7, 1, 0) != LUA_OK) {
        const char* err = lua_tostring(L, -1);
        lua_pop(L, 2);
        return 0;
    }
    int result = 0;
    if (lua_isinteger(L, -1)) {
        result = (int)lua_tointeger(L, -1);
    }
    lua_pop(L, 2);
    return result;
}

float LuaBackendClass::CallFloat(const std::string& func) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, (int)table);
    lua_getfield(L, -1, func.c_str());
    lua_pushvalue(L, -2);
    if (lua_pcall(L, 1, 1, 0) != LUA_OK) {
        const char* err = lua_tostring(L, -1);
        lua_pop(L, 2);
        return 0.0f;
    }
    float result = 0.0f;
    if (lua_isnumber(L, -1)) {
        result = (float)lua_tonumber(L, -1);
    }
    lua_pop(L, 2);
    return result;
}
float LuaBackendClass::CallFloat(const std::string& func, void* arg1) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, (int)table);
    lua_getfield(L, -1, func.c_str());
    lua_pushvalue(L, -2);
    lua_pushlightuserdata(L, arg1);
    if (lua_pcall(L, 2, 1, 0) != LUA_OK) {
        const char* err = lua_tostring(L, -1);
        lua_pop(L, 2);
        return 0.0f;
    }
    float result = 0.0f;
    if (lua_isnumber(L, -1)) {
        result = (float)lua_tonumber(L, -1);
    }
    lua_pop(L, 2);
    return result;
}
float LuaBackendClass::CallFloat(const std::string& func, void* arg1, void* arg2) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, (int)table);
    lua_getfield(L, -1, func.c_str());
    lua_pushvalue(L, -2);
    lua_pushlightuserdata(L, arg1);
    lua_pushlightuserdata(L, arg2);
    if (lua_pcall(L, 3, 1, 0) != LUA_OK) {
        const char* err = lua_tostring(L, -1);
        lua_pop(L, 2);
        return 0.0f;
    }
    float result = 0.0f;
    if (lua_isnumber(L, -1)) {
        result = (float)lua_tonumber(L, -1);
    }
    lua_pop(L, 2);
    return result;
}
float LuaBackendClass::CallFloat(const std::string& func, void* arg1, void* arg2, void* arg3) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, (int)table);
    lua_getfield(L, -1, func.c_str());
    lua_pushvalue(L, -2);
    lua_pushlightuserdata(L, arg1);
    lua_pushlightuserdata(L, arg2);
    lua_pushlightuserdata(L, arg3);
    if (lua_pcall(L, 4, 1, 0) != LUA_OK) {
        const char* err = lua_tostring(L, -1);
        lua_pop(L, 2);
        return 0.0f;
    }
    float result = 0.0f;
    if (lua_isnumber(L, -1)) {
        result = (float)lua_tonumber(L, -1);
    }
    lua_pop(L, 2);
    return result;
}
float LuaBackendClass::CallFloat(const std::string& func, void* arg1, void* arg2, void* arg3, void* arg4) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, (int)table);
    lua_getfield(L, -1, func.c_str());
    lua_pushvalue(L, -2);
    lua_pushlightuserdata(L, arg1);
    lua_pushlightuserdata(L, arg2);
    lua_pushlightuserdata(L, arg3);
    lua_pushlightuserdata(L, arg4);
    if (lua_pcall(L, 5, 1, 0) != LUA_OK) {
        const char* err = lua_tostring(L, -1);
        lua_pop(L, 2);
        return 0.0f;
    }
    float result = 0.0f;
    if (lua_isnumber(L, -1)) {
        result = (float)lua_tonumber(L, -1);
    }
    lua_pop(L, 2);
    return result;
}
float LuaBackendClass::CallFloat(const std::string& func, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, (int)table);
    lua_getfield(L, -1, func.c_str());
    lua_pushvalue(L, -2);
    lua_pushlightuserdata(L, arg1);
    lua_pushlightuserdata(L, arg2);
    lua_pushlightuserdata(L, arg3);
    lua_pushlightuserdata(L, arg4);
    lua_pushlightuserdata(L, arg5);
    if (lua_pcall(L, 6, 1, 0) != LUA_OK) {
        const char* err = lua_tostring(L, -1);
        lua_pop(L, 2);
        return 0.0f;
    }
    float result = 0.0f;
    if (lua_isnumber(L, -1)) {
        result = (float)lua_tonumber(L, -1);
    }
    lua_pop(L, 2);
    return result;
}
float LuaBackendClass::CallFloat(const std::string& func, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, void* arg6) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, (int)table);
    lua_getfield(L, -1, func.c_str());
    lua_pushvalue(L, -2);
    lua_pushlightuserdata(L, arg1);
    lua_pushlightuserdata(L, arg2);
    lua_pushlightuserdata(L, arg3);
    lua_pushlightuserdata(L, arg4);
    lua_pushlightuserdata(L, arg5);
    lua_pushlightuserdata(L, arg6);
    if (lua_pcall(L, 7, 1, 0) != LUA_OK) {
        const char* err = lua_tostring(L, -1);
        lua_pop(L, 2);
        return 0.0f;
    }
    float result = 0.0f;
    if (lua_isnumber(L, -1)) {
        result = (float)lua_tonumber(L, -1);
    }
    lua_pop(L, 2);
    return result;
}

bool LuaBackendClass::CallBool(const std::string& func) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, (int)table);
    lua_getfield(L, -1, func.c_str());
    lua_pushvalue(L, -2);
    if (lua_pcall(L, 1, 1, 0) != LUA_OK) {
        const char* err = lua_tostring(L, -1);
        lua_pop(L, 2);
        return false;
    }
    bool result = false;
    if (lua_isboolean(L, -1)) {
        result = lua_toboolean(L, -1);
    }
    lua_pop(L, 2);
    return result;
}
bool LuaBackendClass::CallBool(const std::string& func, void* arg1) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, (int)table);
    lua_getfield(L, -1, func.c_str());
    lua_pushvalue(L, -2);
    lua_pushlightuserdata(L, arg1);
    if (lua_pcall(L, 2, 1, 0) != LUA_OK) {
        const char* err = lua_tostring(L, -1);
        lua_pop(L, 2);
        return false;
    }
    bool result = false;
    if (lua_isboolean(L, -1)) {
        result = lua_toboolean(L, -1);
    }
    lua_pop(L, 2);
    return result;
}
bool LuaBackendClass::CallBool(const std::string& func, void* arg1, void* arg2) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, (int)table);
    lua_getfield(L, -1, func.c_str());
    lua_pushvalue(L, -2);
    lua_pushlightuserdata(L, arg1);
    lua_pushlightuserdata(L, arg2);
    if (lua_pcall(L, 3, 1, 0) != LUA_OK) {
        const char* err = lua_tostring(L, -1);
        lua_pop(L, 2);
        return false;
    }
    bool result = false;
    if (lua_isboolean(L, -1)) {
        result = lua_toboolean(L, -1);
    }
    lua_pop(L, 2);
    return result;
}
bool LuaBackendClass::CallBool(const std::string& func, void* arg1, void* arg2, void* arg3) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, (int)table);
    lua_getfield(L, -1, func.c_str());
    lua_pushvalue(L, -2);
    lua_pushlightuserdata(L, arg1);
    lua_pushlightuserdata(L, arg2);
    lua_pushlightuserdata(L, arg3);
    if (lua_pcall(L, 4, 1, 0) != LUA_OK) {
        const char* err = lua_tostring(L, -1);
        lua_pop(L, 2);
        return false;
    }
    bool result = false;
    if (lua_isboolean(L, -1)) {
        result = lua_toboolean(L, -1);
    }
    lua_pop(L, 2);
    return result;
}
bool LuaBackendClass::CallBool(const std::string& func, void* arg1, void* arg2, void* arg3, void* arg4) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, (int)table);
    lua_getfield(L, -1, func.c_str());
    lua_pushvalue(L, -2);
    lua_pushlightuserdata(L, arg1);
    lua_pushlightuserdata(L, arg2);
    lua_pushlightuserdata(L, arg3);
    lua_pushlightuserdata(L, arg4);
    if (lua_pcall(L, 5, 1, 0) != LUA_OK) {
        const char* err = lua_tostring(L, -1);
        lua_pop(L, 2);
        return false;
    }
    bool result = false;
    if (lua_isboolean(L, -1)) {
        result = lua_toboolean(L, -1);
    }
    lua_pop(L, 2);
    return result;
}
bool LuaBackendClass::CallBool(const std::string& func, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, (int)table);
    lua_getfield(L, -1, func.c_str());
    lua_pushvalue(L, -2);
    lua_pushlightuserdata(L, arg1);
    lua_pushlightuserdata(L, arg2);
    lua_pushlightuserdata(L, arg3);
    lua_pushlightuserdata(L, arg4);
    lua_pushlightuserdata(L, arg5);
    if (lua_pcall(L, 6, 1, 0) != LUA_OK) {
        const char* err = lua_tostring(L, -1);
        lua_pop(L, 2);
        return false;
    }
    bool result = false;
    if (lua_isboolean(L, -1)) {
        result = lua_toboolean(L, -1);
    }
    lua_pop(L, 2);
    return result;
}
bool LuaBackendClass::CallBool(const std::string& func, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, void* arg6) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, (int)table);
    lua_getfield(L, -1, func.c_str());
    lua_pushvalue(L, -2);
    lua_pushlightuserdata(L, arg1);
    lua_pushlightuserdata(L, arg2);
    lua_pushlightuserdata(L, arg3);
    lua_pushlightuserdata(L, arg4);
    lua_pushlightuserdata(L, arg5);
    lua_pushlightuserdata(L, arg6);
    if (lua_pcall(L, 7, 1, 0) != LUA_OK) {
        const char* err = lua_tostring(L, -1);
        lua_pop(L, 2);
        return false;
    }
    bool result = false;
    if (lua_isboolean(L, -1)) {
        result = lua_toboolean(L, -1);
    }
    lua_pop(L, 2);
    return result;
}

void LuaBackendClass::SetMetatable(void* metatable) {
    // Set the metatable for this Lua object
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, table); // push this object's table
    lua_rawgeti(L, LUA_REGISTRYINDEX, (int)(intptr_t)metatable); // push metatable
    lua_setmetatable(L, -2);
    lua_pop(L, 1); // pop the table
}
void* LuaBackendClass::GetMetatable() {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, table); // push this object's table
    if (!lua_istable(L, -1)) {
        lua_pop(L, 1);
        return nullptr;
    }
    if (!lua_getmetatable(L, -1)) {
        lua_pop(L, 1); // pop table
        return nullptr;
    }
    // At this point, metatable is on top of stack
    int ref = luaL_ref(L, LUA_REGISTRYINDEX);
    lua_pop(L, 1); // pop the table
    return (void*)(intptr_t)ref;
}
void LuaBackendClass::RawSet(void* key, void* value) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, table);
    lua_pushlightuserdata(L, key);
    lua_pushlightuserdata(L, value);
    lua_rawset(L, -3);
    lua_pop(L, 1);
}

void* LuaBackendClass::RawGet(void* key) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, table);
    lua_pushlightuserdata(L, key);
    lua_rawget(L, -2);
    void* result = nullptr;
    if (lua_islightuserdata(L, -1)) {
        result = lua_touserdata(L, -1);
    }
    lua_pop(L, 2);
    return result;
}

void LuaBackendClass::RawSet(int key, void* value) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, table);
    lua_pushinteger(L, key);
    lua_pushlightuserdata(L, value);
    lua_rawset(L, -3);
    lua_pop(L, 1);
}

void* LuaBackendClass::RawGet(int key) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, table);
    lua_pushinteger(L, key);
    lua_rawget(L, -2);
    void* result = nullptr;
    if (lua_islightuserdata(L, -1)) {
        result = lua_touserdata(L, -1);
    }
    lua_pop(L, 2);
    return result;
}

int LuaBackendClass::Len() {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, table);
#if LUA_VERSION_NUM >= 502
    int len = (int)lua_rawlen(L, -1);
#else
    int len = (int)lua_objlen(L, -1);
#endif
    lua_pop(L, 1);
    return len;
}

int LuaBackendClass::Size() {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, table);
    int count = 0;
    lua_pushnil(L);
    while (lua_next(L, -2) != 0) {
        ++count;
        lua_pop(L, 1);
    }
    lua_pop(L, 1);
    return count;
}

bool LuaBackendClass::IsEmpty() {
    return Size() == 0;
}

void LuaBackendClass::Wipe() {

void LuaBackendClass::SetMulMetamethod(int funcRef) { SetMetamethod("__mul", funcRef); }
void LuaBackendClass::SetDivMetamethod(int funcRef) { SetMetamethod("__div", funcRef); }
void LuaBackendClass::SetEqMetamethod(int funcRef)  { SetMetamethod("__eq", funcRef); }
void LuaBackendClass::SetLtMetamethod(int funcRef)  { SetMetamethod("__lt", funcRef); }
void LuaBackendClass::SetLeMetamethod(int funcRef)  { SetMetamethod("__le", funcRef); }
void LuaBackendClass::SetCallMetamethod(int funcRef) { SetMetamethod("__call", funcRef); }
void LuaBackendClass::SetIndexMetamethod(int funcRef) { SetMetamethod("__index", funcRef); }
void LuaBackendClass::SetNewIndexMetamethod(int funcRef) { SetMetamethod("__newindex", funcRef); }

// --- STL-style algorithm adapters ---
template<typename Predicate>
LuaBackendClass::Iterator LuaBackendClass::find_if(Predicate pred) {
    for (auto it = begin(); it != end(); ++it) {
        auto kv = *it;
        if (pred(kv.first, kv.second))
            return it;
    }
    return end();
}

template<typename Predicate>
bool LuaBackendClass::any_of(Predicate pred) {
    for (auto it = begin(); it != end(); ++it) {
        auto kv = *it;
        if (pred(kv.first, kv.second))
            return true;
    }
    return false;
}

template<typename Predicate>
bool LuaBackendClass::all_of(Predicate pred) {
    for (auto it = begin(); it != end(); ++it) {
        auto kv = *it;
        if (!pred(kv.first, kv.second))
            return false;
    }
    return true;
}

template<typename Func>
void LuaBackendClass::for_each(Func func) {
    for (auto it = begin(); it != end(); ++it) {
        auto kv = *it;
        func(kv.first, kv.second);
    }
}

// --- Reverse iterator support ---
LuaBackendClass::ReverseIterator::ReverseIterator(lua_State* L_, int tableRef_, bool end)
    : L(L_), tableRef(tableRef_), index(0), atEnd(end) {
    // Collect all items
    lua_rawgeti(L, LUA_REGISTRYINDEX, tableRef);
    lua_pushnil(L);
    while (lua_next(L, -2) != 0) {
        void* key = nullptr;
        void* value = nullptr;
        if (lua_type(L, -2) == LUA_TLIGHTUSERDATA)
            key = lua_touserdata(L, -2);
        else if (lua_type(L, -2) == LUA_TNUMBER)
            key = (void*)(intptr_t)lua_tointeger(L, -2);
        if (lua_type(L, -1) == LUA_TLIGHTUSERDATA)
            value = lua_touserdata(L, -1);
        else if (lua_type(L, -1) == LUA_TNUMBER)
            value = (void*)(intptr_t)lua_tointeger(L, -1);
        items.emplace_back(key, value);
        lua_pop(L, 1);
    }
    lua_pop(L, 1);
    if (!items.empty()) {
        index = items.size() - 1;
    } else {
        atEnd = true;
    }
    if (end) {
        index = size_t(-1);
        atEnd = true;
    }
}
LuaBackendClass::ReverseIterator& LuaBackendClass::ReverseIterator::operator++() {
    if (atEnd) return *this;
    if (index == 0) {
        atEnd = true;
    } else {
        --index;
    }
    return *this;
}
std::pair<void*, void*> LuaBackendClass::ReverseIterator::operator*() const {
    if (atEnd || items.empty()) return {nullptr, nullptr};
    return items[index];
}
bool LuaBackendClass::ReverseIterator::operator!=(const ReverseIterator& other) const {
    return atEnd != other.atEnd || index != other.index;
}
LuaBackendClass::ReverseIterator LuaBackendClass::rbegin() {
    return ReverseIterator(LuaManager::Instance().GetState(), table, false);
}
LuaBackendClass::ReverseIterator LuaBackendClass::rend() {
    return ReverseIterator(LuaManager::Instance().GetState(), table, true);
}

// --- Weak reference support ---
void LuaBackendClass::MakeWeak() {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, table);
    if (!lua_getmetatable(L, -1)) {
        lua_newtable(L);
    }
    lua_pushstring(L, "__mode");
    lua_pushstring(L, "v"); // weak values
    lua_settable(L, -3);
    lua_setmetatable(L, -2);
    lua_pop(L, 1);
}

bool LuaBackendClass::IsWeak() const {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, table);
    bool weak = false;
    if (lua_getmetatable(L, -1)) {
        lua_pushstring(L, "__mode");
        lua_gettable(L, -2);
        if (lua_isstring(L, -1)) {
            std::string mode = lua_tostring(L, -1);
            weak = (mode.find('v') != std::string::npos);
        }
        lua_pop(L, 2);
    } else {
        lua_pop(L, 1);
    }
    return weak;
}

// --- Helpers for common metamethods ---
void LuaBackendClass::SetAddMetamethod(int funcRef) {
    SetMetamethod("__add", funcRef);
}
void LuaBackendClass::SetSubMetamethod(int funcRef) {
    SetMetamethod("__sub", funcRef);
}
void LuaBackendClass::SetToStringMetamethod(int funcRef) {
    SetMetamethod("__tostring", funcRef);
}

// --- In-place filter/map ---
void LuaBackendClass::FilterInPlace(std::function<bool(void*, void*)> pred) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, table);
    std::vector<void*> toRemove;
    lua_pushnil(L);
    while (lua_next(L, -2) != 0) {
        void* key = nullptr;
        void* value = nullptr;
        if (lua_type(L, -2) == LUA_TLIGHTUSERDATA)
            key = lua_touserdata(L, -2);
        else if (lua_type(L, -2) == LUA_TNUMBER)
            key = (void*)(intptr_t)lua_tointeger(L, -2);
        if (lua_type(L, -1) == LUA_TLIGHTUSERDATA)
            value = lua_touserdata(L, -1);
        else if (lua_type(L, -1) == LUA_TNUMBER)
            value = (void*)(intptr_t)lua_tointeger(L, -1);
        if (!pred(key, value))
            toRemove.push_back(key);
        lua_pop(L, 1);
    }
    for (void* key : toRemove) {
        lua_pushlightuserdata(L, key);
        lua_pushnil(L);
        lua_rawset(L, -3);
    }
    lua_pop(L, 1);
}

template<typename R>
void LuaBackendClass::MapInPlace(std::function<R(void*, void*&)> func) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, table);
    lua_pushnil(L);
    std::vector<std::pair<void*, R>> updates;
    while (lua_next(L, -2) != 0) {
        void* key = nullptr;
        void* value = nullptr;
        if (lua_type(L, -2) == LUA_TLIGHTUSERDATA)
            key = lua_touserdata(L, -2);
        else if (lua_type(L, -2) == LUA_TNUMBER)
            key = (void*)(intptr_t)lua_tointeger(L, -2);
        if (lua_type(L, -1) == LUA_TLIGHTUSERDATA)
            value = lua_touserdata(L, -1);
        else if (lua_type(L, -1) == LUA_TNUMBER)
            value = (void*)(intptr_t)lua_tointeger(L, -1);
        R newValue = func(key, value);
        updates.emplace_back(key, newValue);
        lua_pop(L, 1);
    }
    for (const auto& kv : updates) {
        lua_pushlightuserdata(L, kv.first);
        zombie::LuaUtils::Push(L, kv.second);
        lua_rawset(L, -3);
    }
    lua_pop(L, 1);
}

// --- Nested accessors and default value support ---
template<typename T>
T LuaBackendClass::GetNested(const std::vector<std::string>& keys, const T& defaultValue) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, table);
    for (size_t i = 0; i < keys.size(); ++i) {
        lua_pushstring(L, keys[i].c_str());
        lua_gettable(L, -2);
        if (lua_isnil(L, -1)) {
            lua_pop(L, 2);
            return defaultValue;
        }
        if (i + 1 < keys.size())
            lua_remove(L, -2); // keep only the new table
    }
    T result = zombie::LuaUtils::To<T>(L, -1);
    lua_pop(L, 2);
    return result;
}

template<typename T>
void LuaBackendClass::SetNested(const std::vector<std::string>& keys, const T& value) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, table);
    for (size_t i = 0; i + 1 < keys.size(); ++i) {
        lua_pushstring(L, keys[i].c_str());
        lua_gettable(L, -2);
        if (!lua_istable(L, -1)) {
            lua_pop(L, 1);
            lua_newtable(L);
            lua_pushstring(L, keys[i].c_str());
            lua_pushvalue(L, -2);
            lua_settable(L, -4);
        }
        lua_remove(L, -2);
    }
    lua_pushstring(L, keys.back().c_str());
    zombie::LuaUtils::Push(L, value);
    lua_settable(L, -3);
    lua_pop(L, 1);
}

// --- Reference management ---
bool LuaBackendClass::IsValid() const {
    return table != LUA_NOREF && table != LUA_REFNIL;
}
void LuaBackendClass::Release() {
    if (IsValid()) {
        lua_State* L = LuaManager::Instance().GetState();
        luaL_unref(L, LUA_REGISTRYINDEX, table);
        table = LUA_NOREF;
    }
}
int LuaBackendClass::GetRef() const {
    return table;
}

// --- Error/logging ---
void LuaBackendClass::LogLuaError(lua_State* L, const std::string& context) {
    const char* err = lua_tostring(L, -1);
    if (err) {
        if (!context.empty())
            fprintf(stderr, "[Lua Error][%s]: %s\n", context.c_str(), err);
        else
            fprintf(stderr, "[Lua Error]: %s\n", err);
    }
    lua_pop(L, 1);
}

// --- Metamethod utilities ---
void LuaBackendClass::SetMetamethod(const std::string& name, int funcRef) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, table);
    if (!lua_getmetatable(L, -1)) {
        lua_newtable(L);
    }
    lua_pushstring(L, name.c_str());
    lua_rawgeti(L, LUA_REGISTRYINDEX, funcRef);
    lua_settable(L, -3);
    lua_setmetatable(L, -2);
    lua_pop(L, 1);
}
int LuaBackendClass::GetMetamethod(const std::string& name) {
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, table);
    if (!lua_getmetatable(L, -1)) {
        lua_pop(L, 1);
        return LUA_REFNIL;
    }
    lua_pushstring(L, name.c_str());
    lua_gettable(L, -2);
    int ref = LUA_REFNIL;
    if (!lua_isnil(L, -1)) {
        ref = luaL_ref(L, LUA_REGISTRYINDEX);
    } else {
        lua_pop(L, 1);
    }
    lua_pop(L, 2);
    return ref;
}

// --- Iterator adapter ---
LuaBackendClass::Iterator::Iterator(lua_State* L_, int tableRef_, bool end)
    : L(L_), tableRef(tableRef_), keyRef(LUA_REFNIL), atEnd(end) {
    if (!end) {
        lua_rawgeti(L, LUA_REGISTRYINDEX, tableRef);
        lua_pushnil(L);
        if (lua_next(L, -2) == 0) {
            atEnd = true;
            lua_pop(L, 1);
        } else {
            keyRef = luaL_ref(L, LUA_REGISTRYINDEX);
            lua_pop(L, 1);
        }
        lua_pop(L, 1);
    }
}
LuaBackendClass::Iterator& LuaBackendClass::Iterator::operator++() {
    if (atEnd) return *this;
    lua_rawgeti(L, LUA_REGISTRYINDEX, tableRef);
    lua_rawgeti(L, LUA_REGISTRYINDEX, keyRef);
    if (lua_next(L, -2) == 0) {
        atEnd = true;
        lua_pop(L, 1);
    } else {
        luaL_unref(L, LUA_REGISTRYINDEX, keyRef);
        keyRef = luaL_ref(L, LUA_REGISTRYINDEX);
        lua_pop(L, 1);
    }
    lua_pop(L, 1);
    return *this;
}
std::pair<void*, void*> LuaBackendClass::Iterator::operator*() const {
    lua_rawgeti(L, LUA_REGISTRYINDEX, tableRef);
    lua_rawgeti(L, LUA_REGISTRYINDEX, keyRef);
    void* key = nullptr;
    void* value = nullptr;
    if (lua_type(L, -1) == LUA_TLIGHTUSERDATA)
        key = lua_touserdata(L, -1);
    else if (lua_type(L, -1) == LUA_TNUMBER)
        key = (void*)(intptr_t)lua_tointeger(L, -1);
    lua_pop(L, 1);
    lua_pushvalue(L, -1);
    if (lua_type(L, -1) == LUA_TLIGHTUSERDATA)
        value = lua_touserdata(L, -1);
    else if (lua_type(L, -1) == LUA_TNUMBER)
        value = (void*)(intptr_t)lua_tointeger(L, -1);
    lua_pop(L, 2);
    return {key, value};
}
bool LuaBackendClass::Iterator::operator!=(const Iterator& other) const {
    return atEnd != other.atEnd;
}
LuaBackendClass::Iterator LuaBackendClass::begin() {
    return Iterator(LuaManager::Instance().GetState(), table, false);
}
LuaBackendClass::Iterator LuaBackendClass::end() {
    return Iterator(LuaManager::Instance().GetState(), table, true);
}

    // --- Table filtering/mapping ---
    std::vector<void*> LuaBackendClass::Filter(std::function<bool(void*, void*)> pred) {
        std::vector<void*> keys;
        lua_State* L = LuaManager::Instance().GetState();
        lua_rawgeti(L, LUA_REGISTRYINDEX, table);
        lua_pushnil(L);
        while (lua_next(L, -2) != 0) {
            void* key = nullptr;
            void* value = nullptr;
            if (lua_type(L, -2) == LUA_TLIGHTUSERDATA)
                key = lua_touserdata(L, -2);
            else if (lua_type(L, -2) == LUA_TNUMBER)
                key = (void*)(intptr_t)lua_tointeger(L, -2);
            if (lua_type(L, -1) == LUA_TLIGHTUSERDATA)
                value = lua_touserdata(L, -1);
            else if (lua_type(L, -1) == LUA_TNUMBER)
                value = (void*)(intptr_t)lua_tointeger(L, -1);
            if (pred(key, value))
                keys.push_back(key);
            lua_pop(L, 1);
        }
        lua_pop(L, 1);
        return keys;
    }

    template<typename R>
    std::vector<R> LuaBackendClass::Map(std::function<R(void*, void*)> func) {
        std::vector<R> results;
        lua_State* L = LuaManager::Instance().GetState();
        lua_rawgeti(L, LUA_REGISTRYINDEX, table);
        lua_pushnil(L);
        while (lua_next(L, -2) != 0) {
            void* key = nullptr;
            void* value = nullptr;
            if (lua_type(L, -2) == LUA_TLIGHTUSERDATA)
                key = lua_touserdata(L, -2);
            else if (lua_type(L, -2) == LUA_TNUMBER)
                key = (void*)(intptr_t)lua_tointeger(L, -2);
            if (lua_type(L, -1) == LUA_TLIGHTUSERDATA)
                value = lua_touserdata(L, -1);
            else if (lua_type(L, -1) == LUA_TNUMBER)
                value = (void*)(intptr_t)lua_tointeger(L, -1);
            results.push_back(func(key, value));
            lua_pop(L, 1);
        }
        lua_pop(L, 1);
        return results;
    }
    // --- Type-safe accessors ---
    template<typename T>
    void LuaBackendClass::Set(const std::string& key, const T& value) {
        lua_State* L = LuaManager::Instance().GetState();
        lua_rawgeti(L, LUA_REGISTRYINDEX, table);
        lua_pushstring(L, key.c_str());
        zombie::LuaUtils::Push(L, value);
        lua_settable(L, -3);
        lua_pop(L, 1);
    }

    template<typename T>
    T LuaBackendClass::Get(const std::string& key) {
        lua_State* L = LuaManager::Instance().GetState();
        lua_rawgeti(L, LUA_REGISTRYINDEX, table);
        lua_pushstring(L, key.c_str());
        lua_gettable(L, -2);
        T result = zombie::LuaUtils::To<T>(L, -1);
        lua_pop(L, 2);
        return result;
    }

    template<typename T>
    void LuaBackendClass::Set(int key, const T& value) {
        lua_State* L = LuaManager::Instance().GetState();
        lua_rawgeti(L, LUA_REGISTRYINDEX, table);
        lua_pushinteger(L, key);
        zombie::LuaUtils::Push(L, value);
        lua_settable(L, -3);
        lua_pop(L, 1);
    }

    template<typename T>
    T LuaBackendClass::Get(int key) {
        lua_State* L = LuaManager::Instance().GetState();
        lua_rawgeti(L, LUA_REGISTRYINDEX, table);
        lua_pushinteger(L, key);
        lua_gettable(L, -2);
        T result = zombie::LuaUtils::To<T>(L, -1);
        lua_pop(L, 2);
        return result;
    }

    // --- String key support for RawSet/RawGet ---
    void LuaBackendClass::RawSet(const std::string& key, void* value) {
        lua_State* L = LuaManager::Instance().GetState();
        lua_rawgeti(L, LUA_REGISTRYINDEX, table);
        lua_pushstring(L, key.c_str());
        lua_pushlightuserdata(L, value);
        lua_rawset(L, -3);
        lua_pop(L, 1);
    }

    void* LuaBackendClass::RawGet(const std::string& key) {
        lua_State* L = LuaManager::Instance().GetState();
        lua_rawgeti(L, LUA_REGISTRYINDEX, table);
        lua_pushstring(L, key.c_str());
        lua_rawget(L, -2);
        void* result = nullptr;
        if (lua_islightuserdata(L, -1)) {
            result = lua_touserdata(L, -1);
        }
        lua_pop(L, 2);
        return result;
    }
    // Iterate all key-value pairs, calling a C++ function for each
    void LuaBackendClass::ForEach(std::function<void(void*, void*)> fn) {
        lua_State* L = LuaManager::Instance().GetState();
        lua_rawgeti(L, LUA_REGISTRYINDEX, table);
        std::vector<std::pair<void*, void*>> items;
        items.reserve(Size());
        lua_pushnil(L);
        while (lua_next(L, -2) != 0) {
            void* key = nullptr;
            void* value = nullptr;
            if (lua_type(L, -2) == LUA_TLIGHTUSERDATA)
                key = lua_touserdata(L, -2);
            else if (lua_type(L, -2) == LUA_TNUMBER)
                key = (void*)(intptr_t)lua_tointeger(L, -2);
            if (lua_type(L, -1) == LUA_TLIGHTUSERDATA)
                value = lua_touserdata(L, -1);
            else if (lua_type(L, -1) == LUA_TNUMBER)
                value = (void*)(intptr_t)lua_tointeger(L, -1);
            items.emplace_back(key, value);
            lua_pop(L, 1);
        }
        lua_pop(L, 1);
        for (const auto& kv : items) {
            fn(kv.first, kv.second);
        }
    }

    // Collect all keys as void* (lightuserdata or int)
    std::vector<void*> LuaBackendClass::Keys() {
        std::vector<void*> keys;
        lua_State* L = LuaManager::Instance().GetState();
        lua_rawgeti(L, LUA_REGISTRYINDEX, table);
        keys.reserve(Size());
        lua_pushnil(L);
        while (lua_next(L, -2) != 0) {
            if (lua_type(L, -2) == LUA_TLIGHTUSERDATA)
                keys.push_back(lua_touserdata(L, -2));
            else if (lua_type(L, -2) == LUA_TNUMBER)
                keys.push_back((void*)(intptr_t)lua_tointeger(L, -2));
            lua_pop(L, 1);
        }
        lua_pop(L, 1);
        return keys;
    }

    // Collect all values as void* (lightuserdata or int)
    std::vector<void*> LuaBackendClass::Values() {
        std::vector<void*> values;
        lua_State* L = LuaManager::Instance().GetState();
        lua_rawgeti(L, LUA_REGISTRYINDEX, table);
        values.reserve(Size());
        lua_pushnil(L);
        while (lua_next(L, -2) != 0) {
            if (lua_type(L, -1) == LUA_TLIGHTUSERDATA)
                values.push_back(lua_touserdata(L, -1));
            else if (lua_type(L, -1) == LUA_TNUMBER)
                values.push_back((void*)(intptr_t)lua_tointeger(L, -1));
            lua_pop(L, 1);
        }
        lua_pop(L, 1);
        return values;
    }

    // Save all key-value pairs to another Lua table (by registry ref)
    void LuaBackendClass::SaveToTable(int destTableRef) {
        lua_State* L = LuaManager::Instance().GetState();
        lua_rawgeti(L, LUA_REGISTRYINDEX, table);
        lua_rawgeti(L, LUA_REGISTRYINDEX, destTableRef);
        lua_pushnil(L);
        while (lua_next(L, -3) != 0) {
            lua_pushvalue(L, -2); // duplicate key
            lua_pushvalue(L, -2); // duplicate value
            lua_settable(L, -4);  // destTable[key] = value
            lua_pop(L, 1); // pop value
        }
        lua_pop(L, 2); // pop both tables
    }

    // Load all key-value pairs from another Lua table (by registry ref)
    void LuaBackendClass::LoadFromTable(int srcTableRef) {
        lua_State* L = LuaManager::Instance().GetState();
        lua_rawgeti(L, LUA_REGISTRYINDEX, table);
        lua_rawgeti(L, LUA_REGISTRYINDEX, srcTableRef);
        lua_pushnil(L);
        while (lua_next(L, -2) != 0) {
            lua_pushvalue(L, -2); // duplicate key
            lua_pushvalue(L, -2); // duplicate value
            lua_settable(L, -5);  // this->table[key] = value
            lua_pop(L, 1); // pop value
        }
        lua_pop(L, 2); // pop both tables
    }

    // Basic iterator: returns a vector of pairs (key, value)
    std::vector<std::pair<void*, void*>> LuaBackendClass::Items() {
        std::vector<std::pair<void*, void*>> items;
        lua_State* L = LuaManager::Instance().GetState();
        lua_rawgeti(L, LUA_REGISTRYINDEX, table);
        items.reserve(Size());
        lua_pushnil(L);
        while (lua_next(L, -2) != 0) {
            void* key = nullptr;
            void* value = nullptr;
            if (lua_type(L, -2) == LUA_TLIGHTUSERDATA)
                key = lua_touserdata(L, -2);
            else if (lua_type(L, -2) == LUA_TNUMBER)
                key = (void*)(intptr_t)lua_tointeger(L, -2);
            if (lua_type(L, -1) == LUA_TLIGHTUSERDATA)
                value = lua_touserdata(L, -1);
            else if (lua_type(L, -1) == LUA_TNUMBER)
                value = (void*)(intptr_t)lua_tointeger(L, -1);
            items.emplace_back(key, value);
            lua_pop(L, 1);
        }
        lua_pop(L, 1);
        return items;
    }
    lua_State* L = LuaManager::Instance().GetState();
    lua_rawgeti(L, LUA_REGISTRYINDEX, table);
    lua_pushnil(L);
    while (lua_next(L, -2) != 0) {
        lua_pop(L, 1);
        lua_pushvalue(L, -1);
        lua_pushnil(L);
        lua_settable(L, -4);
        lua_pushnil(L);
    }
    lua_pop(L, 1);
}
// ...other table/iterator/save/load methods as needed

} // namespace zombie
