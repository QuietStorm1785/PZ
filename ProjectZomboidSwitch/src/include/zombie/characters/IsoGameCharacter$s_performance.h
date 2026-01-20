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


class IsoGameCharacter {
public:
    static const PerformanceProfileProbe postUpdate = std::make_shared<PerformanceProfileProbe>("IsoGameCharacter.postUpdate");
    static PerformanceProfileProbe update = std::make_shared<PerformanceProfileProbe>("IsoGameCharacter.update");

   private IsoGameCharacter$s_performance() {
   }
}
} // namespace characters
} // namespace zombie
