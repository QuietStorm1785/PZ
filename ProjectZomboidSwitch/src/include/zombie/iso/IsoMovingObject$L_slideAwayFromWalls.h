#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector2f.h"

namespace zombie {
namespace iso {


class IsoMovingObject {
public:
    static const Vector2f vector2f = std::make_shared<Vector2f>();
    static const Vector2 vector2 = std::make_shared<Vector2>();
    static const Vector3 vector3 = std::make_shared<Vector3>();

   private IsoMovingObject$L_slideAwayFromWalls() {
   }
}
} // namespace iso
} // namespace zombie
