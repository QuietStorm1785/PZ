#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/Vector2.h"

namespace zombie {


class CollisionManager {
public:
    bool WillIntersect;
    bool Intersect;
    Vector2 MinimumTranslationVector;

   public CollisionManager$PolygonCollisionResult(CollisionManager var1) {
      this.this$0 = var1;
      this.MinimumTranslationVector = std::make_unique<Vector2>();
   }
}
} // namespace zombie
