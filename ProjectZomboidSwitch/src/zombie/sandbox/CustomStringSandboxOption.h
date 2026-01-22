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


class CustomStringSandboxOption : public CustomSandboxOption {
public:
    const std::string defaultValue;

   CustomStringSandboxOption(std::string var1, std::string var2) {
      super(var1);
      this.defaultValue = var2;
   }

    static CustomStringSandboxOption parse(Block var0) {
    Value var1 = var0.getValue("default");
      if (var1 == nullptr) {
    return nullptr;
      } else {
    CustomStringSandboxOption var2 = std::make_shared<CustomStringSandboxOption>(var0.id, var1.getValue().trim());
         return !var2.parseCommon(var0) ? nullptr : var2;
      }
   }
}
} // namespace sandbox
} // namespace zombie
