#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace vehicles {

class PolygonalMap2 {
public:
    int x;
    int y;

   PolygonalMap2$Point init(int var1, int var2) {
      this.x = var1;
      this.y = var2;
    return this;
   }

    bool equals(void* var1) {
      return dynamic_cast<PolygonalMap2*>(var1) != nullptr$Point && ((PolygonalMap2$Point)var1).x == this.x && ((PolygonalMap2$Point)var1).y == this.y;
   }
}
} // namespace vehicles
} // namespace zombie
