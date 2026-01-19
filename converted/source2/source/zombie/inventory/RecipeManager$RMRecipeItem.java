package zombie.inventory;

import java.util.ArrayDeque;

final class RecipeManager$RMRecipeItem {
   InventoryItem item;
   int uses;
   int water;
   static ArrayDeque<RecipeManager$RMRecipeItem> pool = new ArrayDeque<>();

   private RecipeManager$RMRecipeItem() {
   }

   RecipeManager$RMRecipeItem init(InventoryItem var1) {
      this.item = var1;
      return this;
   }

   RecipeManager$RMRecipeItem reset() {
      this.item = null;
      this.uses = 0;
      this.water = 0;
      return this;
   }

   int Use(int var1) {
      int var2 = Math.min(this.uses, var1);
      this.uses -= var2;
      return var2;
   }

   int UseWater(int var1) {
      int var2 = Math.min(this.water, var1);
      this.water -= var2;
      return var2;
   }

   static RecipeManager$RMRecipeItem alloc(InventoryItem var0) {
      return pool.isEmpty() ? new RecipeManager$RMRecipeItem().init(var0) : pool.pop().init(var0);
   }

   static void release(RecipeManager$RMRecipeItem var0) {
      if (!$assertionsDisabled && pool.contains(var0)) {
         throw new AssertionError();
      } else {
         pool.push(var0.reset());
      }
   }
}
