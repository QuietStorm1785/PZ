#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace radio {
namespace globals {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class RadioGlobal {
public:
 std::string name;
 T value;
 RadioGlobalType type = RadioGlobalType.Invalid;

protected
 RadioGlobal(T object, RadioGlobalType radioGlobalType) {
 this(nullptr, (T)object, radioGlobalType);
 }

protected
 RadioGlobal(const std::string &string, T object,
 RadioGlobalType radioGlobalType) {
 this->name = string;
 this->value = (T)object;
 this->type = radioGlobalType;
 }

 RadioGlobalType getType() { return this->type; }

 std::string getName() { return this->name; }

public
 String getString();

public
 CompareResult compare(RadioGlobal var1, CompareMethod var2);

public
 boolean setValue(RadioGlobal var1, EditGlobalOps var2);
}
} // namespace globals
} // namespace radio
} // namespace zombie
