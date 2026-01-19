package zombie.debug.options;

import zombie.debug.BooleanDebugOption;
import zombie.debug.options.Terrain.RenderTiles.IsoGridSquare;

public final class Terrain$RenderTiles$IsoGridSquare$Walls extends OptionGroup {
   public final BooleanDebugOption NW;
   public final BooleanDebugOption W;
   public final BooleanDebugOption N;
   public final BooleanDebugOption Render;
   public final BooleanDebugOption Lighting;
   public final BooleanDebugOption LightingDebug;
   public final BooleanDebugOption LightingOldDebug;
   public final BooleanDebugOption AttachedSprites;

   public Terrain$RenderTiles$IsoGridSquare$Walls(IsoGridSquare var1, IDebugOptionGroup var2) {
      super(var2, "Walls");
      this.this$2 = var1;
      this.NW = newDebugOnlyOption(this.Group, "NW", true);
      this.W = newDebugOnlyOption(this.Group, "W", true);
      this.N = newDebugOnlyOption(this.Group, "N", true);
      this.Render = newDebugOnlyOption(this.Group, "Render", true);
      this.Lighting = newDebugOnlyOption(this.Group, "Lighting", true);
      this.LightingDebug = newDebugOnlyOption(this.Group, "LightingDebug", false);
      this.LightingOldDebug = newDebugOnlyOption(this.Group, "LightingOldDebug", false);
      this.AttachedSprites = newDebugOnlyOption(this.Group, "AttachedSprites", true);
   }
}
