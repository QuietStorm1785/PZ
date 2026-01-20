#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/profiling/PerformanceProfileProbe.h"
#include "zombie/core/profiling/PerformanceProfileProbeList.h"
#include "zombie/iso/IsoCell/s_performance/renderTiles/PperformRenderTilesLayer.h"

namespace zombie {
namespace iso {


class IsoCell {
public:
    static const PerformanceProfileProbe performRenderTiles = std::make_shared<PerformanceProfileProbe>("performRenderTiles");
    static const PerformanceProfileProbe recalculateAnyGridStacks = std::make_shared<PerformanceProfileProbe>("recalculateAnyGridStacks");
    static const PerformanceProfileProbe flattenAnyFoliage = std::make_shared<PerformanceProfileProbe>("flattenAnyFoliage");
    static const PerformanceProfileProbe renderDebugPhysics = std::make_shared<PerformanceProfileProbe>("renderDebugPhysics");
    static const PerformanceProfileProbe renderDebugLighting = std::make_shared<PerformanceProfileProbe>("renderDebugLighting");
   static PerformanceProfileProbeList<PperformRenderTilesLayer> performRenderTilesLayers = PerformanceProfileProbeList.construct(
      "performRenderTiles", 8, PperformRenderTilesLayer.class, PperformRenderTilesLayer::new
   );
}
} // namespace iso
} // namespace zombie
