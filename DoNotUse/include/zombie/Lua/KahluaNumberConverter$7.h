#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/converter/JavaToLuaConverter.h"

namespace zombie {
namespace Lua {


class KahluaNumberConverter {
public:
    void* fromJavaToLua(bool var1) {
    return var1;
   }

   public Class<bool> getJavaType() {
      return bool.class;
   }
}
} // namespace Lua
} // namespace zombie
