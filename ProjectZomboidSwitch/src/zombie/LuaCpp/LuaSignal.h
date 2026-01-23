
#pragma once
#include <vector>
#include <functional>
#include <algorithm>

namespace zombie {
namespace LuaCpp {

// LuaSignal implements a signal-slot/observer pattern for C++/Lua integration.
// Allows connecting, disconnecting, and emitting slots (callbacks) for event-driven programming.
class LuaSignal {
public:
    using Slot = std::function<void()>; // Slot type: any callable with no arguments

    // Connect a slot (callback) to this signal.
    void connect(Slot slot) {
        slots.push_back(slot);
    }

    // Disconnect a slot (callback) from this signal.
    void disconnect(Slot slot) {
        slots.erase(std::remove_if(slots.begin(), slots.end(), [&](const Slot& s) {
            // Compare target addresses for disconnect
            return s.target<void()>() == slot.target<void()>();
        }), slots.end());
    }

    // Emit the signal, calling all connected slots.
    void emit() {
        for (auto& slot : slots) slot();
    }
private:
    std::vector<Slot> slots; // List of connected slots (callbacks)
};

} // namespace LuaCpp
} // namespace zombie
