package zombie;

import zombie.core.profiling.PerformanceProfileFrameProbe;
import zombie.core.profiling.PerformanceProfileProbe;

class GameWindow$s_performance {
   static final PerformanceProfileFrameProbe frameStep = new PerformanceProfileFrameProbe("GameWindow.frameStep");
   static final PerformanceProfileProbe statesRender = new PerformanceProfileProbe("GameWindow.states.render");
   static final PerformanceProfileProbe logic = new PerformanceProfileProbe("GameWindow.logic");

   private GameWindow$s_performance() {
   }
}
