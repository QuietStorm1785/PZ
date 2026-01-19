package zombie.debug.options;

import zombie.debug.BooleanDebugOption;
import zombie.debug.options.Character.DebugOG.AnimateOG;
import zombie.debug.options.Character.DebugOG.RenderOG;

public final class Character$DebugOG extends OptionGroup {
   public final RenderOG Render = new RenderOG(this.Group);
   public final AnimateOG Animate = new AnimateOG(this.Group);
   public final BooleanDebugOption RegisterDebugVariables = newDebugOnlyOption(this.Group, "DebugVariables", false);
   public final BooleanDebugOption AlwaysTripOverFence = newDebugOnlyOption(this.Group, "AlwaysTripOverFence", false);
   public final BooleanDebugOption PlaySoundWhenInvisible = newDebugOnlyOption(this.Group, "PlaySoundWhenInvisible", false);
   public final BooleanDebugOption UpdateAlpha = newDebugOnlyOption(this.Group, "UpdateAlpha", true);
   public final BooleanDebugOption UpdateAlphaEighthSpeed = newDebugOnlyOption(this.Group, "UpdateAlphaEighthSpeed", false);

   public Character$DebugOG(IDebugOptionGroup var1) {
      super(var1, "Debug");
   }
}
