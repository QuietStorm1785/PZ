#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/inventory/types/Clothing/WetDryState.h"

namespace zombie {
namespace inventory {
namespace types {


// $VF: synthetic class
class Clothing {
public:
   static {
      try {
         $SwitchMap$zombie$inventory$types$Clothing$WetDryState[WetDryState.Invalid.ordinal()] = 1;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$inventory$types$Clothing$WetDryState[WetDryState.Dryer.ordinal()] = 2;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$inventory$types$Clothing$WetDryState[WetDryState.Wetter.ordinal()] = 3;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace types
} // namespace inventory
} // namespace zombie
