package zombie.inventory;

import java.util.ArrayDeque;
import java.util.ArrayList;
import zombie.inventory.RecipeManager.RMRecipe;
import zombie.inventory.RecipeManager.RMRecipeItem;
import zombie.inventory.RecipeManager.RMRecipeSource;
import zombie.inventory.RecipeManager.SourceItems;
import zombie.inventory.RecipeManager.RMRecipeItemList.Type;
import zombie.inventory.types.DrainableComboItem;
import zombie.inventory.types.Food;
import zombie.scripting.ScriptManager;

final class RecipeManager$RMRecipeItemList {
   RMRecipeSource source;
   final ArrayList<RMRecipeItem> items = new ArrayList<>();
   int index;
   int usesNeeded;
   Type type = Type.NONE;
   static ArrayDeque<RecipeManager$RMRecipeItemList> pool = new ArrayDeque<>();

   private RecipeManager$RMRecipeItemList() {
   }

   RecipeManager$RMRecipeItemList init(RMRecipeSource var1, int var2) {
      if (!$assertionsDisabled && !this.items.isEmpty()) {
         throw new AssertionError();
      } else {
         this.source = var1;
         this.index = var2;
         String var3 = (String)var1.source.getItems().get(var2);
         this.usesNeeded = (int)var1.source.getCount();
         if ("Water".equals(var3)) {
            this.type = Type.WATER;
         } else if (var1.source.isDestroy()) {
            this.type = Type.DESTROY;
         } else if (ScriptManager.instance.isDrainableItemType(var3)) {
            this.type = Type.DRAINABLE;
         } else if (var1.source.use > 0.0F) {
            this.usesNeeded = (int)var1.source.use;
            this.type = Type.FOOD;
         } else {
            this.type = Type.OTHER;
         }

         return this;
      }
   }

   RecipeManager$RMRecipeItemList reset() {
      this.source = null;
      this.items.clear();
      return this;
   }

   void getItemsFrom(ArrayList<RMRecipeItem> var1, RMRecipe var2) {
      String var3 = (String)this.source.source.getItems().get(this.index);

      for (int var4 = 0; var4 < var1.size(); var4++) {
         RMRecipeItem var5 = (RMRecipeItem)var1.get(var4);
         DrainableComboItem var6 = (DrainableComboItem)zombie.util.Type.tryCastTo(var5.item, DrainableComboItem.class);
         Food var7 = (Food)zombie.util.Type.tryCastTo(var5.item, Food.class);
         if ("Water".equals(var3)) {
            if (var2.Test(var5.item) && var5.item instanceof DrainableComboItem && var5.item.isWaterSource()) {
               var5.water = RecipeManager.AvailableUses(var5.item);
               this.items.add(var5);
            }
         } else if (var3.equals(var5.item.getFullType())
            && (!(var2.recipe.getHeat() > 0.0F) || var6 == null || !var5.item.IsCookable || !(var5.item.getInvHeat() + 1.0F < var2.recipe.getHeat()))
            && (!(var2.recipe.getHeat() < 0.0F) || var6 == null || !var5.item.IsCookable || !(var5.item.getInvHeat() > var2.recipe.getHeat()))
            && (var7 == null || !(var7.getFreezingTime() > 0.0F) || var2.recipe.isAllowFrozenItem())
            && (!var2.recipe.noBrokenItems() || !var5.item.isBroken())
            && (!"Clothing".equals(var5.item.getCategory()) || !var5.item.isFavorite())
            && var2.Test(var5.item)) {
            if (this.source.source.isDestroy()) {
               var5.uses = 1;
               this.items.add(var5);
            } else if (var6 != null) {
               var5.uses = RecipeManager.AvailableUses(var5.item);
               this.items.add(var5);
            } else if (this.source.source.use > 0.0F) {
               if (var5.item instanceof Food) {
                  var5.uses = RecipeManager.AvailableUses(var5.item);
                  this.items.add(var5);
               }
            } else {
               var5.uses = var5.item.getUses();
               this.items.add(var5);
            }
         }
      }
   }

   boolean hasItems() {
      String var1 = (String)this.source.source.getItems().get(this.index);
      int var2 = 0;

      for (int var3 = 0; var3 < this.items.size(); var3++) {
         if ("Water".equals(var1)) {
            var2 += this.items.get(var3).water;
         } else {
            var2 += this.items.get(var3).uses;
         }
      }

      return var2 >= this.usesNeeded;
   }

   int indexOf(InventoryItem var1) {
      for (int var2 = 0; var2 < this.items.size(); var2++) {
         RMRecipeItem var3 = this.items.get(var2);
         if (var3.item == var1) {
            return var2;
         }
      }

      return -1;
   }

   void getAvailableItems(SourceItems var1, boolean var2) {
      if (var2) {
         this.Use(var1.itemsPerSource[this.source.index]);
         var1.typePerSource[this.source.index] = this.type;
         var1.allItems.addAll(var1.itemsPerSource[this.source.index]);
      } else if (!$assertionsDisabled && !this.hasItems()) {
         throw new AssertionError();
      } else {
         if (var1.selectedItem != null) {
            int var3 = this.indexOf(var1.selectedItem);
            if (var3 != -1) {
               RMRecipeItem var4 = this.items.remove(var3);
               this.items.add(0, var4);
            }
         }

         this.Use(var1.itemsPerSource[this.source.index]);
         var1.typePerSource[this.source.index] = this.type;
         var1.allItems.addAll(var1.itemsPerSource[this.source.index]);
      }
   }

   void Use(ArrayList<InventoryItem> var1) {
      String var2 = (String)this.source.source.getItems().get(this.index);
      int var3 = this.usesNeeded;

      for (int var4 = 0; var4 < this.items.size(); var4++) {
         RMRecipeItem var5 = this.items.get(var4);
         if ("Water".equals(var2) && var5.water > 0) {
            var3 -= var5.UseWater(var3);
            var1.add(var5.item);
         } else if (this.source.source.isKeep() && var5.uses > 0) {
            var3 -= Math.min(var5.uses, var3);
            var1.add(var5.item);
         } else if (var5.uses > 0) {
            var3 -= var5.Use(var3);
            var1.add(var5.item);
         }

         if (var3 <= 0) {
            break;
         }
      }
   }

   static RecipeManager$RMRecipeItemList alloc(RMRecipeSource var0, int var1) {
      return pool.isEmpty() ? new RecipeManager$RMRecipeItemList().init(var0, var1) : pool.pop().init(var0, var1);
   }

   static void release(RecipeManager$RMRecipeItemList var0) {
      if (!$assertionsDisabled && pool.contains(var0)) {
         throw new AssertionError();
      } else {
         pool.push(var0.reset());
      }
   }
}
