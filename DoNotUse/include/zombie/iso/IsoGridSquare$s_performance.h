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


class IsoGridSquare {
public:
    static const PerformanceProfileProbe renderFloor = std::make_shared<PerformanceProfileProbe>("IsoGridSquare.renderFloor", false);

   private IsoGridSquare$s_performance() {
   }
}
} // namespace iso
} // namespace zombie
