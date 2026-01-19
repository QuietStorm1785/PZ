package zombie.inventory;

import zombie.inventory.ItemContainer.InventoryItemList;
import zombie.popman.ObjectPool;

final class ItemContainer$InventoryItemListPool extends ObjectPool<InventoryItemList> {
   public ItemContainer$InventoryItemListPool() {
      super(InventoryItemList::new);
   }

   public void release(InventoryItemList var1) {
      var1.clear();
      super.release(var1);
   }
}
