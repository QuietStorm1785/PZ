#pragma once
#include "zombie/core/Core.h"
#include "zombie/core/skinnedmodel/ModelCamera.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace opengl {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ParticleModelCamera : public ModelCamera {
public:
 void Begin() {
 Core.getInstance().DoPushIsoParticleStuff(this->m_x, this->m_y, this->m_z);
 }

 void End() { Core.getInstance().DoPopIsoStuff(); }
}
} // namespace opengl
} // namespace core
} // namespace zombie
