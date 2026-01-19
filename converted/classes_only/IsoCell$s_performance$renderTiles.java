package zombie.iso;

import zombie.core.profiling.PerformanceProfileProbe;
import zombie.core.profiling.PerformanceProfileProbeList;
import zombie.iso.IsoCell.s_performance.renderTiles.PperformRenderTilesLayer;

class IsoCell$s_performance$renderTiles {
   static final PerformanceProfileProbe performRenderTiles = new PerformanceProfileProbe("performRenderTiles");
   static final PerformanceProfileProbe recalculateAnyGridStacks = new PerformanceProfileProbe("recalculateAnyGridStacks");
   static final PerformanceProfileProbe flattenAnyFoliage = new PerformanceProfileProbe("flattenAnyFoliage");
   static final PerformanceProfileProbe renderDebugPhysics = new PerformanceProfileProbe("renderDebugPhysics");
   static final PerformanceProfileProbe renderDebugLighting = new PerformanceProfileProbe("renderDebugLighting");
   static PerformanceProfileProbeList<PperformRenderTilesLayer> performRenderTilesLayers = PerformanceProfileProbeList.construct(
      "performRenderTiles", 8, PperformRenderTilesLayer.class, PperformRenderTilesLayer::new
   );
}
