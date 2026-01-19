package zombie.inventory;

import java.util.Objects;
import java.util.function.Predicate;

final class ItemContainer$CategoryPredicate implements Predicate<InventoryItem> {
   String category;

   private ItemContainer$CategoryPredicate() {
   }

   ItemContainer$CategoryPredicate init(String var1) {
      this.category = Objects.requireNonNull(var1);
      return this;
   }

   public boolean test(InventoryItem var1) {
      return var1.getCategory().equals(this.category);
   }
}
