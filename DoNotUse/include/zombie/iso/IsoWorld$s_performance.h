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


class IsoWorld {
public:
    static const PerformanceProfileProbe isoWorldUpdate = std::make_shared<PerformanceProfileProbe>("IsoWorld.update");
    static const PerformanceProfileProbe isoWorldRender = std::make_shared<PerformanceProfileProbe>("IsoWorld.render");

   private IsoWorld$s_performance() {
   }
}
} // namespace iso
} // namespace zombie
