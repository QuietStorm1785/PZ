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

class BaseScriptObject {
public:
 ScriptModule module = nullptr;

 void Load(std::string_view var1, String[] var2) {}

 ScriptModule getModule() { return this->module; }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
