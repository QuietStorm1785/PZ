package zombie.scripting.objects;

import java.util.function.Predicate;
import zombie.inventory.InventoryItem;
import zombie.scripting.objects.Fixing.Fixer;

final class Fixing$PredicateRequired implements Predicate<InventoryItem> {
   Fixer fixer;
   InventoryItem brokenItem;
   int uses;

   private Fixing$PredicateRequired() {
   }

   public boolean test(InventoryItem var1) {
      if (this.uses >= this.fixer.getNumberOfUse()) {
         return false;
      } else if (var1 == this.brokenItem) {
         return false;
      } else if (!this.fixer.getFixerName().equals(var1.getType())) {
         return false;
      } else {
         int var2 = Fixing.countUses(var1);
         if (var2 > 0) {
            this.uses += var2;
            return true;
         } else {
            return false;
         }
      }
   }
}
