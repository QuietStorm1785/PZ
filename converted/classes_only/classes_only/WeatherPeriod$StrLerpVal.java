package zombie.iso.weather;

import zombie.debug.DebugLog;

public enum WeatherPeriod$StrLerpVal {
   Entry(1),
   Target(2),
   NextTarget(3),
   None(0);

   private final int value;

   private WeatherPeriod$StrLerpVal(int var3) {
      this.value = var3;
      if (WeatherPeriod.cache.containsKey(var3)) {
         DebugLog.log("StrLerpVal WARNING: trying to add id twice. id=" + var3);
      }

      WeatherPeriod.cache.put(var3, this);
   }

   public int getValue() {
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
