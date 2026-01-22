#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/inventory/RecipeManager/RMRecipeItemList/Type.h"

namespace zombie {
namespace inventory {


// $VF: synthetic class
class RecipeManager {
public:
   static {
      try {
         $SwitchMap$zombie$inventory$RecipeManager$RMRecipeItemList$Type[Type.DRAINABLE.ordinal()] = 1;
      } catch (NoSuchFieldError var5) {
      }

      try {
         $SwitchMap$zombie$inventory$RecipeManager$RMRecipeItemList$Type[Type.FOOD.ordinal()] = 2;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$zombie$inventory$RecipeManager$RMRecipeItemList$Type[Type.DESTROY.ordinal()] = 3;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$inventory$RecipeManager$RMRecipeItemList$Type[Type.OTHER.ordinal()] = 4;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$inventory$RecipeManager$RMRecipeItemList$Type[Type.WATER.ordinal()] = 5;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace inventory
} // namespace zombie
