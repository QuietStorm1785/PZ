#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {

class IsoDirectionSet {
public:
    int set = 0;

    static IsoDirections rotate(IsoDirections var0, int var1) {
      var1 += var0.index();
      var1 %= 8;
      return IsoDirections.fromIndex(var1);
   }

    IsoDirections getNext() {
      for (int var1 = 0; var1 < 8; var1++) {
    int var2 = 1 << var1;
         if ((this.set & var2) != 0) {
            this.set ^= var2;
            return IsoDirections.fromIndex(var1);
         }
      }

      return IsoDirections.Max;
   }
}
} // namespace iso
} // namespace zombie
