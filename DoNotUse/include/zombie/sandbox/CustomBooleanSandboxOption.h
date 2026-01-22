#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/scripting/ScriptParser/Block.h"
#include "zombie/scripting/ScriptParser/Value.h"

namespace zombie {
namespace sandbox {


class CustomBooleanSandboxOption : public CustomSandboxOption {
public:
    const bool defaultValue;

   CustomBooleanSandboxOption(std::string var1, boolean var2) {
      super(var1);
      this.defaultValue = var2;
   }

    static CustomBooleanSandboxOption parse(Block var0) {
    Value var1 = var0.getValue("default");
      if (var1 == nullptr) {
    return nullptr;
      } else {
    bool var2 = bool.parseBoolean(var1.getValue().trim());
    CustomBooleanSandboxOption var3 = std::make_shared<CustomBooleanSandboxOption>(var0.id, var2);
         return !var3.parseCommon(var0) ? nullptr : var3;
      }
   }
}
} // namespace sandbox
} // namespace zombie
