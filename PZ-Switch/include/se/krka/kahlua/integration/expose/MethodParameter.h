#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace se {
namespace krka {
namespace kahlua {
namespace integration {
namespace expose {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class MethodParameter {
public:
 const std::string name;
 const std::string type;
 const std::string description;

public
 MethodParameter(const std::string &string0, const std::string &string1,
 const std::string &string2) {
 this->name = string0;
 this->type = string1;
 this->description = string2;
 }

 std::string getName() { return this->name; }

 std::string getType() { return this->type; }

 std::string getDescription() { return this->description; }
}
} // namespace expose
} // namespace integration
} // namespace kahlua
} // namespace krka
} // namespace se
