#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoDirections.h"

namespace zombie {
namespace ai {
namespace states {


// $VF: synthetic class
class ClimbOverWallState {
public:
   static {
      try {
         $SwitchMap$zombie$iso$IsoDirections[IsoDirections.N.ordinal()] = 1;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$zombie$iso$IsoDirections[IsoDirections.S.ordinal()] = 2;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$iso$IsoDirections[IsoDirections.W.ordinal()] = 3;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$iso$IsoDirections[IsoDirections.E.ordinal()] = 4;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
