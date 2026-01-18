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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ParticleModelCamera : public ModelCamera {
public:
 void Begin() {
 Core.getInstance().DoPushIsoParticleStuff(this->m_x, this->m_y, this->m_z);
 }

 void End() {
 Core.getInstance().DoPopIsoStuff();
 }
}
} // namespace opengl
} // namespace core
} // namespace zombie
