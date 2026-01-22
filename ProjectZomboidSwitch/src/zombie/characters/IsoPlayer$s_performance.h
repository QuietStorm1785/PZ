#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/profiling/PerformanceProfileProbe.h"

namespace zombie {
namespace characters {


class IsoPlayer {
public:
    static const PerformanceProfileProbe postUpdate = std::make_shared<PerformanceProfileProbe>("IsoPlayer.postUpdate");
    static const PerformanceProfileProbe highlightRangedTargets = std::make_shared<PerformanceProfileProbe>("IsoPlayer.highlightRangedTargets");
    static const PerformanceProfileProbe update = std::make_shared<PerformanceProfileProbe>("IsoPlayer.update");

   private IsoPlayer$s_performance() {
   }
}
} // namespace characters
} // namespace zombie
