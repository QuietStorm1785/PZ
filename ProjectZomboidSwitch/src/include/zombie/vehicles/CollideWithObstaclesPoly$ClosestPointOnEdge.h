#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector2f.h"
#include "zombie/vehicles/CollideWithObstaclesPoly/CCEdge.h"
#include "zombie/vehicles/CollideWithObstaclesPoly/CCNode.h"

namespace zombie {
namespace vehicles {


class CollideWithObstaclesPoly {
public:
    CCEdge edge;
    CCNode node;
    const Vector2f point = std::make_shared<Vector2f>();
    double distSq;

   private CollideWithObstaclesPoly$ClosestPointOnEdge() {
   }
}
} // namespace vehicles
} // namespace zombie
