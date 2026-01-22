#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/util/vector/Matrix4f.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {


class AnimationPlayer {
public:
    static const Matrix4f boneTransform = std::make_shared<Matrix4f>();

   private AnimationPlayer$L_getUnweightedModelTransform() {
   }
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
