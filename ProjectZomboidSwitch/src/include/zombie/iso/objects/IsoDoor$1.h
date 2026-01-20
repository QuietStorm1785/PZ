#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/objects/IsoDoor/DoorType.h"

namespace zombie {
namespace iso {
namespace objects {


// $VF: synthetic class
class IsoDoor {
public:
   static {
      try {
         $SwitchMap$zombie$iso$objects$IsoDoor$DoorType[DoorType.WeakWooden.ordinal()] = 1;
      } catch (NoSuchFieldError var6) {
      }

      try {
         $SwitchMap$zombie$iso$objects$IsoDoor$DoorType[DoorType.StrongWooden.ordinal()] = 2;
      } catch (NoSuchFieldError var5) {
      }

      $SwitchMap$zombie$iso$IsoDirections = new int[IsoDirections.values().length];

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
} // namespace objects
} // namespace iso
} // namespace zombie
