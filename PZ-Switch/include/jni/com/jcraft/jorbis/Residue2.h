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

class Residue2 :  Residue0 {
:
    int inverse(Block var1, void* var2, float[][] var3, int[] var4, int var5) {
    int var6 = 0;
      var6 = 0;

      while (var6 < var5 && var4[var6] == 0) {
         var6++;
      }

    return var6 = = var5 ? 0 : _2inverse(var1, var2, var3, var5);
   }
}
} // namespace jorbis
} // namespace jcraft
} // namespace com
