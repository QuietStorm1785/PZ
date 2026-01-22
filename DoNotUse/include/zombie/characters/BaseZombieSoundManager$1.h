#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace characters {


class BaseZombieSoundManager {
public:
   BaseZombieSoundManager$1(BaseZombieSoundManager var1) {
      this.this$0 = var1;
   }

    int compare(IsoZombie var1, IsoZombie var2) {
    float var3 = this.this$0.getClosestListener(var1.x, var1.y, var1.z);
    float var4 = this.this$0.getClosestListener(var2.x, var2.y, var2.z);
      if (var3 > var4) {
    return 1;
      } else {
         return var3 < var4 ? -1 : 0;
      }
   }
}
} // namespace characters
} // namespace zombie
