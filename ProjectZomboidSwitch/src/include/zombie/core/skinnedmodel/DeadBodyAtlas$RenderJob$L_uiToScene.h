#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/vehicles/UI3DScene/Plane.h"
#include "zombie/vehicles/UI3DScene/Ray.h"

namespace zombie {
namespace core {
namespace skinnedmodel {


class DeadBodyAtlas {
public:
    static const Plane plane = std::make_shared<Plane>();
    static const Ray ray = std::make_shared<Ray>();
}
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
