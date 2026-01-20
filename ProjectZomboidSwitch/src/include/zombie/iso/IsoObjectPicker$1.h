#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoObjectPicker/ClickObject.h"
#include <algorithm>

namespace zombie {
namespace iso {


class IsoObjectPicker {
public:
    int compare(ClickObject var1, ClickObject var2) {
    int var3 = var1.getScore();
    int var4 = var2.getScore();
      if (var3 > var4) {
    return 1;
      } else if (var3 < var4) {
         return -1;
      } else {
         return var1.tile != nullptr && var1.tile.square != nullptr && var2.tile != nullptr && var1.tile.square == var2.tile.square
            ? var1.tile.getObjectIndex() - var2.tile.getObjectIndex()
            : 0;
      }
   }
}
} // namespace iso
} // namespace zombie
