#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/opengl/GL11.h"
#include "zombie/core/Core.h"
#include "zombie/core/skinnedmodel/ModelCamera.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {


class AnimatedModel {
public:
    float x;
    float y;
    float z;
    float angle;

   private AnimatedModel$WorldModelCamera() {
   }

    void Begin() {
      Core.getInstance().DoPushIsoStuff(this.x, this.y, this.z, this.angle, false);
      GL11.glDepthMask(true);
   }

    void End() {
      Core.getInstance().DoPopIsoStuff();
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
