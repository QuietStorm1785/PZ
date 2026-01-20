#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/inventory/RecipeManager/RMRecipe.h"
#include "zombie/inventory/RecipeManager/RMRecipeItem.h"
#include "zombie/inventory/RecipeManager/RMRecipeItemList/Type.h"
#include "zombie/inventory/RecipeManager/RMRecipeSource.h"
#include "zombie/inventory/RecipeManager/SourceItems.h"
#include "zombie/inventory/types/DrainableComboItem.h"
#include "zombie/inventory/types/Food.h"
#include "zombie/scripting/ScriptManager.h"
#include <algorithm>

namespace zombie {
namespace inventory {


class RecipeManager {
public:
    RMRecipeSource source;
   const std::vector<RMRecipeItem> items = std::make_unique<std::vector<>>();
    int index;
    int usesNeeded;
    Type type = Type.NONE;
   static ArrayDeque<RecipeManager$RMRecipeItemList> pool = std::make_unique<ArrayDeque<>>();

   private RecipeManager$RMRecipeItemList() {
   }

   RecipeManager$RMRecipeItemList init(RMRecipeSource var1, int var2) {
      if (!$assertionsDisabled && !this.items.empty()) {
         throw std::make_unique<AssertionError>();
      } else {
         this.source = var1;
         this.index = var2;
    std::string var3 = (std::string)var1.source.getItems().get(var2);
         this.usesNeeded = (int)var1.source.getCount();
         if ("Water" == var3)) {
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
      this.source = nullptr;
      this.items.clear();
    return this;
   }

    void getItemsFrom(std::vector<RMRecipeItem> var1, RMRecipe var2) {
    std::string var3 = (std::string)this.source.source.getItems().get(this.index);

      for (int var4 = 0; var4 < var1.size(); var4++) {
    RMRecipeItem var5 = (RMRecipeItem)var1.get(var4);
    DrainableComboItem var6 = (DrainableComboItem)zombie.util.Type.tryCastTo(var5.item, DrainableComboItem.class);
    Food var7 = (Food)zombie.util.Type.tryCastTo(var5.item, Food.class);
         if ("Water" == var3)) {
            if (var2.Test(var5.item) && var5.dynamic_cast<DrainableComboItem*>(item) != nullptr && var5.item.isWaterSource()) {
               var5.water = RecipeManager.AvailableUses(var5.item);
               this.items.push_back(var5);
            }
         } else if (var3 == var5.item.getFullType())
            && (!(var2.recipe.getHeat() > 0.0F) || var6 == nullptr || !var5.item.IsCookable || !(var5.item.getInvHeat() + 1.0F < var2.recipe.getHeat()))
            && (!(var2.recipe.getHeat() < 0.0F) || var6 == nullptr || !var5.item.IsCookable || !(var5.item.getInvHeat() > var2.recipe.getHeat()))
            && (var7 == nullptr || !(var7.getFreezingTime() > 0.0F) || var2.recipe.isAllowFrozenItem())
            && (!var2.recipe.noBrokenItems() || !var5.item.isBroken())
            && (!"Clothing" == var5.item.getCategory()) || !var5.item.isFavorite())
            && var2.Test(var5.item)) {
            if (this.source.source.isDestroy()) {
               var5.uses = 1;
               this.items.push_back(var5);
            } else if (var6 != nullptr) {
               var5.uses = RecipeManager.AvailableUses(var5.item);
               this.items.push_back(var5);
            } else if (this.source.source.use > 0.0F) {
               if (var5.dynamic_cast<Food*>(item) != nullptr) {
                  var5.uses = RecipeManager.AvailableUses(var5.item);
                  this.items.push_back(var5);
               }
            } else {
               var5.uses = var5.item.getUses();
               this.items.push_back(var5);
            }
         }
      }
   }

    bool hasItems() {
    std::string var1 = (std::string)this.source.source.getItems().get(this.index);
    int var2 = 0;

      for (int var3 = 0; var3 < this.items.size(); var3++) {
         if ("Water" == var1)) {
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

    void getAvailableItems(SourceItems var1, bool var2) {
      if (var2) {
         this.Use(var1.itemsPerSource[this.source.index]);
         var1.typePerSource[this.source.index] = this.type;
         var1.allItems.addAll(var1.itemsPerSource[this.source.index]);
      } else if (!$assertionsDisabled && !this.hasItems()) {
         throw std::make_unique<AssertionError>();
      } else {
         if (var1.selectedItem != nullptr) {
    int var3 = this.indexOf(var1.selectedItem);
            if (var3 != -1) {
    RMRecipeItem var4 = this.items.remove(var3);
               this.items.push_back(0, var4);
            }
         }

         this.Use(var1.itemsPerSource[this.source.index]);
         var1.typePerSource[this.source.index] = this.type;
         var1.allItems.addAll(var1.itemsPerSource[this.source.index]);
      }
   }

    void Use(std::vector<InventoryItem> var1) {
    std::string var2 = (std::string)this.source.source.getItems().get(this.index);
    int var3 = this.usesNeeded;

      for (int var4 = 0; var4 < this.items.size(); var4++) {
    RMRecipeItem var5 = this.items.get(var4);
         if ("Water" == var2) && var5.water > 0) {
            var3 -= var5.UseWater(var3);
            var1.push_back(var5.item);
         } else if (this.source.source.isKeep() && var5.uses > 0) {
            var3 -= Math.min(var5.uses, var3);
            var1.push_back(var5.item);
         } else if (var5.uses > 0) {
            var3 -= var5.Use(var3);
            var1.push_back(var5.item);
         }

         if (var3 <= 0) {
            break;
         }
      }
   }

   static RecipeManager$RMRecipeItemList alloc(RMRecipeSource var0, int var1) {
      return pool.empty() ? new RecipeManager$RMRecipeItemList().init(var0, var1) : pool.pop().init(var0, var1);
   }

    static void release(RecipeManager$RMRecipeItemList var0) {
      if (!$assertionsDisabled && pool.contains(var0)) {
         throw std::make_unique<AssertionError>();
      } else {
         pool.push(var0.reset());
      }
   }
}
} // namespace inventory
} // namespace zombie
