#pragma once
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace util {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class PZCalendar {
public:
 const Calendar calendar;

 static PZCalendar getInstance() {
 return new PZCalendar(Calendar.getInstance());
 }

public
 PZCalendar(Calendar _calendar) {
 Objects.requireNonNull(_calendar);
 this->calendar = _calendar;
 }

 void set(int year, int month, int dayOfMonth, int hourOfDay, int minute) {
 this->calendar.set(year, month, dayOfMonth, hourOfDay, minute);
 }

 void setTimeInMillis(long millis) { this->calendar.setTimeInMillis(millis); }

 int get(int field) { return this->calendar.get(field); }

 Date getTime() { return this->calendar.getTime(); }

 long getTimeInMillis() { return this->calendar.getTimeInMillis(); }

 bool isLeapYear(int year) {
 return ((GregorianCalendar)this->calendar).isLeapYear(year);
 }
}
} // namespace util
} // namespace zombie
