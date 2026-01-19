#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/profiling/PerformanceProfileFrameProbe.h"
#include "zombie/core/profiling/PerformanceProfileProbe.h"

namespace zombie {


class GameWindow {
public:
    static const PerformanceProfileFrameProbe frameStep = new PerformanceProfileFrameProbe("GameWindow.frameStep");
    static const PerformanceProfileProbe statesRender = new PerformanceProfileProbe("GameWindow.states.render");
    static const PerformanceProfileProbe logic = new PerformanceProfileProbe("GameWindow.logic");

   private GameWindow$s_performance() {
   }
}
} // namespace zombie
