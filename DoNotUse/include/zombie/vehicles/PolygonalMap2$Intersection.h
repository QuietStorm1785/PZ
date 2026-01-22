#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/vehicles/PolygonalMap2/Edge.h"
#include "zombie/vehicles/PolygonalMap2/Node.h"

namespace zombie {
namespace vehicles {


class PolygonalMap2 {
public:
    Edge edge1;
    Edge edge2;
    float dist1;
    float dist2;
    Node nodeSplit;

   PolygonalMap2$Intersection(Edge var1, Edge var2, float var3, float var4, float var5, float var6) {
      this.edge1 = var1;
      this.edge2 = var2;
      this.dist1 = var3;
      this.dist2 = var4;
      this.nodeSplit = Node.alloc().init(var5, var6, var1.node1.z);
   }

   PolygonalMap2$Intersection(Edge var1, Edge var2, float var3, float var4, Node var5) {
      this.edge1 = var1;
      this.edge2 = var2;
      this.dist1 = var3;
      this.dist2 = var4;
      this.nodeSplit = var5;
   }

    Edge split(Edge var1) {
      return var1.split(this.nodeSplit);
   }
}
} // namespace vehicles
} // namespace zombie
