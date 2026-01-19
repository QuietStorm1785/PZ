package zombie.inventory;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.HashSet;
import zombie.Lua.LuaManager;
import zombie.characters.IsoGameCharacter;
import zombie.inventory.RecipeManager.RMRecipeItem;
import zombie.inventory.RecipeManager.RMRecipeSource;
import zombie.inventory.RecipeManager.SourceItems;
import zombie.inventory.types.DrainableComboItem;
import zombie.scripting.objects.Recipe;

final class RecipeManager$RMRecipe {
   Recipe recipe;
   final ArrayList<RMRecipeSource> sources = new ArrayList<>();
   final ArrayList<RMRecipeItem> allItems = new ArrayList<>();
   boolean usesWater;
   final HashSet<String> allSourceTypes = new HashSet<>();
   static ArrayDeque<RecipeManager$RMRecipe> pool = new ArrayDeque<>();

   private RecipeManager$RMRecipe() {
   }

   RecipeManager$RMRecipe init(Recipe var1) {
      if (!$assertionsDisabled && !this.allItems.isEmpty()) {
         throw new AssertionError();
      } else if (!$assertionsDisabled && !this.sources.isEmpty()) {
         throw new AssertionError();
      } else if (!$assertionsDisabled && !this.allSourceTypes.isEmpty()) {
         throw new AssertionError();
      } else {
         this.recipe = var1;
         this.usesWater = false;

         for (int var2 = 0; var2 < var1.getSource().size(); var2++) {
            RMRecipeSource var3 = RMRecipeSource.alloc(this, var2);
            if (var3.usesWater) {
               this.usesWater = true;
            }

            this.allSourceTypes.addAll(var3.source.getItems());
            this.sources.add(var3);
         }

         return this;
      }
   }

   RecipeManager$RMRecipe reset() {
      this.recipe = null;

      for (int var1 = 0; var1 < this.allItems.size(); var1++) {
         RMRecipeItem.release(this.allItems.get(var1));
      }

      this.allItems.clear();

      for (int var2 = 0; var2 < this.sources.size(); var2++) {
         RMRecipeSource.release(this.sources.get(var2));
      }

      this.sources.clear();
      this.allSourceTypes.clear();
      return this;
   }

   void getItemsFromContainers(IsoGameCharacter var1, ArrayList<ItemContainer> var2, InventoryItem var3) {
      for (int var4 = 0; var4 < var2.size(); var4++) {
         this.getItemsFromContainer(var1, (ItemContainer)var2.get(var4), var3);
      }

      if (this.Test(var3)) {
         for (int var6 = 0; var6 < this.sources.size(); var6++) {
            RMRecipeSource var5 = this.sources.get(var6);
            var5.getItemsFrom(this.allItems, this);
         }
      }
   }

   void getItemsFromContainer(IsoGameCharacter var1, ItemContainer var2, InventoryItem var3) {
      for (int var4 = 0; var4 < var2.getItems().size(); var4++) {
         InventoryItem var5 = (InventoryItem)var2.getItems().get(var4);
         if ((var3 != null && var3 == var5 || !var1.isEquippedClothing(var5) || this.isKeep(var5.getFullType()))
            && (!this.recipe.InSameInventory || this.isKeep(var5.getFullType()) || var3 == null || var2 == var3.getContainer())) {
            if (this.usesWater && var5 instanceof DrainableComboItem && var5.isWaterSource()) {
               this.allItems.add(RMRecipeItem.alloc(var5));
            } else if (this.allSourceTypes.contains(var5.getFullType())) {
               this.allItems.add(RMRecipeItem.alloc(var5));
            }
         }
      }
   }

   boolean Test(InventoryItem var1) {
      if (var1 != null && this.recipe.LuaTest != null) {
         Object var2 = LuaManager.getFunctionObject(this.recipe.LuaTest);
         if (var2 == null) {
            return false;
         } else {
            Boolean var3 = LuaManager.caller.protectedCallBoolean(LuaManager.thread, var2, var1, this.recipe.getResult());
            return var3 == Boolean.TRUE;
         }
      } else {
         return true;
      }
   }

   boolean hasItems() {
      for (int var1 = 0; var1 < this.sources.size(); var1++) {
         RMRecipeSource var2 = this.sources.get(var1);
         if (!var2.hasItems()) {
            return false;
         }
      }

      return true;
   }

   boolean isKeep(String var1) {
      for (int var2 = 0; var2 < this.sources.size(); var2++) {
         RMRecipeSource var3 = this.sources.get(var2);
         if (var3.isKeep(var1)) {
            return true;
         }
      }

      return false;
   }

   void getAvailableItems(SourceItems var1, boolean var2) {
      if (!$assertionsDisabled && !var2 && !this.hasItems()) {
         throw new AssertionError();
      } else {
         for (int var3 = 0; var3 < this.sources.size(); var3++) {
            RMRecipeSource var4 = this.sources.get(var3);
            if (!$assertionsDisabled && !var2 && !var4.hasItems()) {
               throw new AssertionError();
            }

            var4.getAvailableItems(var1, var2);
         }
      }
   }

   void Use(ArrayList<InventoryItem> var1) {
      if (!$assertionsDisabled && !this.hasItems()) {
         throw new AssertionError();
      } else {
         for (int var2 = 0; var2 < this.sources.size(); var2++) {
            RMRecipeSource var3 = this.sources.get(var2);
            if (!$assertionsDisabled && !var3.hasItems()) {
               throw new AssertionError();
            }

            var3.Use(var1);
         }
      }
   }

   static RecipeManager$RMRecipe alloc(Recipe var0) {
      return pool.isEmpty() ? new RecipeManager$RMRecipe().init(var0) : pool.pop().init(var0);
   }

   static void release(RecipeManager$RMRecipe var0) {
      if (!$assertionsDisabled && pool.contains(var0)) {
         throw new AssertionError();
      } else {
         pool.push(var0.reset());
      }
   }
}
