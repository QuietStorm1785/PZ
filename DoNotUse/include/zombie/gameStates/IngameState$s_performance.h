#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/profiling/PerformanceProfileProbe.h"

namespace zombie {
namespace gameStates {


class IngameState {
public:
    static const PerformanceProfileProbe render = std::make_shared<PerformanceProfileProbe>("IngameState.render");
    static const PerformanceProfileProbe renderFrame = std::make_shared<PerformanceProfileProbe>("IngameState.renderFrame");
    static const PerformanceProfileProbe renderFrameText = std::make_shared<PerformanceProfileProbe>("IngameState.renderFrameText");
    static const PerformanceProfileProbe renderFrameUI = std::make_shared<PerformanceProfileProbe>("IngameState.renderFrameUI");
    static const PerformanceProfileProbe update = std::make_shared<PerformanceProfileProbe>("IngameState.update");

   private IngameState$s_performance() {
   }
}
} // namespace gameStates
} // namespace zombie
