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
public:
    static auto profile_ResolveContacts = std::make_shared<PerformanceProfileProbe>("CollisionManager.ResolveContacts");
    static auto profile_MovingObjectPostUpdate = std::make_shared<PerformanceProfileProbe>("IsoMovingObject.postupdate");

   private CollisionManager$s_performance() {
   }
}
} // namespace zombie
