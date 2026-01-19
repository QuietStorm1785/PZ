package zombie.debug.options;

import zombie.debug.BooleanDebugOption;
import zombie.debug.options.Terrain.RenderTiles.IsoGridSquare;

public final class Terrain$RenderTiles extends OptionGroup {
   public final BooleanDebugOption Enable;
   public final BooleanDebugOption NewRender;
   public final BooleanDebugOption Shadows;
   public final BooleanDebugOption BloodDecals;
   public final BooleanDebugOption Water;
   public final BooleanDebugOption WaterShore;
   public final BooleanDebugOption WaterBody;
   public final BooleanDebugOption Lua;
   public final BooleanDebugOption VegetationCorpses;
   public final BooleanDebugOption MinusFloorCharacters;
   public final BooleanDebugOption RenderGridSquares;
   public final BooleanDebugOption RenderSprites;
   public final BooleanDebugOption OverlaySprites;
   public final BooleanDebugOption AttachedAnimSprites;
   public final BooleanDebugOption AttachedChildren;
   public final BooleanDebugOption AttachedWallBloodSplats;
   public final BooleanDebugOption UseShaders;
   public final BooleanDebugOption HighContrastBg;
   public final IsoGridSquare IsoGridSquare;

   public Terrain$RenderTiles(Terrain var1, IDebugOptionGroup var2) {
      super(var2, "RenderTiles");
      this.this$0 = var1;
      this.Enable = newDebugOnlyOption(this.Group, "Enable", true);
      this.NewRender = newDebugOnlyOption(this.Group, "NewRender", true);
      this.Shadows = newDebugOnlyOption(this.Group, "Shadows", true);
      this.BloodDecals = newDebugOnlyOption(this.Group, "BloodDecals", true);
      this.Water = newDebugOnlyOption(this.Group, "Water", true);
      this.WaterShore = newDebugOnlyOption(this.Group, "WaterShore", true);
      this.WaterBody = newDebugOnlyOption(this.Group, "WaterBody", true);
      this.Lua = newDebugOnlyOption(this.Group, "Lua", true);
      this.VegetationCorpses = newDebugOnlyOption(this.Group, "VegetationCorpses", true);
      this.MinusFloorCharacters = newDebugOnlyOption(this.Group, "MinusFloorCharacters", true);
      this.RenderGridSquares = newDebugOnlyOption(this.Group, "RenderGridSquares", true);
      this.RenderSprites = newDebugOnlyOption(this.Group, "RenderSprites", true);
      this.OverlaySprites = newDebugOnlyOption(this.Group, "OverlaySprites", true);
      this.AttachedAnimSprites = newDebugOnlyOption(this.Group, "AttachedAnimSprites", true);
      this.AttachedChildren = newDebugOnlyOption(this.Group, "AttachedChildren", true);
      this.AttachedWallBloodSplats = newDebugOnlyOption(this.Group, "AttachedWallBloodSplats", true);
      this.UseShaders = newOption(this.Group, "UseShaders", true);
      this.HighContrastBg = newDebugOnlyOption(this.Group, "HighContrastBg", false);
      this.IsoGridSquare = new IsoGridSquare(this, this.Group);
   }
}
