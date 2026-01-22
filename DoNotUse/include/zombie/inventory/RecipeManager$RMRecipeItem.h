#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace inventory {


class RecipeManager {
public:
    InventoryItem item;
    int uses;
    int water;
   static ArrayDeque<RecipeManager$RMRecipeItem> pool = std::make_unique<ArrayDeque<>>();

   private RecipeManager$RMRecipeItem() {
   }

   RecipeManager$RMRecipeItem init(InventoryItem var1) {
      this.item = var1;
    return this;
   }

   RecipeManager$RMRecipeItem reset() {
      this.item = nullptr;
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
      return pool.empty() ? new RecipeManager$RMRecipeItem().init(var0) : pool.pop().init(var0);
   }

    static void release(RecipeManager$RMRecipeItem var0) {
      if (!$assertionsDisabled && pool.contains(var0)) {
         throw std::make_unique<AssertionError>();
      } else {
         pool.push(var0.reset());
      }
   }
}
} // namespace inventory
} // namespace zombie
