#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/DebugLog.h"
#include "zombie/erosion/utils/Noise2D.h"
#include <algorithm>

namespace zombie {
namespace erosion {
namespace season {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


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
 private float[] rain = new float[]{0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F};
 double suSol;
 double wiSol;
 const GregorianCalendar zeroDay = new GregorianCalendar(1970, 0, 1, 0, 0);
 int day;
 int month;
 int year;
 bool isH1;
 private ErosionSeason.YearData[] yearData = new ErosionSeason.YearData[3];
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
 Noise2D per = new Noise2D();
 int seedA = 64;
 int seedB = 128;
 int seedC = 255;
 String[] names = new String[]{"Default", "Spring", "Early Summer", "Late Summer", "Autumn", "Winter"};

 void init(int _lat, int _tempMax, int _tempMin, int _tempDiff, int _seasonLag, float _noon, int _seedA, int _seedB, int _seedC) {
 this->lat = _lat;
 this->tempMax = _tempMax;
 this->tempMin = _tempMin;
 this->tempDiff = _tempDiff;
 this->seasonLag = _seasonLag;
 this->highNoon = _noon;
 this->highNoonCurrent = _noon;
 this->seedA = _seedA;
 this->seedB = _seedB;
 this->seedC = _seedC;
 this->summerTilt = 2.0F;
 this->winterMod = this->tempMin < 0 ? 0.05F * -this->tempMin : 0.02F * -this->tempMin;
 this->summerMod = this->tempMax < 0 ? 0.05F * this->tempMax : 0.02F * this->tempMax;
 this->suSol = 2.0 * this->degree(Math.acos(-Math.tan(this->radian(this->lat) * Math.tan(this->radian(23.44) / 15.0;
 this->wiSol = 2.0 * this->degree(Math.acos(Math.tan(this->radian(this->lat) * Math.tan(this->radian(23.44) / 15.0;
 this->per.reset();
 this->per.addLayer(_seedA, 8.0F, 2.0F);
 this->per.addLayer(_seedB, 6.0F, 4.0F);
 this->per.addLayer(_seedC, 4.0F, 6.0F);
 this->yearData[0] = new ErosionSeason.YearData();
 this->yearData[1] = new ErosionSeason.YearData();
 this->yearData[2] = new ErosionSeason.YearData();
 }

 int getLat() {
 return this->lat;
 }

 int getTempMax() {
 return this->tempMax;
 }

 int getTempMin() {
 return this->tempMin;
 }

 int getTempDiff() {
 return this->tempDiff;
 }

 int getSeasonLag() {
 return this->seasonLag;
 }

 float getHighNoon() {
 return this->highNoon;
 }

 int getSeedA() {
 return this->seedA;
 }

 int getSeedB() {
 return this->seedB;
 }

 int getSeedC() {
 return this->seedC;
 }

 public void setRain(
 float _jan, float _feb, float _mar, float _apr, float _may, float _jun, float _jul, float _aug, float _sep, float _oct, float _nov, float _dec
 ) {
 this->rain[0] = _jan;
 this->rain[1] = _feb;
 this->rain[2] = _mar;
 this->rain[3] = _apr;
 this->rain[4] = _may;
 this->rain[5] = _jun;
 this->rain[6] = _jul;
 this->rain[7] = _aug;
 this->rain[8] = _sep;
 this->rain[9] = _oct;
 this->rain[10] = _nov;
 this->rain[11] = _dec;
 float float0 = 0.0F;

 for (float float1 : this->rain) {
 float0 += float1;
 }

 this->rainYearAverage = (int)Math.floor(365.0F * (float0 / this->rain.length);
 }

 ErosionSeason clone() {
 ErosionSeason erosionSeason0 = new ErosionSeason();
 erosionSeason0.init(this->lat, this->tempMax, this->tempMin, this->tempDiff, this->seasonLag, this->highNoon, this->seedA, this->seedB, this->seedC);
 erosionSeason0.setRain(
 this->rain[0],
 this->rain[1],
 this->rain[2],
 this->rain[3],
 this->rain[4],
 this->rain[5],
 this->rain[6],
 this->rain[7],
 this->rain[8],
 this->rain[9],
 this->rain[10],
 this->rain[11]
 );
 return erosionSeason0;
 }

 float getCurDayPercent() {
 return this->curDayPercent;
 }

 double getMaxDaylightWinter() {
 return this->wiSol;
 }

 double getMaxDaylightSummer() {
 return this->suSol;
 }

 float getDusk() {
 return this->dayDusk;
 }

 float getDawn() {
 return this->dayDawn;
 }

 float getDaylight() {
 return this->dayDaylight;
 }

 float getDayTemperature() {
 return this->dayTemperature;
 }

 float getDayMeanTemperature() {
 return this->dayMeanTemperature;
 }

 int getSeason() {
 return this->curSeason;
 }

 float getDayHighNoon() {
 return this->highNoonCurrent;
 }

 std::string getSeasonName() {
 return this->names[this->curSeason];
 }

 bool isSeason(int _season) {
 return _season = = this->curSeason;
 }

 GregorianCalendar getWinterStartDay(int _day, int _month, int _year) {
 GregorianCalendar gregorianCalendar = new GregorianCalendar(_year, _month, _day);
 long long0 = gregorianCalendar.getTime().getTime();
 return long0 < this->yearData[0].winterEndDayUnx ? this->yearData[0].winterStartDay : this->yearData[1].winterStartDay;
 }

 float getSeasonDay() {
 return this->curSeasonDay;
 }

 float getSeasonDays() {
 return this->curSeasonDays;
 }

 float getSeasonStrength() {
 return this->curSeasonStrength;
 }

 float getSeasonProgression() {
 return this->curSeasonProgression;
 }

 float getDayNoiseVal() {
 return this->dayNoiseVal;
 }

 bool isRainDay() {
 return this->isRainDay;
 }

 float getRainDayStrength() {
 return this->rainDayStrength;
 }

 float getRainYearAverage() {
 return this->rainYearAverage;
 }

 bool isThunderDay() {
 return this->isThunderDay;
 }

 bool isSunnyDay() {
 return this->isSunnyDay;
 }

 void setDay(int _day, int _month, int _year) {
 if (_year == 0) {
 DebugLog.log("NOTICE: year value is 0?");
 }

 GregorianCalendar gregorianCalendar = new GregorianCalendar(_year, _month, _day, 0, 0);
 long long0 = gregorianCalendar.getTime().getTime();
 this->setYearData(_year);
 this->setSeasonData((float)long0, gregorianCalendar, _year, _month);
 this->setDaylightData(long0, gregorianCalendar);
 }

 void setYearData(int int0) {
 if (this->yearData[1].year != int0) {
 for (int int1 = 0; int1 < 3; int1++) {
 int int2 = int1 - 1;
 int int3 = int0 + int2;
 this->yearData[int1].year = int3;
 this->yearData[int1].winSols = new GregorianCalendar(int3, 11, 22);
 this->yearData[int1].sumSols = new GregorianCalendar(int3, 5, 22);
 this->yearData[int1].winSolsUnx = this->yearData[int1].winSols.getTime().getTime();
 this->yearData[int1].sumSolsUnx = this->yearData[int1].sumSols.getTime().getTime();
 this->yearData[int1].hottestDay = new GregorianCalendar(int3, 5, 22);
 this->yearData[int1].coldestDay = new GregorianCalendar(int3, 11, 22);
 this->yearData[int1].hottestDay.add(5, this->seasonLag);
 this->yearData[int1].coldestDay.add(5, this->seasonLag);
 this->yearData[int1].hottestDayUnx = this->yearData[int1].hottestDay.getTime().getTime();
 this->yearData[int1].coldestDayUnx = this->yearData[int1].coldestDay.getTime().getTime();
 this->yearData[int1].winterS = this->per.layeredNoise(64 + int3, 64.0F);
 this->yearData[int1].winterE = this->per.layeredNoise(64.0F, 64 + int3);
 this->yearData[int1].winterStartDay = new GregorianCalendar(int3, 11, 22);
 this->yearData[int1].winterEndDay = new GregorianCalendar(int3, 11, 22);
 this->yearData[int1].winterStartDay.add(5, (int)(-Math.floor(40.0F + 40.0F * this->winterMod + 20.0F * this->yearData[int1].winterS);
 this->yearData[int1].winterEndDay.add(5, (int)Math.floor(40.0F + 40.0F * this->winterMod + 20.0F * this->yearData[int1].winterE);
 this->yearData[int1].winterStartDayUnx = this->yearData[int1].winterStartDay.getTime().getTime();
 this->yearData[int1].winterEndDayUnx = this->yearData[int1].winterEndDay.getTime().getTime();
 this->yearData[int1].summerS = this->per.layeredNoise(128 + int3, 128.0F);
 this->yearData[int1].summerE = this->per.layeredNoise(128.0F, 128 + int3);
 this->yearData[int1].summerStartDay = new GregorianCalendar(int3, 5, 22);
 this->yearData[int1].summerEndDay = new GregorianCalendar(int3, 5, 22);
 this->yearData[int1].summerStartDay.add(5, (int)(-Math.floor(40.0F + 40.0F * this->summerMod + 20.0F * this->yearData[int1].summerS);
 this->yearData[int1].summerEndDay.add(5, (int)Math.floor(40.0F + 40.0F * this->summerMod + 20.0F * this->yearData[int1].summerE);
 this->yearData[int1].summerStartDayUnx = this->yearData[int1].summerStartDay.getTime().getTime();
 this->yearData[int1].summerEndDayUnx = this->yearData[int1].summerEndDay.getTime().getTime();
 }

 this->yearData[1].lastSummerStr = this->yearData[0].summerS + this->yearData[0].summerE - 1.0F;
 this->yearData[1].lastWinterStr = this->yearData[0].winterS + this->yearData[0].winterE - 1.0F;
 this->yearData[1].summerStr = this->yearData[1].summerS + this->yearData[1].summerE - 1.0F;
 this->yearData[1].winterStr = this->yearData[1].winterS + this->yearData[1].winterE - 1.0F;
 this->yearData[1].nextSummerStr = this->yearData[2].summerS + this->yearData[2].summerE - 1.0F;
 this->yearData[1].nextWinterStr = this->yearData[2].winterS + this->yearData[2].winterE - 1.0F;
 }
 }

 void setSeasonData(float float0, GregorianCalendar gregorianCalendar2, int var3, int int0) {
 GregorianCalendar gregorianCalendar0;
 GregorianCalendar gregorianCalendar1;
 if (float0 < (float)this->yearData[0].winterEndDayUnx) {
 this->curSeason = 5;
 gregorianCalendar0 = this->yearData[0].winterStartDay;
 gregorianCalendar1 = this->yearData[0].winterEndDay;
 } else if (float0 < (float)this->yearData[1].summerStartDayUnx) {
 this->curSeason = 1;
 gregorianCalendar0 = this->yearData[0].winterEndDay;
 gregorianCalendar1 = this->yearData[1].summerStartDay;
 } else if (float0 < (float)this->yearData[1].summerEndDayUnx) {
 this->curSeason = 2;
 gregorianCalendar0 = this->yearData[1].summerStartDay;
 gregorianCalendar1 = this->yearData[1].summerEndDay;
 } else if (float0 < (float)this->yearData[1].winterStartDayUnx) {
 this->curSeason = 4;
 gregorianCalendar0 = this->yearData[1].summerEndDay;
 gregorianCalendar1 = this->yearData[1].winterStartDay;
 } else {
 this->curSeason = 5;
 gregorianCalendar0 = this->yearData[1].winterStartDay;
 gregorianCalendar1 = this->yearData[1].winterEndDay;
 }

 this->curSeasonDay = this->dayDiff(gregorianCalendar2, gregorianCalendar0);
 this->curSeasonDays = this->dayDiff(gregorianCalendar0, gregorianCalendar1);
 this->curSeasonStrength = this->curSeasonDays / 90.0F - 1.0F;
 this->curSeasonProgression = this->curSeasonDay / this->curSeasonDays;
 float float1;
 float float2;
 float float3;
 if (float0 < (float)this->yearData[0].coldestDayUnx && float0 >= (float)this->yearData[0].hottestDayUnx) {
 float1 = this->tempMax + this->tempDiff / 2 * this->yearData[1].lastSummerStr;
 float2 = this->tempMin + this->tempDiff / 2 * this->yearData[1].lastWinterStr;
 float3 = this->dayDiff(gregorianCalendar2, this->yearData[0].hottestDay) / this->dayDiff(this->yearData[0].hottestDay, this->yearData[0].coldestDay);
 } else if (float0 < (float)this->yearData[1].hottestDayUnx && float0 >= (float)this->yearData[0].coldestDayUnx) {
 float1 = this->tempMin + this->tempDiff / 2 * this->yearData[1].lastWinterStr;
 float2 = this->tempMax + this->tempDiff / 2 * this->yearData[1].summerStr;
 float3 = this->dayDiff(gregorianCalendar2, this->yearData[0].coldestDay) / this->dayDiff(this->yearData[1].hottestDay, this->yearData[0].coldestDay);
 } else if (float0 < (float)this->yearData[1].coldestDayUnx && float0 >= (float)this->yearData[1].hottestDayUnx) {
 float1 = this->tempMax + this->tempDiff / 2 * this->yearData[1].summerStr;
 float2 = this->tempMin + this->tempDiff / 2 * this->yearData[1].winterStr;
 float3 = this->dayDiff(gregorianCalendar2, this->yearData[1].hottestDay) / this->dayDiff(this->yearData[1].hottestDay, this->yearData[1].coldestDay);
 } else {
 float1 = this->tempMin + this->tempDiff / 2 * this->yearData[1].winterStr;
 float2 = this->tempMax + this->tempDiff / 2 * this->yearData[1].nextSummerStr;
 float3 = this->dayDiff(gregorianCalendar2, this->yearData[1].coldestDay) / this->dayDiff(this->yearData[1].coldestDay, this->yearData[2].hottestDay);
 }

 float float4 = (float)this->clerp(float3, float1, float2);
 float float5 = this->dayDiff(this->zeroDay, gregorianCalendar2) / 20.0F;
 this->dayNoiseVal = this->per.layeredNoise(float5, 0.0F);
 float float6 = this->dayNoiseVal * 2.0F - 1.0F;
 this->dayTemperature = float4 + this->tempDiff * float6;
 this->dayMeanTemperature = float4;
 this->isThunderDay = false;
 this->isRainDay = false;
 this->isSunnyDay = false;
 float float7 = 0.1F + this->rain[int0] <= 1.0F ? 0.1F + this->rain[int0] : 1.0F;
 if (float7 > 0.0F && this->dayNoiseVal < float7) {
 this->isRainDay = true;
 this->rainDayStrength = 1.0F - this->dayNoiseVal / float7;
 float float8 = this->per.layeredNoise(0.0F, float5);
 if (float8 > 0.6) {
 this->isThunderDay = true;
 }
 }

 if (this->dayNoiseVal > 0.6) {
 this->isSunnyDay = true;
 }
 }

 void setDaylightData(long long0, GregorianCalendar gregorianCalendar2) {
 GregorianCalendar gregorianCalendar0;
 GregorianCalendar gregorianCalendar1;
 if (long0 < this->yearData[1].winSolsUnx && long0 >= this->yearData[1].sumSolsUnx) {
 this->isH1 = false;
 gregorianCalendar0 = this->yearData[1].sumSols;
 gregorianCalendar1 = this->yearData[1].winSols;
 } else {
 this->isH1 = true;
 if (long0 >= this->yearData[1].winSolsUnx) {
 gregorianCalendar0 = this->yearData[1].winSols;
 gregorianCalendar1 = this->yearData[2].sumSols;
 } else {
 gregorianCalendar0 = this->yearData[0].winSols;
 gregorianCalendar1 = this->yearData[1].sumSols;
 }
 }

 float float0 = this->dayDiff(gregorianCalendar2, gregorianCalendar0) / this->dayDiff(gregorianCalendar0, gregorianCalendar1);
 float float1 = float0;
 if (this->isH1) {
 this->dayDaylight = (float)this->clerp(float0, this->wiSol, this->suSol);
 } else {
 this->dayDaylight = (float)this->clerp(float0, this->suSol, this->wiSol);
 float1 = 1.0F - float0;
 }

 this->curDayPercent = float1;
 this->highNoonCurrent = this->highNoon + this->summerTilt * float1;
 this->dayDawn = this->highNoonCurrent - this->dayDaylight / 2.0F;
 this->dayDusk = this->highNoonCurrent + this->dayDaylight / 2.0F;
 }

 float dayDiff(GregorianCalendar gregorianCalendar1, GregorianCalendar gregorianCalendar0) {
 long long0 = gregorianCalendar1.getTime().getTime() - gregorianCalendar0.getTime().getTime();
 return (float)Math.abs(long0 / 86400000L);
 }

 double clerp(double double1, double double3, double double2) {
 double double0 = (1.0 - Math.cos(double1 * Math.PI) / 2.0;
 return double3 * (1.0 - double0) + double2 * double0;
 }

 double lerp(double double1, double double0, double double2) {
 return double0 + double1 * (double2 - double0);
 }

 double radian(double double0) {
 return double0 * (Math.PI / 180.0);
 }

 double degree(double double0) {
 return double0 * (180.0 / Math.PI);
 }

 static void Reset() {
 }

 void setCurSeason(int season) {
 this->curSeason = season;
 }

 private static class YearData {
 int year = Integer.MIN_VALUE;
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
 }
}
} // namespace season
} // namespace erosion
} // namespace zombie
