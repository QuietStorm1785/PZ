#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace util {


class PZCalendar {
public:
    const Calendar calendar;

    static PZCalendar getInstance() {
      return std::make_shared<PZCalendar>(Calendar.getInstance());
   }

    public PZCalendar(Calendar var1) {
      Objects.requireNonNull(var1);
      this.calendar = var1;
   }

    void set(int var1, int var2, int var3, int var4, int var5) {
      this.calendar.set(var1, var2, var3, var4, var5);
   }

    void setTimeInMillis(long var1) {
      this.calendar.setTimeInMillis(var1);
   }

    int get(int var1) {
      return this.calendar.get(var1);
   }

    Date getTime() {
      return this.calendar.getTime();
   }

    long getTimeInMillis() {
      return this.calendar.getTimeInMillis();
   }

    bool isLeapYear(int var1) {
      return ((GregorianCalendar)this.calendar).isLeapYear(var1);
   }
}
} // namespace util
} // namespace zombie
