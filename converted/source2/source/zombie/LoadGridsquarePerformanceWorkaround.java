package zombie;

import zombie.LoadGridsquarePerformanceWorkaround.ItemPicker;
import zombie.iso.ContainerOverlays;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoObject;
import zombie.iso.TileOverlays;
import zombie.iso.objects.IsoWorldInventoryObject;
import zombie.network.GameClient;

public final class LoadGridsquarePerformanceWorkaround {
   public static void init(int var0, int var1) {
      if (!GameClient.bClient) {
         ItemPicker.instance.init();
      }
   }

   public static void LoadGridsquare(IsoGridSquare var0) {
      if (ItemPicker.instance.begin(var0)) {
         IsoObject[] var1 = (IsoObject[])var0.getObjects().getElements();
         int var2 = var0.getObjects().size();

         for (int var3 = 0; var3 < var2; var3++) {
            IsoObject var4 = var1[var3];
            if (!(var4 instanceof IsoWorldInventoryObject)) {
               if (!GameClient.bClient) {
                  ItemPicker.instance.checkObject(var4);
               }

               if (var4.sprite != null && var4.sprite.name != null && !ContainerOverlays.instance.hasOverlays(var4)) {
                  TileOverlays.instance.updateTileOverlaySprite(var4);
               }
            }
         }
      }

      ItemPicker.instance.end(var0);
   }
}
