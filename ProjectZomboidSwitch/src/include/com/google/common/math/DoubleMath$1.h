#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/math/RoundingMode.h"

namespace com {
namespace google {
namespace common {
namespace math {


// $VF: synthetic class
class DoubleMath {
public:
   static {
      try {
         $SwitchMap$java$math$RoundingMode[RoundingMode.UNNECESSARY.ordinal()] = 1;
      } catch (NoSuchFieldError var8) {
      }

      try {
         $SwitchMap$java$math$RoundingMode[RoundingMode.FLOOR.ordinal()] = 2;
      } catch (NoSuchFieldError var7) {
      }

      try {
         $SwitchMap$java$math$RoundingMode[RoundingMode.CEILING.ordinal()] = 3;
      } catch (NoSuchFieldError var6) {
      }

      try {
         $SwitchMap$java$math$RoundingMode[RoundingMode.DOWN.ordinal()] = 4;
      } catch (NoSuchFieldError var5) {
      }

      try {
         $SwitchMap$java$math$RoundingMode[RoundingMode.UP.ordinal()] = 5;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$java$math$RoundingMode[RoundingMode.HALF_EVEN.ordinal()] = 6;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$java$math$RoundingMode[RoundingMode.HALF_UP.ordinal()] = 7;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$java$math$RoundingMode[RoundingMode.HALF_DOWN.ordinal()] = 8;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace math
} // namespace common
} // namespace google
} // namespace com
