package zombie.inventory;

import java.util.Comparator;

final class ItemContainer$ConditionComparator implements Comparator<InventoryItem> {
   private ItemContainer$ConditionComparator() {
   }

   public int compare(InventoryItem var1, InventoryItem var2) {
      return var1.getCondition() - var2.getCondition();
   }
}
