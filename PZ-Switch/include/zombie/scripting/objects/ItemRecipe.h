#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace scripting {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ItemRecipe {
public:
 std::string name;
 int use = -1;
 bool cooked = false;
 std::string module = nullptr;

 int getUse() { return this->use; }

public
 ItemRecipe(std::string_view _name, std::string_view _module, int _use) {
 this->name = _name;
 this->use = _use;
 this->setModule(_module);
 }

 std::string getName() { return this->name; }

 std::string getModule() { return this->module; }

 void setModule(std::string_view _module) { this->module = _module; }

 std::string getFullType() { return this->module + "." + this->name; }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
