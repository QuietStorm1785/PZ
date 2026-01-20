#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ui/RadarPanel/ZombiePos.h"
#include <algorithm>

namespace zombie {
namespace ui {


class RadarPanel {
public:
   private ArrayDeque<ZombiePos> pool = std::make_unique<ArrayDeque<>>();

   private RadarPanel$ZombiePosPool() {
   }

    ZombiePos alloc(float var1, float var2) {
      return this.pool.empty() ? std::make_shared<ZombiePos>(var1, var2) : this.pool.pop().set(var1, var2);
   }

    void release(Collection<ZombiePos> var1) {
      this.pool.addAll(var1);
   }
}
} // namespace ui
} // namespace zombie
