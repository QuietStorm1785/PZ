#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/text/SimpleDateFormat.h"
#include "java/time/temporal/ChronoUnit.h"
#include "zombie/GameTime.h"
#include "zombie/SandboxOptions.h"
#include "zombie/debug/DebugLog.h"
#include <algorithm>

namespace zombie {
namespace iso {
namespace weather {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * TurboTuTone.
 */
class ClimateValues {
public:
 double simplexOffsetA = 0.0;
 double simplexOffsetB = 0.0;
 double simplexOffsetC = 0.0;
 double simplexOffsetD = 0.0;
 ClimateManager clim;
 GameTime gt;
 float time = 0.0F;
 float dawn = 0.0F;
 float dusk = 0.0F;
 float noon = 0.0F;
 float dayMeanTemperature = 0.0F;
 double airMassNoiseFrequencyMod = 0.0;
 float noiseAirmass = 0.0F;
 float airMassTemperature = 0.0F;
 float baseTemperature = 0.0F;
 float dayLightLagged = 0.0F;
 float nightLagged = 0.0F;
 float temperature = 0.0F;
 bool temperatureIsSnow = false;
 float humidity = 0.0F;
 float windIntensity = 0.0F;
 float windAngleIntensity = 0.0F;
 float windAngleDegrees = 0.0F;
 float nightStrength = 0.0F;
 float dayLightStrength = 0.0F;
 float ambient = 0.0F;
 float desaturation = 0.0F;
 float dayLightStrengthBase = 0.0F;
 float lerpNight = 0.0F;
 float cloudyT = 0.0F;
 float cloudIntensity = 0.0F;
 float airFrontAirmass = 0.0F;
 bool dayDoFog = false;
 float dayFogStrength = 0.0F;
 float dayFogDuration = 0.0F;
 private ClimateManager.DayInfo testCurrentDay;
 private ClimateManager.DayInfo testNextDay;
 double cacheWorldAgeHours = 0.0;
 int cacheYear;
 int cacheMonth;
 int cacheDay;
 Random seededRandom;

 public ClimateValues(ClimateManager _clim) {
 this->simplexOffsetA = _clim.getSimplexOffsetA();
 this->simplexOffsetB = _clim.getSimplexOffsetB();
 this->simplexOffsetC = _clim.getSimplexOffsetC();
 this->simplexOffsetD = _clim.getSimplexOffsetD();
 this->clim = _clim;
 this->gt = GameTime.getInstance();
 this->seededRandom = new Random(1984L);
 }

 ClimateValues getCopy() {
 ClimateValues climateValues0 = new ClimateValues(this->clim);
 this->CopyValues(climateValues0);
 return climateValues0;
 }

 void CopyValues(ClimateValues copy) {
 if (copy != this) {
 copy.time = this->time;
 copy.dawn = this->dawn;
 copy.dusk = this->dusk;
 copy.noon = this->noon;
 copy.dayMeanTemperature = this->dayMeanTemperature;
 copy.airMassNoiseFrequencyMod = this->airMassNoiseFrequencyMod;
 copy.noiseAirmass = this->noiseAirmass;
 copy.airMassTemperature = this->airMassTemperature;
 copy.baseTemperature = this->baseTemperature;
 copy.dayLightLagged = this->dayLightLagged;
 copy.nightLagged = this->nightLagged;
 copy.temperature = this->temperature;
 copy.temperatureIsSnow = this->temperatureIsSnow;
 copy.humidity = this->humidity;
 copy.windIntensity = this->windIntensity;
 copy.windAngleIntensity = this->windAngleIntensity;
 copy.windAngleDegrees = this->windAngleDegrees;
 copy.nightStrength = this->nightStrength;
 copy.dayLightStrength = this->dayLightStrength;
 copy.ambient = this->ambient;
 copy.desaturation = this->desaturation;
 copy.dayLightStrengthBase = this->dayLightStrengthBase;
 copy.lerpNight = this->lerpNight;
 copy.cloudyT = this->cloudyT;
 copy.cloudIntensity = this->cloudIntensity;
 copy.airFrontAirmass = this->airFrontAirmass;
 copy.dayDoFog = this->dayDoFog;
 copy.dayFogStrength = this->dayFogStrength;
 copy.dayFogDuration = this->dayFogDuration;
 copy.cacheWorldAgeHours = this->cacheWorldAgeHours;
 copy.cacheYear = this->cacheYear;
 copy.cacheMonth = this->cacheMonth;
 copy.cacheDay = this->cacheDay;
 }
 }

 void print() {
 DebugLog.log("==================================================");
 DebugLog.log("Current time of day = " + this->gt.getTimeOfDay());
 DebugLog.log("Current Worldagehours = " + this->gt.getWorldAgeHours());
 DebugLog.log("--------------------------------------------------");
 if (this->testCurrentDay.empty()) {
 GregorianCalendar gregorianCalendar = new GregorianCalendar(this->cacheYear, this->cacheMonth, this->cacheDay);
 DebugLog.log("Printing climate values for: " + new SimpleDateFormat("yyyy MM dd").format(gregorianCalendar.getTime()));
 } else {
 DebugLog.log("Printing climate values for: " + new SimpleDateFormat("yyyy MM dd").format(this->testCurrentDay.calendar.getTime()));
 }

 DebugLog.log("--------------------------------------------------");
 DebugLog.log("Poll Worldagehours = " + this->cacheWorldAgeHours);
 DebugLog.log("Poll time = " + this->time);
 DebugLog.log("dawn = " + this->dawn);
 DebugLog.log("dusk = " + this->dusk);
 DebugLog.log("noon = " + this->noon);
 DebugLog.log("daymeantemperature = " + this->dayMeanTemperature);
 DebugLog.log("airMassNoiseFrequencyMod = " + this->airMassNoiseFrequencyMod);
 DebugLog.log("noiseAirmass = " + this->noiseAirmass);
 DebugLog.log("airMassTemperature = " + this->airMassTemperature);
 DebugLog.log("baseTemperature = " + this->baseTemperature);
 DebugLog.log("dayLightLagged = " + this->dayLightLagged);
 DebugLog.log("nightLagged = " + this->nightLagged);
 DebugLog.log("temperature = " + this->temperature);
 DebugLog.log("temperatureIsSnow = " + this->temperatureIsSnow);
 DebugLog.log("humidity = " + this->humidity);
 DebugLog.log("windIntensity = " + this->windIntensity);
 DebugLog.log("windAngleIntensity = " + this->windAngleIntensity);
 DebugLog.log("windAngleDegrees = " + this->windAngleDegrees);
 DebugLog.log("nightStrength = " + this->nightStrength);
 DebugLog.log("dayLightStrength = " + this->dayLightStrength);
 DebugLog.log("ambient = " + this->ambient);
 DebugLog.log("desaturation = " + this->desaturation);
 DebugLog.log("dayLightStrengthBase = " + this->dayLightStrengthBase);
 DebugLog.log("lerpNight = " + this->lerpNight);
 DebugLog.log("cloudyT = " + this->cloudyT);
 DebugLog.log("cloudIntensity = " + this->cloudIntensity);
 DebugLog.log("airFrontAirmass = " + this->airFrontAirmass);
 }

 void pollDate(int year, int month, int dayOfMonth) {
 this->pollDate(year, month, dayOfMonth, 0, 0);
 }

 void pollDate(int year, int month, int dayOfMonth, int hourOfDay) {
 this->pollDate(year, month, dayOfMonth, hourOfDay, 0);
 }

 void pollDate(int year, int month, int dayOfMonth, int hourOfDay, int minute) {
 this->pollDate(new GregorianCalendar(year, month, dayOfMonth, hourOfDay, minute);
 }

 void pollDate(GregorianCalendar calendar) {
 if (this->testCurrentDay.empty()) {
 this->testCurrentDay = new ClimateManager.DayInfo();
 }

 if (this->testNextDay.empty()) {
 this->testNextDay = new ClimateManager.DayInfo();
 }

 double double0 = this->gt.getWorldAgeHours();
 this->clim.setDayInfo(this->testCurrentDay, calendar.get(5), calendar.get(2), calendar.get(1), 0);
 this->clim.setDayInfo(this->testNextDay, calendar.get(5), calendar.get(2), calendar.get(1), 1);
 GregorianCalendar gregorianCalendar = new GregorianCalendar(
 this->gt.getYear(), this->gt.getMonth(), this->gt.getDayPlusOne(), this->gt.getHour(), this->gt.getMinutes()
 );
 double double1 = ChronoUnit.MINUTES.between(gregorianCalendar.toInstant(), calendar.toInstant());
 double1 /= 60.0;
 double double2 = double0 + double1;
 float float0 = calendar.get(11) + calendar.get(12) / 60.0F;
 this->updateValues(double2, float0, this->testCurrentDay, this->testNextDay);
 }

 void updateValues(double double0, float float4, ClimateManager.DayInfo dayInfo0, ClimateManager.DayInfo dayInfo1) {
 if (dayInfo0.year != this->cacheYear || dayInfo0.month != this->cacheMonth || dayInfo0.day != this->cacheDay) {
 int int0 = (int)this->clim.getSimplexOffsetC();
 int int1 = (int)this->clim.getSimplexOffsetD();
 long long0 = (dayInfo0.year - 1990) * 100000;
 long0 += dayInfo0.month * dayInfo0.day * 1234;
 long0 += (dayInfo0.year - 1990) * dayInfo0.month * 10000;
 long0 += (int1 - int0) * dayInfo0.day;
 this->seededRandom.setSeed(long0);
 this->dayFogStrength = 0.0F;
 this->dayDoFog = false;
 this->dayFogDuration = 0.0F;
 float float0 = this->seededRandom.nextInt(1000);
 this->dayDoFog = float0 < 200.0F;
 if (this->dayDoFog) {
 this->dayFogDuration = 4.0F;
 if (float0 < 25.0F) {
 this->dayFogStrength = 1.0F;
 this->dayFogDuration += 2.0F;
 } else {
 this->dayFogStrength = this->seededRandom.nextFloat();
 }

 float float1 = dayInfo0.season.getDayMeanTemperature();
 float float2 = (float)SimplexNoise.noise(
 this->simplexOffsetA, (double0 + 12.0 - 48.0) / this->clim.getAirMassNoiseFrequencyMod(SandboxOptions.instance.getRainModifier())
 );
 float1 += float2 * 8.0F;
 float float3 = this->seededRandom.nextFloat();
 if (float1 < 0.0F) {
 this->dayFogDuration = this->dayFogDuration + 5.0F * this->dayFogStrength;
 this->dayFogDuration += 8.0F * float3;
 } else if (float1 < 10.0F) {
 this->dayFogDuration = this->dayFogDuration + 2.5F * this->dayFogStrength;
 this->dayFogDuration += 5.0F * float3;
 } else if (float1 < 20.0F) {
 this->dayFogDuration = this->dayFogDuration + 1.5F * this->dayFogStrength;
 this->dayFogDuration += 2.5F * float3;
 } else {
 this->dayFogDuration = this->dayFogDuration + 1.0F * this->dayFogStrength;
 this->dayFogDuration += 1.0F * float3;
 }

 if (this->dayFogDuration > 24.0F - dayInfo0.season.getDawn()) {
 this->dayFogDuration = 24.0F - dayInfo0.season.getDawn() - 1.0F;
 }
 }
 }

 this->cacheWorldAgeHours = double0;
 this->cacheYear = dayInfo0.year;
 this->cacheMonth = dayInfo0.month;
 this->cacheDay = dayInfo0.day;
 this->time = float4;
 this->dawn = dayInfo0.season.getDawn();
 this->dusk = dayInfo0.season.getDusk();
 this->noon = dayInfo0.season.getDayHighNoon();
 this->dayMeanTemperature = dayInfo0.season.getDayMeanTemperature();
 float float5 = float4 / 24.0F;
 float float6 = ClimateManager.lerp(float5, dayInfo0.season.getCurDayPercent(), dayInfo1.season.getCurDayPercent());
 this->airMassNoiseFrequencyMod = this->clim.getAirMassNoiseFrequencyMod(SandboxOptions.instance.getRainModifier());
 this->noiseAirmass = (float)SimplexNoise.noise(this->simplexOffsetA, double0 / this->airMassNoiseFrequencyMod);
 float float7 = (float)SimplexNoise.noise(this->simplexOffsetC, double0 / this->airMassNoiseFrequencyMod);
 this->airMassTemperature = (float)SimplexNoise.noise(this->simplexOffsetA, (double0 - 48.0) / this->airMassNoiseFrequencyMod);
 double double1 = Math.floor(double0) + 12.0;
 this->airFrontAirmass = (float)SimplexNoise.noise(this->simplexOffsetA, double1 / this->airMassNoiseFrequencyMod);
 float float8 = ClimateManager.clerp(float5, dayInfo0.season.getDayTemperature(), dayInfo1.season.getDayTemperature());
 float float9 = ClimateManager.clerp(float5, dayInfo0.season.getDayMeanTemperature(), dayInfo1.season.getDayMeanTemperature());
 bool boolean0 = float8 < float9;
 this->baseTemperature = float9 + this->airMassTemperature * 8.0F;
 float float10 = 4.0F;
 float float11 = this->dusk + float10;
 if (float11 >= 24.0F) {
 float11 -= 24.0F;
 }

 this->dayLightLagged = this->clim.getTimeLerpHours(float4, this->dawn + float10, float11, true);
 float float12 = 5.0F * (1.0F - this->dayLightLagged);
 this->nightLagged = this->clim.getTimeLerpHours(float4, float11, this->dawn + float10, true);
 float12 += 5.0F * this->nightLagged;
 this->temperature = this->baseTemperature + 1.0F - float12;
 if (!(this->temperature < 0.0F) && !ClimateManager.WINTER_IS_COMING) {
 this->temperatureIsSnow = false;
 } else {
 this->temperatureIsSnow = true;
 }

 float float13 = this->temperature;
 float13 = (45.0F - float13) / 90.0F;
 float13 = ClimateManager.clamp01(1.0F - float13);
 float float14 = (1.0F + float7) * 0.5F;
 this->humidity = float14 * float13;
 float float15 = 1.0F - (this->airMassTemperature + 1.0F) * 0.5F;
 float float16 = 1.0F - float6 * 0.4F;
 float float17 = (float)SimplexNoise.noise(double0 / 40.0, this->simplexOffsetA);
 float float18 = (float17 + 1.0F) * 0.5F;
 float18 *= float15 * float16;
 float18 *= 0.65F;
 this->windIntensity = float18;
 float float19 = (float)SimplexNoise.noise(double0 / 80.0, this->simplexOffsetB);
 this->windAngleIntensity = float19;
 float float20 = (float)SimplexNoise.noise(double0 / 40.0, this->simplexOffsetD);
 float20 = (float20 + 1.0F) * 0.5F;
 this->windAngleDegrees = 360.0F * float20;
 this->lerpNight = this->clim.getTimeLerpHours(float4, this->dusk, this->dawn, true);
 this->lerpNight = ClimateManager.clamp(0.0F, 1.0F, this->lerpNight * 2.0F);
 this->nightStrength = this->lerpNight;
 this->dayLightStrengthBase = 1.0F - this->nightStrength;
 float float21 = 1.0F - 0.15F * float6 - 0.2F * this->windIntensity;
 this->dayLightStrengthBase *= float21;
 this->dayLightStrength = this->dayLightStrengthBase;
 this->ambient = this->dayLightStrength;
 float float22 = (1.0F - dayInfo0.season.getCurDayPercent()) * 0.4F;
 float float23 = (1.0F - dayInfo1.season.getCurDayPercent()) * 0.4F;
 this->desaturation = ClimateManager.lerp(float5, float22, float23);
 this->cloudyT = 1.0F - ClimateManager.clamp01((this->airMassTemperature + 0.8F) * 0.625F);
 this->cloudyT *= 0.8F;
 this->cloudyT = ClimateManager.clamp01(this->cloudyT + this->windIntensity);
 this->cloudIntensity = ClimateManager.clamp01(this->windIntensity * 2.0F);
 this->cloudIntensity = this->cloudIntensity - this->cloudIntensity * 0.5F * this->nightStrength;
 }

 float getTime() {
 return this->time;
 }

 float getDawn() {
 return this->dawn;
 }

 float getDusk() {
 return this->dusk;
 }

 float getNoon() {
 return this->noon;
 }

 double getAirMassNoiseFrequencyMod() {
 return this->airMassNoiseFrequencyMod;
 }

 float getNoiseAirmass() {
 return this->noiseAirmass;
 }

 float getAirMassTemperature() {
 return this->airMassTemperature;
 }

 float getBaseTemperature() {
 return this->baseTemperature;
 }

 float getDayLightLagged() {
 return this->dayLightLagged;
 }

 float getNightLagged() {
 return this->nightLagged;
 }

 float getTemperature() {
 return this->temperature;
 }

 bool isTemperatureIsSnow() {
 return this->temperatureIsSnow;
 }

 float getHumidity() {
 return this->humidity;
 }

 float getWindIntensity() {
 return this->windIntensity;
 }

 float getWindAngleIntensity() {
 return this->windAngleIntensity;
 }

 float getWindAngleDegrees() {
 return this->windAngleDegrees;
 }

 float getNightStrength() {
 return this->nightStrength;
 }

 float getDayLightStrength() {
 return this->dayLightStrength;
 }

 float getAmbient() {
 return this->ambient;
 }

 float getDesaturation() {
 return this->desaturation;
 }

 float getDayLightStrengthBase() {
 return this->dayLightStrengthBase;
 }

 float getLerpNight() {
 return this->lerpNight;
 }

 float getCloudyT() {
 return this->cloudyT;
 }

 float getCloudIntensity() {
 return this->cloudIntensity;
 }

 float getAirFrontAirmass() {
 return this->airFrontAirmass;
 }

 double getCacheWorldAgeHours() {
 return this->cacheWorldAgeHours;
 }

 int getCacheYear() {
 return this->cacheYear;
 }

 int getCacheMonth() {
 return this->cacheMonth;
 }

 int getCacheDay() {
 return this->cacheDay;
 }

 float getDayMeanTemperature() {
 return this->dayMeanTemperature;
 }

 bool isDayDoFog() {
 return this->dayDoFog;
 }

 float getDayFogStrength() {
 return this->dayFogStrength;
 }

 float getDayFogDuration() {
 return this->dayFogDuration;
 }
}
} // namespace weather
} // namespace iso
} // namespace zombie
