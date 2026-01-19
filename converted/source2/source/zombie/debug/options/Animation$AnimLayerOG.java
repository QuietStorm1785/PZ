package zombie.debug.options;

import zombie.debug.BooleanDebugOption;

public final class Animation$AnimLayerOG extends OptionGroup {
   public final BooleanDebugOption LogStateChanges = newDebugOnlyOption(this.Group, "Debug.LogStateChanges", false);
   public final BooleanDebugOption AllowAnimNodeOverride = newDebugOnlyOption(this.Group, "Debug.AllowAnimNodeOverride", false);

   Animation$AnimLayerOG(IDebugOptionGroup var1) {
      super(var1, "AnimLayer");
   }
}
