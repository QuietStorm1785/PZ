package zombie.worldMap;

import zombie.config.BooleanConfigOption;
import zombie.config.DoubleConfigOption;

public final class WorldMapSettings$WorldMap {
   public DoubleConfigOption CenterX;
   public DoubleConfigOption CenterY;
   public DoubleConfigOption Zoom;
   public BooleanConfigOption Isometric;
   public BooleanConfigOption ShowSymbolsUI;

   public WorldMapSettings$WorldMap(WorldMapSettings var1) {
      this.this$0 = var1;
      this.CenterX = this.this$0.newOption("WorldMap.CenterX", -Double.MAX_VALUE, Double.MAX_VALUE, 0.0);
      this.CenterY = this.this$0.newOption("WorldMap.CenterY", -Double.MAX_VALUE, Double.MAX_VALUE, 0.0);
      this.Zoom = this.this$0.newOption("WorldMap.Zoom", 0.0, 24.0, 0.0);
      this.Isometric = this.this$0.newOption("WorldMap.Isometric", true);
      this.ShowSymbolsUI = this.this$0.newOption("WorldMap.ShowSymbolsUI", true);
   }
}
