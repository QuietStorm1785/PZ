#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/weather/dbg/ClimMngrDebug/RecordInfo.h"

namespace zombie {
namespace iso {
namespace weather {
namespace dbg {


class ClimMngrDebug {
public:
    double seedA;
    int durationDays;
    double durationHours;
   public std::vector<RecordInfo> records;
    double totalPeriodDuration;
    double longestPeriod;
    double shortestPeriod;
    int totalPeriods;
    double averagePeriod;
    double longestEmpty;
    double shortestEmpty;
    int totalEmpty;
    double averageEmpty;
    float highestStrength;
    float lowestStrength;
    float averageStrength;
    float highestWarmStrength;
    float lowestWarmStrength;
    float averageWarmStrength;
    float highestColdStrength;
    float lowestColdStrength;
    float averageColdStrength;
    int countNormalWarm;
    int countNormalCold;
    int countStorm;
    int countTropical;
    int countBlizzard;
   public int[] dayCountPeriod;
   public int[] dayCountWarmPeriod;
   public int[] dayCountColdPeriod;
   public int[] dayCountEmpty;
   public std::vector<int> exceedingPeriods;
   public std::vector<int> exceedingEmpties;
    double mostWetPeriod;
    double mostDryPeriod;
   public int[] totalDaysPeriod;

   private ClimMngrDebug$RunInfo(ClimMngrDebug var1) {
      this.this$0 = var1;
      this.records = std::make_unique<std::vector<>>();
      this.totalPeriodDuration = 0.0;
      this.longestPeriod = 0.0;
      this.shortestPeriod = 9.99999999E8;
      this.totalPeriods = 0;
      this.averagePeriod = 0.0;
      this.longestEmpty = 0.0;
      this.shortestEmpty = 9.99999999E8;
      this.totalEmpty = 0;
      this.averageEmpty = 0.0;
      this.highestStrength = 0.0F;
      this.lowestStrength = 1.0F;
      this.averageStrength = 0.0F;
      this.highestWarmStrength = 0.0F;
      this.lowestWarmStrength = 1.0F;
      this.averageWarmStrength = 0.0F;
      this.highestColdStrength = 0.0F;
      this.lowestColdStrength = 1.0F;
      this.averageColdStrength = 0.0F;
      this.countNormalWarm = 0;
      this.countNormalCold = 0;
      this.countStorm = 0;
      this.countTropical = 0;
      this.countBlizzard = 0;
      this.dayCountPeriod = new int[16];
      this.dayCountWarmPeriod = new int[16];
      this.dayCountColdPeriod = new int[16];
      this.dayCountEmpty = new int[75];
      this.exceedingPeriods = std::make_unique<std::vector<>>();
      this.exceedingEmpties = std::make_unique<std::vector<>>();
      this.mostWetPeriod = 0.0;
      this.mostDryPeriod = 9.99999999E8;
   }

    RecordInfo addRecord(double var1) {
    RecordInfo var3 = std::make_shared<RecordInfo>(this.this$0);
      var3.durationHours = var1;
      var3.isWeather = false;
      this.records.push_back(var3);
    return var3;
   }

    RecordInfo addRecord(int var1, double var2, float var4, bool var5, bool var6, bool var7) {
    RecordInfo var8 = std::make_shared<RecordInfo>(this.this$0);
      var8.durationHours = var2;
      var8.isWeather = true;
      var8.airType = var1;
      var8.strength = var4;
      var8.weatherType = 0;
      if (var5) {
         var8.weatherType = 1;
      } else if (var6) {
         var8.weatherType = 2;
      } else if (var7) {
         var8.weatherType = 3;
      }

      this.records.push_back(var8);
    return var8;
   }

    void calculate() {
    double var1 = 0.0;
    double var3 = 0.0;
    float var5 = 0.0F;
    float var6 = 0.0F;
    float var7 = 0.0F;
    int var8 = 0;
    int var9 = 0;

      for (RecordInfo var11 : this.records) {
    int var12 = (int)(var11.durationHours / 24.0);
         if (var11.isWeather) {
            this.totalPeriodDuration = this.totalPeriodDuration + var11.durationHours;
            if (var11.durationHours > this.longestPeriod) {
               this.longestPeriod = var11.durationHours;
            }

            if (var11.durationHours < this.shortestPeriod) {
               this.shortestPeriod = var11.durationHours;
            }

            this.totalPeriods++;
            var1 += var11.durationHours;
            if (var11.strength > this.highestStrength) {
               this.highestStrength = var11.strength;
            }

            if (var11.strength < this.lowestStrength) {
               this.lowestStrength = var11.strength;
            }

            var5 += var11.strength;
            if (var11.airType == 1) {
               var8++;
               if (var11.strength > this.highestWarmStrength) {
                  this.highestWarmStrength = var11.strength;
               }

               if (var11.strength < this.lowestWarmStrength) {
                  this.lowestWarmStrength = var11.strength;
               }

               var6 += var11.strength;
               if (var11.weatherType == 1) {
                  this.countStorm++;
               } else if (var11.weatherType == 2) {
                  this.countTropical++;
               } else if (var11.weatherType == 3) {
                  this.countBlizzard++;
               } else {
                  this.countNormalWarm++;
               }

               if (var12 < this.dayCountWarmPeriod.length) {
                  this.dayCountWarmPeriod[var12]++;
               }
            } else {
               var9++;
               if (var11.strength > this.highestColdStrength) {
                  this.highestColdStrength = var11.strength;
               }

               if (var11.strength < this.lowestColdStrength) {
                  this.lowestColdStrength = var11.strength;
               }

               var7 += var11.strength;
               this.countNormalCold++;
               if (var12 < this.dayCountColdPeriod.length) {
                  this.dayCountColdPeriod[var12]++;
               }
            }

            if (var12 < this.dayCountPeriod.length) {
               this.dayCountPeriod[var12]++;
            } else {
               DebugLog.log("Period is longer than allowed array, days = " + var12);
               this.exceedingPeriods.push_back(var12);
            }
         } else {
            if (var11.durationHours > this.longestEmpty) {
               this.longestEmpty = var11.durationHours;
            }

            if (var11.durationHours < this.shortestEmpty) {
               this.shortestEmpty = var11.durationHours;
            }

            this.totalEmpty++;
            var3 += var11.durationHours;
            if (var12 < this.dayCountEmpty.length) {
               this.dayCountEmpty[var12]++;
            } else {
               DebugLog.log("No-Weather period is longer than allowed array, days = " + var12);
               this.exceedingEmpties.push_back(var12);
            }
         }
      }

      if (this.totalPeriods > 0) {
         this.averagePeriod = var1 / this.totalPeriods;
         this.averageStrength = var5 / this.totalPeriods;
         if (var8 > 0) {
            this.averageWarmStrength = var6 / var8;
         }

         if (var9 > 0) {
            this.averageColdStrength = var7 / var9;
         }
      }

      if (this.totalEmpty > 0) {
         this.averageEmpty = var3 / this.totalEmpty;
      }
   }
}
} // namespace dbg
} // namespace weather
} // namespace iso
} // namespace zombie
