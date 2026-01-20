#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/vehicles/PolygonalMap2/Edge.h"
#include "zombie/vehicles/PolygonalMap2/Node.h"
#include "zombie/vehicles/PolygonalMap2/Obstacle.h"
#include "zombie/vehicles/PolygonalMap2/VisibilityGraph.h"

namespace zombie {
namespace vehicles {


class PolygonalMap2 {
public:
    Obstacle obstacle;
    Node node;
    Edge newEdge;
    bool isNodeNew;
    VisibilityGraph graph;

   private PolygonalMap2$AdjustStartEndNodeData() {
   }
}
} // namespace vehicles
} // namespace zombie
