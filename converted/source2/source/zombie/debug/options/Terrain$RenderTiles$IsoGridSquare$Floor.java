package zombie.debug.options;

import zombie.debug.BooleanDebugOption;
import zombie.debug.options.Terrain.RenderTiles.IsoGridSquare;

public final class Terrain$RenderTiles$IsoGridSquare$Floor extends OptionGroup {
   public final BooleanDebugOption Lighting;
   public final BooleanDebugOption LightingOld;
   public final BooleanDebugOption LightingDebug;

   public Terrain$RenderTiles$IsoGridSquare$Floor(IsoGridSquare var1, IDebugOptionGroup var2) {
      super(var2, "Floor");
      this.this$2 = var1;
      this.Lighting = newDebugOnlyOption(this.Group, "Lighting", true);
      this.LightingOld = newDebugOnlyOption(this.Group, "LightingOld", false);
      this.LightingDebug = newDebugOnlyOption(this.Group, "LightingDebug", false);
   }
}
