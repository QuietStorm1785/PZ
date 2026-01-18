#pragma once
#include "zombie/core/opengl/IModelCamera.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ModelCamera {
public:
 static ModelCamera instance = nullptr;
 float m_useAngle;
 bool m_bUseWorldIso;
 float m_x;
 float m_y;
 float m_z;
 bool m_bInVehicle;
 bool bDepthMask = true;
}
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
