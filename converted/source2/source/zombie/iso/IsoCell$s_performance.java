package zombie.iso;

import zombie.core.profiling.PerformanceProfileProbe;

class IsoCell$s_performance {
   static final PerformanceProfileProbe isoCellUpdate = new PerformanceProfileProbe("IsoCell.update");
   static final PerformanceProfileProbe isoCellRender = new PerformanceProfileProbe("IsoCell.render");
   static final PerformanceProfileProbe isoCellRenderTiles = new PerformanceProfileProbe("IsoCell.renderTiles");
   static final PerformanceProfileProbe isoCellDoBuilding = new PerformanceProfileProbe("IsoCell.doBuilding");

   private IsoCell$s_performance() {
   }
}
