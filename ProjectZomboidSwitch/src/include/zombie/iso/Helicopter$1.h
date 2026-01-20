#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/Helicopter/State.h"

namespace zombie {
namespace iso {


// $VF: synthetic class
class Helicopter {
public:
   static {
      try {
         $SwitchMap$zombie$iso$Helicopter$State[State.Arriving.ordinal()] = 1;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$zombie$iso$Helicopter$State[State.Hovering.ordinal()] = 2;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$iso$Helicopter$State[State.Searching.ordinal()] = 3;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$iso$Helicopter$State[State.Leaving.ordinal()] = 4;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace iso
} // namespace zombie
