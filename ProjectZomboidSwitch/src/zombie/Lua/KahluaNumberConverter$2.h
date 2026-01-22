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
    int fromLuaToJava(double var1, Class<int> var2) {
      return var1.intValue();
   }

   public Class<int> getJavaType() {
      return int.class;
   }

   public Class<double> getLuaType() {
      return double.class;
   }
}
} // namespace Lua
} // namespace zombie
