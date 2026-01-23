
#include "ExampleObject.h"


namespace zombie {
namespace LuaCpp {


// Construct an ExampleObject with a name and value.
ExampleObject::ExampleObject(const std::string& name, int value)
    : name(name), value(value) {}


// Get the name property.
std::string ExampleObject::GetName() const { return name; }
// Set the name property.
void ExampleObject::SetName(const std::string& n) { name = n; }
// Get the value property.
int ExampleObject::GetValue() const { return value; }
// Set the value property.
void ExampleObject::SetValue(int v) { value = v; }


} // namespace LuaCpp
} // namespace zombie
