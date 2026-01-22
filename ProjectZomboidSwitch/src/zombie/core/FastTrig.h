#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {

class FastTrig {
public:
    static double cos(double var0) {
    return sin(var0 +);
   }

    static double sin(double var0) {
      var0 = reduceSinAngle(var0);
      return Math.abs(var0) <= Math.PI / 4 ? Math.sin(var0) : Math.cos((Math.PI / 2) - var0);
   }

    static double reduceSinAngle(double var0) {
      var0 %= Math.PI * 2;
      if (Math.abs(var0) > Math.PI) {
         var0 -= Math.PI * 2;
      }

      if (Math.abs(var0) > Math.PI / 2) {
         var0 = Math.PI - var0;
      }

    return var0;
   }
}
} // namespace core
} // namespace zombie
