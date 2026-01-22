#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/vehicles/PolygonalMap2/Edge.h"
#include "zombie/vehicles/PolygonalMap2/Intersection.h"
#include <algorithm>

namespace zombie {
namespace vehicles {


class PolygonalMap2 {
public:
    Edge edge;

    int compare(Intersection var1, Intersection var2) {
    float var3 = this.edge == var1.edge1 ? var1.dist1 : var1.dist2;
    float var4 = this.edge == var2.edge1 ? var2.dist1 : var2.dist2;
      if (var3 < var4) {
         return -1;
      } else {
         return var3 > var4 ? 1 : 0;
      }
   }
}
} // namespace vehicles
} // namespace zombie
