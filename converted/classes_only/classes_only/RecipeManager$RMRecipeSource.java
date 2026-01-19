package zombie.inventory;

import java.util.ArrayDeque;
import java.util.ArrayList;
import zombie.inventory.RecipeManager.RMRecipe;
import zombie.inventory.RecipeManager.RMRecipeItem;
import zombie.inventory.RecipeManager.RMRecipeItemList;
import zombie.inventory.RecipeManager.SourceItems;
import zombie.inventory.types.HandWeapon;
import zombie.scripting.objects.Recipe.Source;

final class RecipeManager$RMRecipeSource {
   RMRecipe recipe;
   Source source;
   int index;
   final ArrayList<RMRecipeItemList> itemLists = new ArrayList<>();
   boolean usesWater;
   static ArrayDeque<RecipeManager$RMRecipeSource> pool = new ArrayDeque<>();

   private RecipeManager$RMRecipeSource() {
   }

   RecipeManager$RMRecipeSource init(RMRecipe var1, int var2) {
      this.recipe = var1;
      this.source = (Source)var1.recipe.getSource().get(var2);
      this.index = var2;
      if (!$assertionsDisabled && !this.itemLists.isEmpty()) {
         throw new AssertionError();
      } else {
         for (int var3 = 0; var3 < this.source.getItems().size(); var3++) {
            this.itemLists.add(RMRecipeItemList.alloc(this, var3));
         }

         this.usesWater = this.source.getItems().contains("Water");
         return this;
      }
   }

   RecipeManager$RMRecipeSource reset() {
      for (int var1 = 0; var1 < this.itemLists.size(); var1++) {
         RMRecipeItemList.release(this.itemLists.get(var1));
      }

      this.itemLists.clear();
      return this;
   }

   void getItemsFrom(ArrayList<RMRecipeItem> var1, RMRecipe var2) {
      for (int var3 = 0; var3 < this.itemLists.size(); var3++) {
         RMRecipeItemList var4 = this.itemLists.get(var3);
         var4.getItemsFrom(var1, var2);
      }
   }

   boolean hasItems() {
      for (int var1 = 0; var1 < this.itemLists.size(); var1++) {
         RMRecipeItemList var2 = this.itemLists.get(var1);
         if (var2.hasItems()) {
            return true;
         }
      }

      return false;
   }

   boolean isKeep(String var1) {
      return this.source.getItems().contains(var1) ? this.source.keep : false;
   }

   void getAvailableItems(SourceItems var1, boolean var2) {
      if (var2) {
         for (int var7 = 0; var7 < this.itemLists.size(); var7++) {
            RMRecipeItemList var8 = this.itemLists.get(var7);
            var8.getAvailableItems(var1, var2);
         }
      } else {
         int var3 = -1;

         for (int var4 = 0; var4 < this.itemLists.size(); var4++) {
            RMRecipeItemList var5 = this.itemLists.get(var4);
            if (var5.hasItems()) {
               InventoryItem var6 = ((RMRecipeItem)var5.items.get(0)).item;
               if (var1.selectedItem != null && var5.indexOf(var1.selectedItem) != -1) {
                  var3 = var4;
                  break;
               }

               if (var6 != null && var6 instanceof HandWeapon && (var6.isEquipped() || var6.isInPlayerInventory())) {
                  var3 = var4;
                  break;
               }

               if (var3 == -1) {
                  var3 = var4;
               }
            }
         }

         if (var3 != -1) {
            this.itemLists.get(var3).getAvailableItems(var1, var2);
         }
      }
   }

   void Use(ArrayList<InventoryItem> var1) {
      if (!$assertionsDisabled && !this.hasItems()) {
         throw new AssertionError();
      } else {
         for (int var2 = 0; var2 < this.itemLists.size(); var2++) {
            RMRecipeItemList var3 = this.itemLists.get(var2);
            if (var3.hasItems()) {
               var3.Use(var1);
               return;
            }
         }

         if (!$assertionsDisabled) {
            throw new AssertionError();
         }
      }
   }

   static RecipeManager$RMRecipeSource alloc(RMRecipe var0, int var1) {
      return pool.isEmpty() ? new RecipeManager$RMRecipeSource().init(var0, var1) : pool.pop().init(var0, var1);
   }

   static void release(RecipeManager$RMRecipeSource var0) {
      if (!$assertionsDisabled && pool.contains(var0)) {
         throw new AssertionError();
      } else {
         pool.push(var0.reset());
      }
   }
}
