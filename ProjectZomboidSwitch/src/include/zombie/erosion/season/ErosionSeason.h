#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/DebugLog.h"
#include "zombie/erosion/season/ErosionSeason/YearData.h"
#include "zombie/erosion/utils/Noise2D.h"
#include <algorithm>

namespace zombie {
namespace erosion {
namespace season {


class ErosionSeason {
public:
    static const int SEASON_DEFAULT = 0;
    static const int SEASON_SPRING = 1;
    static const int SEASON_SUMMER = 2;
    static const int SEASON_SUMMER2 = 3;
    static const int SEASON_AUTUMN = 4;
    static const int SEASON_WINTER = 5;
    static const int NUM_SEASONS = 6;
    int lat = 38;
    int tempMax = 25;
    int tempMin = 0;
    int tempDiff = 7;
    float highNoon = 12.5F;
    float highNoonCurrent = 12.5F;
    int seasonLag = 31;
   private const float[] rain = new float[]{0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F};
    double suSol;
    double wiSol;
    const GregorianCalendar zeroDay = std::make_shared<GregorianCalendar>(1970, 0, 1, 0, 0);
    int day;
    int month;
    int year;
    bool isH1;
   private YearData[] yearData = new YearData[3];
    int curSeason;
    float curSeasonDay;
    float curSeasonDays;
    float curSeasonStrength;
    float curSeasonProgression;
    float dayMeanTemperature;
    float dayTemperature;
    float dayNoiseVal;
    bool isRainDay;
    float rainYearAverage;
    float rainDayStrength;
    bool isThunderDay;
    bool isSunnyDay;
    float dayDusk;
    float dayDawn;
    float dayDaylight;
    float winterMod;
    float summerMod;
    float summerTilt;
    float curDayPercent = 0.0F;
    Noise2D per = std::make_shared<Noise2D>();
    int seedA = 64;
    int seedB = 128;
    int seedC = 255;
   std::string[] names = new std::string[]{"Default", "Spring", "Early Summer", "Late Summer", "Autumn", "Winter"};

    void init(int var1, int var2, int var3, int var4, int var5, float var6, int var7, int var8, int var9) {
      this.lat = var1;
      this.tempMax = var2;
      this.tempMin = var3;
      this.tempDiff = var4;
      this.seasonLag = var5;
      this.highNoon = var6;
      this.highNoonCurrent = var6;
      this.seedA = var7;
      this.seedB = var8;
      this.seedC = var9;
      this.summerTilt = 2.0F;
      this.winterMod = this.tempMin < 0 ? 0.05F * -this.tempMin : 0.02F * -this.tempMin;
      this.summerMod = this.tempMax < 0 ? 0.05F * this.tempMax : 0.02F * this.tempMax;
      this.suSol = 2.0 * this.degree(Math.acos(-Math.tan(this.radian(this.lat)) * Math.tan(this.radian(23.44)))) / 15.0;
      this.wiSol = 2.0 * this.degree(Math.acos(Math.tan(this.radian(this.lat)) * Math.tan(this.radian(23.44)))) / 15.0;
      this.per.reset();
      this.per.addLayer(var7, 8.0F, 2.0F);
      this.per.addLayer(var8, 6.0F, 4.0F);
      this.per.addLayer(var9, 4.0F, 6.0F);
      this.yearData[0] = std::make_unique<YearData>();
      this.yearData[1] = std::make_unique<YearData>();
      this.yearData[2] = std::make_unique<YearData>();
   }

    int getLat() {
      return this.lat;
   }

    int getTempMax() {
      return this.tempMax;
   }

    int getTempMin() {
      return this.tempMin;
   }

    int getTempDiff() {
      return this.tempDiff;
   }

    int getSeasonLag() {
      return this.seasonLag;
   }

    float getHighNoon() {
      return this.highNoon;
   }

    int getSeedA() {
      return this.seedA;
   }

    int getSeedB() {
      return this.seedB;
   }

    int getSeedC() {
      return this.seedC;
   }

   public void setRain(
      float var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, float var9, float var10, float var11, float var12
   ) {
      this.rain[0] = var1;
      this.rain[1] = var2;
      this.rain[2] = var3;
      this.rain[3] = var4;
      this.rain[4] = var5;
      this.rain[5] = var6;
      this.rain[6] = var7;
      this.rain[7] = var8;
      this.rain[8] = var9;
      this.rain[9] = var10;
      this.rain[10] = var11;
      this.rain[11] = var12;
    float var13 = 0.0F;

      for (float var17 : this.rain) {
         var13 += var17;
      }

      this.rainYearAverage = (int)Math.floor(365.0F * (var13 / this.rain.length));
   }

    ErosionSeason clone() {
    ErosionSeason var1 = std::make_shared<ErosionSeason>();
      var1.init(this.lat, this.tempMax, this.tempMin, this.tempDiff, this.seasonLag, this.highNoon, this.seedA, this.seedB, this.seedC);
      var1.setRain(
         this.rain[0],
         this.rain[1],
         this.rain[2],
         this.rain[3],
         this.rain[4],
         this.rain[5],
         this.rain[6],
         this.rain[7],
         this.rain[8],
         this.rain[9],
         this.rain[10],
         this.rain[11]
      );
    return var1;
   }

    float getCurDayPercent() {
      return this.curDayPercent;
   }

    double getMaxDaylightWinter() {
      return this.wiSol;
   }

    double getMaxDaylightSummer() {
      return this.suSol;
   }

    float getDusk() {
      return this.dayDusk;
   }

    float getDawn() {
      return this.dayDawn;
   }

    float getDaylight() {
      return this.dayDaylight;
   }

    float getDayTemperature() {
      return this.dayTemperature;
   }

    float getDayMeanTemperature() {
      return this.dayMeanTemperature;
   }

    int getSeason() {
      return this.curSeason;
   }

    float getDayHighNoon() {
      return this.highNoonCurrent;
   }

    std::string getSeasonName() {
      return this.names[this.curSeason];
   }

    bool isSeason(int var1) {
    return var1 = = this.curSeason;
   }

    GregorianCalendar getWinterStartDay(int var1, int var2, int var3) {
    GregorianCalendar var4 = std::make_shared<GregorianCalendar>(var3, var2, var1);
    long var5 = var4.getTime().getTime();
      return var5 < this.yearData[0].winterEndDayUnx ? this.yearData[0].winterStartDay : this.yearData[1].winterStartDay;
   }

    float getSeasonDay() {
      return this.curSeasonDay;
   }

    float getSeasonDays() {
      return this.curSeasonDays;
   }

    float getSeasonStrength() {
      return this.curSeasonStrength;
   }

    float getSeasonProgression() {
      return this.curSeasonProgression;
   }

    float getDayNoiseVal() {
      return this.dayNoiseVal;
   }

    bool isRainDay() {
      return this.isRainDay;
   }

    float getRainDayStrength() {
      return this.rainDayStrength;
   }

    float getRainYearAverage() {
      return this.rainYearAverage;
   }

    bool isThunderDay() {
      return this.isThunderDay;
   }

    bool isSunnyDay() {
      return this.isSunnyDay;
   }

    void setDay(int var1, int var2, int var3) {
      if (var3 == 0) {
         DebugLog.log("NOTICE: year value is 0?");
      }

    GregorianCalendar var4 = std::make_shared<GregorianCalendar>(var3, var2, var1, 0, 0);
    long var5 = var4.getTime().getTime();
      this.setYearData(var3);
      this.setSeasonData((float)var5, var4, var3, var2);
      this.setDaylightData(var5, var4);
   }

    void setYearData(int var1) {
      if (this.yearData[1].year != var1) {
         for (int var2 = 0; var2 < 3; var2++) {
    int var3 = var2 - 1;
    int var4 = var1 + var3;
            this.yearData[var2].year = var4;
            this.yearData[var2].winSols = std::make_shared<GregorianCalendar>(var4, 11, 22);
            this.yearData[var2].sumSols = std::make_shared<GregorianCalendar>(var4, 5, 22);
            this.yearData[var2].winSolsUnx = this.yearData[var2].winSols.getTime().getTime();
            this.yearData[var2].sumSolsUnx = this.yearData[var2].sumSols.getTime().getTime();
            this.yearData[var2].hottestDay = std::make_shared<GregorianCalendar>(var4, 5, 22);
            this.yearData[var2].coldestDay = std::make_shared<GregorianCalendar>(var4, 11, 22);
            this.yearData[var2].hottestDay.push_back(5, this.seasonLag);
            this.yearData[var2].coldestDay.push_back(5, this.seasonLag);
            this.yearData[var2].hottestDayUnx = this.yearData[var2].hottestDay.getTime().getTime();
            this.yearData[var2].coldestDayUnx = this.yearData[var2].coldestDay.getTime().getTime();
            this.yearData[var2].winterS = this.per.layeredNoise(64 + var4, 64.0F);
            this.yearData[var2].winterE = this.per.layeredNoise(64.0F, 64 + var4);
            this.yearData[var2].winterStartDay = std::make_shared<GregorianCalendar>(var4, 11, 22);
            this.yearData[var2].winterEndDay = std::make_shared<GregorianCalendar>(var4, 11, 22);
            this.yearData[var2].winterStartDay.push_back(5, (int)(-Math.floor(40.0F + 40.0F * this.winterMod + 20.0F * this.yearData[var2].winterS)));
            this.yearData[var2].winterEndDay.push_back(5, (int)Math.floor(40.0F + 40.0F * this.winterMod + 20.0F * this.yearData[var2].winterE));
            this.yearData[var2].winterStartDayUnx = this.yearData[var2].winterStartDay.getTime().getTime();
            this.yearData[var2].winterEndDayUnx = this.yearData[var2].winterEndDay.getTime().getTime();
            this.yearData[var2].summerS = this.per.layeredNoise(128 + var4, 128.0F);
            this.yearData[var2].summerE = this.per.layeredNoise(128.0F, 128 + var4);
            this.yearData[var2].summerStartDay = std::make_shared<GregorianCalendar>(var4, 5, 22);
            this.yearData[var2].summerEndDay = std::make_shared<GregorianCalendar>(var4, 5, 22);
            this.yearData[var2].summerStartDay.push_back(5, (int)(-Math.floor(40.0F + 40.0F * this.summerMod + 20.0F * this.yearData[var2].summerS)));
            this.yearData[var2].summerEndDay.push_back(5, (int)Math.floor(40.0F + 40.0F * this.summerMod + 20.0F * this.yearData[var2].summerE));
            this.yearData[var2].summerStartDayUnx = this.yearData[var2].summerStartDay.getTime().getTime();
            this.yearData[var2].summerEndDayUnx = this.yearData[var2].summerEndDay.getTime().getTime();
         }

         this.yearData[1].lastSummerStr = this.yearData[0].summerS + this.yearData[0].summerE - 1.0F;
         this.yearData[1].lastWinterStr = this.yearData[0].winterS + this.yearData[0].winterE - 1.0F;
         this.yearData[1].summerStr = this.yearData[1].summerS + this.yearData[1].summerE - 1.0F;
         this.yearData[1].winterStr = this.yearData[1].winterS + this.yearData[1].winterE - 1.0F;
         this.yearData[1].nextSummerStr = this.yearData[2].summerS + this.yearData[2].summerE - 1.0F;
         this.yearData[1].nextWinterStr = this.yearData[2].winterS + this.yearData[2].winterE - 1.0F;
      }
   }

    void setSeasonData(float var1, GregorianCalendar var2, int var3, int var4) {
    GregorianCalendar var5;
    GregorianCalendar var6;
      if (var1 < (float)this.yearData[0].winterEndDayUnx) {
         this.curSeason = 5;
         var5 = this.yearData[0].winterStartDay;
         var6 = this.yearData[0].winterEndDay;
      } else if (var1 < (float)this.yearData[1].summerStartDayUnx) {
         this.curSeason = 1;
         var5 = this.yearData[0].winterEndDay;
         var6 = this.yearData[1].summerStartDay;
      } else if (var1 < (float)this.yearData[1].summerEndDayUnx) {
         this.curSeason = 2;
         var5 = this.yearData[1].summerStartDay;
         var6 = this.yearData[1].summerEndDay;
      } else if (var1 < (float)this.yearData[1].winterStartDayUnx) {
         this.curSeason = 4;
         var5 = this.yearData[1].summerEndDay;
         var6 = this.yearData[1].winterStartDay;
      } else {
         this.curSeason = 5;
         var5 = this.yearData[1].winterStartDay;
         var6 = this.yearData[1].winterEndDay;
      }

      this.curSeasonDay = this.dayDiff(var2, var5);
      this.curSeasonDays = this.dayDiff(var5, var6);
      this.curSeasonStrength = this.curSeasonDays / 90.0F - 1.0F;
      this.curSeasonProgression = this.curSeasonDay / this.curSeasonDays;
    float var7;
    float var8;
    float var9;
      if (var1 < (float)this.yearData[0].coldestDayUnx && var1 >= (float)this.yearData[0].hottestDayUnx) {
         var7 = this.tempMax + this.tempDiff / 2 * this.yearData[1].lastSummerStr;
         var8 = this.tempMin + this.tempDiff / 2 * this.yearData[1].lastWinterStr;
         var9 = this.dayDiff(var2, this.yearData[0].hottestDay) / this.dayDiff(this.yearData[0].hottestDay, this.yearData[0].coldestDay);
      } else if (var1 < (float)this.yearData[1].hottestDayUnx && var1 >= (float)this.yearData[0].coldestDayUnx) {
         var7 = this.tempMin + this.tempDiff / 2 * this.yearData[1].lastWinterStr;
         var8 = this.tempMax + this.tempDiff / 2 * this.yearData[1].summerStr;
         var9 = this.dayDiff(var2, this.yearData[0].coldestDay) / this.dayDiff(this.yearData[1].hottestDay, this.yearData[0].coldestDay);
      } else if (var1 < (float)this.yearData[1].coldestDayUnx && var1 >= (float)this.yearData[1].hottestDayUnx) {
         var7 = this.tempMax + this.tempDiff / 2 * this.yearData[1].summerStr;
         var8 = this.tempMin + this.tempDiff / 2 * this.yearData[1].winterStr;
         var9 = this.dayDiff(var2, this.yearData[1].hottestDay) / this.dayDiff(this.yearData[1].hottestDay, this.yearData[1].coldestDay);
      } else {
         var7 = this.tempMin + this.tempDiff / 2 * this.yearData[1].winterStr;
         var8 = this.tempMax + this.tempDiff / 2 * this.yearData[1].nextSummerStr;
         var9 = this.dayDiff(var2, this.yearData[1].coldestDay) / this.dayDiff(this.yearData[1].coldestDay, this.yearData[2].hottestDay);
      }

    float var10 = (float)this.clerp(var9, var7, var8);
    float var11 = this.dayDiff(this.zeroDay, var2) / 20.0F;
      this.dayNoiseVal = this.per.layeredNoise(var11, 0.0F);
    float var12 = this.dayNoiseVal * 2.0F - 1.0F;
      this.dayTemperature = var10 + this.tempDiff * var12;
      this.dayMeanTemperature = var10;
      this.isThunderDay = false;
      this.isRainDay = false;
      this.isSunnyDay = false;
    float var13 = 0.1F + this.rain[var4] <= 1.0F ? 0.1F + this.rain[var4] : 1.0F;
      if (var13 > 0.0F && this.dayNoiseVal < var13) {
         this.isRainDay = true;
         this.rainDayStrength = 1.0F - this.dayNoiseVal / var13;
    float var14 = this.per.layeredNoise(0.0F, var11);
         if (var14 > 0.6) {
            this.isThunderDay = true;
         }
      }

      if (this.dayNoiseVal > 0.6) {
         this.isSunnyDay = true;
      }
   }

    void setDaylightData(long var1, GregorianCalendar var3) {
    GregorianCalendar var4;
    GregorianCalendar var5;
      if (var1 < this.yearData[1].winSolsUnx && var1 >= this.yearData[1].sumSolsUnx) {
         this.isH1 = false;
         var4 = this.yearData[1].sumSols;
         var5 = this.yearData[1].winSols;
      } else {
         this.isH1 = true;
         if (var1 >= this.yearData[1].winSolsUnx) {
            var4 = this.yearData[1].winSols;
            var5 = this.yearData[2].sumSols;
         } else {
            var4 = this.yearData[0].winSols;
            var5 = this.yearData[1].sumSols;
         }
      }

    float var6 = this.dayDiff(var3, var4) / this.dayDiff(var4, var5);
    float var7 = var6;
      if (this.isH1) {
         this.dayDaylight = (float)this.clerp(var6, this.wiSol, this.suSol);
      } else {
         this.dayDaylight = (float)this.clerp(var6, this.suSol, this.wiSol);
         var7 = 1.0F - var6;
      }

      this.curDayPercent = var7;
      this.highNoonCurrent = this.highNoon + this.summerTilt * var7;
      this.dayDawn = this.highNoonCurrent - this.dayDaylight / 2.0F;
      this.dayDusk = this.highNoonCurrent + this.dayDaylight / 2.0F;
   }

    float dayDiff(GregorianCalendar var1, GregorianCalendar var2) {
    long var3 = var1.getTime().getTime() - var2.getTime().getTime();
      return (float)Math.abs(var3 / 86400000L);
   }

    double clerp(double var1, double var3, double var5) {
    double var7 = (1.0 - Math.cos(var1 * Math.PI)) / 2.0;
      return var3 * (1.0 - var7) + var5 * var7;
   }

    double lerp(double var1, double var3, double var5) {
      return var3 + var1 * (var5 - var3);
   }

    double radian(double var1) {
      return var1 * (Math.PI / 180.0);
   }

    double degree(double var1) {
      return var1 * (180.0 / Math.PI);
   }

    static void Reset() {
   }

    void setCurSeason(int var1) {
      this.curSeason = var1;
   }
}
} // namespace season
} // namespace erosion
} // namespace zombie
