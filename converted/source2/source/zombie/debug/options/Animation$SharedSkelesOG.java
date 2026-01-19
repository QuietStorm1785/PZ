package zombie.debug.options;

import zombie.debug.BooleanDebugOption;

public final class Animation$SharedSkelesOG extends OptionGroup {
   public final BooleanDebugOption Enabled = newDebugOnlyOption(this.Group, "Enabled", true);
   public final BooleanDebugOption AllowLerping = newDebugOnlyOption(this.Group, "AllowLerping", true);

   Animation$SharedSkelesOG(IDebugOptionGroup var1) {
      super(var1, "SharedSkeles");
   }
}
