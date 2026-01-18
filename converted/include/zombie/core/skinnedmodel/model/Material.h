#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/Vector3.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


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
