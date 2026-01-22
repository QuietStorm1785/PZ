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
    std::string file;
    float scale = 1.0F;
    const Vector3f offset = std::make_shared<Vector3f>();
    const Vector3f rotate = std::make_shared<Vector3f>();

    std::string getId() {
      return this.id;
   }

    Vector3f getOffset() {
      return this.offset;
   }

    Vector3f getRotate() {
      return this.rotate;
   }

   VehicleScript$Model makeCopy() {
      VehicleScript$Model var1 = new VehicleScript$Model();
      var1.id = this.id;
      var1.file = this.file;
      var1.scale = this.scale;
      var1.offset.set(this.offset);
      var1.rotate.set(this.rotate);
    return var1;
   }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
