#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace erosion {
namespace season {


class ErosionSeason {
public:
    int year = int.MIN_VALUE;
    GregorianCalendar winSols;
    GregorianCalendar sumSols;
    long winSolsUnx;
    long sumSolsUnx;
    GregorianCalendar hottestDay;
    GregorianCalendar coldestDay;
    long hottestDayUnx;
    long coldestDayUnx;
    float winterS;
    float winterE;
    GregorianCalendar winterStartDay;
    GregorianCalendar winterEndDay;
    long winterStartDayUnx;
    long winterEndDayUnx;
    float summerS;
    float summerE;
    GregorianCalendar summerStartDay;
    GregorianCalendar summerEndDay;
    long summerStartDayUnx;
    long summerEndDayUnx;
    float lastSummerStr;
    float lastWinterStr;
    float summerStr;
    float winterStr;
    float nextSummerStr;
    float nextWinterStr;

   private ErosionSeason$YearData() {
   }
}
} // namespace season
} // namespace erosion
} // namespace zombie
