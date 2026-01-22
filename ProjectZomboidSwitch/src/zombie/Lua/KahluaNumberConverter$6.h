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
    short fromLuaToJava(double var1, Class<int16_t> var2) {
      return var1.shortValue();
   }

   public Class<int16_t> getJavaType() {
      return int16_t.class;
   }

   public Class<double> getLuaType() {
      return double.class;
   }
}
} // namespace Lua
} // namespace zombie
