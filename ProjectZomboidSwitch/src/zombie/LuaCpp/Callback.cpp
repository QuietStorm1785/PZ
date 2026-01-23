
#include "Callback.h"


namespace zombie {


// Construct a Callback for a given sprite name.
Callback::Callback(const std::string& spriteName)
    : spriteName(spriteName) {}


// Destructor for Callback. No special cleanup needed.
Callback::~Callback() {}


// Add a Lua function (by registry reference) with a given priority.
// If a function with the same priority exists, it is replaced. Otherwise, insert in descending priority order.
void Callback::AddFunction(int luaFuncRef, short prio) {
    // Insert by priority (higher first)
    auto it = priority.begin();
    auto fit = functions.begin();
    for (; it != priority.end(); ++it, ++fit) {
        if (*it < prio) {
            priority.insert(it, prio);
            functions.insert(fit, luaFuncRef);
            return;
        }
        if (*it == prio) {
            *fit = luaFuncRef;
            *it = prio;
            return;
        }
    }
    // If not inserted, append to the end.
    priority.push_back(prio);
    functions.push_back(luaFuncRef);
}


// Get all Lua function registry references associated with this callback.
const std::vector<int>& Callback::GetFunctions() const {
    return functions;
}


// Get all priorities associated with the Lua functions.
const std::vector<short>& Callback::GetPriorities() const {
    return priority;
}


// Get the sprite name this callback is associated with.
const std::string& Callback::GetSpriteName() const {
    return spriteName;
}


} // namespace zombie
