#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector3f.h"

namespace zombie {
namespace vehicles {


class UI3DScene {
public:
    const Vector3f center = std::make_shared<Vector3f>();
    const Vector3f orientation = std::make_shared<Vector3f>();
    float radius = 1.0F;

   private UI3DScene$Circle() {
   }
}
} // namespace vehicles
} // namespace zombie
