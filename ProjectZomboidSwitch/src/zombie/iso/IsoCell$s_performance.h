#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/profiling/PerformanceProfileProbe.h"

namespace zombie {
namespace iso {


class IsoCell {
public:
    static const PerformanceProfileProbe isoCellUpdate = std::make_shared<PerformanceProfileProbe>("IsoCell.update");
    static const PerformanceProfileProbe isoCellRender = std::make_shared<PerformanceProfileProbe>("IsoCell.render");
    static const PerformanceProfileProbe isoCellRenderTiles = std::make_shared<PerformanceProfileProbe>("IsoCell.renderTiles");
    static const PerformanceProfileProbe isoCellDoBuilding = std::make_shared<PerformanceProfileProbe>("IsoCell.doBuilding");

   private IsoCell$s_performance() {
   }
}
} // namespace iso
} // namespace zombie
