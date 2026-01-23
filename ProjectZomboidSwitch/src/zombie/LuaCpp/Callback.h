
#pragma once
#include <string>
#include <vector>
#include <memory>


namespace zombie {

// Callback class for associating Lua functions (by registry reference) with a sprite name and priority.
// Used for event/callback integration between C++ and Lua, similar to MapObjects$Callback in Java.
class Callback {
public:
    // Construct a Callback for a given sprite name.
    Callback(const std::string& spriteName);
    ~Callback();

    // Add a Lua function (as registry reference) with a given priority.
    void AddFunction(int luaFuncRef, short priority);
    // Get all Lua function registry references associated with this callback.
    const std::vector<int>& GetFunctions() const;
    // Get all priorities associated with the Lua functions.
    const std::vector<short>& GetPriorities() const;
    // Get the sprite name this callback is associated with.
    const std::string& GetSpriteName() const;

private:
    std::string spriteName;         // Name of the sprite this callback is for
    std::vector<int> functions;     // Lua registry references for callback functions
    std::vector<short> priority;    // Priority values for each function
};

} // namespace zombie
