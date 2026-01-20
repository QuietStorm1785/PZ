#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {

class BoxedStaticValues {
public:
   static double[] doubles = new double[10000];
   static double[] negdoubles = new double[10000];
   static double[] doublesh = new double[10000];
   static double[] negdoublesh = new double[10000];

    static double toDouble(double var0) {
      if (var0 >= 10000.0) {
    return var0;
      } else if (var0 <= -10000.0) {
    return var0;
      } else if ((int)Math.abs(var0) == Math.abs(var0)) {
         return var0 < 0.0 ? negdoubles[(int)(-var0)] : doubles[(int)var0];
      } else if ((int)Math.abs(var0) == Math.abs(var0) - 0.5) {
         return var0 < 0.0 ? negdoublesh[(int)(-var0)] : doublesh[(int)var0];
      } else {
    return var0;
      }
   }

   static {
      for (int var0 = 0; var0 < 10000; var0++) {
         doubles[var0] = (double)var0;
         negdoubles[var0] = -doubles[var0];
         doublesh[var0] = var0 + 0.5;
         negdoublesh[var0] = -(doubles[var0] + 0.5);
      }
   }
}
} // namespace core
} // namespace zombie
