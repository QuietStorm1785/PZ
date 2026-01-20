#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/inventory/RecipeManager/RMRecipe.h"
#include "zombie/inventory/RecipeManager/RMRecipeItem.h"
#include "zombie/inventory/RecipeManager/RMRecipeItemList.h"
#include "zombie/inventory/RecipeManager/SourceItems.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/scripting/objects/Recipe/Source.h"
#include <algorithm>

namespace zombie {
namespace inventory {


class RecipeManager {
public:
    RMRecipe recipe;
    Source source;
    int index;
   const std::vector<RMRecipeItemList> itemLists = std::make_unique<std::vector<>>();
    bool usesWater;
   static ArrayDeque<RecipeManager$RMRecipeSource> pool = std::make_unique<ArrayDeque<>>();

   private RecipeManager$RMRecipeSource() {
   }

   RecipeManager$RMRecipeSource init(RMRecipe var1, int var2) {
      this.recipe = var1;
      this.source = (Source)var1.recipe.getSource().get(var2);
      this.index = var2;
      if (!$assertionsDisabled && !this.itemLists.empty()) {
         throw std::make_unique<AssertionError>();
      } else {
         for (int var3 = 0; var3 < this.source.getItems().size(); var3++) {
            this.itemLists.push_back(RMRecipeItemList.alloc(this, var3));
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

    void getItemsFrom(std::vector<RMRecipeItem> var1, RMRecipe var2) {
      for (int var3 = 0; var3 < this.itemLists.size(); var3++) {
    RMRecipeItemList var4 = this.itemLists.get(var3);
         var4.getItemsFrom(var1, var2);
      }
   }

    bool hasItems() {
      for (int var1 = 0; var1 < this.itemLists.size(); var1++) {
    RMRecipeItemList var2 = this.itemLists.get(var1);
         if (var2.hasItems()) {
    return true;
         }
      }

    return false;
   }

    bool isKeep(const std::string& var1) {
      return this.source.getItems().contains(var1) ? this.source.keep : false;
   }

    void getAvailableItems(SourceItems var1, bool var2) {
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
               if (var1.selectedItem != nullptr && var5.indexOf(var1.selectedItem) != -1) {
                  var3 = var4;
                  break;
               }

               if (var6 != nullptr && dynamic_cast<HandWeapon*>(var6) != nullptr && (var6.isEquipped() || var6.isInPlayerInventory())) {
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

    void Use(std::vector<InventoryItem> var1) {
      if (!$assertionsDisabled && !this.hasItems()) {
         throw std::make_unique<AssertionError>();
      } else {
         for (int var2 = 0; var2 < this.itemLists.size(); var2++) {
    RMRecipeItemList var3 = this.itemLists.get(var2);
            if (var3.hasItems()) {
               var3.Use(var1);
               return;
            }
         }

         if (!$assertionsDisabled) {
            throw std::make_unique<AssertionError>();
         }
      }
   }

   static RecipeManager$RMRecipeSource alloc(RMRecipe var0, int var1) {
      return pool.empty() ? new RecipeManager$RMRecipeSource().init(var0, var1) : pool.pop().init(var0, var1);
   }

    static void release(RecipeManager$RMRecipeSource var0) {
      if (!$assertionsDisabled && pool.contains(var0)) {
         throw std::make_unique<AssertionError>();
      } else {
         pool.push(var0.reset());
      }
   }
}
} // namespace inventory
} // namespace zombie
