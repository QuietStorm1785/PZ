#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/fonts/AngelCodeFont/DisplayList.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace fonts {


class AngelCodeFont {
public:
   AngelCodeFont$1(AngelCodeFont var1, int var2, float var3, boolean var4) {
      super(var2, var3, var4);
      this.this$0 = var1;
   }

    bool removeEldestEntry(Entry var1) {
      this.this$0.eldestDisplayList = (DisplayList)var1.getValue();
      this.this$0.eldestDisplayListID = this.this$0.eldestDisplayList.id;
    return false;
   }
}
} // namespace fonts
} // namespace core
} // namespace zombie
