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
    static auto frameStep = std::make_shared<PerformanceProfileFrameProbe>("GameWindow.frameStep");
    static auto statesRender = std::make_shared<PerformanceProfileProbe>("GameWindow.states.render");
    static auto logic = std::make_shared<PerformanceProfileProbe>("GameWindow.logic");

   private GameWindow$s_performance() {
   }
}
} // namespace zombie
