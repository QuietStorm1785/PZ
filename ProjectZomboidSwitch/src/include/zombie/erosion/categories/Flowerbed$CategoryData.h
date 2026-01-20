#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/erosion/categories/ErosionCategory/Data.h"
#include <filesystem>

namespace zombie {
namespace erosion {
namespace categories {


class Flowerbed {
public:
    int gameObj;

   private Flowerbed$CategoryData() {
   }

    void save(ByteBuffer var1) {
      super.save(var1);
      var1.put((byte)this.gameObj);
   }

    void load(ByteBuffer var1, int var2) {
      super.load(var1, var2);
      this.gameObj = var1.get();
   }
}
} // namespace categories
} // namespace erosion
} // namespace zombie
