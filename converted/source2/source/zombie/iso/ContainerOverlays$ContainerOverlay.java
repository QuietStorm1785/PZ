package zombie.iso;

import java.util.ArrayList;
import zombie.iso.ContainerOverlays.ContainerOverlayEntry;
import zombie.util.LocationRNG;

final class ContainerOverlays$ContainerOverlay {
   public String name;
   public final ArrayList<ContainerOverlayEntry> entries = new ArrayList<>();

   private ContainerOverlays$ContainerOverlay() {
   }

   public void getEntries(String var1, ArrayList<ContainerOverlayEntry> var2) {
      var2.clear();

      for (int var3 = 0; var3 < this.entries.size(); var3++) {
         ContainerOverlayEntry var4 = this.entries.get(var3);
         if (var4.room.equalsIgnoreCase(var1)) {
            var2.add(var4);
         }
      }
   }

   public ContainerOverlayEntry pickRandom(String var1, int var2, int var3, int var4) {
      this.getEntries(var1, ContainerOverlays.tempEntries);
      if (ContainerOverlays.tempEntries.isEmpty()) {
         return null;
      } else {
         int var5 = LocationRNG.instance.nextInt(ContainerOverlays.tempEntries.size(), var2, var3, var4);
         return (ContainerOverlayEntry)ContainerOverlays.tempEntries.get(var5);
      }
   }
}
