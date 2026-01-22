#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/inventory/RecipeManager/RMRecipeItemList/Type.h"
#include "zombie/scripting/objects/Recipe.h"

namespace zombie {
namespace inventory {


class RecipeManager {
public:
    InventoryItem selectedItem;
   const std::vector<InventoryItem> allItems = std::make_unique<std::vector<>>();
   const std::vector<InventoryItem>[] itemsPerSource;
   const Type[] typePerSource;

   RecipeManager$SourceItems(Recipe var1, IsoGameCharacter var2, InventoryItem var3, std::vector<InventoryItem> var4) {
      this.itemsPerSource = new std::vector[var1.getSource().size()];

      for (int var5 = 0; var5 < this.itemsPerSource.length; var5++) {
         this.itemsPerSource[var5] = std::make_unique<std::vector<>>();
      }

      this.typePerSource = new Type[var1.getSource().size()];
      this.selectedItem = var3;
   }

   public std::vector<InventoryItem> getItems() {
      return this.allItems;
   }
}
} // namespace inventory
} // namespace zombie
