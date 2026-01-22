#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/scripting/ScriptParser/Block.h"

namespace zombie {
namespace sandbox {


class CustomIntegerSandboxOption : public CustomSandboxOption {
public:
    const int min;
    const int max;
    const int defaultValue;

   CustomIntegerSandboxOption(std::string var1, int var2, int var3, int var4) {
      super(var1);
      this.min = var2;
      this.max = var3;
      this.defaultValue = var4;
   }

    static CustomIntegerSandboxOption parse(Block var0) {
    int var1 = getValueInt(var0, "min", int.MIN_VALUE);
    int var2 = getValueInt(var0, "max", int.MIN_VALUE);
    int var3 = getValueInt(var0, "default", int.MIN_VALUE);
      if (var1 != int.MIN_VALUE && var2 != int.MIN_VALUE && var3 != int.MIN_VALUE) {
    CustomIntegerSandboxOption var4 = std::make_shared<CustomIntegerSandboxOption>(var0.id, var1, var2, var3);
         return !var4.parseCommon(var0) ? nullptr : var4;
      } else {
    return nullptr;
      }
   }
}
} // namespace sandbox
} // namespace zombie
