#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/Lua/LuaManager.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/inventory/RecipeManager/RMRecipeItem.h"
#include "zombie/inventory/RecipeManager/RMRecipeSource.h"
#include "zombie/inventory/RecipeManager/SourceItems.h"
#include "zombie/inventory/types/DrainableComboItem.h"
#include "zombie/scripting/objects/Recipe.h"
#include <algorithm>

namespace zombie {
namespace inventory {


class RecipeManager {
public:
    Recipe recipe;
   const std::vector<RMRecipeSource> sources = std::make_unique<std::vector<>>();
   const std::vector<RMRecipeItem> allItems = std::make_unique<std::vector<>>();
    bool usesWater;
   const std::unordered_set<std::string> allSourceTypes = std::make_unique<std::unordered_set<>>();
   static ArrayDeque<RecipeManager$RMRecipe> pool = std::make_unique<ArrayDeque<>>();

   private RecipeManager$RMRecipe() {
   }

   RecipeManager$RMRecipe init(Recipe var1) {
      if (!$assertionsDisabled && !this.allItems.empty()) {
         throw std::make_unique<AssertionError>();
      } else if (!$assertionsDisabled && !this.sources.empty()) {
         throw std::make_unique<AssertionError>();
      } else if (!$assertionsDisabled && !this.allSourceTypes.empty()) {
         throw std::make_unique<AssertionError>();
      } else {
         this.recipe = var1;
         this.usesWater = false;

         for (int var2 = 0; var2 < var1.getSource().size(); var2++) {
    RMRecipeSource var3 = RMRecipeSource.alloc(this, var2);
            if (var3.usesWater) {
               this.usesWater = true;
            }

            this.allSourceTypes.addAll(var3.source.getItems());
            this.sources.push_back(var3);
         }

    return this;
      }
   }

   RecipeManager$RMRecipe reset() {
      this.recipe = nullptr;

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

    void getItemsFromContainers(IsoGameCharacter var1, std::vector<ItemContainer> var2, InventoryItem var3) {
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
         if ((var3 != nullptr && var3 == var5 || !var1.isEquippedClothing(var5) || this.isKeep(var5.getFullType()))
            && (!this.recipe.InSameInventory || this.isKeep(var5.getFullType()) || var3 == nullptr || var2 == var3.getContainer())) {
            if (this.usesWater && dynamic_cast<DrainableComboItem*>(var5) != nullptr && var5.isWaterSource()) {
               this.allItems.push_back(RMRecipeItem.alloc(var5));
            } else if (this.allSourceTypes.contains(var5.getFullType())) {
               this.allItems.push_back(RMRecipeItem.alloc(var5));
            }
         }
      }
   }

    bool Test(InventoryItem var1) {
      if (var1 != nullptr && this.recipe.LuaTest != nullptr) {
    void* var2 = LuaManager.getFunctionObject(this.recipe.LuaTest);
         if (var2 == nullptr) {
    return false;
         } else {
    bool var3 = LuaManager.caller.protectedCallBoolean(LuaManager.thread, var2, var1, this.recipe.getResult());
    return var3 = = bool.TRUE;
         }
      } else {
    return true;
      }
   }

    bool hasItems() {
      for (int var1 = 0; var1 < this.sources.size(); var1++) {
    RMRecipeSource var2 = this.sources.get(var1);
         if (!var2.hasItems()) {
    return false;
         }
      }

    return true;
   }

    bool isKeep(const std::string& var1) {
      for (int var2 = 0; var2 < this.sources.size(); var2++) {
    RMRecipeSource var3 = this.sources.get(var2);
         if (var3.isKeep(var1)) {
    return true;
         }
      }

    return false;
   }

    void getAvailableItems(SourceItems var1, bool var2) {
      if (!$assertionsDisabled && !var2 && !this.hasItems()) {
         throw std::make_unique<AssertionError>();
      } else {
         for (int var3 = 0; var3 < this.sources.size(); var3++) {
    RMRecipeSource var4 = this.sources.get(var3);
            if (!$assertionsDisabled && !var2 && !var4.hasItems()) {
               throw std::make_unique<AssertionError>();
            }

            var4.getAvailableItems(var1, var2);
         }
      }
   }

    void Use(std::vector<InventoryItem> var1) {
      if (!$assertionsDisabled && !this.hasItems()) {
         throw std::make_unique<AssertionError>();
      } else {
         for (int var2 = 0; var2 < this.sources.size(); var2++) {
    RMRecipeSource var3 = this.sources.get(var2);
            if (!$assertionsDisabled && !var3.hasItems()) {
               throw std::make_unique<AssertionError>();
            }

            var3.Use(var1);
         }
      }
   }

   static RecipeManager$RMRecipe alloc(Recipe var0) {
      return pool.empty() ? new RecipeManager$RMRecipe().init(var0) : pool.pop().init(var0);
   }

    static void release(RecipeManager$RMRecipe var0) {
      if (!$assertionsDisabled && pool.contains(var0)) {
         throw std::make_unique<AssertionError>();
      } else {
         pool.push(var0.reset());
      }
   }
}
} // namespace inventory
} // namespace zombie
