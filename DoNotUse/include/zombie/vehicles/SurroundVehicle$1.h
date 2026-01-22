#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/vehicles/SurroundVehicle/PositionSide.h"

namespace zombie {
namespace vehicles {


// $VF: synthetic class
class SurroundVehicle {
public:
   static {
      try {
         $SwitchMap$zombie$vehicles$SurroundVehicle$PositionSide[PositionSide.Front.ordinal()] = 1;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$zombie$vehicles$SurroundVehicle$PositionSide[PositionSide.Rear.ordinal()] = 2;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$vehicles$SurroundVehicle$PositionSide[PositionSide.Left.ordinal()] = 3;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$vehicles$SurroundVehicle$PositionSide[PositionSide.Right.ordinal()] = 4;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace vehicles
} // namespace zombie
