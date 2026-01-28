#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <glm/vec3.hpp>
#include "zombie/iso/Vector2.h"

namespace zombie {
namespace vehicles {


class BaseVehicle {
public:
   static const Vector2[] testVecs1 = new Vector2[4];
   static const Vector2[] testVecs2 = new Vector2[4];
    static const Vector3f worldPos = std::make_shared<Vector3f>();

   private BaseVehicle$L_testCollisionWithVehicle() {
   }
}
} // namespace vehicles
} // namespace zombie
