package zombie.iso;

import java.util.ArrayList;
import zombie.iso.TileOverlays.TileOverlayUsage;
import zombie.util.LocationRNG;

final class TileOverlays$TileOverlayEntry {
   public String room;
   public int chance;
   public final ArrayList<String> tiles = new ArrayList<>();
   public final TileOverlayUsage usage = new TileOverlayUsage();

   private TileOverlays$TileOverlayEntry() {
   }

   public boolean matchUsage(IsoGridSquare var1) {
      return this.usage.match(var1);
   }

   public String pickRandom(int var1, int var2, int var3) {
      int var4 = LocationRNG.instance.nextInt(this.chance, var1, var2, var3);
      if (var4 == 0 && !this.tiles.isEmpty()) {
         var4 = LocationRNG.instance.nextInt(this.tiles.size());
         return this.tiles.get(var4);
      } else {
         return null;
      }
   }
}
