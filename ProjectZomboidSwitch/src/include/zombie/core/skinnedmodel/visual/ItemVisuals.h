#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/population/ClothingItem.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace visual {


class ItemVisuals : public std::vector {
public:
    void save(ByteBuffer var1) {
      var1.putShort((short)this.size());

      for (int var2 = 0; var2 < this.size(); var2++) {
         this.get(var2).save(var1);
      }
   }

    void load(ByteBuffer var1, int var2) {
      this.clear();
    short var3 = var1.getShort();

      for (int var4 = 0; var4 < var3; var4++) {
    ItemVisual var5 = std::make_shared<ItemVisual>();
         var5.load(var1, var2);
         this.push_back(var5);
      }
   }

    ItemVisual findHat() {
      for (int var1 = 0; var1 < this.size(); var1++) {
    ItemVisual var2 = this.get(var1);
    ClothingItem var3 = var2.getClothingItem();
         if (var3 != nullptr && var3.isHat()) {
    return var2;
         }
      }

    return nullptr;
   }

    ItemVisual findMask() {
      for (int var1 = 0; var1 < this.size(); var1++) {
    ItemVisual var2 = this.get(var1);
    ClothingItem var3 = var2.getClothingItem();
         if (var3 != nullptr && var3.isMask()) {
    return var2;
         }
      }

    return nullptr;
   }
}
} // namespace visual
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
