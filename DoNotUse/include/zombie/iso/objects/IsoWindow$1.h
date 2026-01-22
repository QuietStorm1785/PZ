#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/objects/IsoWindow/WindowType.h"

namespace zombie {
namespace iso {
namespace objects {


// $VF: synthetic class
class IsoWindow {
public:
   static {
      try {
         $SwitchMap$zombie$iso$objects$IsoWindow$WindowType[WindowType.SinglePane.ordinal()] = 1;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$iso$objects$IsoWindow$WindowType[WindowType.DoublePane.ordinal()] = 2;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
