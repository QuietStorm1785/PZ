package zombie.inventory;

import java.util.ArrayList;
import zombie.audio.BaseSoundEmitter;
import zombie.iso.IsoWorld;

public final class ItemSoundManager {
   private static final ArrayList<InventoryItem> items = new ArrayList<>();
   private static final ArrayList<BaseSoundEmitter> emitters = new ArrayList<>();
   private static final ArrayList<InventoryItem> toAdd = new ArrayList<>();
   private static final ArrayList<InventoryItem> toRemove = new ArrayList<>();
   private static final ArrayList<InventoryItem> toStopItems = new ArrayList<>();
   private static final ArrayList<BaseSoundEmitter> toStopEmitters = new ArrayList<>();

   public static void addItem(InventoryItem var0) {
      if (var0 != null && !items.contains(var0)) {
         toRemove.remove(var0);
         int var1 = toStopItems.indexOf(var0);
         if (var1 != -1) {
            toStopItems.remove(var1);
            BaseSoundEmitter var2 = toStopEmitters.remove(var1);
            items.add(var0);
            emitters.add(var2);
         } else if (!toAdd.contains(var0)) {
            toAdd.add(var0);
         }
      }
   }

   public static void removeItem(InventoryItem var0) {
      toAdd.remove(var0);
      int var1 = items.indexOf(var0);
      if (var0 != null && var1 != -1) {
         if (!toRemove.contains(var0)) {
            toRemove.add(var0);
         }
      }
   }

   public static void removeItems(ArrayList<InventoryItem> var0) {
      for (int var1 = 0; var1 < var0.size(); var1++) {
         removeItem((InventoryItem)var0.get(var1));
      }
   }

   public static void update() {
      if (!toStopItems.isEmpty()) {
         for (int var0 = 0; var0 < toStopItems.size(); var0++) {
            BaseSoundEmitter var1 = toStopEmitters.get(var0);
            var1.stopAll();
            IsoWorld.instance.returnOwnershipOfEmitter(var1);
         }

         toStopItems.clear();
         toStopEmitters.clear();
      }

      if (!toAdd.isEmpty()) {
         for (int var4 = 0; var4 < toAdd.size(); var4++) {
            InventoryItem var7 = toAdd.get(var4);

            assert !items.contains(var7);

            items.add(var7);
            BaseSoundEmitter var2 = IsoWorld.instance.getFreeEmitter();
            IsoWorld.instance.takeOwnershipOfEmitter(var2);
            emitters.add(var2);
         }

         toAdd.clear();
      }

      if (!toRemove.isEmpty()) {
         for (int var5 = 0; var5 < toRemove.size(); var5++) {
            InventoryItem var8 = toRemove.get(var5);

            assert items.contains(var8);

            int var10 = items.indexOf(var8);
            items.remove(var10);
            BaseSoundEmitter var3 = emitters.get(var10);
            emitters.remove(var10);
            toStopItems.add(var8);
            toStopEmitters.add(var3);
         }

         toRemove.clear();
      }

      for (int var6 = 0; var6 < items.size(); var6++) {
         InventoryItem var9 = items.get(var6);
         BaseSoundEmitter var11 = emitters.get(var6);
         ItemContainer var12 = var9.getOutermostContainer();
         if (var12 != null) {
            if (var12.containingItem != null && var12.containingItem.getWorldItem() != null) {
               if (var12.containingItem.getWorldItem().getWorldObjectIndex() == -1) {
                  var12 = null;
               }
            } else if (var12.parent != null) {
               if (var12.parent.getObjectIndex() == -1 && var12.parent.getMovingObjectIndex() == -1 && var12.parent.getStaticMovingObjectIndex() == -1) {
                  var12 = null;
               }
            } else {
               var12 = null;
            }
         }

         if (var12 != null || var9.getWorldItem() != null && var9.getWorldItem().getWorldObjectIndex() != -1) {
            var9.updateSound(var11);
            var11.tick();
         } else {
            removeItem(var9);
         }
      }
   }

   public static void Reset() {
      items.clear();
      emitters.clear();
      toAdd.clear();
      toRemove.clear();
      toStopItems.clear();
      toStopEmitters.clear();
   }
}
