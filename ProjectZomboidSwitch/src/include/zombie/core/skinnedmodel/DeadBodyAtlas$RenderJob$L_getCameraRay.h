#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Matrix4f.h"
#include "org/joml/Vector3f.h"

namespace zombie {
namespace core {
namespace skinnedmodel {


class DeadBodyAtlas {
public:
    static const Matrix4f matrix4f = std::make_shared<Matrix4f>();
    static const Vector3f ray_start = std::make_shared<Vector3f>();
    static const Vector3f ray_end = std::make_shared<Vector3f>();
}
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
