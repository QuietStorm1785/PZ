#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector2d.h"

namespace zombie {
namespace worldMap {


class MapProjection {
public:
    Vector2d min;
    Vector2d max;

   public MapProjection$BoundingBox(Vector2d var1, Vector2d var2) {
      this.min = var1;
      this.max = var2;
   }
}
} // namespace worldMap
} // namespace zombie
