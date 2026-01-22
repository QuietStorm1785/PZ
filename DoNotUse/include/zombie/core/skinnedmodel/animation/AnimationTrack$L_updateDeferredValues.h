#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/util/vector/Quaternion.h"
#include "org/lwjgl/util/vector/Vector3f.h"
#include "zombie/iso/Vector2.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {


class AnimationTrack {
public:
    static const Keyframe keyFrame = std::make_shared<Keyframe>(std::make_shared<Vector3f>(), std::make_shared<Quaternion>(), std::make_shared<Vector3f>(1.0F, 1.0F, 1.0F));
    static const Keyframe prevKeyFrame = std::make_shared<Keyframe>(std::make_shared<Vector3f>(), std::make_shared<Quaternion>(), std::make_shared<Vector3f>(1.0F, 1.0F, 1.0F));
    static const Vector2 crDiff = std::make_shared<Vector2>();
    static const Vector2 diff = std::make_shared<Vector2>();

   private AnimationTrack$L_updateDeferredValues() {
   }
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
