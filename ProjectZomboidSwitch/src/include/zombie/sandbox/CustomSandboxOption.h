#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/math/PZMath.h"
#include "zombie/scripting/ScriptParser/Block.h"
#include "zombie/scripting/ScriptParser/Value.h"
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace sandbox {


class CustomSandboxOption {
public:
    const std::string m_id;
    std::string m_page;
    std::string m_translation;

   CustomSandboxOption(std::string var1) {
      this.m_id = var1;
   }

    static double getValueDouble(Block var0, const std::string& var1, double var2) {
    Value var4 = var0.getValue(var1);
    return var4 = = nullptr ? var2 : PZMath.tryParseDouble(var4.getValue().trim(), var2);
   }

    static float getValueFloat(Block var0, const std::string& var1, float var2) {
    Value var3 = var0.getValue(var1);
    return var3 = = nullptr ? var2 : PZMath.tryParseFloat(var3.getValue().trim(), var2);
   }

    static int getValueInt(Block var0, const std::string& var1, int var2) {
    Value var3 = var0.getValue(var1);
    return var3 = = nullptr ? var2 : PZMath.tryParseInt(var3.getValue().trim(), var2);
   }

    bool parseCommon(Block var1) {
    Value var2 = var1.getValue("page");
      if (var2 != nullptr) {
         this.m_page = StringUtils.discardNullOrWhitespace(var2.getValue().trim());
      }

    Value var3 = var1.getValue("translation");
      if (var3 != nullptr) {
         this.m_translation = StringUtils.discardNullOrWhitespace(var3.getValue().trim());
      }

    return true;
   }
}
} // namespace sandbox
} // namespace zombie
