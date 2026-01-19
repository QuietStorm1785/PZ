package zombie.network;

import zombie.core.profiling.PerformanceProfileFrameProbe;
import zombie.core.profiling.PerformanceProfileProbe;

class GameServer$s_performance {
   static final PerformanceProfileFrameProbe frameStep = new PerformanceProfileFrameProbe("GameServer.frameStep");
   static final PerformanceProfileProbe mainLoopDealWithNetData = new PerformanceProfileProbe("GameServer.mainLoopDealWithNetData");
   static final PerformanceProfileProbe RCONServerUpdate = new PerformanceProfileProbe("RCONServer.update");

   private GameServer$s_performance() {
   }
}
