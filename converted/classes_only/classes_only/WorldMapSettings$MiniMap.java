package zombie.worldMap;

import zombie.config.BooleanConfigOption;
import zombie.config.DoubleConfigOption;

public class WorldMapSettings$MiniMap {
   public DoubleConfigOption Zoom;
   public BooleanConfigOption Isometric;
   public BooleanConfigOption ShowSymbols;
   public BooleanConfigOption StartVisible;

   public WorldMapSettings$MiniMap(WorldMapSettings var1) {
      this.this$0 = var1;
      this.Zoom = this.this$0.newOption("MiniMap.Zoom", 0.0, 24.0, 19.0);
      this.Isometric = this.this$0.newOption("MiniMap.Isometric", true);
      this.ShowSymbols = this.this$0.newOption("MiniMap.ShowSymbols", false);
      this.StartVisible = this.this$0.newOption("MiniMap.StartVisible", true);
   }
}
