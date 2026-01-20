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
    const Vector3f origin = std::make_shared<Vector3f>();
    const Vector3f direction = std::make_shared<Vector3f>();
    float t;

   public UI3DScene$Ray() {
   }

   UI3DScene$Ray(UI3DScene$Ray var1) {
      this.origin.set(var1.origin);
      this.direction.set(var1.direction);
      this.t = var1.t;
   }
}
} // namespace vehicles
} // namespace zombie
