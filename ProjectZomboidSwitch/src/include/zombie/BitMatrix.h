#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {

class BitMatrix {
public:
    static bool Is(int var0, int var1, int var2, int var3) {
      return (1 << (var1 + 1) * 9 + (var2 + 1) * 3 + var3 + 1 & var0) == 1 << (var1 + 1) * 9 + (var2 + 1) * 3 + var3 + 1;
   }

    static int Set(int var0, int var1, int var2, int var3, bool var4) {
      if (var4) {
         var0 |= 1 << (var1 + 1) * 9 + (var2 + 1) * 3 + var3 + 1;
      } else {
         var0 &= ~(1 << (var1 + 1) * 9 + (var2 + 1) * 3 + var3 + 1);
      }

    return var0;
   }
}
} // namespace zombie
