#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/converter/JavaToLuaConverter.h"
#include "zombie/Lua/KahluaNumberConverter/DoubleCache.h"

namespace zombie {
namespace Lua {


class KahluaNumberConverter {
public:
   private const Class<T> clazz;

   public KahluaNumberConverter$NumberToLuaConverter(Class<T> var1) {
      this.clazz = var1;
   }

    void* fromJavaToLua(T var1) {
      return dynamic_cast<double*>(var1) != nullptr ? var1 : DoubleCache.valueOf(var1.doubleValue());
   }

   public Class<T> getJavaType() {
      return this.clazz;
   }
}
} // namespace Lua
} // namespace zombie
