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


class ClimateMoon {
public:
   private static const int[] day_year = new int[]{-1, -1, 30, 58, 89, 119, 150, 180, 211, 241, 272, 303, 333};
   private static const std::string[] moon_phase_name = new std::string[]{
      "New", "Waxing crescent", "First quarter", "Waxing gibbous", "Full", "Waning gibbous", "Third quarter", "Waning crescent"
   };
   private static const float[] units = new float[]{0.0F, 0.25F, 0.5F, 0.75F, 1.0F, 0.75F, 0.5F, 0.25F};
    static int last_year;
    static int last_month;
    static int last_day;
    static int current_phase = 0;
    static float current_float = 0.0F;
    static ClimateMoon instance = std::make_shared<ClimateMoon>();

    static ClimateMoon getInstance() {
    return instance;
   }

    static void updatePhase(int var0, int var1, int var2) {
      if (var0 != last_year || var1 != last_month || var2 != last_day) {
         last_year = var0;
         last_month = var1;
         last_day = var2;
         current_phase = getMoonPhase(var0, var1, var2);
         if (current_phase > 7) {
            current_phase = 7;
         }

         if (current_phase < 0) {
            current_phase = 0;
         }

         current_float = units[current_phase];
         DebugLog.log("Updated MoonPhase = " + getPhaseName() + ", float = " + current_float + ", int = " + current_phase);
      }
   }

    static std::string getPhaseName() {
      return moon_phase_name[current_phase];
   }

    static float getMoonFloat() {
    return current_float;
   }

    int getCurrentMoonPhase() {
    return current_phase;
   }

    static int getMoonPhase(int var0, int var1, int var2) {
      if (var1 < 0 || var1 > 12) {
         var1 = 0;
      }

    int var6 = var2 + day_year[var1];
      if (var1 > 2 && isLeapYearP(var0)) {
         var6++;
      }

    int var4 = var0 / 100 + 1;
    int var7 = var0 % 19 + 1;
    int var5 = (11 * var7 + 20 + (8 * var4 + 5) / 25 - 5 - (3 * var4 / 4 - 12)) % 30;
      if (var5 <= 0) {
         var5 += 30;
      }

      if (var5 == 25 && var7 > 11 || var5 == 24) {
         var5++;
      }

      return ((var6 + var5) * 6 + 11) % 177 / 22 & 7;
   }

    static int daysInMonth(int var0, int var1) {
    int var2 = 31;
      switch (var0) {
         case 2:
            var2 = isLeapYearP(var1) ? 29 : 28;
         case 3:
         case 5:
         case 7:
         case 8:
         case 10:
         default:
            break;
         case 4:
         case 6:
         case 9:
         case 11:
            var2 = 30;
      }

    return var2;
   }

    static bool isLeapYearP(int var0) {
      return var0 % 4 == 0 && (var0 % 400 == 0 || var0 % 100 != 0);
   }
}
} // namespace weather
} // namespace iso
} // namespace zombie
