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

class IAnimListener {
public:
    virtual ~IAnimListener() = default;
    void onAnimStarted(AnimationTrack var1);

    void onLoopedAnim(AnimationTrack var1);

    void onNonLoopedAnimFadeOut(AnimationTrack var1);

    void onNonLoopedAnimFinished(AnimationTrack var1);

    void onTrackDestroyed(AnimationTrack var1);
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
