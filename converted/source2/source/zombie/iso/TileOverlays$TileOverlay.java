package zombie.iso;

import java.util.ArrayList;
import zombie.iso.TileOverlays.TileOverlayEntry;
import zombie.util.LocationRNG;

final class TileOverlays$TileOverlay {
   public String tile;
   public final ArrayList<TileOverlayEntry> entries = new ArrayList<>();

   private TileOverlays$TileOverlay() {
   }

   public void getEntries(String var1, IsoGridSquare var2, ArrayList<TileOverlayEntry> var3) {
      var3.clear();

      for (int var4 = 0; var4 < this.entries.size(); var4++) {
         TileOverlayEntry var5 = this.entries.get(var4);
         if (var5.room.equalsIgnoreCase(var1) && var5.matchUsage(var2)) {
            var3.add(var5);
         }
      }
   }

   public TileOverlayEntry pickRandom(String var1, IsoGridSquare var2) {
      this.getEntries(var1, var2, TileOverlays.tempEntries);
      if (TileOverlays.tempEntries.isEmpty()) {
         return null;
      } else {
         int var3 = LocationRNG.instance.nextInt(TileOverlays.tempEntries.size(), var2.x, var2.y, var2.z);
         return (TileOverlayEntry)TileOverlays.tempEntries.get(var3);
      }
   }
}
