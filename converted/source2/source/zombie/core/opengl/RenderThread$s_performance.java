package zombie.core.opengl;

import zombie.core.profiling.PerformanceProfileFrameProbe;
import zombie.core.profiling.PerformanceProfileProbe;

class RenderThread$s_performance {
   static final PerformanceProfileFrameProbe renderStep = new PerformanceProfileFrameProbe("RenderThread.renderStep");
   static final PerformanceProfileProbe displayUpdate = new PerformanceProfileProbe("Display.update(true)");
   static final PerformanceProfileProbe spriteRendererPostRender = new PerformanceProfileProbe("SpriteRenderer.postRender");

   private RenderThread$s_performance() {
   }
}
