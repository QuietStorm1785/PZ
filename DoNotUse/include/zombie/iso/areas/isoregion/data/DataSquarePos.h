#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/areas/isoregion/IsoRegions.h"
#include <algorithm>

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {
namespace data {


class DataSquarePos {
public:
    static bool DEBUG_POOL = true;
   private static const ArrayDeque<DataSquarePos> pool = std::make_unique<ArrayDeque<>>();
    int x;
    int y;
    int z;

    static DataSquarePos alloc(int var0, int var1, int var2) {
    DataSquarePos var3 = !pool.empty() ? pool.pop() : std::make_shared<DataSquarePos>();
      var3.set(var0, var1, var2);
    return var3;
   }

    static void release(DataSquarePos var0) {
      assert !pool.contains(var0);

      if (DEBUG_POOL && pool.contains(var0)) {
         IsoRegions.warn("DataSquarePos.release Trying to release a DataSquarePos twice.");
      } else {
         pool.push(var0.reset());
      }
   }

    private DataSquarePos() {
   }

    DataSquarePos reset() {
    return this;
   }

    void set(int var1, int var2, int var3) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
   }
}
} // namespace data
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie
