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
    static const Matrix4f Pa = std::make_shared<Matrix4f>();
    static const Matrix4f mA = std::make_shared<Matrix4f>();
    static const Matrix4f mB = std::make_shared<Matrix4f>();
    static const Matrix4f umA = std::make_shared<Matrix4f>();
    static const Matrix4f umB = std::make_shared<Matrix4f>();
    static const Matrix4f mAinv = std::make_shared<Matrix4f>();
    static const Matrix4f umBinv = std::make_shared<Matrix4f>();
    static const Matrix4f result = std::make_shared<Matrix4f>();

   private AnimationPlayer$L_getTrackTransform() {
   }
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
