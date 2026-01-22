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


class IsoZombie {
public:
    static const PerformanceProfileProbe update = std::make_shared<PerformanceProfileProbe>("IsoZombie.update");
    static const PerformanceProfileProbe postUpdate = std::make_shared<PerformanceProfileProbe>("IsoZombie.postUpdate");

   private IsoZombie$s_performance() {
   }
}
} // namespace characters
} // namespace zombie
