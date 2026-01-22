#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector3f.h"
#include "zombie/core/math/PZMath.h"

namespace zombie {
namespace scripting {
namespace objects {


class VehicleScript {
public:
    int type;
    const Vector3f offset = std::make_shared<Vector3f>();
    const Vector3f rotate = std::make_shared<Vector3f>();
    const Vector3f extents = std::make_shared<Vector3f>();
    float radius;

    std::string getTypeString() {
      switch (this.type) {
         case 1:
            return "box";
         case 2:
            return "sphere";
         default:
            throw RuntimeException("unhandled VehicleScript.PhysicsShape");
      }
   }

    Vector3f getOffset() {
      return this.offset;
   }

    Vector3f getExtents() {
      return this.extents;
   }

    Vector3f getRotate() {
      return this.rotate;
   }

    float getRadius() {
      return this.radius;
   }

    void setRadius(float var1) {
      this.radius = PZMath.clamp(var1, 0.05F, 5.0F);
   }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
