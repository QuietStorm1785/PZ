#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/profiling/PerformanceProfileProbe.h"

namespace zombie {


class CollisionManager {
:
    static const PerformanceProfileProbe profile_ResolveContacts = new PerformanceProfileProbe("CollisionManager.ResolveContacts");
    static const PerformanceProfileProbe profile_MovingObjectPostUpdate = new PerformanceProfileProbe("IsoMovingObject.postupdate");

   private CollisionManager$s_performance() {
   }
}
} // namespace zombie
