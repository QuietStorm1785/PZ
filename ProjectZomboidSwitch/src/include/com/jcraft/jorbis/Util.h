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

class Util {
public:
    static int icount(int var0) {
    int var1 = 0;

      while (var0 != 0) {
         var1 += var0 & 1;
         var0 >>>= 1;
      }

    return var1;
   }

    static int ilog(int var0) {
    int var1 = 0;

      while (var0 != 0) {
         var1++;
         var0 >>>= 1;
      }

    return var1;
   }

    static int ilog2(int var0) {
    int var1 = 0;

      while (var0 > 1) {
         var1++;
         var0 >>>= 1;
      }

    return var1;
   }
}
} // namespace jorbis
} // namespace jcraft
} // namespace com
