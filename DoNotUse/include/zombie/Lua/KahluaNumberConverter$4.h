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
    uint8_t fromLuaToJava(double var1, Class<uint8_t> var2) {
      return var1.byteValue();
   }

   public Class<uint8_t> getJavaType() {
      return uint8_t.class;
   }

   public Class<double> getLuaType() {
      return double.class;
   }
}
} // namespace Lua
} // namespace zombie
