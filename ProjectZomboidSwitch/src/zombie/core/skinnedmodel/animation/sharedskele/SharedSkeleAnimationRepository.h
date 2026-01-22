#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/animation/AnimationClip.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {
namespace sharedskele {


class SharedSkeleAnimationRepository {
public:
   private const std::unordered_map<AnimationClip, SharedSkeleAnimationTrack> m_tracksMap = std::make_unique<std::unordered_map<>>();

    SharedSkeleAnimationTrack getTrack(AnimationClip var1) {
      return this.m_tracksMap.get(var1);
   }

    void setTrack(AnimationClip var1, SharedSkeleAnimationTrack var2) {
      this.m_tracksMap.put(var1, var2);
   }
}
} // namespace sharedskele
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
