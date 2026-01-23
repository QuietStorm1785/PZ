
#pragma once
#include <string>
#include <vector>
#include <memory>
#include <functional>


namespace zombie {
namespace LuaCpp {


// Forward declarations for Lua interop types
class LuaCaller;
class KahluaTable;
class LuaClosure;


// Event class for managing Lua/C++ event callbacks and dispatch.
// Allows registering, adding, removing, and triggering Lua closures as event listeners.
class Event {
public:
    static constexpr int ADD = 0;              // Index for add operation
    static constexpr int NUM_FUNCTIONS = 1;    // Number of event operations

    // Helper class for adding a callback to the event.
    class Add {
    public:
        Add(Event& e) : event(e) {}
        void operator()(LuaClosure* closure); // Add a Lua closure as a callback
    private:
        Event& event;
    };

    // Helper class for removing a callback from the event.
    class Remove {
    public:
        Remove(Event& e) : event(e) {}
        void operator()(LuaClosure* closure); // Remove a Lua closure from callbacks
    private:
        Event& event;
    };

    // Construct an Event with a name and index.
    Event(const std::string& name, int index);
    // Trigger the event, calling all registered Lua closures with arguments.
    bool trigger(KahluaTable* table, LuaCaller* caller, std::vector<void*> args, bool slowCheck = false);
    // Register the event with a platform and KahluaTable (for Lua integration).
    void registerEvent(void* platform, KahluaTable* table);
    // Add a Lua closure as a callback.
    void addCallback(LuaClosure* closure);
    // Remove a Lua closure from callbacks.
    void removeCallback(LuaClosure* closure);
    // Get the event's name.
    const std::string& getName() const;
    // Get the event's index.
    int getIndex() const;
    // Get the number of registered callbacks.
    size_t callbackCount() const;
private:
    std::string name;                  // Name of the event
    int index;                         // Index/id of the event
    std::vector<LuaClosure*> callbacks;// Registered Lua closures (listeners)
    Add add;                           // Helper for adding callbacks
    Remove remove;                     // Helper for removing callbacks
};


} // namespace LuaCpp
} // namespace zombie
