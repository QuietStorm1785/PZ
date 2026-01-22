#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/weather/WeatherPeriod/StrLerpVal.h"

namespace zombie {
namespace iso {
namespace weather {


// $VF: synthetic class
class WeatherPeriod {
public:
   static {
      try {
         $SwitchMap$zombie$iso$weather$WeatherPeriod$StrLerpVal[StrLerpVal.Entry.ordinal()] = 1;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$zombie$iso$weather$WeatherPeriod$StrLerpVal[StrLerpVal.Target.ordinal()] = 2;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$iso$weather$WeatherPeriod$StrLerpVal[StrLerpVal.NextTarget.ordinal()] = 3;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$iso$weather$WeatherPeriod$StrLerpVal[StrLerpVal.None.ordinal()] = 4;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace weather
} // namespace iso
} // namespace zombie
