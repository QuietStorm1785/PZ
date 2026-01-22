#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/DebugLog.h"

namespace zombie {
namespace iso {
namespace weather {


enum class WeatherPeriod {
   Entry(1),
   Target(2),
   NextTarget(3),
   None(0);

    const int value;

   private WeatherPeriod$StrLerpVal(int var3) {
      this.value = var3;
      if (WeatherPeriod.cache.containsKey(var3)) {
         DebugLog.log("StrLerpVal WARNING: trying to add id twice. id=" + var3);
      }

      WeatherPeriod.cache.put(var3, this);
   }

    int getValue() {
      return this.value;
   }

   public static WeatherPeriod$StrLerpVal fromValue(int var0) {
      if (WeatherPeriod.cache.containsKey(var0)) {
         return (WeatherPeriod$StrLerpVal)WeatherPeriod.cache.get(var0);
      } else {
         DebugLog.log("StrLerpVal, trying to get from invalid id: " + var0);
    return None;
      }
   }
}
} // namespace weather
} // namespace iso
} // namespace zombie
