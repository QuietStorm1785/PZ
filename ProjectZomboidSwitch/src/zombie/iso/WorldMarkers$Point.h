#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {

class WorldMarkers {
public:
    float x;
    float y;

   WorldMarkers$Point(float var1, float var2) {
      this.x = var1;
      this.y = var2;
   }

   public WorldMarkers$Point set(float var1, float var2) {
      this.x = var1;
      this.y = var2;
    return this;
   }

    bool notInfinite() {
      return !float.isInfinite(this.x) && !float.isInfinite(this.y);
   }

    std::string toString() {
      return std::string.format("{%f, %f}", this.x, this.y);
   }
}
} // namespace iso
} // namespace zombie
