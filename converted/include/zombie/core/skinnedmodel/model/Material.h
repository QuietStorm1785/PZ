#pragma once
#include "zombie/core/skinnedmodel/Vector3.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Material {
public:
  std::string Name;
  std::string DiffuseTexture;
  Vector3 AmbientColour;
  Vector3 DiffuseColour;
  Vector3 SpecularColour;
  int SpecularPower;
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
