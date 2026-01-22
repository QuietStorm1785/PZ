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
    std::string anim;
    float rate = 1.0F;
    bool bAnimate = true;
    bool bLoop = false;
    bool bReverse = false;
    const Vector3f offset = std::make_shared<Vector3f>();
    const Vector3f angle = std::make_shared<Vector3f>();
    std::string sound;

   VehicleScript$Anim makeCopy() {
      VehicleScript$Anim var1 = new VehicleScript$Anim();
      var1.id = this.id;
      var1.anim = this.anim;
      var1.rate = this.rate;
      var1.bAnimate = this.bAnimate;
      var1.bLoop = this.bLoop;
      var1.bReverse = this.bReverse;
      var1.offset.set(this.offset);
      var1.angle.set(this.angle);
      var1.sound = this.sound;
    return var1;
   }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
