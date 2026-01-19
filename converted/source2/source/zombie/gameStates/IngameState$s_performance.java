package zombie.gameStates;

import zombie.core.profiling.PerformanceProfileProbe;

class IngameState$s_performance {
   static final PerformanceProfileProbe render = new PerformanceProfileProbe("IngameState.render");
   static final PerformanceProfileProbe renderFrame = new PerformanceProfileProbe("IngameState.renderFrame");
   static final PerformanceProfileProbe renderFrameText = new PerformanceProfileProbe("IngameState.renderFrameText");
   static final PerformanceProfileProbe renderFrameUI = new PerformanceProfileProbe("IngameState.renderFrameUI");
   static final PerformanceProfileProbe update = new PerformanceProfileProbe("IngameState.update");

   private IngameState$s_performance() {
   }
}
