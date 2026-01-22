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
    char fromLuaToJava(double var1, Class<char> var2) {
      return (char)var1.intValue();
   }

   public Class<char> getJavaType() {
      return char.class;
   }

   public Class<double> getLuaType() {
      return double.class;
   }
}
} // namespace Lua
} // namespace zombie
