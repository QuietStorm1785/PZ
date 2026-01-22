#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace ui {

class RadarPanel {
public:
    float x;
    float y;

   public RadarPanel$ZombiePos(float var1, float var2) {
      this.x = var1;
      this.y = var2;
   }

   public RadarPanel$ZombiePos set(float var1, float var2) {
      this.x = var1;
      this.y = var2;
    return this;
   }
}
} // namespace ui
} // namespace zombie
