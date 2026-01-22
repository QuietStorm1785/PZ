#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Core.h"
#include "zombie/core/skinnedmodel/ModelCamera.h"

namespace zombie {
namespace core {
namespace opengl {


class ParticleModelCamera : public ModelCamera {
public:
    void Begin() {
      Core.getInstance().DoPushIsoParticleStuff(this.m_x, this.m_y, this.m_z);
   }

    void End() {
      Core.getInstance().DoPopIsoStuff();
   }
}
} // namespace opengl
} // namespace core
} // namespace zombie
