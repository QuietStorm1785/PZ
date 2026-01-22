#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/converter/LuaToJavaConverter.h"

namespace zombie {
namespace Lua {


class KahluaNumberConverter {
public:
    float fromLuaToJava(double var1, Class<float> var2) {
      return std::make_shared<float>(var1.floatValue());
   }

   public Class<float> getJavaType() {
      return float.class;
   }

   public Class<double> getLuaType() {
      return double.class;
   }
}
} // namespace Lua
} // namespace zombie
