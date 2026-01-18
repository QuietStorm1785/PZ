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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class SharedSkeleAnimationRepository {
public:
 private HashMap<AnimationClip, SharedSkeleAnimationTrack> m_tracksMap = std::make_unique<HashMap<>>();

 SharedSkeleAnimationTrack getTrack(AnimationClip clip) {
 return this->m_tracksMap.get(clip);
 }

 void setTrack(AnimationClip clip, SharedSkeleAnimationTrack track) {
 this->m_tracksMap.put(clip, track);
 }
}
} // namespace sharedskele
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
