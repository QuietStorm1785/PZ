#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector2f.h"
#include "zombie/vehicles/PolygonalMap2/Edge.h"
#include "zombie/vehicles/PolygonalMap2/Node.h"

namespace zombie {
namespace vehicles {


class PolygonalMap2 {
public:
    Edge edge;
    Node node;
    const Vector2f point = std::make_shared<Vector2f>();
    double distSq;

   private PolygonalMap2$ClosestPointOnEdge() {
   }
}
} // namespace vehicles
} // namespace zombie
