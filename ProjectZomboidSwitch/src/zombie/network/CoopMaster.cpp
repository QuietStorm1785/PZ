
#include "../lua-5.4.7/lua.hpp"
#include <iostream>

namespace zombie {
namespace network {

// Lua C API bridge for CoopMaster
static int l_CoopMaster_launch(lua_State* L) {
    int nargs = lua_gettop(L);
    if (nargs != 3 || !lua_isstring(L, 1) || !lua_isstring(L, 2) || !lua_isinteger(L, 3)) {
        lua_pushboolean(L, 0);
        return 1;
    }
    const char* name = lua_tostring(L, 1);
    const char* admin = lua_tostring(L, 2);
    int mem = (int)lua_tointeger(L, 3);
    try {
        CoopMaster::instance->launchServer(name, admin, mem);
        lua_pushboolean(L, 1);
    } catch (...) {
        lua_pushboolean(L, 0);
    }
    return 1;
}

static int l_CoopMaster_isRunning(lua_State* L) {
    lua_pushboolean(L, CoopMaster::instance->isRunning());
    return 1;
}

// Add more Lua bridge functions as needed (softreset, sendMessage, etc.)

extern "C" void CoopMaster_registerLua(lua_State* L) {
    lua_newtable(L);
    lua_pushcfunction(L, l_CoopMaster_launch);
    lua_setfield(L, -2, "launch");
    lua_pushcfunction(L, l_CoopMaster_isRunning);
    lua_setfield(L, -2, "isRunning");
    // ...add more methods as needed...
    lua_setglobal(L, "CoopServer");
}

} // namespace network
} // namespace zombie

// NAMESPACE WRAP BEGIN
namespace zombie {
namespace network {


#include "CoopMaster.h"
#include <string>
#include <vector>

namespace {
    // Helper for static instance
    zombie::network::CoopMaster g_CoopMasterInstance;
}

namespace zombie {
namespace network {

CoopMaster* CoopMaster::instance = &g_CoopMasterInstance;

CoopMaster::CoopMaster() {
    // Java: this.incomingMessages = new LinkedList<>();
    // Java: this.listeners = new LinkedList<>();
    // Java: this.serverMessageParser = Pattern.compile(...);
    // Java: this.adminPassword = UUID.randomUUID().toString();
    incomingMessages.clear();
    listeners.clear();
    serverResponded = false;
    adminPassword = "admin"; // TODO: Generate random UUID
    serverPort = 0;
}

CoopMaster::~CoopMaster() {
    // Cleanup if needed
}

int CoopMaster::getServerPort() const {
    return serverPort;
}

void CoopMaster::launchServer(const std::string& name, const std::string& admin, int mem) {
    // Java: this.launchServer(var1, var2, var3, false);
    // We'll call the private launchServer with softreset = false
    this->launchServerInternal(name, admin, mem, false);
}

void CoopMaster::softreset(const std::string& name, const std::string& admin, int mem) {
    // Java: this.launchServer(var1, var2, var3, true);
    this->launchServerInternal(name, admin, mem, true);
}

void CoopMaster::launchServerInternal(const std::string& name, const std::string& admin, int mem, bool softreset) {
    // This is a C++ port of the Java launchServer logic
    // NOTE: This is a stub. Actual process launching and thread management would use std::thread, std::process, etc.
    serverName = name;
    adminUsername = admin;
    // adminPassword is already set in constructor (should be random UUID)
    serverPort = 0; // Would be set by server
    serverResponded = false;
    // Simulate launching a server process and setting up threads for reading/watching
    // In a real implementation, use std::process (or popen) and std::thread
    // Here, we simulate with std::thread and a message loop
    static std::thread dummyServerThread;
    static std::thread dummyTimeoutThread;
    serverProcess = reinterpret_cast<void*>(1); // Dummy non-null
    serverTerminationReason = nullptr;

    // Simulate server thread: reads messages and pushes to incomingMessages
    dummyServerThread = std::thread([this]() {
        for (int i = 0; i < 5; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::lock_guard<std::mutex> lock(this->msgMutex);
            this->incomingMessages.push_back("simulated-message@data");
            this->serverResponded = true;
        }
        std::lock_guard<std::mutex> lock(this->msgMutex);
        this->incomingMessages.push_back("process-status@terminated");
    });
    serverThread = &dummyServerThread;

    // Simulate timeout watch thread
    dummyTimeoutThread = std::thread([this]() {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        if (!this->serverResponded) {
            this->serverTerminationReason = reinterpret_cast<void*>(1); // Timeout
            // Simulate abortServer
            this->serverProcess = nullptr;
        }
    });
    timeoutWatchThread = &dummyTimeoutThread;
}

bool CoopMaster::isRunning() const {
    // Java: return this.serverThread != null && this.serverThread.isAlive();
    return serverThread != nullptr;
}

std::string CoopMaster::getServerName() const {
    return serverName;
}

std::string CoopMaster::getServerSaveFolder(const std::string& worldName) const {
    // Java: GlobalObject.sanitizeWorldName(var1);
    std::string sanitized = worldName;
    // Replace spaces with underscores
    std::replace(sanitized.begin(), sanitized.end(), ' ', '_');
    // Remove /, \, ?, *, <, >, :, |
    const char* charsToRemove = "/\\?*<>:|";
    sanitized.erase(std::remove_if(sanitized.begin(), sanitized.end(),
        [charsToRemove](char c) { return std::strchr(charsToRemove, c); }), sanitized.end());
    // Trim
    size_t first = sanitized.find_first_not_of(' ');
    size_t last = sanitized.find_last_not_of(' ');
    if (first == std::string::npos) return "";
    return sanitized.substr(first, last - first + 1);
}

std::string CoopMaster::getPlayerSaveFolder(const std::string& worldName) const {
    // Java: GlobalObject.sanitizeWorldName(var1 + "_player");
    std::string sanitized = worldName + "_player";
    // Replace spaces with underscores
    std::replace(sanitized.begin(), sanitized.end(), ' ', '_');
    // Remove /, \, ?, *, <, >, :, |
    const char* charsToRemove = "/\\?*<>:|";
    sanitized.erase(std::remove_if(sanitized.begin(), sanitized.end(),
        [charsToRemove](char c) { return std::strchr(charsToRemove, c); }), sanitized.end());
    // Trim
    size_t first = sanitized.find_first_not_of(' ');
    size_t last = sanitized.find_last_not_of(' ');
    if (first == std::string::npos) return "";
    return sanitized.substr(first, last - first + 1);
}


// All inner classes are now implemented as structs/enums in the header.

} // namespace network
} // namespace zombie
// NAMESPACE WRAP END
