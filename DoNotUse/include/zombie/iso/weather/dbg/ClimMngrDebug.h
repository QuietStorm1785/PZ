#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/text/SimpleDateFormat.h"
#include "zombie/GameTime.h"
#include "zombie/SandboxOptions.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/Rand.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/erosion/season/ErosionSeason.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/iso/weather/ClimateManager/AirFront.h"
#include "zombie/iso/weather/SimplexNoise.h"
#include "zombie/iso/weather/WeatherPeriod.h"
#include "zombie/iso/weather/WeatherPeriod/WeatherStage.h"
#include "zombie/iso/weather/dbg/ClimMngrDebug/RecordInfo.h"
#include "zombie/iso/weather/dbg/ClimMngrDebug/RunInfo.h"
#include "zombie/network/GameClient.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace weather {
namespace dbg {


class ClimMngrDebug : public ClimateManager {
public:
    GregorianCalendar calendar;
    double worldAgeHours = 0.0;
    double worldAgeHoursStart = 0.0;
    double weatherPeriodTime = 0.0;
    double simplexOffsetA;
    AirFront currentFront;
    WeatherPeriod weatherPeriod;
    bool tickIsDayChange = false;
   public std::vector<RunInfo> runs = std::make_unique<std::vector<>>();
    RunInfo currentRun;
    ErosionSeason season;
    int TotalDaysPeriodIndexMod = 5;
    bool DoOverrideSandboxRainMod = false;
    int SandboxRainModOverride = 3;
    int durDays = 0;
    static const int WEATHER_NORMAL = 0;
    static const int WEATHER_STORM = 1;
    static const int WEATHER_TROPICAL = 2;
    static const int WEATHER_BLIZZARD = 3;
    FileWriter writer;

    public ClimMngrDebug() {
      this.currentFront = std::make_unique<AirFront>();
      this.weatherPeriod = std::make_shared<WeatherPeriod>(this, nullptr);
      this.weatherPeriod.setPrintStuff(false);
   }

    void setRainModOverride(int var1) {
      this.DoOverrideSandboxRainMod = true;
      this.SandboxRainModOverride = var1;
   }

    void unsetRainModOverride() {
      this.DoOverrideSandboxRainMod = false;
      this.SandboxRainModOverride = 3;
   }

    void SimulateDays(int var1, int var2) {
      this.durDays = var1;
      DebugLog.log("Starting " + var2 + " simulations of " + var1 + " days per run...");
    uint8_t var3 = 0;
    uint8_t var4 = 0;
      DebugLog.log("Year: " + GameTime.instance.getYear() + ", Month: " + var3 + ", Day: " + var4);

      for (int var5 = 0; var5 < var2; var5++) {
         this.calendar = std::make_shared<GregorianCalendar>(GameTime.instance.getYear(), var3, var4, 0, 0);
         this.season = ClimateManager.getInstance().getSeason().clone();
         this.season
            .init(
               this.season.getLat(),
               this.season.getTempMax(),
               this.season.getTempMin(),
               this.season.getTempDiff(),
               this.season.getSeasonLag(),
               this.season.getHighNoon(),
               Rand.Next(0, 255),
               Rand.Next(0, 255),
               Rand.Next(0, 255)
            );
         this.simplexOffsetA = Rand.Next(0, 8000);
         this.worldAgeHours = 250.0;
         this.weatherPeriodTime = this.worldAgeHours;
         this.worldAgeHoursStart = this.worldAgeHours;
    double var6 = this.getAirMassNoiseFrequencyMod(SandboxOptions.instance.getRainModifier());
    float var8 = (float)SimplexNoise.noise(this.simplexOffsetA, this.worldAgeHours / var6);
    int var9 = var8 < 0.0F ? -1 : 1;
         this.currentFront.setFrontType(var9);
         this.weatherPeriod.stopWeatherPeriod();
    double var10 = this.worldAgeHours + 24.0;
    int var12 = var1 * 24;
         this.currentRun = std::make_shared<RunInfo>(this);
         this.currentRun.durationDays = var1;
         this.currentRun.durationHours = var12;
         this.currentRun.seedA = this.simplexOffsetA;
         this.runs.push_back(this.currentRun);

         for (int var13 = 0; var13 < var12; var13++) {
            this.tickIsDayChange = false;
            this.worldAgeHours++;
            if (this.worldAgeHours >= var10) {
               this.tickIsDayChange = true;
               var10 += 24.0;
               this.calendar.push_back(5, 1);
    int var14 = this.calendar.get(5);
    int var15 = this.calendar.get(2);
    int var16 = this.calendar.get(1);
               this.season.setDay(var14, var15, var16);
            }

            this.update_sim();
         }
      }

      this.saveData();
   }

    void update_sim() {
    double var1 = this.getAirMassNoiseFrequencyMod(SandboxOptions.instance.getRainModifier());
    float var3 = (float)SimplexNoise.noise(this.simplexOffsetA, this.worldAgeHours / var1);
    int var4 = var3 < 0.0F ? -1 : 1;
      if (this.currentFront.getType() != var4) {
         if (this.worldAgeHours > this.weatherPeriodTime) {
            this.weatherPeriod.initSimulationDebug(this.currentFront, this.worldAgeHours);
            this.recordAndCloseWeatherPeriod();
         }

         this.currentFront.setFrontType(var4);
      }

      if (!WINTER_IS_COMING
         && !THE_DESCENDING_FOG
         && this.worldAgeHours >= this.worldAgeHoursStart + 72.0
         && this.worldAgeHours <= this.worldAgeHoursStart + 96.0
         && !this.weatherPeriod.isRunning()
         && this.worldAgeHours > this.weatherPeriodTime
         && Rand.Next(0, 1000) < 50) {
         this.triggerCustomWeatherStage(3, 10.0F);
      }

      if (this.tickIsDayChange) {
    double var5 = Math.floor(this.worldAgeHours) + 12.0;
    float var7 = (float)SimplexNoise.noise(this.simplexOffsetA, var5 / var1);
         var4 = var7 < 0.0F ? -1 : 1;
         if (var4 == this.currentFront.getType()) {
            this.currentFront.addDaySample(var7);
         }
      }
   }

    void recordAndCloseWeatherPeriod() {
      if (this.weatherPeriod.isRunning()) {
         if (this.worldAgeHours - this.weatherPeriodTime > 0.0) {
            this.currentRun.addRecord(this.worldAgeHours - this.weatherPeriodTime);
         }

         this.weatherPeriodTime = this.worldAgeHours + Math.ceil(this.weatherPeriod.getDuration());
    bool var1 = false;
    bool var2 = false;
    bool var3 = false;

         for (WeatherStage var5 : this.weatherPeriod.getWeatherStages()) {
            if (var5.getStageID() == 3) {
               var1 = true;
            }

            if (var5.getStageID() == 8) {
               var2 = true;
            }

            if (var5.getStageID() == 7) {
               var3 = true;
            }
         }

         this.currentRun
            .addRecord(this.currentFront.getType(), this.weatherPeriod.getDuration(), this.weatherPeriod.getFrontCache().getStrength(), var1, var2, var3);
      }

      this.weatherPeriod.stopWeatherPeriod();
   }

    bool triggerCustomWeatherStage(int var1, float var2) {
      if (!GameClient.bClient && !this.weatherPeriod.isRunning()) {
    AirFront var3 = std::make_shared<AirFront>();
         var3.setFrontType(1);
         var3.setStrength(0.95F);
         this.weatherPeriod.initSimulationDebug(var3, this.worldAgeHours, var1, var2);
         this.recordAndCloseWeatherPeriod();
    return true;
      } else {
    return false;
      }
   }

    double getAirMassNoiseFrequencyMod(int var1) {
      return this.DoOverrideSandboxRainMod ? super.getAirMassNoiseFrequencyMod(this.SandboxRainModOverride) : super.getAirMassNoiseFrequencyMod(var1);
   }

    float getRainTimeMultiplierMod(int var1) {
      return this.DoOverrideSandboxRainMod ? super.getRainTimeMultiplierMod(this.SandboxRainModOverride) : super.getRainTimeMultiplierMod(var1);
   }

    ErosionSeason getSeason() {
      return this.season;
   }

    float getDayMeanTemperature() {
      return this.season.getDayMeanTemperature();
   }

    void resetOverrides() {
   }

    RunInfo calculateTotal() {
    RunInfo var1 = std::make_shared<RunInfo>(this);
      var1.totalDaysPeriod = new int[50];
    double var2 = 0.0;
    double var4 = 0.0;
    float var6 = 0.0F;
    float var7 = 0.0F;
    float var8 = 0.0F;

      for (RunInfo var10 : this.runs) {
         if (var10.totalPeriodDuration < var1.mostDryPeriod) {
            var1.mostDryPeriod = var10.totalPeriodDuration;
         }

         if (var10.totalPeriodDuration > var1.mostWetPeriod) {
            var1.mostWetPeriod = var10.totalPeriodDuration;
         }

         var1.totalPeriodDuration = var1.totalPeriodDuration + var10.totalPeriodDuration;
         if (var10.longestPeriod > var1.longestPeriod) {
            var1.longestPeriod = var10.longestPeriod;
         }

         if (var10.shortestPeriod < var1.shortestPeriod) {
            var1.shortestPeriod = var10.shortestPeriod;
         }

         var1.totalPeriods = var1.totalPeriods + var10.totalPeriods;
         var1.averagePeriod = var1.averagePeriod + var10.averagePeriod;
         if (var10.longestEmpty > var1.longestEmpty) {
            var1.longestEmpty = var10.longestEmpty;
         }

         if (var10.shortestEmpty < var1.shortestEmpty) {
            var1.shortestEmpty = var10.shortestEmpty;
         }

         var1.totalEmpty = var1.totalEmpty + var10.totalEmpty;
         var1.averageEmpty = var1.averageEmpty + var10.averageEmpty;
         if (var10.highestStrength > var1.highestStrength) {
            var1.highestStrength = var10.highestStrength;
         }

         if (var10.lowestStrength < var1.lowestStrength) {
            var1.lowestStrength = var10.lowestStrength;
         }

         var1.averageStrength = var1.averageStrength + var10.averageStrength;
         if (var10.highestWarmStrength > var1.highestWarmStrength) {
            var1.highestWarmStrength = var10.highestWarmStrength;
         }

         if (var10.lowestWarmStrength < var1.lowestWarmStrength) {
            var1.lowestWarmStrength = var10.lowestWarmStrength;
         }

         var1.averageWarmStrength = var1.averageWarmStrength + var10.averageWarmStrength;
         if (var10.highestColdStrength > var1.highestColdStrength) {
            var1.highestColdStrength = var10.highestColdStrength;
         }

         if (var10.lowestColdStrength < var1.lowestColdStrength) {
            var1.lowestColdStrength = var10.lowestColdStrength;
         }

         var1.averageColdStrength = var1.averageColdStrength + var10.averageColdStrength;
         var1.countNormalWarm = var1.countNormalWarm + var10.countNormalWarm;
         var1.countNormalCold = var1.countNormalCold + var10.countNormalCold;
         var1.countStorm = var1.countStorm + var10.countStorm;
         var1.countTropical = var1.countTropical + var10.countTropical;
         var1.countBlizzard = var1.countBlizzard + var10.countBlizzard;

         for (int var11 = 0; var11 < var10.dayCountPeriod.length; var11++) {
            var1.dayCountPeriod[var11] = var1.dayCountPeriod[var11] + var10.dayCountPeriod[var11];
         }

         for (int var13 = 0; var13 < var10.dayCountWarmPeriod.length; var13++) {
            var1.dayCountWarmPeriod[var13] = var1.dayCountWarmPeriod[var13] + var10.dayCountWarmPeriod[var13];
         }

         for (int var14 = 0; var14 < var10.dayCountColdPeriod.length; var14++) {
            var1.dayCountColdPeriod[var14] = var1.dayCountColdPeriod[var14] + var10.dayCountColdPeriod[var14];
         }

         for (int var15 = 0; var15 < var10.dayCountEmpty.length; var15++) {
            var1.dayCountEmpty[var15] = var1.dayCountEmpty[var15] + var10.dayCountEmpty[var15];
         }

         for (int var16 = 0; var16 < var10.exceedingPeriods.size(); var16++) {
            var1.exceedingPeriods.push_back((int)var10.exceedingPeriods.get(var16));
         }

         for (int var17 = 0; var17 < var10.exceedingEmpties.size(); var17++) {
            var1.exceedingEmpties.push_back((int)var10.exceedingEmpties.get(var17));
         }

    int var18 = (int)(var10.totalPeriodDuration / (this.TotalDaysPeriodIndexMod * 24));
         if (var18 < var1.totalDaysPeriod.length) {
            var1.totalDaysPeriod[var18]++;
         } else {
            DebugLog.log("Total days Period is longer than allowed array, days = " + var18 * this.TotalDaysPeriodIndexMod);
         }
      }

      if (this.runs.size() > 0) {
    int var12 = this.runs.size();
         var1.totalPeriodDuration /= var12;
         var1.averagePeriod /= var12;
         var1.averageEmpty /= var12;
         var1.averageStrength /= var12;
         var1.averageWarmStrength /= var12;
         var1.averageColdStrength /= var12;
      }

    return var1;
   }

    void saveData() {
      if (this.runs.size() > 0) {
         try {
            for (RunInfo var2 : this.runs) {
               var2.calculate();
            }

    RunInfo var22 = this.calculateTotal();
    std::string var23 = std::make_shared<SimpleDateFormat>("yyyyMMddHHmmss").format(std::make_shared<Date>());
            ZomboidFileSystem.instance.getFileInCurrentSave("climate").mkdirs();
    File var3 = ZomboidFileSystem.instance.getFileInCurrentSave("climate");
            if (var3.exists() && var3.isDirectory()) {
    std::string var4 = ZomboidFileSystem.instance.getFileNameInCurrentSave("climate", var23 + ".txt");
               DebugLog.log("Attempting to save test data to: " + var4);
    File var5 = std::make_shared<File>(var4);
               DebugLog.log("Saving climate test data: " + var4);

               try (FileWriter var6 = std::make_shared<FileWriter>(var5, false)) {
                  this.writer = var6;
    int var7 = this.runs.size();
                  this.write("Simulation results." + System.lineSeparator());
                  this.write("Runs: " + this.runs.size() + ", days per cycle: " + this.durDays);
                  if (this.DoOverrideSandboxRainMod) {
                     this.write("RainModifier used: " + this.SandboxRainModOverride);
                  } else {
                     this.write("RainModifier used: " + SandboxOptions.instance.getRainModifier());
                  }

                  this.write("");
                  this.write("===================================================================");
                  this.write(" TOTALS OVERVIEW");
                  this.write("===================================================================");
                  this.write("");
                  this.write("Total weather periods: " + var22.totalPeriods + ", average per cycle: " + var22.totalPeriods / var7);
                  this.write("Longest weather: " + this.formatDuration(var22.longestPeriod));
                  this.write("Shortest weather: " + this.formatDuration(var22.shortestPeriod));
                  this.write("Average weather: " + this.formatDuration(var22.averagePeriod));
                  this.write("");
                  this.write("Average total weather days per cycle: " + this.formatDuration(var22.totalPeriodDuration));
                  this.write("");
                  this.write("Driest cycle total weather days: " + this.formatDuration(var22.mostDryPeriod));
                  this.write("Wettest cycle total weather days: " + this.formatDuration(var22.mostWetPeriod));
                  this.write("");
                  this.write("Total clear periods: " + var22.totalEmpty + ", average per cycle: " + var22.totalEmpty / var7);
                  this.write("Longest clear: " + this.formatDuration(var22.longestEmpty));
                  this.write("Shortest clear: " + this.formatDuration(var22.shortestEmpty));
                  this.write("Average clear: " + this.formatDuration(var22.averageEmpty));
                  this.write("");
                  this.write("Highest Front strength: " + var22.highestStrength);
                  this.write("Lowest Front strength: " + var22.lowestStrength);
                  this.write("Average Front strength: " + var22.averageStrength);
                  this.write("");
                  this.write("Highest WarmFront strength: " + var22.highestWarmStrength);
                  this.write("Lowest WarmFront strength: " + var22.lowestWarmStrength);
                  this.write("Average WarmFront strength: " + var22.averageWarmStrength);
                  this.write("");
                  this.write("Highest ColdFront strength: " + var22.highestColdStrength);
                  this.write("Lowest ColdFront strength: " + var22.lowestColdStrength);
                  this.write("Average ColdFront strength: " + var22.averageColdStrength);
                  this.write("");
                  this.write("Weather period types:");
    double var8 = var7;
                  this.write("Normal warm: " + var22.countNormalWarm + ", average: " + this.round(var22.countNormalWarm / var8));
                  this.write("Normal cold: " + var22.countNormalCold + ", average: " + this.round(var22.countNormalCold / var8));
                  this.write("Normal storm: " + var22.countStorm + ", average: " + this.round((double)var22.countStorm / var7));
                  this.write("Normal tropical: " + var22.countTropical + ", average: " + this.round(var22.countTropical / var8));
                  this.write("Normal blizzard: " + var22.countBlizzard + ", average: " + this.round(var22.countBlizzard / var8));
                  this.write("");
                  this.write("Distribution duration in days (total periods)");
                  this.printCountTable(var6, var22.dayCountPeriod);
                  this.write("");
                  this.write("Distribution duration in days (WARM periods)");
                  this.printCountTable(var6, var22.dayCountWarmPeriod);
                  this.write("");
                  this.write("Distribution duration in days (COLD periods)");
                  this.printCountTable(var6, var22.dayCountColdPeriod);
                  this.write("");
                  this.write("Distribution duration in days (clear periods)");
                  this.printCountTable(var6, var22.dayCountEmpty);
                  this.write("");
                  this.write("Amount of weather periods exceeding threshold: " + var22.exceedingPeriods.size());
                  if (var22.exceedingPeriods.size() > 0) {
                     for (int var11 : var22.exceedingPeriods) {
                        this.writer.write(var11 + " days, ");
                     }
                  }

                  this.write("");
                  this.write("");
                  this.write("Amount of clear periods exceeding threshold: " + var22.exceedingEmpties.size());
                  if (var22.exceedingEmpties.size() > 0) {
                     for (int var29 : var22.exceedingEmpties) {
                        this.writer.write(var29 + " days, ");
                     }
                  }

                  this.write("");
                  this.write("");
                  this.write("Distribution duration total weather days:");
                  this.printCountTable(this.writer, var22.totalDaysPeriod, this.TotalDaysPeriodIndexMod);
                  this.writeDataExtremes();
                  this.writer = nullptr;
               } catch (Exception var20) {
                  var20.printStackTrace();
               }

               var5 = ZomboidFileSystem.instance.getFileInCurrentSave("climate", var23 + "_DATA.txt");

               try (FileWriter var26 = std::make_shared<FileWriter>(var5, false)) {
                  this.writer = var26;
                  this.writeData();
                  this.writer = nullptr;
               } catch (Exception var17) {
                  var17.printStackTrace();
               }

               var5 = ZomboidFileSystem.instance.getFileInCurrentSave("climate", var23 + "_PATTERNS.txt");

               try (FileWriter var27 = std::make_shared<FileWriter>(var5, false)) {
                  this.writer = var27;
                  this.writePatterns();
                  this.writer = nullptr;
               } catch (Exception var14) {
                  var14.printStackTrace();
               }
            }
         } catch (Exception var21) {
            var21.printStackTrace();
         }
      }
   }

    double round(double var1) {
      return Math.round(var1 * 100.0) / 100.0;
   }

    void writeRunInfo(RunInfo var1, int var2) {
      this.write("===================================================================");
      this.write(" RUN NR: " + var2);
      this.write("===================================================================");
      this.write("");
      this.write("Total weather periods: " + var1.totalPeriods);
      this.write("Longest weather: " + this.formatDuration(var1.longestPeriod));
      this.write("Shortest weather: " + this.formatDuration(var1.shortestPeriod));
      this.write("Average weather: " + this.formatDuration(var1.averagePeriod));
      this.write("");
      this.write("Total weather days for cycle: " + this.formatDuration(var1.totalPeriodDuration));
      this.write("");
      this.write("Total clear periods: " + var1.totalEmpty);
      this.write("Longest clear: " + this.formatDuration(var1.longestEmpty));
      this.write("Shortest clear: " + this.formatDuration(var1.shortestEmpty));
      this.write("Average clear: " + this.formatDuration(var1.averageEmpty));
      this.write("");
      this.write("Highest Front strength: " + var1.highestStrength);
      this.write("Lowest Front strength: " + var1.lowestStrength);
      this.write("Average Front strength: " + var1.averageStrength);
      this.write("");
      this.write("Highest WarmFront strength: " + var1.highestWarmStrength);
      this.write("Lowest WarmFront strength: " + var1.lowestWarmStrength);
      this.write("Average WarmFront strength: " + var1.averageWarmStrength);
      this.write("");
      this.write("Highest ColdFront strength: " + var1.highestColdStrength);
      this.write("Lowest ColdFront strength: " + var1.lowestColdStrength);
      this.write("Average ColdFront strength: " + var1.averageColdStrength);
      this.write("");
      this.write("Weather period types:");
      this.write("Normal warm: " + var1.countNormalWarm);
      this.write("Normal cold: " + var1.countNormalCold);
      this.write("Normal storm: " + var1.countStorm);
      this.write("Normal tropical: " + var1.countTropical);
      this.write("Normal blizzard: " + var1.countBlizzard);
      this.write("");
      this.write("Distribution duration in days (total periods)");
      this.printCountTable(this.writer, var1.dayCountPeriod);
      this.write("");
      this.write("Distribution duration in days (WARM periods)");
      this.printCountTable(this.writer, var1.dayCountWarmPeriod);
      this.write("");
      this.write("Distribution duration in days (COLD periods)");
      this.printCountTable(this.writer, var1.dayCountColdPeriod);
      this.write("");
      this.write("Distribution duration in days (clear periods)");
      this.printCountTable(this.writer, var1.dayCountEmpty);
      this.write("");
      this.write("Amount of weather periods exceeding threshold: " + var1.exceedingPeriods.size());
      if (var1.exceedingPeriods.size() > 0) {
         for (int var4 : var1.exceedingPeriods) {
            this.write(var4 + " days.");
         }
      }

      this.write("");
      this.write("Amount of clear periods exceeding threshold: " + var1.exceedingEmpties.size());
      if (var1.exceedingEmpties.size() > 0) {
         for (int var6 : var1.exceedingEmpties) {
            this.write(var6 + " days.");
         }
      }
   }

    void write(const std::string& var1) {
      this.writer.write(var1 + System.lineSeparator());
   }

    void writeDataExtremes() {
    int var1 = 0;
    int var2 = -1;
    int var3 = -1;
    RunInfo var4 = nullptr;
    RunInfo var5 = nullptr;

      for (RunInfo var7 : this.runs) {
         var1++;
         if (var4 == nullptr || var7.totalPeriodDuration < var4.totalPeriodDuration) {
            var4 = var7;
            var2 = var1;
         }

         if (var5 == nullptr || var7.totalPeriodDuration > var5.totalPeriodDuration) {
            var5 = var7;
            var3 = var1;
         }
      }

      this.write("");
      this.write("MOST DRY RUN:");
      if (var4 != nullptr) {
         this.writeRunInfo(var4, var2);
      }

      this.write("");
      this.write("MOST WET RUN:");
      if (var5 != nullptr) {
         this.writeRunInfo(var5, var3);
      }
   }

    void writeData() {
    int var1 = 0;

      for (RunInfo var3 : this.runs) {
         this.writeRunInfo(var3, ++var1);
      }
   }

    void writePatterns() {
    std::string var1 = "-";
    std::string var2 = "#";
    std::string var3 = "S";
    std::string var4 = "T";
    std::string var5 = "B";
    int var7 = 0;
    int var8 = 0;

      for (RunInfo var10 : this.runs) {
         var8 = 0;

         for (RecordInfo var12 : var10.records) {
            var7 = (int)Math.ceil(var12.durationHours / 24.0);
    std::string var6;
            if (var12.isWeather && var12.weatherType == 1) {
               var6 = new std::string(new char[var7]).replace("\u0000", var3);
            } else if (var12.isWeather && var12.weatherType == 2) {
               var6 = new std::string(new char[var7]).replace("\u0000", var4);
            } else if (var12.isWeather && var12.weatherType == 3) {
               var6 = new std::string(new char[var7]).replace("\u0000", var5);
            } else if (var8 == 0 && !var12.isWeather && var7 >= 2) {
               var6 = new std::string(new char[var7 - 1]).replace("\u0000", var1);
            } else {
               var6 = new std::string(new char[var7]).replace("\u0000", var12.isWeather ? var2 : var1);
            }

            this.writer.write(var6);
            var8++;
         }

         this.writer.write(System.lineSeparator());
      }
   }

    void printCountTable(FileWriter var1, int[] var2) {
      this.printCountTable(var1, var2, 1);
   }

    void printCountTable(FileWriter var1, int[] var2, int var3) {
      if (var2 != nullptr && var2.length > 0) {
    int var4 = 0;

         for (int var5 = 0; var5 < var2.length; var5++) {
            if (var2[var5] > var4) {
               var4 = var2[var5];
            }
         }

         this.write("    DAYS   COUNT GRAPH");
    float var6 = 50.0F / var4;
         if (var4 > 0) {
            for (int var7 = 0; var7 < var2.length; var7++) {
    std::string var10 = "";
               var10 = var10 + std::string.format("%1$8s", var7 * var3 + "-" + (var7 * var3 + var3));
    int var8 = var2[var7];
               var10 = var10 + std::string.format("%1$8s", var8);
               var10 = var10 + " ";
    int var9 = (int)(var8 * var6);
               if (var9 > 0) {
                  var10 = var10 + new std::string(new char[var9]).replace("\u0000", "#");
               } else if (var8 > 0) {
                  var10 = var10 + "*";
               }

               this.write(var10);
            }
         }
      }
   }

    std::string formatDuration(double var1) {
    int var3 = (int)(var1 / 24.0);
    int var4 = (int)(var1 - var3 * 24);
      return var3 + " days, " + var4 + " hours.";
   }
}
} // namespace dbg
} // namespace weather
} // namespace iso
} // namespace zombie
