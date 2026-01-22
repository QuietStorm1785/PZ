#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {


class AnimationClip {
public:
   const Keyframe[] m_keyframes;

   AnimationClip$KeyframeByBoneIndexElement(List<Keyframe> var1) {
      this.m_keyframes = var1.toArray(new Keyframe[0]);
   }
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
