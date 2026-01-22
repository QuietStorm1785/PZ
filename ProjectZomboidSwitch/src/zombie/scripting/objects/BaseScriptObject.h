#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace scripting {
namespace objects {

class BaseScriptObject {
public:
    ScriptModule module = nullptr;

    void Load(const std::string& var1, std::string[] var2) {
   }

    ScriptModule getModule() {
      return this.module;
   }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
