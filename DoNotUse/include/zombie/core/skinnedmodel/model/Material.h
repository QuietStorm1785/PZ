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
