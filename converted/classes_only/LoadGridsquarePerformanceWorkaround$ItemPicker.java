package zombie;

import zombie.characters.IsoPlayer;
import zombie.inventory.ItemContainer;
import zombie.inventory.ItemPickerJava;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoObject;
import zombie.iso.sprite.IsoSprite;
import zombie.network.GameServer;

class LoadGridsquarePerformanceWorkaround$ItemPicker {
   public static final LoadGridsquarePerformanceWorkaround$ItemPicker instance = new LoadGridsquarePerformanceWorkaround$ItemPicker();
   private IsoGridSquare square;

   private LoadGridsquarePerformanceWorkaround$ItemPicker() {
   }

   public void init() {
   }

   public boolean begin(IsoGridSquare var1) {
      if (var1.isOverlayDone()) {
         this.square = null;
         return false;
      } else {
         this.square = var1;
         return true;
      }
   }

   public void checkObject(IsoObject var1) {
      IsoSprite var2 = var1.getSprite();
      if (var2 != null && var2.getName() != null) {
         ItemContainer var3 = var1.getContainer();
         if (var3 != null && !var3.isExplored()) {
            ItemPickerJava.fillContainer(var3, IsoPlayer.getInstance());
            var3.setExplored(true);
            if (GameServer.bServer) {
               GameServer.sendItemsInContainer(var1, var3);
            }
         }

         if (var3 == null || !var3.isEmpty()) {
            ItemPickerJava.updateOverlaySprite(var1);
         }
      }
   }

   public void end(IsoGridSquare var1) {
      var1.setOverlayDone(true);
   }
}
