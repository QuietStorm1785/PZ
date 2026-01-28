#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <glm/vec3.hpp>

namespace zombie {
namespace vehicles {


class UI3DScene {
public:
    const Vector3f point = std::make_shared<Vector3f>();
    const Vector3f normal = std::make_shared<Vector3f>();

   public UI3DScene$Plane() {
   }

   public UI3DScene$Plane(Vector3f var1, Vector3f var2) {
      this.point.set(var2);
      this.normal.set(var1);
   }

   public UI3DScene$Plane set(Vector3f var1, Vector3f var2) {
      this.point.set(var2);
      this.normal.set(var1);
    return this;
   }
}
} // namespace vehicles
} // namespace zombie
