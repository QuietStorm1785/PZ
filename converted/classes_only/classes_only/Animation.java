package zombie.debug.options;

import zombie.debug.BooleanDebugOption;
import zombie.debug.options.Animation.AnimLayerOG;
import zombie.debug.options.Animation.SharedSkelesOG;

public final class Animation extends OptionGroup {
   public final BooleanDebugOption Debug = newDebugOnlyOption(this.Group, "Debug", false);
   public final BooleanDebugOption AllowEarlyTransitionOut = newDebugOnlyOption(this.Group, "AllowEarlyTransitionOut", true);
   public final AnimLayerOG AnimLayer = new AnimLayerOG(this.Group);
   public final SharedSkelesOG SharedSkeles = new SharedSkelesOG(this.Group);
   public final BooleanDebugOption AnimRenderPicker = newDebugOnlyOption(this.Group, "Render.Picker", false);
   public final BooleanDebugOption BlendUseFbx = newDebugOnlyOption(this.Group, "BlendUseFbx", false);

   public Animation() {
      super("Animation");
   }
}
