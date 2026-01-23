// ExampleObject.h
#pragma once
#include <string>

namespace zombie {
namespace LuaCpp {

// Example C++ class to demonstrate Lua binding of userdata objects
class ExampleObject {
public:
    // Construct with a name and value
    ExampleObject(const std::string& name, int value);
    // Get the name property
    std::string GetName() const;
    // Set the name property
    void SetName(const std::string& name);
    // Get the value property
    int GetValue() const;
    // Set the value property
    void SetValue(int v);
private:
    std::string name; // Name of the object
    int value;        // Integer value
};

} // namespace LuaCpp
} // namespace zombie
