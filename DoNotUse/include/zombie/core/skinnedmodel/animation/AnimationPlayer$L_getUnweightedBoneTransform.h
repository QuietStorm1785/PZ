#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/util/vector/Quaternion.h"
#include "org/lwjgl/util/vector/Vector3f.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {


class AnimationPlayer {
public:
    static const Vector3f pos = std::make_shared<Vector3f>();
    static const Quaternion rot = std::make_shared<Quaternion>();
    static const Vector3f scale = std::make_shared<Vector3f>();

   private AnimationPlayer$L_getUnweightedBoneTransform() {
   }
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
