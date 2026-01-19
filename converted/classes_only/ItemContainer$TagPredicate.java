package zombie.inventory;

import java.util.Objects;
import java.util.function.Predicate;

final class ItemContainer$TagPredicate implements Predicate<InventoryItem> {
   String tag;

   private ItemContainer$TagPredicate() {
   }

   ItemContainer$TagPredicate init(String var1) {
      this.tag = Objects.requireNonNull(var1);
      return this;
   }

   public boolean test(InventoryItem var1) {
      return var1.hasTag(this.tag);
   }
}
