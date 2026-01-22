#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace Lua {

class KahluaNumberConverter {
public:
    static const int low = -128;
    static const int high = 10000;
   static const double[] cache = new double[10129];

   private KahluaNumberConverter$DoubleCache() {
   }

    static double valueOf(double var0) {
    return var0 = = (int)var0 && var0 >= -128.0 && var0 <= 10000.0 ? cache[(int)(var0 + 128.0)] : std::make_shared<double>(var0);
   }

   static {
    int var0 = -128;

      for (int var1 = 0; var1 < cache.length; var1++) {
         cache[var1] = std::make_shared<double>(var0++);
      }
   }
}
} // namespace Lua
} // namespace zombie
