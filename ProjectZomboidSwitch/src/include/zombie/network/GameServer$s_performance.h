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
namespace network {


class GameServer {
public:
    static const PerformanceProfileFrameProbe frameStep = std::make_shared<PerformanceProfileFrameProbe>("GameServer.frameStep");
    static const PerformanceProfileProbe mainLoopDealWithNetData = std::make_shared<PerformanceProfileProbe>("GameServer.mainLoopDealWithNetData");
    static const PerformanceProfileProbe RCONServerUpdate = std::make_shared<PerformanceProfileProbe>("RCONServer.update");

   private GameServer$s_performance() {
   }
}
} // namespace network
} // namespace zombie
