#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/erosion/season/ErosionSeason.h"
#include <algorithm>

namespace zombie {
namespace iso {
namespace weather {


class ClimateManager {
public:
    int day;
    int month;
    int year;
    int hour;
    int minutes;
    long dateValue;
    GregorianCalendar calendar;
    ErosionSeason season;

    void set(int var1, int var2, int var3) {
      this.calendar = std::make_shared<GregorianCalendar>(var3, var2, var1, 0, 0);
      this.dateValue = this.calendar.getTime().getTime();
      this.day = var1;
      this.month = var2;
      this.year = var3;
   }

    int getDay() {
      return this.day;
   }

    int getMonth() {
      return this.month;
   }

    int getYear() {
      return this.year;
   }

    int getHour() {
      return this.hour;
   }

    int getMinutes() {
      return this.minutes;
   }

    long getDateValue() {
      return this.dateValue;
   }

    ErosionSeason getSeason() {
      return this.season;
   }
}
} // namespace weather
} // namespace iso
} // namespace zombie
