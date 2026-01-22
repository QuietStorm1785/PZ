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
namespace physics {


class WorldSimulation {
public:
    static const PerformanceProfileProbe worldSimulationUpdate = std::make_shared<PerformanceProfileProbe>("WorldSimulation.update");

   private WorldSimulation$s_performance() {
   }
}
} // namespace physics
} // namespace core
} // namespace zombie
