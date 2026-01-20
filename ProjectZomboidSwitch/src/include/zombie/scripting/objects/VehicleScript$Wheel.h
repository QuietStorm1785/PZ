#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector3f.h"

namespace zombie {
namespace scripting {
namespace objects {


class VehicleScript {
public:
    std::string id;
    std::string model;
    bool front;
    const Vector3f offset = std::make_shared<Vector3f>();
    float radius = 0.5F;
    float width = 0.4F;

    std::string getId() {
      return this.id;
   }

    Vector3f getOffset() {
      return this.offset;
   }

   VehicleScript$Wheel makeCopy() {
      VehicleScript$Wheel var1 = new VehicleScript$Wheel();
      var1.id = this.id;
      var1.model = this.model;
      var1.front = this.front;
      var1.offset.set(this.offset);
      var1.radius = this.radius;
      var1.width = this.width;
    return var1;
   }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
