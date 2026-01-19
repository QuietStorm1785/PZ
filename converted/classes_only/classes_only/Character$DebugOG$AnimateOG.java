package zombie.debug.options;

import zombie.debug.BooleanDebugOption;

public final class Character$DebugOG$AnimateOG extends OptionGroup {
   public final BooleanDebugOption DeferredRotationOnly = newDebugOnlyOption(this.Group, "DeferredRotationsOnly", false);
   public final BooleanDebugOption NoBoneMasks = newDebugOnlyOption(this.Group, "NoBoneMasks", false);
   public final BooleanDebugOption NoBoneTwists = newDebugOnlyOption(this.Group, "NoBoneTwists", false);
   public final BooleanDebugOption ZeroCounterRotationBone = newDebugOnlyOption(this.Group, "ZeroCounterRotation", false);

   public Character$DebugOG$AnimateOG(IDebugOptionGroup var1) {
      super(var1, "Animate");
   }
}
