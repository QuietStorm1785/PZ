#include <vector>
#include <unordered_map>
// LuaManager.h
#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include "lua.hpp"
#include "zombie/LuaCpp/Event.h"
#include "zombie/LuaCpp/LuaSignal.h"

namespace zombie {

// Main class for managing Lua state, script loading, event/callback registration, and C++/Lua interop.
class LuaManager {
    // --- Lua-side event system: register and trigger Lua callbacks from C++ ---
    // Register a Lua event by name.
    void RegisterLuaEvent(const std::string& eventName);
    // Add a Lua function (by registry reference) as a listener for a Lua event.
    void AddLuaEventListener(const std::string& eventName, int luaFuncRef);
    // Remove a Lua function (by registry reference) from a Lua event's listeners.
    void RemoveLuaEventListener(const std::string& eventName, int luaFuncRef);
    // Trigger a Lua event, calling all registered listeners with nargs arguments.
    void TriggerLuaEvent(const std::string& eventName, int nargs = 0);
private:
    struct LuaEvent {
        std::vector<int> listeners; // Lua registry references for event listeners
    };
    std::unordered_map<std::string, LuaEvent> luaEvents; // Map of event name to listeners
public:
    // --- Singleton access ---
    // Get the singleton instance of LuaManager.
    static LuaManager& Instance();

    // --- State management ---
    // Initialize the Lua state and open libraries.
    void Init();
    // Close the Lua state and free resources.
    void Shutdown();
    // Get the raw Lua state pointer.
    lua_State* GetState();

    // --- Script loading ---
    // Load and run a Lua script file.
    bool LoadScript(const std::string& filename);
    // Load all Lua scripts in a directory.
    void LoadDirectory(const std::string& dirPath);

    // --- Function/class registration ---
    // Register a C++ function as a Lua global.
    void RegisterFunction(const std::string& name, lua_CFunction fn);
    // Register a C++ class/metatable and its methods with Lua.
    void RegisterClass(const std::string& name, const luaL_Reg* methods);

    // --- Event system (integrated with LuaCpp::Event) ---
    // Register a C++ event by name.
    void RegisterEvent(const std::string& eventName);
    // Add a C++/Lua callback closure to an event.
    void AddEventCallback(const std::string& eventName, LuaCpp::LuaClosure* closure);
    // Remove a callback closure from an event.
    void RemoveEventCallback(const std::string& eventName, LuaCpp::LuaClosure* closure);
    // Trigger a C++ event, passing arguments to all registered callbacks.
    bool TriggerEvent(const std::string& eventName, std::vector<void*> args = {});

    // --- Signal-slot/observer pattern for C++/Lua ---
    // Register a named signal for the observer pattern.
    void RegisterSignal(const std::string& name);
    // Connect a slot (callback) to a named signal.
    void ConnectSignal(const std::string& name, LuaCpp::LuaSignal::Slot slot);
    // Emit a signal, calling all connected slots.
    void EmitSignal(const std::string& name);

    // --- Utility ---
    // Call a Lua global function by name, with arguments and expected results.
    bool CallGlobal(const std::string& funcName, int nargs = 0, int nresults = 0);
    // Push a Lua function onto the stack by name.
    bool PushFunction(const std::string& funcName);

private:
    LuaManager();
    ~LuaManager();
    lua_State* L; // The Lua state
    std::unordered_map<std::string, LuaCpp::Event> events;
    std::unordered_map<std::string, LuaCpp::LuaSignal> signals; // C++ signals
};

// --- Global object manager mirroring LuaManager$GlobalObject ---
class LuaGlobalObject {
public:
    static Model* LoadVehicleModel(const std::string& name, const std::string& path, const std::string& type);
    static Model* LoadZomboidModel();
    static void SetModelMetaData(const std::string& name, const std::string& meta1, const std::string& meta2, const std::string& meta3, bool flag);
    // ...other static methods as needed
};

// --- Item query/event handler mirroring LuaManager$GlobalObject$ItemQuery ---
class LuaItemQuery {
public:
    LuaItemQuery(const std::vector<std::string>& ids, int luaFuncRef, void* arg);
    void OnItemCreated(long id, bool success);
    void OnItemNotCreated(int id);
    void OnItemUpdated(bool success);
    void OnItemNotUpdated(int id);
    void OnItemSubscribed(long id);
    void OnItemNotSubscribed(long id, int code);
    void OnItemDownloaded(long id);
    void OnItemNotDownloaded(long id, int code);
    void OnItemQueryCompleted(long id, int count);
    void OnItemQueryNotCompleted(long id, int code);
private:
    int luaFuncRef;
    void* arg;
    long handle;
};

// --- Lua comparator mirroring LuaManager$GlobalObject$TimSortComparator ---
class LuaComparator {
public:
    LuaComparator(int luaFuncRef);
    int Compare(void* a, void* b);
private:
    int luaFuncRef;
};

// --- Lua file writer mirroring LuaManager$GlobalObject$LuaFileWriter ---
class LuaFileWriter {
public:
    LuaFileWriter(const std::string& filename);
    void Write(const std::string& text);
    void Writeln(const std::string& text);
    void Close();
private:
    std::ofstream writer;
};

// --- LuaExposer: mirrors LuaManager$Exposer for C++/Lua integration ---
class LuaExposer {
public:
    // Expose all registered types/classes to Lua
    void ExposeAll();
    // Mark a type as exposed
    template<typename T>
    void SetExposed();
    // Check if a type should be exposed
    template<typename T>
    bool ShouldExpose();
private:
    std::unordered_set<std::type_index> exposedTypes;
};

// --- LuaHookManager: manages Lua hooks/events, mirrors Java LuaHookManager ---
class LuaHookManager {
public:
    // Trigger a hook/event by name with up to 6 arguments
    static bool TriggerHook(const std::string& name);
    static bool TriggerHook(const std::string& name, void* arg1);
    static bool TriggerHook(const std::string& name, void* arg1, void* arg2);
    static bool TriggerHook(const std::string& name, void* arg1, void* arg2, void* arg3);
    static bool TriggerHook(const std::string& name, void* arg1, void* arg2, void* arg3, void* arg4);
    static bool TriggerHook(const std::string& name, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5);
    static bool TriggerHook(const std::string& name, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, void* arg6);

    // Add and register events
    static void AddEvent(const std::string& name);
    static void AddEvents();
    static void Clear();
    static void RegisterHooks();
    static void Reset();

private:
    struct Event {
        std::string name;
        std::vector<int> callbacks; // Lua registry refs
        Event(const std::string& n) : name(n) {}
        bool trigger(lua_State* L, void** args, int nargs);
    };
    static std::vector<Event> eventList;
    static std::unordered_map<std::string, Event*> eventMap;
};

// --- LuaBackendClass: mirrors Java LuaBackendClass for table/function access ---
class LuaBackendClass {
                                                                        void SetMulMetamethod(int funcRef); // __mul
                                                                        void SetDivMetamethod(int funcRef); // __div
                                                                        void SetEqMetamethod(int funcRef);  // __eq
                                                                        void SetLtMetamethod(int funcRef);  // __lt
                                                                        void SetLeMetamethod(int funcRef);  // __le
                                                                        void SetCallMetamethod(int funcRef); // __call
                                                                        void SetIndexMetamethod(int funcRef); // __index
                                                                        void SetNewIndexMetamethod(int funcRef); // __newindex
                                                                    // --- STL-style algorithm adapters ---
                                                                    template<typename Predicate>
                                                                    Iterator find_if(Predicate pred);
                                                                    template<typename Predicate>
                                                                    bool any_of(Predicate pred);
                                                                    template<typename Predicate>
                                                                    bool all_of(Predicate pred);
                                                                    template<typename Func>
                                                                    void for_each(Func func);
                                                                // --- Reverse iterator support ---
                                                                class ReverseIterator {
                                                                public:
                                                                    ReverseIterator(lua_State* L, int tableRef, bool end = false);
                                                                    ReverseIterator& operator++();
                                                                    std::pair<void*, void*> operator*() const;
                                                                    bool operator!=(const ReverseIterator& other) const;
                                                                private:
                                                                    lua_State* L;
                                                                    int tableRef;
                                                                    std::vector<std::pair<void*, void*>> items;
                                                                    size_t index;
                                                                    bool atEnd;
                                                                };
                                                                ReverseIterator rbegin();
                                                                ReverseIterator rend();
                                                            // --- Weak reference support ---
                                                            void MakeWeak();
                                                            bool IsWeak() const;
                                                        // --- Helpers for common metamethods ---
                                                        void SetAddMetamethod(int funcRef); // __add
                                                        void SetSubMetamethod(int funcRef); // __sub
                                                        void SetToStringMetamethod(int funcRef); // __tostring
                                                        // ...add more as needed
                                                    // --- In-place filter/map ---
                                                    void FilterInPlace(std::function<bool(void*, void*)> pred);
                                                    template<typename R>
                                                    void MapInPlace(std::function<R(void*, void*&)> func);
                                                // --- Nested accessors and default value support ---
                                                template<typename T>
                                                T GetNested(const std::vector<std::string>& keys, const T& defaultValue = T());
                                                template<typename T>
                                                void SetNested(const std::vector<std::string>& keys, const T& value);
                                            // --- Reference management ---
                                            bool IsValid() const;
                                            void Release();
                                            int GetRef() const;

                                            // --- Error/logging ---
                                            static void LogLuaError(lua_State* L, const std::string& context = "");

                                            // --- Metamethod utilities ---
                                            void SetMetamethod(const std::string& name, int funcRef);
                                            int GetMetamethod(const std::string& name);

                                            // --- Iterator adapter ---
                                            class Iterator {
                                            public:
                                                Iterator(lua_State* L, int tableRef, bool end = false);
                                                Iterator& operator++();
                                                std::pair<void*, void*> operator*() const;
                                                bool operator!=(const Iterator& other) const;
                                            private:
                                                lua_State* L;
                                                int tableRef;
                                                int keyRef;
                                                bool atEnd;
                                            };
                                            Iterator begin();
                                            Iterator end();
                                        // --- Table filtering/mapping ---
                                        // Filter: returns a vector of keys for which pred(key, value) is true
                                        std::vector<void*> Filter(std::function<bool(void*, void*)> pred);
                                        // Map: applies func(key, value) to all pairs, returns vector of results
                                        template<typename R>
                                        std::vector<R> Map(std::function<R(void*, void*)> func);
                                    // --- Type-safe accessors ---
                                    template<typename T>
                                    void Set(const std::string& key, const T& value);
                                    template<typename T>
                                    T Get(const std::string& key);

                                    template<typename T>
                                    void Set(int key, const T& value);
                                    template<typename T>
                                    T Get(int key);

                                    // --- String key support for RawSet/RawGet ---
                                    void RawSet(const std::string& key, void* value);
                                    void* RawGet(const std::string& key);
                                // --- Lua-side event/callback registration ---
                                static void RegisterLuaEvent(const std::string& eventName);
                                static void AddLuaEventListener(const std::string& eventName, int luaFuncRef);
                                static void RemoveLuaEventListener(const std::string& eventName, int luaFuncRef);
                                static void TriggerLuaEvent(const std::string& eventName, int nargs = 0);
                            private:
                                static std::unordered_map<std::string, std::vector<int>> luaEventListeners;
                            // --- Template-based type conversion ---
                            template<typename T>
                            static void Push(lua_State* L, const T& value);
                            template<typename T>
                            static T Get(lua_State* L, int idx);

                            // --- Smart pointer support ---
                            template<typename T>
                            static void PushSharedPtr(lua_State* L, std::shared_ptr<T> ptr, const std::string& metatableName);
                            template<typename T>
                            static std::shared_ptr<T> GetSharedPtr(lua_State* L, int idx);
                            template<typename T>
                            static void PushUniquePtr(lua_State* L, std::unique_ptr<T> ptr, const std::string& metatableName);
                            template<typename T>
                            static std::unique_ptr<T> GetUniquePtr(lua_State* L, int idx);
                        // --- Bytecode support ---
                        static bool LoadBytecode(lua_State* L, const std::vector<char>& bytecode, const std::string& chunkName = "");
                        static bool DumpBytecode(lua_State* L, int funcIndex, std::vector<char>& outBytecode);
                    // --- Type conversion utilities ---
                    static int ToInt(lua_State* L, int idx);
                    static float ToFloat(lua_State* L, int idx);
                    static bool ToBool(lua_State* L, int idx);
                    static std::string ToString(lua_State* L, int idx);
                    static void* ToPtr(lua_State* L, int idx);

                    static void PushInt(lua_State* L, int value);
                    static void PushFloat(lua_State* L, float value);
                    static void PushBool(lua_State* L, bool value);
                    static void PushString(lua_State* L, const std::string& value);
                    static void PushPtr(lua_State* L, void* value);
                // --- Type-safe argument extraction ---
                static std::string GetArgString(lua_State* L, int idx);
                static int GetArgInt(lua_State* L, int idx);
                static void* GetArgPtr(lua_State* L, int idx);
                static bool GetArgBool(lua_State* L, int idx);

                // --- Reference management ---
                static int Ref(lua_State* L, int idx);
                static void Unref(lua_State* L, int ref);

                // --- Scoped stack management ---
                class StackGuard {
                public:
                    StackGuard(lua_State* L);
                    ~StackGuard();
                private:
                    lua_State* L;
                    int top;
                };

                // --- Error reporting/logging ---
                static void LogError(const std::string& msg);

                // --- Lua function as std::function ---
                static std::function<int(void*)> MakeLuaFunction(int ref);

                // --- Coroutine yield/resume with values ---
                static int Yield(lua_State* L, int nresults);
                static int Resume(lua_State* co, int nargs, int* nresults = nullptr);

                // --- Automatic metatable registration ---
                template<typename T>
                static void RegisterMetatable(const std::string& name, const luaL_Reg* methods);
            // Advanced callback registration
            using CallbackFn = std::function<int(lua_State*)>;
            static int RegisterCallback(const std::string& name, CallbackFn cb);
        private:
            static std::unordered_map<std::string, CallbackFn> callbackMap;
            static int GenericCallback(lua_State* L);
        // Advanced userdata
        void PushUserdata(void* ptr, const std::string& metatableName);
        void* ToUserdata(int index);

        // Function binding
        static void BindFunction(const std::string& name, lua_CFunction fn);

        // Coroutine support
        static int CreateCoroutine(const std::string& funcName);
        static int ResumeCoroutine(int coroutineRef, int nargs = 0);
    // Metatable support
    void SetMetatable(int metatableRef);
    int GetMetatable();
public:
    LuaBackendClass(const std::string& typeName);
    std::string GetString(const std::string& key);
    void CallVoid(const std::string& func);
    void CallVoid(const std::string& func, void* arg1);
    void CallVoid(const std::string& func, void* arg1, void* arg2);
    void CallVoid(const std::string& func, void* arg1, void* arg2, void* arg3);
    void CallVoid(const std::string& func, void* arg1, void* arg2, void* arg3, void* arg4);
    void CallVoid(const std::string& func, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5);
    void CallVoid(const std::string& func, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, void* arg6);
    void* Call(const std::string& func);
    void* Call(const std::string& func, void* arg1);
    void* Call(const std::string& func, void* arg1, void* arg2);
    void* Call(const std::string& func, void* arg1, void* arg2, void* arg3);
    void* Call(const std::string& func, void* arg1, void* arg2, void* arg3, void* arg4);
    void* Call(const std::string& func, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5);
    void* Call(const std::string& func, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, void* arg6);
    int CallInt(const std::string& func);
    int CallInt(const std::string& func, void* arg1);
    int CallInt(const std::string& func, void* arg1, void* arg2);
    int CallInt(const std::string& func, void* arg1, void* arg2, void* arg3);
    int CallInt(const std::string& func, void* arg1, void* arg2, void* arg3, void* arg4);
    int CallInt(const std::string& func, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5);
    int CallInt(const std::string& func, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, void* arg6);
    float CallFloat(const std::string& func);
    float CallFloat(const std::string& func, void* arg1);
    float CallFloat(const std::string& func, void* arg1, void* arg2);
    float CallFloat(const std::string& func, void* arg1, void* arg2, void* arg3);
    float CallFloat(const std::string& func, void* arg1, void* arg2, void* arg3, void* arg4);
    float CallFloat(const std::string& func, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5);
    float CallFloat(const std::string& func, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, void* arg6);
    bool CallBool(const std::string& func);
    bool CallBool(const std::string& func, void* arg1);
    bool CallBool(const std::string& func, void* arg1, void* arg2);
    bool CallBool(const std::string& func, void* arg1, void* arg2, void* arg3);
    bool CallBool(const std::string& func, void* arg1, void* arg2, void* arg3, void* arg4);
    bool CallBool(const std::string& func, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5);
    bool CallBool(const std::string& func, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, void* arg6);

    // Table manipulation
    void SetField(const std::string& key, const std::string& value);
    void SetField(const std::string& key, void* value);
    std::string GetFieldString(const std::string& key);
    void* GetFieldPtr(const std::string& key);
    void SetIndex(int idx, void* value);
    void* GetIndex(int idx);
    bool HasKey(const std::string& key);
    std::vector<std::string> Keys();
    void Clear();

private:
    int table; // Lua registry ref
    int typeTable;
};
};

} // namespace zombie
