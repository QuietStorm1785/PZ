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


class CustomDoubleSandboxOption : public CustomSandboxOption {
public:
    const double min;
    const double max;
    const double defaultValue;

   CustomDoubleSandboxOption(std::string var1, double var2, double var4, double var6) {
      super(var1);
      this.min = var2;
      this.max = var4;
      this.defaultValue = var6;
   }

    static CustomDoubleSandboxOption parse(Block var0) {
    double var1 = getValueDouble(var0, "min", double.NaN);
    double var3 = getValueDouble(var0, "max", double.NaN);
    double var5 = getValueDouble(var0, "default", double.NaN);
      if (!double.isNaN(var1) && !double.isNaN(var3) && !double.isNaN(var5)) {
    CustomDoubleSandboxOption var7 = std::make_shared<CustomDoubleSandboxOption>(var0.id, var1, var3, var5);
         return !var7.parseCommon(var0) ? nullptr : var7;
      } else {
    return nullptr;
      }
   }
}
} // namespace sandbox
} // namespace zombie
