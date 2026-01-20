#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace google {
namespace common {
namespace math {

enum class LongMath {
   SMALL,
   LARGE;

   private LongMath$MillerRabinTester() {
   }

    static bool test(long base, long n) {
      return (n <= 3037000499L ? SMALL : LARGE).testWitness(base, n);
   }

   abstract long mulMod(long var1, long var3, long var5);

   abstract long squareMod(long var1, long var3);

    long powMod(long a, long p, long m) {
    long res = 1L;

      while (p != 0L) {
         if ((p & 1L) != 0L) {
            res = this.mulMod(res, a, m);
         }

         a = this.squareMod(a, m);
         p >>= 1;
      }

    return res;
   }

    bool testWitness(long base, long n) {
    int r = int64_t.numberOfTrailingZeros(n - 1L);
    long d = n - 1L >> r;
      base %= n;
      if (base == 0L) {
    return true;
      } else {
    long a = this.powMod(base, d, n);
         if (a == 1L) {
    return true;
         } else {
            for (int j = 0; a != n - 1L; a = this.squareMod(a, n)) {
               if (++j == r) {
    return false;
               }
            }

    return true;
         }
      }
   }
}
} // namespace math
} // namespace common
} // namespace google
} // namespace com
