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


class SpriteRenderer {
public:
    static const PerformanceProfileProbe waitForReadyState = std::make_shared<PerformanceProfileProbe>("waitForReadyState");
    static const PerformanceProfileProbe waitForReadySlotToOpen = std::make_shared<PerformanceProfileProbe>("waitForReadySlotToOpen");

   private SpriteRenderer$s_performance() {
   }
}
} // namespace core
} // namespace zombie
