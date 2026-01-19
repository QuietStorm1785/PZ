package zombie.characters.action;

import zombie.core.profiling.PerformanceProfileProbe;

class ActionContext$s_performance {
   static final PerformanceProfileProbe update = new PerformanceProfileProbe("ActionContext.update");
   static final PerformanceProfileProbe evaluateCurrentStateTransitions = new PerformanceProfileProbe("ActionContext.evaluateCurrentStateTransitions");
   static final PerformanceProfileProbe evaluateSubStateTransitions = new PerformanceProfileProbe("ActionContext.evaluateSubStateTransitions");

   private ActionContext$s_performance() {
   }
}
