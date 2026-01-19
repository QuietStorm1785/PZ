#pragma once
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/SandboxOptions.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/Rand.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/erosion/season/ErosionSeason.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
namespace weather {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * TurboTuTone.
 */
class WeatherPeriod {
public:
 static const int STAGE_START = 0;
 static const int STAGE_SHOWERS = 1;
 static const int STAGE_HEAVY_PRECIP = 2;
 static const int STAGE_STORM = 3;
 static const int STAGE_CLEARING = 4;
 static const int STAGE_MODERATE = 5;
 static const int STAGE_DRIZZLE = 6;
 static const int STAGE_BLIZZARD = 7;
 static const int STAGE_TROPICAL_STORM = 8;
 static const int STAGE_INTERMEZZO = 9;
 static const int STAGE_MODDED = 10;
 static const int STAGE_KATEBOB_STORM = 11;
 static const int STAGE_MAX = 12;
 static const float FRONT_STRENGTH_THRESHOLD = 0.1F;
 ClimateManager climateManager;
private
 ClimateManager.AirFront frontCache = new ClimateManager.AirFront();
 double startTime;
 double duration;
 double currentTime;
private
 WeatherPeriod.WeatherStage currentStage;
private
 ArrayList<WeatherPeriod.WeatherStage> weatherStages = new ArrayList<>(20);
 int weatherStageIndex = 0;
private
 Stack<WeatherPeriod.WeatherStage> stagesPool = std::make_unique<Stack<>>();
 bool isRunning = false;
 float totalProgress = 0.0F;
 float stageProgress = 0.0F;
 float weatherNoise;
 static float maxTemperatureInfluence = 7.0F;
 float temperatureInfluence = 0.0F;
 float currentStrength;
 float rainThreshold;
 float windAngleDirMod = 1.0F;
 bool isThunderStorm = false;
 bool isTropicalStorm = false;
 bool isBlizzard = false;
 float precipitationFinal = 0.0F;
 ThunderStorm thunderStorm;
 ClimateColorInfo cloudColor = new ClimateColorInfo(0.4F, 0.2F, 0.2F, 0.4F);
 ClimateColorInfo cloudColorReddish =
 new ClimateColorInfo(0.66F, 0.12F, 0.12F, 0.4F);
 ClimateColorInfo cloudColorGreenish =
 new ClimateColorInfo(0.32F, 0.48F, 0.12F, 0.4F);
 ClimateColorInfo cloudColorBlueish =
 new ClimateColorInfo(0.16F, 0.48F, 0.48F, 0.4F);
 ClimateColorInfo cloudColorPurplish =
 new ClimateColorInfo(0.66F, 0.12F, 0.66F, 0.4F);
 ClimateColorInfo cloudColorTropical =
 new ClimateColorInfo(0.4F, 0.2F, 0.2F, 0.4F);
 ClimateColorInfo cloudColorBlizzard =
 new ClimateColorInfo(0.12F, 0.13F, 0.21F, 0.5F, 0.38F, 0.4F, 0.5F, 0.8F);
 static bool PRINT_STUFF = false;
 static float kateBobStormProgress = 0.45F;
 int kateBobStormX = 2000;
 int kateBobStormY = 2000;
 Random seededRandom;
 ClimateValues climateValues;
 bool isDummy = false;
 bool hasStartedInit = false;
private
 static HashMap<Integer, WeatherPeriod.StrLerpVal> cache =
 std::make_unique<HashMap<>>();

public
 WeatherPeriod(ClimateManager climmgr, ThunderStorm ts) {
 this->climateManager = climmgr;
 this->thunderStorm = ts;

 for (int int0 = 0; int0 < 30; int0++) {
 this->stagesPool.push(new WeatherPeriod.WeatherStage());
 }

 PRINT_STUFF = true;
 this->seededRandom = new Random(1984L);
 this->climateValues = climmgr.getClimateValuesCopy();
 }

 void setDummy(bool b) { this->isDummy = b; }

 static float getMaxTemperatureInfluence() { return maxTemperatureInfluence; }

 void setKateBobStormProgress(float progress) {
 kateBobStormProgress = PZMath.clamp_01(progress);
 }

 void setKateBobStormCoords(int x, int y) {
 this->kateBobStormX = x;
 this->kateBobStormY = y;
 }

 ClimateColorInfo getCloudColorReddish() { return this->cloudColorReddish; }

 ClimateColorInfo getCloudColorGreenish() { return this->cloudColorGreenish; }

 ClimateColorInfo getCloudColorBlueish() { return this->cloudColorBlueish; }

 ClimateColorInfo getCloudColorPurplish() { return this->cloudColorPurplish; }

 ClimateColorInfo getCloudColorTropical() { return this->cloudColorTropical; }

 ClimateColorInfo getCloudColorBlizzard() { return this->cloudColorBlizzard; }

 bool isRunning() { return this->isRunning; }

 double getDuration() { return this->duration; }

public
 ClimateManager.AirFront getFrontCache() { return this->frontCache; }

 int getCurrentStageID() {
 return this->currentStage != nullptr ? this->currentStage.stageID : -1;
 }

public
 WeatherPeriod.WeatherStage getCurrentStage() { return this->currentStage; }

 double getWeatherNoise() { return this->weatherNoise; }

 float getCurrentStrength() { return this->currentStrength; }

 float getRainThreshold() { return this->rainThreshold; }

 bool isThunderStorm() { return this->isThunderStorm; }

 bool isTropicalStorm() { return this->isTropicalStorm; }

 bool isBlizzard() { return this->isBlizzard; }

 float getPrecipitationFinal() { return this->precipitationFinal; }

 ClimateColorInfo getCloudColor() { return this->cloudColor; }

 void setCloudColor(ClimateColorInfo cloudcol) { this->cloudColor = cloudcol; }

 float getTotalProgress() { return this->totalProgress; }

 float getStageProgress() { return this->stageProgress; }

 bool hasTropical() {
 for (int int0 = 0; int0 < this->weatherStages.size(); int0++) {
 if (this->weatherStages.get(int0).getStageID() == 8) {
 return true;
 }
 }

 return false;
 }

 bool hasStorm() {
 for (int int0 = 0; int0 < this->weatherStages.size(); int0++) {
 if (this->weatherStages.get(int0).getStageID() == 3) {
 return true;
 }
 }

 return false;
 }

 bool hasBlizzard() {
 for (int int0 = 0; int0 < this->weatherStages.size(); int0++) {
 if (this->weatherStages.get(int0).getStageID() == 7) {
 return true;
 }
 }

 return false;
 }

 bool hasHeavyRain() {
 for (int int0 = 0; int0 < this->weatherStages.size(); int0++) {
 if (this->weatherStages.get(int0).getStageID() == 2) {
 return true;
 }
 }

 return false;
 }

 float getTotalStrength() { return this->frontCache.getStrength(); }

public
 WeatherPeriod.WeatherStage getStageForWorldAge(double worldAgeHours) {
 for (int int0 = 0; int0 < this->weatherStages.size(); int0++) {
 if (worldAgeHours >= this->weatherStages.get(int0).getStageStart() &&
 worldAgeHours < this->weatherStages.get(int0).getStageEnd()) {
 return this->weatherStages.get(int0);
 }
 }

 return nullptr;
 }

 float getWindAngleDegrees() { return this->frontCache.getAngleDegrees(); }

 int getFrontType() { return this->frontCache.getType(); }

 void print(std::string_view string) {
 if (PRINT_STUFF && !this->isDummy) {
 DebugLog.log(string);
 }
 }

 void setPrintStuff(bool b) { PRINT_STUFF = b; }

 bool getPrintStuff() { return PRINT_STUFF; }

 void initSimulationDebug(ClimateManager.AirFront front,
 double hoursSinceStart) {
 GameTime gameTime = GameTime.getInstance();
 this->init(front, hoursSinceStart, gameTime.getYear(), gameTime.getMonth(),
 gameTime.getDayPlusOne(), -1, -1.0F);
 }

 void initSimulationDebug(ClimateManager.AirFront front,
 double hoursSinceStart, int doThisStageOnly,
 float singleStageDuration) {
 GameTime gameTime = GameTime.getInstance();
 this->init(front, hoursSinceStart, gameTime.getYear(), gameTime.getMonth(),
 gameTime.getDayPlusOne(), doThisStageOnly, singleStageDuration);
 }

 void init(ClimateManager.AirFront airFront, double double0, int int0,
 int int1, int int2) {
 this->init(airFront, double0, int0, int1, int2, -1, -1.0F);
 }

 void init(ClimateManager.AirFront airFront, double double0, int int0,
 int int1, int int2, int int3, float float0) {
 this->climateValues.pollDate(int0, int1, int2);
 this->reseed(int0, int1, int2);
 this->hasStartedInit = false;
 if (this->startInit(airFront, double0) {
 if (int3 >= 0 && int3 < 12) {
 this->createSingleStage(int3, float0);
 } else {
 this->createWeatherPattern();
 }

 LuaEventManager.triggerEvent("OnWeatherPeriodStart", this);
 this->endInit();
 }
 }

 void reseed(int int2, int int3, int int4) {
 int int0 = (int)this->climateManager.getSimplexOffsetA();
 int int1 = (int)this->climateManager.getSimplexOffsetB();
 long long0 = (int2 - 1990) * 100000;
 long0 += int3 * int4 * 1234;
 long0 += (int2 - 1990) * int3 * 10000;
 long0 += (int1 - int0) * int4;
 this->print("Reseeding weather period, new seed: " + long0);
 this->seededRandom.setSeed(long0);
 }

 float RandNext(float float0, float float1) {
 if (float0 == float1) {
 return float0;
 } else {
 if (float0 > float1) {
 float0 = float1;
 float1 = float1;
 }

 return float0 + this->seededRandom.nextFloat() * (float1 - float0);
 }
 }

 float RandNext(float float0) {
 return this->seededRandom.nextFloat() * float0;
 }

 int RandNext(int int0, int int1) {
 if (int0 == int1) {
 return int0;
 } else {
 if (int0 > int1) {
 int0 = int1;
 int1 = int1;
 }

 return int0 + this->seededRandom.nextInt(int1 - int0);
 }
 }

 int RandNext(int int0) { return this->seededRandom.nextInt(int0); }

 bool startCreateModdedPeriod(bool warmFront, float strength, float angle) {
 double double0 = GameTime.getInstance().getWorldAgeHours();
 ClimateManager.AirFront airFront = new ClimateManager.AirFront();
 float float0 = ClimateManager.clamp(0.0F, 360.0F, angle);
 airFront.setFrontType(warmFront ? 1 : -1);
 airFront.setFrontWind(float0);
 airFront.setStrength(ClimateManager.clamp01(strength);
 GameTime gameTime = GameTime.getInstance();
 this->reseed(gameTime.getYear(), gameTime.getMonth(),
 gameTime.getDayPlusOne());
 this->hasStartedInit = false;
 if (!this->startInit(airFront, double0) {
 return false;
 } else {
 this->print(
 "WeatherPeriod: Creating MODDED weather pattern with strength = " +
 this->frontCache.getStrength());
 this->clearCurrentWeatherStages();
 return true;
 }
 }

 bool endCreateModdedPeriod() {
 if (!this->endInit()) {
 return false;
 } else {
 this->linkWeatherStages();
 this->duration = 0.0;

 for (int int0 = 0; int0 < this->weatherStages.size(); int0++) {
 this->duration =
 this->duration + this->weatherStages.get(int0).stageDuration;
 }

 this->print("WeatherPeriod: Duration = " + this->duration + ".");
 this->weatherStageIndex = 0;
 this->currentStage = this->weatherStages.get(this->weatherStageIndex)
 .startStage(this->startTime);
 this->print("WeatherPeriod: PATTERN GENERATION FINISHED.");
 return true;
 }
 }

 bool startInit(ClimateManager.AirFront airFront, double double0) {
 if (!this->isRunning && !GameClient.bClient &&
 !(airFront.getStrength() < 0.1F) {
 this->startTime = double0;
 this->frontCache.copyFrom(airFront);
 if (this->frontCache.getAngleDegrees() >= 90.0F &&
 this->frontCache.getAngleDegrees() < 270.0F) {
 this->windAngleDirMod = 1.0F;
 } else {
 this->windAngleDirMod = -1.0F;
 }

 this->hasStartedInit = true;
 return true;
 } else {
 return false;
 }
 }

 bool endInit() {
 if (this->hasStartedInit && !this->isRunning && !GameClient.bClient &&
 this->weatherStages.size() > 0) {
 this->currentStrength = 0.0F;
 this->totalProgress = 0.0F;
 this->stageProgress = 0.0F;
 this->isRunning = true;
 if (GameServer.bServer && !this->isDummy) {
 this->climateManager.transmitClimatePacket(
 ClimateManager.ClimateNetAuth.ServerOnly, (byte)1, nullptr);
 }

 this->hasStartedInit = false;
 return true;
 } else {
 this->hasStartedInit = false;
 return false;
 }
 }

 void stopWeatherPeriod() {
 this->clearCurrentWeatherStages();
 this->currentStage = nullptr;
 this->resetClimateManagerOverrides();
 this->isRunning = false;
 this->totalProgress = 0.0F;
 this->stageProgress = 0.0F;
 LuaEventManager.triggerEvent("OnWeatherPeriodStop", this);
 }

 void writeNetWeatherData(ByteBuffer output) {
 output.put((byte)(this->isRunning ? 1 : 0);
 if (this->isRunning) {
 output.put((byte)(this->isThunderStorm ? 1 : 0);
 output.put((byte)(this->isTropicalStorm ? 1 : 0);
 output.put((byte)(this->isBlizzard ? 1 : 0);
 output.putFloat(this->currentStrength);
 output.putDouble(this->duration);
 output.putFloat(this->totalProgress);
 output.putFloat(this->stageProgress);
 }
 }

 void readNetWeatherData(ByteBuffer input) {
 this->isRunning = input.get() == 1;
 if (this->isRunning) {
 this->isThunderStorm = input.get() == 1;
 this->isTropicalStorm = input.get() == 1;
 this->isBlizzard = input.get() == 1;
 this->currentStrength = input.getFloat();
 this->duration = input.getDouble();
 this->totalProgress = input.getFloat();
 this->stageProgress = input.getFloat();
 } else {
 this->isThunderStorm = false;
 this->isTropicalStorm = false;
 this->isBlizzard = false;
 this->currentStrength = 0.0F;
 this->duration = 0.0;
 this->totalProgress = 0.0F;
 this->stageProgress = 0.0F;
 }
 }

public
 ArrayList<WeatherPeriod.WeatherStage> getWeatherStages() {
 return this->weatherStages;
 }

 void linkWeatherStages() {
 WeatherPeriod.WeatherStage weatherStage0 = nullptr;
 void *object = nullptr;
 WeatherPeriod.WeatherStage weatherStage1 = nullptr;

 for (int int0 = 0; int0 < this->weatherStages.size(); int0++) {
 weatherStage1 = this->weatherStages.get(int0);
 object = nullptr;
 if (int0 + 1 < this->weatherStages.size()) {
 object = this->weatherStages.get(int0 + 1);
 }

 weatherStage1.previousStage = weatherStage0;
 weatherStage1.nextStage = (WeatherPeriod.WeatherStage)object;
 weatherStage1.creationFinished = true;
 weatherStage0 = weatherStage1;
 }
 }

 void clearCurrentWeatherStages() {
 this->print("WeatherPeriod: Clearing existing stages...");

 for (WeatherPeriod.WeatherStage weatherStage : this->weatherStages) {
 weatherStage.reset();
 this->stagesPool.push(weatherStage);
 }

 this->weatherStages.clear();
 }

 void createSingleStage(int int0, float float0) {
 this->print("WeatherPeriod: Creating single stage weather pattern with "
 "strength = " +
 this->frontCache.getStrength());
 if (int0 == 8) {
 this->cloudColor = this->cloudColorTropical;
 } else if (int0 == 7) {
 this->cloudColor = this->cloudColorBlizzard;
 }

 this->clearCurrentWeatherStages();
 this->createAndAddStage(0, 1.0);
 this->createAndAddStage(int0, float0);
 this->createAndAddStage(4, 1.0);
 this->linkWeatherStages();
 this->duration = 0.0;

 for (int int1 = 0; int1 < this->weatherStages.size(); int1++) {
 this->duration =
 this->duration + this->weatherStages.get(int1).stageDuration;
 }

 this->print("WeatherPeriod: Duration = " + float0 + ".");
 this->weatherStageIndex = 0;
 this->currentStage = this->weatherStages.get(this->weatherStageIndex)
 .startStage(this->startTime);
 this->print("WeatherPeriod: PATTERN GENERATION FINISHED.");
 }

 void createWeatherPattern() {
 this->print("WeatherPeriod: Creating weather pattern with strength = " +
 this->frontCache.getStrength());
 this->clearCurrentWeatherStages();
 ErosionSeason erosionSeason = this->climateManager.getSeason();
 float float0 = this->climateValues.getDayMeanTemperature();
 this->print("WeatherPeriod: Day mean temperature = " + float0 + " C.");
 this->print("WeatherPeriod: season = " + erosionSeason.getSeasonName());
 float float1 = 0.0F;
 float float2 = 0.0F;
 float float3 = 0.0F;
 float float4 = 1.0F;
 float float5 = this->RandNext(0.0F, 100.0F);
 int int0 = erosionSeason.getSeason();
 bool boolean0 = IsoWorld.instance.getGameMode().equals("Winter is Coming");
 if (boolean0) {
 int0 = 5;
 }

 switch (int0) {
 case 1:
 if (float5 < 75.0F) {
 this->cloudColor = this->cloudColorGreenish;
 } else {
 this->cloudColor = this->cloudColorBlueish;
 }

 float1 = 75.0F;
 float2 = 10.0F;
 float3 = 0.0F;
 float4 = 1.25F;
 break;
 case 2:
 if (float5 < 25.0F) {
 this->cloudColor = this->cloudColorGreenish;
 } else {
 this->cloudColor = this->cloudColorReddish;
 }

 float1 = 60.0F;
 float2 = 55.0F;
 float3 = 0.0F;
 break;
 case 3:
 this->cloudColor = this->cloudColorReddish;
 float1 = 75.0F;
 float2 = 80.0F;
 float3 = 0.0F;
 float4 = 1.15F;
 break;
 case 4:
 if (float5 < 50.0F) {
 this->cloudColor = this->cloudColorReddish;
 } else if (float5 < 75.0F) {
 this->cloudColor = this->cloudColorPurplish;
 } else {
 this->cloudColor = this->cloudColorBlueish;
 }

 float1 = 100.0F;
 float2 = 25.0F;
 float3 = 0.0F;
 float4 = 1.35F;
 break;
 case 5:
 if (float5 < 45.0F) {
 this->cloudColor = this->cloudColorPurplish;
 } else {
 this->cloudColor = this->cloudColorBlueish;
 }

 float1 = 10.0F;
 float2 = 0.0F;
 if (float0 < 5.5F) {
 float3 = ClimateManager.clamp(0.0F, 85.0F, (5.5F - float0) * 3.0F);
 float3 += 25.0F;
 if (float0 < 2.5F) {
 float3 += 55.0F;
 } else if (float0 < 0.0F) {
 float3 += 75.0F;
 }

 if (float3 > 95.0F) {
 float3 = 95.0F;
 }
 } else {
 float3 = 0.0F;
 }

 if (boolean0) {
 if (this->frontCache.getStrength() > 0.75F) {
 float3 = 100.0F;
 } else {
 float3 = 75.0F;
 }

 if (this->frontCache.getStrength() > 0.5F) {
 float4 = 1.45F;
 }
 }
 }

 float4 *= this->climateManager.getRainTimeMultiplierMod(
 SandboxOptions.instance.getRainModifier());
 this->print(
 "WeatherPeriod: cloudColor r=" + this->cloudColor.getExterior().r +
 ", g=" + this->cloudColor.getExterior().g +
 ", b=" + this->cloudColor.getExterior().b);
 this->print("WeatherPeriod: chances, storm=" + float1 + ", tropical=" +
 float2 + ", blizzard=" + float3 + ". rainTimeMulti=" + float4);
 std::vector arrayList = new ArrayList();
 WeatherPeriod.WeatherStage weatherStage = nullptr;
 if (this->frontCache.getType() == 1) {
 this->print("WeatherPeriod: Warm to cold front selected.");
 bool boolean1 = false;
 bool boolean2 = false;
 bool boolean3 = false;
 if (this->frontCache.getStrength() > 0.75F) {
 if (float2 > 0.0F && this->RandNext(0.0F, 100.0F) < float2) {
 this->print("WeatherPeriod: tropical storm triggered.");
 boolean2 = true;
 } else if (float3 > 0.0F && this->RandNext(0.0F, 100.0F) < float3) {
 this->print("WeatherPeriod: blizzard triggered.");
 boolean1 = true;
 }
 }

 if (!boolean1 && !boolean2 && this->frontCache.getStrength() > 0.5F &&
 float1 > 0.0F && this->RandNext(0.0F, 100.0F) < float1) {
 this->print("WeatherPeriod: storm triggered.");
 boolean3 = true;
 }

 float float6 =
 this->RandNext(24.0F, 48.0F) * this->frontCache.getStrength();
 float float7 = 0.0F;
 if (boolean2) {
 arrayList.add(this->createStage(
 8,
 8.0F + this->RandNext(0.0F, 16.0F * this->frontCache.getStrength())));
 this->cloudColor = this->cloudColorTropical;
 if (this->RandNext(0.0F, 100.0F) <
 60.0F * this->frontCache.getStrength()) {
 arrayList.add(this->createStage(
 3, 5.0F + this->RandNext(0.0F,
 5.0F * this->frontCache.getStrength())));
 }

 if (this->RandNext(0.0F, 100.0F) <
 30.0F * this->frontCache.getStrength()) {
 arrayList.add(this->createStage(
 3, 5.0F + this->RandNext(0.0F,
 5.0F * this->frontCache.getStrength())));
 }
 } else if (boolean1) {
 arrayList.add(this->createStage(
 7, 24.0F +
 this->RandNext(0.0F, 24.0F * this->frontCache.getStrength())));
 this->cloudColor = this->cloudColorBlizzard;
 } else if (boolean3) {
 arrayList.add(this->createStage(
 3,
 5.0F + this->RandNext(0.0F, 5.0F * this->frontCache.getStrength())));
 if (this->RandNext(0.0F, 100.0F) <
 70.0F * this->frontCache.getStrength()) {
 arrayList.add(this->createStage(
 3, 4.0F + this->RandNext(0.0F,
 4.0F * this->frontCache.getStrength())));
 }

 if (this->RandNext(0.0F, 100.0F) <
 50.0F * this->frontCache.getStrength()) {
 arrayList.add(this->createStage(
 3, 4.0F + this->RandNext(0.0F,
 4.0F * this->frontCache.getStrength())));
 }

 if (this->RandNext(0.0F, 100.0F) <
 25.0F * this->frontCache.getStrength()) {
 arrayList.add(this->createStage(
 3, 4.0F + this->RandNext(0.0F,
 3.0F * this->frontCache.getStrength())));
 }

 if (this->RandNext(0.0F, 100.0F) <
 12.5F * this->frontCache.getStrength()) {
 arrayList.add(this->createStage(
 3, 4.0F + this->RandNext(0.0F,
 2.0F * this->frontCache.getStrength())));
 }
 }

 for (int int1 = 0; int1 < arrayList.size(); int1++) {
 float7 =
 (float)(float7 + ((WeatherPeriod.WeatherStage)arrayList.get(int1)
 .getStageDuration());
 }

 while (float7 < float6) {
 weatherStage = switch (this->RandNext(0, 10) {
 case 0 -> this->createStage(5, 1.0F + this->RandNext(0.0F, 3.0F * this->frontCache.getStrength()));
 case 1, 2, 3 -> this->createStage(1, 2.0F + this->RandNext(0.0F, 4.0F * this->frontCache.getStrength()));
 default -> this->createStage(2, 2.0F + this->RandNext(0.0F, 4.0F * this->frontCache.getStrength()));
 };
 float7 = (float)(float7 + weatherStage.getStageDuration());
 arrayList.add(weatherStage);
 }
 } else {
 this->print("WeatherPeriod: Cold to warm front selected.");
 if (this->cloudColor == this->cloudColorReddish) {
 float5 = this->RandNext(0.0F, 100.0F);
 if (float5 < 50.0F) {
 this->cloudColor = this->cloudColorBlueish;
 } else {
 this->cloudColor = this->cloudColorPurplish;
 }
 }

 float float8 = this->RandNext(12.0F, 24.0F) * this->frontCache.getStrength();
 float float9 = 0.0F;

 while (float9 < float8) {
 weatherStage = switch (this->RandNext(0, 10) {
 case 0 -> this->createStage(1, 2.0F + this->RandNext(0.0F, 3.0F * this->frontCache.getStrength()));
 case 1, 2, 3, 4 -> this->createStage(6, 2.0F + this->RandNext(0.0F, 3.0F * this->frontCache.getStrength()));
 default -> this->createStage(5, 2.0F + this->RandNext(0.0F, 3.0F * this->frontCache.getStrength()));
 };
 float9 = (float)(float9 + weatherStage.getStageDuration());
 arrayList.add(weatherStage);
 }
 }

 Collections.shuffle(arrayList, this->seededRandom);
 float float10 = this->RandNext(30.0F, 60.0F);
 this->weatherStages.add(this->createStage(0, 1.0F + this->RandNext(0.0F, 2.0F * this->frontCache.getStrength())));

 for (int int2 = 0; int2 < arrayList.size(); int2++) {
 this->weatherStages.add((WeatherPeriod.WeatherStage)arrayList.get(int2);
 if (int2 < arrayList.size() - 1 && this->RandNext(0.0F, 100.0F) < float10) {
 this->weatherStages.add(this->createStage(4, 1.0F + this->RandNext(0.0F, 2.0F * this->frontCache.getStrength())));
 this->weatherStages.add(this->createStage(9, 1.0F + this->RandNext(0.0F, 3.0F * this->frontCache.getStrength())));
 float10 = this->RandNext(30.0F, 60.0F);
 }
 }

 if (this->weatherStages.get(this->weatherStages.size() - 1).getStageID() != 9) {
 this->weatherStages.add(this->createStage(4, 2.0F + this->RandNext(0.0F, 3.0F * this->frontCache.getStrength())));
 }

 for (int int3 = 0; int3 < this->weatherStages.size(); int3++) {
 this->weatherStages.get(int3).stageDuration *= float4;
 }

 this->linkWeatherStages();
 this->duration = 0.0;

 for (int int4 = 0; int4 < this->weatherStages.size(); int4++) {
 this->duration = this->duration + this->weatherStages.get(int4).stageDuration;
 }

 this->print("WeatherPeriod: Duration = " + this->duration + ".");
 double double0 = this->startTime;

 for (int int5 = 0; int5 < this->weatherStages.size(); int5++) {
 double0 = this->weatherStages.get(int5).setStageStart(double0);
 }

 this->weatherStageIndex = 0;
 this->currentStage = this->weatherStages.get(this->weatherStageIndex).startStage(this->startTime);
 this->print("WeatherPeriod: PATTERN GENERATION FINISHED.");
 }

 public WeatherPeriod.WeatherStage createAndAddModdedStage(String moddedID, double _duration) {
 return this->createAndAddStage(10, _duration, moddedID);
 }

 public WeatherPeriod.WeatherStage createAndAddStage(int typeid, double _duration) {
 return this->createAndAddStage(typeid, _duration, nullptr);
 }

 private WeatherPeriod.WeatherStage createAndAddStage(int int0, double double0, String string) {
 if (!this->isRunning && this->hasStartedInit && (int0 != 10 || string != nullptr) {
 WeatherPeriod.WeatherStage weatherStage = this->createStage(int0, double0, string);
 this->weatherStages.add(weatherStage);
 return weatherStage;
 } else {
 return nullptr;
 }
 }

 private WeatherPeriod.WeatherStage createStage(int int0, double double0) {
 return this->createStage(int0, double0, nullptr);
 }

 private WeatherPeriod.WeatherStage createStage(int int0, double double0, String string) {
 WeatherPeriod.WeatherStage weatherStage = nullptr;
 if (!this->stagesPool.empty()) {
 weatherStage = this->stagesPool.pop();
 } else {
 weatherStage = new WeatherPeriod.WeatherStage();
 }

 weatherStage.stageID = int0;
 weatherStage.modID = string;
 weatherStage.setStageDuration(double0);
 switch (int0) {
 case 0:
 this->print("WeatherPeriod: Adding stage 'START' with "
 "duration: " +
 double0 + "%.");
 weatherStage.lerpEntryTo(
 WeatherPeriod.StrLerpVal.NextTarget);
 break;
 case 1:
 this->print("WeatherPeriod: Adding stage 'SHOWERS' with "
 "duration: " +
 double0 + "%.");
 weatherStage.targetStrength =
 this->frontCache.getStrength() * 0.5F;
 weatherStage.lerpEntryTo(
 WeatherPeriod.StrLerpVal.Target,
 WeatherPeriod.StrLerpVal.NextTarget);
 break;
 case 2:
 this->print("WeatherPeriod: Adding stage 'HEAVY_PRECIP' "
 "with duration: " +
 double0 + "%.");
 weatherStage.targetStrength =
 this->frontCache.getStrength();
 weatherStage.lerpEntryTo(WeatherPeriod.StrLerpVal.Target,
 WeatherPeriod.StrLerpVal.Target);
 break;
 case 3:
 case 11:
 this->print("WeatherPeriod: Adding stage 'STORM' with "
 "duration: " +
 double0 + "%.");
 if (int0 == 11) {
 this->print("WeatherPeriod: this storm is a kate and "
 "bob storm...");
 }

 weatherStage.targetStrength =
 this->frontCache.getStrength();
 weatherStage.lerpEntryTo(WeatherPeriod.StrLerpVal.Target,
 WeatherPeriod.StrLerpVal.Target);
 if (this->RandNext(0, 100) < 33) {
 weatherStage.fogStrength =
 0.1F + this->RandNext(0.0F, 0.4F);
 }
 break;
 case 4:
 this->print("WeatherPeriod: Adding stage 'CLEARING' with "
 "duration: " +
 double0 + "%.");
 weatherStage.targetStrength =
 this->frontCache.getStrength() * 0.25F;
 weatherStage.lerpEntryTo(WeatherPeriod.StrLerpVal.Target,
 WeatherPeriod.StrLerpVal.None);
 break;
 case 5:
 this->print("WeatherPeriod: Adding stage 'MODERATE' with "
 "duration: " +
 double0 + "%.");
 weatherStage.targetStrength =
 this->frontCache.getStrength() * 0.5F;
 weatherStage.lerpEntryTo(
 WeatherPeriod.StrLerpVal.Target,
 WeatherPeriod.StrLerpVal.NextTarget);
 break;
 case 6:
 this->print("WeatherPeriod: Adding stage 'DRIZZLE' with "
 "duration: " +
 double0 + "%.");
 weatherStage.targetStrength =
 this->frontCache.getStrength() * 0.25F;
 weatherStage.lerpEntryTo(
 WeatherPeriod.StrLerpVal.Target,
 WeatherPeriod.StrLerpVal.NextTarget);
 break;
 case 7:
 this->print("WeatherPeriod: Adding stage 'BLIZZARD' with "
 "duration: " +
 double0 + "%.");
 weatherStage.targetStrength = 1.0F;
 weatherStage.lerpEntryTo(WeatherPeriod.StrLerpVal.Target,
 WeatherPeriod.StrLerpVal.Target);
 weatherStage.fogStrength =
 0.55F + this->RandNext(0.0F, 0.2F);
 break;
 case 8:
 this->print("WeatherPeriod: Adding stage 'TROPICAL_STORM' "
 "with duration: " +
 double0 + "%.");
 weatherStage.targetStrength = 1.0F;
 weatherStage.lerpEntryTo(WeatherPeriod.StrLerpVal.Target,
 WeatherPeriod.StrLerpVal.Target);
 weatherStage.fogStrength =
 0.6F + this->RandNext(0.0F, 0.4F);
 break;
 case 9:
 this->print("WeatherPeriod: Adding stage 'INTERMEZZO' "
 "with duration: " +
 double0 + "%.");
 weatherStage.targetStrength = 0.0F;
 weatherStage.lerpEntryTo(
 WeatherPeriod.StrLerpVal.Target,
 WeatherPeriod.StrLerpVal.NextTarget);
 break;
 case 10:
 this->print("WeatherPeriod: Adding stage 'MODDED' with "
 "duration: " +
 double0 + "%.");
 LuaEventManager.triggerEvent(
 "OnInitModdedWeatherStage", this, weatherStage,
 this->frontCache.getStrength());
 break;
 default:
 this->print("WeatherPeriod Warning: trying to _INIT_ "
 "state that is not recognized, state id=" +
 int0);
 }

 return weatherStage;
 }

 void updateCurrentStage() {
 if (!this->isDummy) {
 this->isBlizzard = false;
 this->isThunderStorm = false;
 this->isTropicalStorm = false;
 switch (this->currentStage.stageID) {
 case 0:
 this->rainThreshold = 0.35F - this->frontCache.getStrength() * 0.2F;
 this->climateManager.fogIntensity.setOverride(
 0.0F, this->currentStage.linearT);
 break;
 case 1:
 this->climateManager.fogIntensity.setOverride(0.0F, 1.0F);
 float float0 =
 ClimateManager.clamp01(this->currentStage.parabolicT * 3.0F);
 this->climateManager.windIntensity.setOverride(
 0.1F * this->weatherNoise, float0);
 this->climateManager.windAngleIntensity.setOverride(0.0F, float0);
 break;
 case 2:
 float float3 = this->frontCache.getStrength() * 0.5F;
 if (this->currentStage.linearT < 0.1F) {
 float3 = ClimateManager.clerp(
 (float)((this->currentTime - this->currentStage.stageStart) /
 (this->currentStage.stageDuration * 0.1),
 0.0F, this->frontCache.getStrength() * 0.5F);
 } else if (this->currentStage.linearT > 0.9F) {
 float3 = ClimateManager.clerp(
 1.0F -
 (float)((this->currentStage.stageEnd - this->currentTime) /
 (this->currentStage.stageDuration * 0.1),
 this->frontCache.getStrength() * 0.5F, 0.0F);
 }

 this->weatherNoise = float3 + this->weatherNoise * (1.0F - float3);
 this->climateManager.fogIntensity.setOverride(0.0F, 1.0F);
 float float4 =
 ClimateManager.clamp01(this->currentStage.parabolicT * 3.0F);
 this->climateManager.windIntensity.setOverride(
 0.5F * this->weatherNoise, float4);
 this->climateManager.windAngleIntensity.setOverride(
 0.7F * this->weatherNoise * this->windAngleDirMod, float4);
 break;
 case 4:
 this->climateManager.fogIntensity.setOverride(
 0.0F, 1.0F - this->currentStage.linearT);
 break;
 case 5:
 this->climateManager.fogIntensity.setOverride(0.0F, 1.0F);
 break;
 case 6:
 this->climateManager.fogIntensity.setOverride(0.0F, 1.0F);
 break;
 case 7:
 this->isBlizzard = true;
 float float1 = this->frontCache.getStrength() * 0.5F;
 if (this->currentStage.linearT < 0.1F) {
 float1 = ClimateManager.clerp(
 (float)((this->currentTime - this->currentStage.stageStart) /
 (this->currentStage.stageDuration * 0.1),
 0.0F, this->frontCache.getStrength() * 0.5F);
 } else if (this->currentStage.linearT > 0.9F) {
 float1 = ClimateManager.clerp(
 1.0F -
 (float)((this->currentStage.stageEnd - this->currentTime) /
 (this->currentStage.stageDuration * 0.1),
 this->frontCache.getStrength() * 0.5F, 0.0F);
 }

 this->weatherNoise = float1 + this->weatherNoise * (1.0F - float1);
 float float2 =
 ClimateManager.clamp01(this->currentStage.parabolicT * 3.0F);
 this->climateManager.windIntensity.setOverride(
 0.75F + 0.25F * this->weatherNoise, float2);
 this->climateManager.windAngleIntensity.setOverride(
 0.7F * this->weatherNoise * this->windAngleDirMod, float2);
 if (PerformanceSettings.FogQuality != 2) {
 if (this->currentStage.fogStrength > 0.0F) {
 this->climateManager.fogIntensity.setOverride(
 this->currentStage.fogStrength, float2);
 } else {
 this->climateManager.fogIntensity.setOverride(1.0F, float2);
 }
 }
 break;
 case 8:
 this->isTropicalStorm = true;
 case 3:
 case 11:
 this->isThunderStorm = !this->isTropicalStorm;
 if (!this->currentStage.hasStartedCloud) {
 float float5 = this->frontCache.getAngleDegrees();
 float float6 = this->frontCache.getStrength();
 float float7 = 8000.0F * float6;
 float float8 = float6;
 float float9 = 0.6F * float6;
 double double0 = this->currentStage.stageDuration;
 bool boolean0 = float6 > 0.7;
 int int0 = Rand.Next(1, 3);
 if (this->currentStage.stageID == 8) {
 int0 = 1;
 float7 = 15000.0F;
 float9 = 0.8F;
 boolean0 = true;
 float6 = 1.0F;
 }

 for (int int1 = 0; int1 < int0; int1++) {
 ThunderStorm.ThunderCloud thunderCloud =
 this->thunderStorm.startThunderCloud(
 float6, float5, float7, float8, float9, double0,
 boolean0,
 this->currentStage.stageID == 11 ? kateBobStormProgress
 : 0.0F);
 if (this->currentStage.stageID == 11 && boolean0 &&
 thunderCloud != nullptr) {
 thunderCloud.setCenter(this->kateBobStormX, this->kateBobStormY,
 float5);
 }

 boolean0 = false;
 }

 this->currentStage.hasStartedCloud = true;
 }

 float float10 = this->frontCache.getStrength() * 0.5F;
 if (this->currentStage.linearT < 0.1F) {
 float10 = ClimateManager.clerp(
 (float)((this->currentTime - this->currentStage.stageStart) /
 (this->currentStage.stageDuration * 0.1),
 0.0F, this->frontCache.getStrength() * 0.5F);
 } else if (this->currentStage.linearT > 0.9F) {
 float10 = ClimateManager.clerp(
 1.0F -
 (float)((this->currentStage.stageEnd - this->currentTime) /
 (this->currentStage.stageDuration * 0.1),
 this->frontCache.getStrength() * 0.5F, 0.0F);
 }

 this->weatherNoise = float10 + this->weatherNoise * (1.0F - float10);
 float float11 =
 ClimateManager.clamp01(this->currentStage.parabolicT * 3.0F);
 if (this->currentStage.stageID == 8) {
 this->climateManager.windIntensity.setOverride(
 0.4F + 0.6F * this->weatherNoise, float11);
 } else {
 this->climateManager.windIntensity.setOverride(
 0.2F + 0.5F * this->weatherNoise, float11);
 }

 this->climateManager.windAngleIntensity.setOverride(
 0.7F * this->weatherNoise * this->windAngleDirMod, float11);
 if (PerformanceSettings.FogQuality != 2) {
 if (this->currentStage.fogStrength > 0.0F) {
 this->climateManager.fogIntensity.setOverride(
 this->currentStage.fogStrength, float11);
 if (this->currentStage.stageID == 8) {
 this->climateManager.colorNewFog.setOverride(
 this->climateManager.getFogTintTropical(), float11);
 } else {
 this->climateManager.colorNewFog.setOverride(
 this->climateManager.getFogTintStorm(), float11);
 }
 } else {
 this->climateManager.fogIntensity.setOverride(0.0F, 1.0F);
 }
 }
 break;
 case 9:
 this->climateManager.fogIntensity.setOverride(0.0F, 1.0F);
 break;
 case 10:
 LuaEventManager.triggerEvent("OnUpdateModdedWeatherStage", this,
 this->currentStage,
 this->frontCache.getStrength());
 break;
 default:
 this->print("WeatherPeriod Warning: trying to _UPDATE_ state that "
 "is not recognized, state id=" +
 this->currentStage.stageID);
 this->resetClimateManagerOverrides();
 this->isRunning = false;
 if (GameServer.bServer) {
 this->climateManager.transmitClimatePacket(
 ClimateManager.ClimateNetAuth.ServerOnly, (byte)1, nullptr);
 }
 }
 }
 }

 void update(double hoursSinceStart) {
 if (!GameClient.bClient && !this->isDummy) {
 if (this->isRunning && this->currentStage != nullptr &&
 this->weatherStageIndex >= 0 && this->weatherStages.size() != 0) {
 if (this->currentTime > this->currentStage.stageEnd) {
 this->weatherStageIndex++;
 LuaEventManager.triggerEvent("OnWeatherPeriodStage", this);
 if (this->weatherStageIndex >= this->weatherStages.size()) {
 this->isRunning = false;
 this->currentStage = nullptr;
 this->resetClimateManagerOverrides();
 if (GameServer.bServer) {
 this->climateManager.transmitClimatePacket(
 ClimateManager.ClimateNetAuth.ServerOnly, (byte)1,
 nullptr);
 }

 return;
 }

 if (this->currentStage != nullptr) {
 this->currentStage.exitStrength = this->currentStrength;
 }

 this->currentStage =
 this->weatherStages.get(this->weatherStageIndex);
 this->currentStage.entryStrength = this->currentStrength;
 this->currentStage.startStage(hoursSinceStart);
 }

 this->currentTime = hoursSinceStart;
 this->weatherNoise =
 0.3F * this->frontCache.getStrength() +
 (float)SimplexNoise.noise(hoursSinceStart, 24000.0) *
 (1.0F - 0.3F * this->frontCache.getStrength());
 this->weatherNoise = (this->weatherNoise + 1.0F) * 0.5F;
 this->currentStage.updateT(this->currentTime);
 this->stageProgress = this->currentStage.linearT;
 this->totalProgress = (float)(this->currentTime -
 this->weatherStages.get(0).stageStart) /
 (float)this->duration;
 this->totalProgress = ClimateManager.clamp01(this->totalProgress);
 this->currentStrength = this->currentStage.getStageCurrentStrength();
 this->updateCurrentStage();
 float float0 =
 ClimateManager.clamp(-1.0F, 1.0F, this->currentStrength * 2.0F) *
 maxTemperatureInfluence;
 if (this->frontCache.getType() == 1) {
 this->temperatureInfluence =
 this->climateManager.temperature.internalValue - float0;
 } else {
 this->temperatureInfluence =
 this->climateManager.temperature.internalValue + float0;
 }

 if (this->isRunning) {
 if (this->weatherNoise > this->rainThreshold) {
 this->precipitationFinal =
 (this->weatherNoise - this->rainThreshold) /
 (1.0F - this->rainThreshold);
 this->precipitationFinal =
 this->precipitationFinal * this->currentStrength;
 } else {
 this->precipitationFinal = 0.0F;
 }

 float float1 = this->precipitationFinal;
 float float2 =
 float1 *
 (1.0F - this->climateManager.nightStrength.internalValue);
 float float3 = 0.5F;
 float3 +=
 0.5F *
 (1.0F - this->climateManager.nightStrength.internalValue);
 float3 = Math.max(
 float3, this->climateManager.cloudIntensity.internalValue);
 float float4 = 0.55F;
 if (PerformanceSettings.FogQuality != 2 &&
 this->currentStage.stageID == 8) {
 float4 += 0.35F * this->currentStage.parabolicT;
 }

 float float5 = 1.0F - float4 * float1;
 float5 = Math.min(
 float5,
 1.0F - this->climateManager.nightStrength.internalValue);
 if (PerformanceSettings.FogQuality != 2 &&
 this->currentStage.stageID == 7) {
 float float6 = 1.0F - 0.75F * this->currentStage.parabolicT;
 float3 *= float6;
 }

 this->climateManager.cloudIntensity.setOverride(
 float3, this->currentStrength);
 this->climateManager.precipitationIntensity.setOverride(
 this->precipitationFinal, 1.0F);
 this->climateManager.globalLight.setOverride(this->cloudColor,
 float2);
 this->climateManager.globalLightIntensity.setOverride(0.4F,
 float2);
 this->climateManager.desaturation.setOverride(
 0.3F, this->currentStrength);
 this->climateManager.temperature.setOverride(
 this->temperatureInfluence, this->currentStrength);
 this->climateManager.ambient.setOverride(float5, float1);
 this->climateManager.dayLightStrength.setOverride(float5, float1);
 if ((!(this->climateManager.getTemperature() < 0.0F) ||
 !this->climateManager.getSeason().isSeason(5) &&
 !ClimateManager.WINTER_IS_COMING) {
 this->climateManager.precipitationIsSnow.setEnableOverride(
 false);
 } else {
 this->climateManager.precipitationIsSnow.setOverride(true);
 }
 }
 } else {
 if (this->isRunning) {
 this->resetClimateManagerOverrides();
 this->isRunning = false;
 LuaEventManager.triggerEvent("OnWeatherPeriodComplete", this);
 if (GameServer.bServer) {
 this->climateManager.transmitClimatePacket(
 ClimateManager.ClimateNetAuth.ServerOnly, (byte)1, nullptr);
 }
 }
 }
 }
 }

 void resetClimateManagerOverrides() {
 if (this->climateManager != nullptr && !this->isDummy) {
 this->climateManager.resetOverrides();
 }
 }

 /**
 * IO
 */
 void save(DataOutputStream output) {
 if (GameClient.bClient && !GameServer.bServer) {
 output.writeByte(0);
 } else {
 output.writeByte(1);
 output.writeBoolean(this->isRunning);
 if (this->isRunning) {
 output.writeInt(this->weatherStageIndex);
 output.writeFloat(this->currentStrength);
 output.writeFloat(this->rainThreshold);
 output.writeBoolean(this->isThunderStorm);
 output.writeBoolean(this->isTropicalStorm);
 output.writeBoolean(this->isBlizzard);
 this->frontCache.save(output);
 output.writeInt(this->weatherStages.size());

 for (int int0 = 0; int0 < this->weatherStages.size(); int0++) {
 WeatherPeriod.WeatherStage weatherStage =
 this->weatherStages.get(int0);
 output.writeInt(weatherStage.stageID);
 output.writeDouble(weatherStage.stageDuration);
 weatherStage.save(output);
 }

 this->cloudColor.save(output);
 }
 }
 }

 void load(DataInputStream input, int worldVersion) {
 uint8_t byte0 = input.readByte();
 if (byte0 == 1) {
 this->isRunning = input.readBoolean();
 if (this->isRunning) {
 this->weatherStageIndex = input.readInt();
 this->currentStrength = input.readFloat();
 this->rainThreshold = input.readFloat();
 this->isThunderStorm = input.readBoolean();
 this->isTropicalStorm = input.readBoolean();
 this->isBlizzard = input.readBoolean();
 this->frontCache.load(input);
 if (this->frontCache.getAngleDegrees() >= 90.0F &&
 this->frontCache.getAngleDegrees() < 270.0F) {
 this->windAngleDirMod = 1.0F;
 } else {
 this->windAngleDirMod = -1.0F;
 }

 this->print(
 "WeatherPeriod: Loading weather pattern with strength = " +
 this->frontCache.getStrength());
 this->clearCurrentWeatherStages();
 int int0 = input.readInt();

 for (int int1 = 0; int1 < int0; int1++) {
 int int2 = input.readInt();
 double double0 = input.readDouble();
 WeatherPeriod.WeatherStage weatherStage =
 !this->stagesPool.empty() ? this->stagesPool.pop()
 : new WeatherPeriod.WeatherStage();
 weatherStage.stageID = int2;
 weatherStage.setStageDuration(double0);
 weatherStage.load(input, worldVersion);
 this->weatherStages.add(weatherStage);
 }

 if (worldVersion >= 170) {
 this->cloudColor.load(input, worldVersion);
 }

 this->linkWeatherStages();
 this->duration = 0.0;

 for (int int3 = 0; int3 < this->weatherStages.size(); int3++) {
 this->duration =
 this->duration + this->weatherStages.get(int3).stageDuration;
 }

 if (this->weatherStageIndex >= 0 &&
 this->weatherStageIndex < this->weatherStages.size()) {
 this->currentStage =
 this->weatherStages.get(this->weatherStageIndex);
 this->print("WeatherPeriod: Pattern loaded!");
 } else {
 this->print("WeatherPeriod: Couldnt load stages correctly.");
 this->isRunning = false;
 }
 }
 }
 }

 public
 static enum StrLerpVal {
 Entry(1), Target(2), NextTarget(3), None(0);

 const int value;

 private StrLerpVal(int int1){
 this->value = int1;
 if (WeatherPeriod.cache.containsKey(int1){DebugLog.log(
 "StrLerpVal WARNING: trying to add id twice. id=" + int1);}

 WeatherPeriod.cache.put(int1, this);
 }

 int getValue() { return this->value; }

 public
 static WeatherPeriod.StrLerpVal fromValue(int id) {
 if (WeatherPeriod.cache.containsKey(id) {
 return WeatherPeriod.cache.get(id);
 } else {
 DebugLog.log("StrLerpVal, trying to get from invalid id: " + id);
 return None;
 }
 }
 }

public
 static class WeatherStage {
 protected
 WeatherPeriod.WeatherStage previousStage;
 protected
 WeatherPeriod.WeatherStage nextStage;
 double stageStart;
 double stageEnd;
 double stageDuration;
 int stageID;
 float entryStrength;
 float exitStrength;
 float targetStrength;
 protected
 WeatherPeriod.StrLerpVal lerpMidVal;
 protected
 WeatherPeriod.StrLerpVal lerpEndVal;
 bool hasStartedCloud = false;
 float fogStrength = 0.0F;
 float linearT;
 float parabolicT;
 bool isCycleFirstHalf = true;
 bool creationFinished = false;
 std::string modID;
 float m;
 float e;

 public
 WeatherStage() {}

 public
 WeatherStage(int id) { this->stageID = id; }

 void setStageID(int id) { this->stageID = id; }

 double getStageStart() { return this->stageStart; }

 double getStageEnd() { return this->stageEnd; }

 double getStageDuration() { return this->stageDuration; }

 int getStageID() { return this->stageID; }

 std::string getModID() { return this->modID; }

 float getLinearT() { return this->linearT; }

 float getParabolicT() { return this->parabolicT; }

 void setTargetStrength(float t) { this->targetStrength = t; }

 bool getHasStartedCloud() { return this->hasStartedCloud; }

 void setHasStartedCloud(bool b) { this->hasStartedCloud = true; }

 void save(DataOutputStream output) {
 output.writeDouble(this->stageStart);
 output.writeFloat(this->entryStrength);
 output.writeFloat(this->exitStrength);
 output.writeFloat(this->targetStrength);
 output.writeInt(this->lerpMidVal.getValue());
 output.writeInt(this->lerpEndVal.getValue());
 output.writeBoolean(this->hasStartedCloud);
 output.writeByte(this->modID != nullptr ? 1 : 0);
 if (this->modID != nullptr) {
 GameWindow.WriteString(output, this->modID);
 }

 output.writeFloat(this->fogStrength);
 }

 void load(DataInputStream input, int worldVersion) {
 this->stageStart = input.readDouble();
 this->stageEnd = this->stageStart + this->stageDuration;
 this->entryStrength = input.readFloat();
 this->exitStrength = input.readFloat();
 this->targetStrength = input.readFloat();
 this->lerpMidVal = WeatherPeriod.StrLerpVal.fromValue(input.readInt());
 this->lerpEndVal = WeatherPeriod.StrLerpVal.fromValue(input.readInt());
 this->hasStartedCloud = input.readBoolean();
 if (worldVersion >= 141 && input.readByte() == 1) {
 this->modID = GameWindow.ReadString(input);
 }

 if (worldVersion >= 170) {
 this->fogStrength = input.readFloat();
 }
 }

 void reset() {
 this->previousStage = nullptr;
 this->nextStage = nullptr;
 this->isCycleFirstHalf = true;
 this->hasStartedCloud = false;
 this->lerpMidVal = WeatherPeriod.StrLerpVal.None;
 this->lerpEndVal = WeatherPeriod.StrLerpVal.None;
 this->entryStrength = 0.0F;
 this->exitStrength = 0.0F;
 this->modID = nullptr;
 this->creationFinished = false;
 this->fogStrength = 0.0F;
 }

 protected
 WeatherPeriod.WeatherStage startStage(double double0) {
 this->stageStart = double0;
 this->stageEnd = double0 + this->stageDuration;
 this->hasStartedCloud = false;
 return this;
 }

 double setStageStart(double double0) {
 this->stageStart = double0;
 this->stageEnd = double0 + this->stageDuration;
 return this->stageEnd;
 }

 protected
 WeatherPeriod.WeatherStage setStageDuration(double double0) {
 this->stageDuration = double0;
 if (this->stageDuration < 1.0) {
 this->stageDuration = 1.0;
 }

 return this;
 }

 protected
 WeatherPeriod.WeatherStage overrideStageDuration(double double0) {
 this->stageDuration = double0;
 return this;
 }

 void lerpEntryTo(int mid, int __end__) {
 if (!this->creationFinished) {
 this->lerpEntryTo(WeatherPeriod.StrLerpVal.fromValue(mid),
 WeatherPeriod.StrLerpVal.fromValue(__end__);
 }
 }

 void lerpEntryTo(WeatherPeriod.StrLerpVal strLerpVal) {
 this->lerpEntryTo(WeatherPeriod.StrLerpVal.None, strLerpVal);
 }

 void lerpEntryTo(WeatherPeriod.StrLerpVal strLerpVal0,
 WeatherPeriod.StrLerpVal strLerpVal1) {
 if (!this->creationFinished) {
 this->lerpMidVal = strLerpVal0;
 this->lerpEndVal = strLerpVal1;
 }
 }

 float getStageCurrentStrength() {
 this->m = this->getLerpValue(this->lerpMidVal);
 this->e = this->getLerpValue(this->lerpEndVal);
 if (this->lerpMidVal == WeatherPeriod.StrLerpVal.None) {
 return ClimateManager.clerp(this->linearT, this->entryStrength, this->e);
 } else {
 return this->isCycleFirstHalf
 ? ClimateManager.clerp(this->parabolicT, this->entryStrength,
 this->m)
 : ClimateManager.clerp(this->parabolicT, this->e, this->m);
 }
 }

 float getLerpValue(WeatherPeriod.StrLerpVal strLerpVal) {
 switch (strLerpVal) {
 case Entry:
 return this->entryStrength;
 case Target:
 return this->targetStrength;
 case NextTarget:
 return this->nextStage != nullptr ? this->nextStage.targetStrength : 0.0F;
 case None:
 return 0.0F;
 default:
 return 0.0F;
 }
 }

 private
 WeatherPeriod.WeatherStage updateT(double double0) {
 this->linearT = this->getPeriodLerpT(double0);
 if (this->stageID == 11) {
 this->linearT =
 WeatherPeriod.kateBobStormProgress +
 (1.0F - WeatherPeriod.kateBobStormProgress) * this->linearT;
 }

 if (this->linearT < 0.5F) {
 this->parabolicT = this->linearT * 2.0F;
 this->isCycleFirstHalf = true;
 } else {
 this->parabolicT = 2.0F - this->linearT * 2.0F;
 this->isCycleFirstHalf = false;
 }

 return this;
 }

 float getPeriodLerpT(double double0) {
 if (double0 < this->stageStart) {
 return 0.0F;
 } else {
 return double0 > this->stageEnd
 ? 1.0F
 : (float)((double0 - this->stageStart) / this->stageDuration);
 }
 }
 }
}
} // namespace weather
} // namespace iso
} // namespace zombie
