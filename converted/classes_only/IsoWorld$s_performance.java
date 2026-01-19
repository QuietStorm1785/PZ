package zombie.iso;

import zombie.core.profiling.PerformanceProfileProbe;

class IsoWorld$s_performance {
   static final PerformanceProfileProbe isoWorldUpdate = new PerformanceProfileProbe("IsoWorld.update");
   static final PerformanceProfileProbe isoWorldRender = new PerformanceProfileProbe("IsoWorld.render");

   private IsoWorld$s_performance() {
   }
}
