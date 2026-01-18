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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

/**
 * Created by LEMMYMAIN on 23/02/2015.
 */
class IAnimListener {
public:
 virtual ~IAnimListener() = default;
 void onAnimStarted(AnimationTrack track);

 void onLoopedAnim(AnimationTrack track);

 void onNonLoopedAnimFadeOut(AnimationTrack track);

 void onNonLoopedAnimFinished(AnimationTrack track);

 void onTrackDestroyed(AnimationTrack track);
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
