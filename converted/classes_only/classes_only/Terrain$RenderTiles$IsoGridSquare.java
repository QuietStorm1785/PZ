package zombie.debug.options;

import zombie.debug.BooleanDebugOption;
import zombie.debug.options.Terrain.RenderTiles;
import zombie.debug.options.Terrain.RenderTiles.IsoGridSquare.Floor;
import zombie.debug.options.Terrain.RenderTiles.IsoGridSquare.Walls;

public final class Terrain$RenderTiles$IsoGridSquare extends OptionGroup {
   public final BooleanDebugOption RenderMinusFloor;
   public final BooleanDebugOption DoorsAndWalls;
   public final BooleanDebugOption DoorsAndWalls_SimpleLighting;
   public final BooleanDebugOption Objects;
   public final BooleanDebugOption MeshCutdown;
   public final BooleanDebugOption IsoPadding;
   public final BooleanDebugOption IsoPaddingDeDiamond;
   public final BooleanDebugOption IsoPaddingAttached;
   public final BooleanDebugOption ShoreFade;
   public final Walls Walls;
   public final Floor Floor;

   public Terrain$RenderTiles$IsoGridSquare(RenderTiles var1, IDebugOptionGroup var2) {
      super(var2, "IsoGridSquare");
      this.this$1 = var1;
      this.RenderMinusFloor = newDebugOnlyOption(this.Group, "RenderMinusFloor", true);
      this.DoorsAndWalls = newDebugOnlyOption(this.Group, "DoorsAndWalls", true);
      this.DoorsAndWalls_SimpleLighting = newDebugOnlyOption(this.Group, "DoorsAndWallsSL", true);
      this.Objects = newDebugOnlyOption(this.Group, "Objects", true);
      this.MeshCutdown = newDebugOnlyOption(this.Group, "MeshCutDown", true);
      this.IsoPadding = newDebugOnlyOption(this.Group, "IsoPadding", true);
      this.IsoPaddingDeDiamond = newDebugOnlyOption(this.Group, "IsoPaddingDeDiamond", true);
      this.IsoPaddingAttached = newDebugOnlyOption(this.Group, "IsoPaddingAttached", true);
      this.ShoreFade = newDebugOnlyOption(this.Group, "ShoreFade", true);
      this.Walls = new Walls(this, this.Group);
      this.Floor = new Floor(this, this.Group);
   }
}
