#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace jcraft {
namespace jorbis {

class Residue1 : public Residue0 {
public:
    int inverse(Block var1, void* var2, float[][] var3, int[] var4, int var5) {
    int var6 = 0;

      for (int var7 = 0; var7 < var5; var7++) {
         if (var4[var7] != 0) {
            var3[var6++] = var3[var7];
         }
      }

      return var6 != 0 ? _01inverse(var1, var2, var3, var6, 1) : 0;
   }
}
} // namespace jorbis
} // namespace jcraft
} // namespace com
