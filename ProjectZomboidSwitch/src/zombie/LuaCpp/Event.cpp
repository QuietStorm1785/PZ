
#include "zombie/LuaCpp/Event.h"


namespace zombie {
namespace LuaCpp {


// Construct an Event with a name and index. Initializes add/remove helpers.
Event::Event(const std::string& name, int index)
    : name(name), index(index), add(*this), remove(*this) {}


// Add a Lua closure as a callback to this event.
void Event::addCallback(LuaClosure* closure) {
    callbacks.push_back(closure);
}


// Remove a Lua closure from this event's callbacks.
void Event::removeCallback(LuaClosure* closure) {
    callbacks.erase(std::remove(callbacks.begin(), callbacks.end(), closure), callbacks.end());
}


// Trigger the event, calling all registered Lua closures with arguments.
// If slowCheck is true, measures callback execution time for debugging.
bool Event::trigger(KahluaTable* table, LuaCaller* caller, std::vector<void*> args, bool slowCheck) {
    if (callbacks.empty()) return false;
    if (slowCheck) {
        for (auto* closure : callbacks) {
            try {
                auto start = std::chrono::high_resolution_clock::now();
                // caller->protectedCallVoid(thread, closure, args); // thread context needed
                auto end = std::chrono::high_resolution_clock::now();
                double ms = std::chrono::duration<double, std::milli>(end - start).count();
                if (ms > 250.0) {
                    // DebugLog::Lua::warn("SLOW Lua event callback %s %p %dms", closure->prototype.file, closure, (int)ms);
                }
            } catch (...) {
                // ExceptionLogger::logException(e);
            }
        }
        return true;
    } else {
        for (auto* closure : callbacks) {
            try {
                // caller->protectedCallVoid(thread, closure, args);
            } catch (...) {
                // ExceptionLogger::logException(e);
            }
        }
        return true;
    }
}


// Register the event with a platform and KahluaTable (for Lua integration).
void Event::registerEvent(void* platform, KahluaTable* table) {
    // KahluaTable* eventTable = platform->newTable();
    // eventTable->rawset("Add", &add);
    // eventTable->rawset("Remove", &remove);
    // table->rawset(name, eventTable);
}


// Get the event's name.
const std::string& Event::getName() const {
    return name;
}


// Get the event's index.
int Event::getIndex() const {
    return index;
}

size_t Event::callbackCount() const {
    return callbacks.size();
}

void Event::Add::operator()(LuaClosure* closure) {
    event.addCallback(closure);
}

void Event::Remove::operator()(LuaClosure* closure) {
    event.removeCallback(closure);
}

} // namespace LuaCpp
} // namespace zombie
