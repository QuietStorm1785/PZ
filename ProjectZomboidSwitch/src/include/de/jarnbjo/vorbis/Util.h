#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace de {
namespace jarnbjo {
namespace vorbis {

class Util {
public:
    static int ilog(int var0) {
    int var1;
      for (var1 = 0; var0 > 0; var1++) {
         var0 >>= 1;
      }

    return var1;
   }

    static float float32unpack(int var0) {
    float var1 = var0 & 2097151;
    float var2 = (var0 & 2145386496) >> 21;
      if ((var0 & -2147483648) != 0) {
         var1 = -var1;
      }

      return var1 * (float)Math.pow(2.0, var2 - 788.0);
   }

    static int lookup1Values(int var0, int var1) {
    int var2 = (int)Math.pow(Math.E, Math.log(var0) / var1);
    return intPow(var2 +);
   }

    static int intPow(int var0, int var1) {
    int var2 = 1;

      while (var1 > 0) {
         var1--;
         var2 *= var0;
      }

    return var2;
   }

    static bool isBitSet(int var0, int var1) {
      return (var0 & 1 << var1) != 0;
   }

    static int icount(int var0) {
    int var1 = 0;

      while (var0 > 0) {
         var1 += var0 & 1;
         var0 >>= 1;
      }

    return var1;
   }

    static int lowNeighbour(int[] var0, int var1) {
    int var2 = -1;
    int var3 = 0;

      for (int var4 = 0; var4 < var0.length && var4 < var1; var4++) {
         if (var0[var4] > var2 && var0[var4] < var0[var1]) {
            var2 = var0[var4];
            var3 = var4;
         }
      }

    return var3;
   }

    static int highNeighbour(int[] var0, int var1) {
    int var2 = int.MAX_VALUE;
    int var3 = 0;

      for (int var4 = 0; var4 < var0.length && var4 < var1; var4++) {
         if (var0[var4] < var2 && var0[var4] > var0[var1]) {
            var2 = var0[var4];
            var3 = var4;
         }
      }

    return var3;
   }

    static int renderPoint(int var0, int var1, int var2, int var3, int var4) {
    int var5 = var3 - var2;
    int var6 = var5 < 0 ? -var5 : var5;
    int var7 = var6 * (var4 - var0) / (var1 - var0);
      return var5 < 0 ? var2 - var7 : var2 + var7;
   }

    static void renderLine(int var0, int var1, int var2, int var3, float[] var4) {
    int var5 = var3 - var1;
    int var6 = var2 - var0;
    int var7 = var5 / var6;
    int var8 = var5 < 0 ? var7 - 1 : var7 + 1;
    int var10 = var1;
    int var11 = 0;
    int var12 = (var5 < 0 ? -var5 : var5) - (var7 > 0 ? var7 * var6 : -var7 * var6);
      var4[var0] *= Floor.DB_STATIC_TABLE[var1];

      for (int var9 = var0 + 1; var9 < var2; var9++) {
         var11 += var12;
         if (var11 >= var6) {
            var11 -= var6;
            var4[var9] *= Floor.DB_STATIC_TABLE[var10 += var8];
         } else {
            var4[var9] *= Floor.DB_STATIC_TABLE[var10 += var7];
         }
      }
   }
}
} // namespace vorbis
} // namespace jarnbjo
} // namespace de
