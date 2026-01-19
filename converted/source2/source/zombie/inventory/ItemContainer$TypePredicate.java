package zombie.inventory;

import java.util.Objects;
import java.util.function.Predicate;

final class ItemContainer$TypePredicate implements Predicate<InventoryItem> {
   String type;

   private ItemContainer$TypePredicate() {
   }

   ItemContainer$TypePredicate init(String var1) {
      this.type = Objects.requireNonNull(var1);
      return this;
   }

   public boolean test(InventoryItem var1) {
      return ItemContainer.compareType(this.type, var1);
   }
}
