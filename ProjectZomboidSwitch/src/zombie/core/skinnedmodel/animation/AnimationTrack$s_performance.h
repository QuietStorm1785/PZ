#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/profiling/PerformanceProfileProbe.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {


class AnimationTrack {
public:
    static const PerformanceProfileProbe tickCurrentTime = std::make_shared<PerformanceProfileProbe>("AnimationTrack.tickCurrentTime");
    static const PerformanceProfileProbe updateKeyframes = std::make_shared<PerformanceProfileProbe>("AnimationTrack.updateKeyframes");
    static const PerformanceProfileProbe updateDeferredValues = std::make_shared<PerformanceProfileProbe>("AnimationTrack.updateDeferredValues");
    static const PerformanceProfileProbe updatePose = std::make_shared<PerformanceProfileProbe>("AnimationTrack.updatePose");

   private AnimationTrack$s_performance() {
   }
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
