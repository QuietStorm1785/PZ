package zombie.debug.options;

import zombie.debug.options.Terrain.RenderTiles;

public final class Terrain extends OptionGroup {
   public final RenderTiles RenderTiles = new RenderTiles(this, this.Group);

   public Terrain() {
      super("Terrain");
   }
}
