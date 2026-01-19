package zombie.debug.options;

import zombie.debug.BooleanDebugOption;

public final class OffscreenBuffer extends OptionGroup {
   public final BooleanDebugOption Render = newDebugOnlyOption(this.Group, "Render", true);

   public OffscreenBuffer() {
      super("OffscreenBuffer");
   }
}
