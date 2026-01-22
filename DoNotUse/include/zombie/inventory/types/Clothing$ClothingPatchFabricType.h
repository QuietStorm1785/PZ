#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace inventory {
namespace types {


enum class Clothing {
   Cotton(1, "Cotton", 5, 0),
   Denim(2, "Denim", 10, 5),
   Leather(3, "Leather", 20, 10);

    int index;
    std::string type;
    int maxScratchDef;
    int maxBiteDef;

   private Clothing$ClothingPatchFabricType(int var3, std::string var4, int var5, int var6) {
      this.index = var3;
      this.type = var4;
      this.maxScratchDef = var5;
      this.maxBiteDef = var6;
   }

    std::string getType() {
      return this.type;
   }

   public static Clothing$ClothingPatchFabricType fromType(std::string var0) {
      if (StringUtils.isNullOrEmpty(var0)) {
    return nullptr;
      } else if (Cotton.type == var0)) {
    return Cotton;
      } else if (Denim.type == var0)) {
    return Denim;
      } else {
         return Leather.type == var0) ? Leather : nullptr;
      }
   }

   public static Clothing$ClothingPatchFabricType fromIndex(int var0) {
      if (var0 == 1) {
    return Cotton;
      } else if (var0 == 2) {
    return Denim;
      } else {
    return var0 = = 3 ? Leather : nullptr;
      }
   }
}
} // namespace types
} // namespace inventory
} // namespace zombie
