#pragma once
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/GameTime.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/Rand.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/erosion/ErosionMain.h"
#include "zombie/erosion/season/ErosionIceQueen.h"
#include "zombie/erosion/season/ErosionSeason.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/IsoPuddles.h"
#include "zombie/iso/IsoWater.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/sprite/SkyBox.h"
#include "zombie/iso/weather/dbg/ClimMngrDebug.h"
#include "zombie/iso/weather/fx/IsoWeatherFX.h"
#include "zombie/iso/weather/fx/SteppedUpdateFloat.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes.h"
#include "zombie/vehicles/BaseVehicle.h"
#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
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
class ClimateManager {
public:
 bool DISABLE_SIMULATION = false;
 bool DISABLE_FX_UPDATE = false;
 bool DISABLE_WEATHER_GENERATION = false;
 static const int FRONT_COLD = -1;
 static const int FRONT_STATIONARY = 0;
 static const int FRONT_WARM = 1;
 static const float MAX_WINDSPEED_KPH = 120.0F;
 static const float MAX_WINDSPEED_MPH = 74.5645F;
 ErosionSeason season;
 long lastMinuteStamp = -1L;
 KahluaTable modDataTable = nullptr;
 float airMass;
 float airMassDaily;
 float airMassTemperature;
 float baseTemperature;
 float snowFall = 0.0F;
 float snowStrength = 0.0F;
 float snowMeltStrength = 0.0F;
 float snowFracNow = 0.0F;
 bool canDoWinterSprites = false;
 float windPower = 0.0F;
 WeatherPeriod weatherPeriod;
 ThunderStorm thunderStorm;
 double simplexOffsetA = 0.0;
 double simplexOffsetB = 0.0;
 double simplexOffsetC = 0.0;
 double simplexOffsetD = 0.0;
 bool dayDoFog = false;
 float dayFogStrength = 0.0F;
 GameTime gt;
 double worldAgeHours;
 bool tickIsClimateTick = false;
 bool tickIsDayChange = false;
 int lastHourStamp = -1;
 bool tickIsHourChange = false;
 bool tickIsTenMins = false;
private
 ClimateManager.AirFront currentFront = new ClimateManager.AirFront();
 ClimateColorInfo colDay;
 ClimateColorInfo colDusk;
 ClimateColorInfo colDawn;
 ClimateColorInfo colNight;
 ClimateColorInfo colNightNoMoon;
 ClimateColorInfo colNightMoon;
 ClimateColorInfo colTemp;
 ClimateColorInfo colFog;
 ClimateColorInfo colFogLegacy;
 ClimateColorInfo colFogNew;
 ClimateColorInfo fogTintStorm;
 ClimateColorInfo fogTintTropical;
 static ClimateManager instance = new ClimateManager();
 static bool WINTER_IS_COMING = false;
 static bool THE_DESCENDING_FOG = false;
 static bool A_STORM_IS_COMING = false;
 ClimateValues climateValues;
 ClimateForecaster climateForecaster;
 ClimateHistory climateHistory;
 float dayLightLagged = 0.0F;
 float nightLagged = 0.0F;
protected
 ClimateManager.ClimateFloat desaturation;
protected
 ClimateManager.ClimateFloat globalLightIntensity;
protected
 ClimateManager.ClimateFloat nightStrength;
protected
 ClimateManager.ClimateFloat precipitationIntensity;
protected
 ClimateManager.ClimateFloat temperature;
protected
 ClimateManager.ClimateFloat fogIntensity;
protected
 ClimateManager.ClimateFloat windIntensity;
protected
 ClimateManager.ClimateFloat windAngleIntensity;
protected
 ClimateManager.ClimateFloat cloudIntensity;
protected
 ClimateManager.ClimateFloat ambient;
protected
 ClimateManager.ClimateFloat viewDistance;
protected
 ClimateManager.ClimateFloat dayLightStrength;
protected
 ClimateManager.ClimateFloat humidity;
protected
 ClimateManager.ClimateColor globalLight;
protected
 ClimateManager.ClimateColor colorNewFog;
protected
 ClimateManager.ClimateBool precipitationIsSnow;
 static const int FLOAT_DESATURATION = 0;
 static const int FLOAT_GLOBAL_LIGHT_INTENSITY = 1;
 static const int FLOAT_NIGHT_STRENGTH = 2;
 static const int FLOAT_PRECIPITATION_INTENSITY = 3;
 static const int FLOAT_TEMPERATURE = 4;
 static const int FLOAT_FOG_INTENSITY = 5;
 static const int FLOAT_WIND_INTENSITY = 6;
 static const int FLOAT_WIND_ANGLE_INTENSITY = 7;
 static const int FLOAT_CLOUD_INTENSITY = 8;
 static const int FLOAT_AMBIENT = 9;
 static const int FLOAT_VIEW_DISTANCE = 10;
 static const int FLOAT_DAYLIGHT_STRENGTH = 11;
 static const int FLOAT_HUMIDITY = 12;
 static const int FLOAT_MAX = 13;
private
 ClimateManager.ClimateFloat[] climateFloats =
 new ClimateManager.ClimateFloat[13];
 static const int COLOR_GLOBAL_LIGHT = 0;
 static const int COLOR_NEW_FOG = 1;
 static const int COLOR_MAX = 2;
private
 ClimateManager.ClimateColor[] climateColors =
 new ClimateManager.ClimateColor[2];
 static const int BOOL_IS_SNOW = 0;
 static const int BOOL_MAX = 1;
private
 ClimateManager.ClimateBool[] climateBooleans =
 new ClimateManager.ClimateBool[1];
 static const float AVG_FAV_AIR_TEMPERATURE = 22.0F;
 static double windNoiseOffset = 0.0;
 static double windNoiseBase = 0.0;
 static double windNoiseFinal = 0.0;
 static double windTickFinal = 0.0;
 ClimateColorInfo colFlare =
 new ClimateColorInfo(1.0F, 0.0F, 0.0F, 1.0F, 1.0F, 0.0F, 0.0F, 1.0F);
 bool flareLaunched = false;
 SteppedUpdateFloat flareIntensity =
 new SteppedUpdateFloat(0.0F, 0.01F, 0.0F, 1.0F);
 float flareIntens;
 float flareMaxLifeTime;
 float flareLifeTime;
 int nextRandomTargetIntens = 10;
 float fogLerpValue = 0.0F;
private
 ClimateManager.SeasonColor seasonColorDawn;
private
 ClimateManager.SeasonColor seasonColorDay;
private
 ClimateManager.SeasonColor seasonColorDusk;
private
 ClimateManager.DayInfo previousDay;
private
 ClimateManager.DayInfo currentDay;
private
 ClimateManager.DayInfo nextDay;
 static const uint8_t PacketUpdateClimateVars = 0;
 static const uint8_t PacketWeatherUpdate = 1;
 static const uint8_t PacketThunderEvent = 2;
 static const uint8_t PacketFlare = 3;
 static const uint8_t PacketAdminVarsUpdate = 4;
 static const uint8_t PacketRequestAdminVars = 5;
 static const uint8_t PacketClientChangedAdminVars = 6;
 static const uint8_t PacketClientChangedWeather = 7;
 float networkLerp = 0.0F;
 long networkUpdateStamp = 0L;
 float networkLerpTime = 5000.0F;
 float networkLerpTimeBase = 5000.0F;
 float networkAdjustVal = 0.0F;
 bool networkPrint = false;
private
 ClimateManager.ClimateNetInfo netInfo = new ClimateManager.ClimateNetInfo();
 ClimateValues climateValuesFronts;
private
 static float[] windAngles = new float[]{
 22.5F, 67.5F, 112.5F, 157.5F, 202.5F, 247.5F, 292.5F, 337.5F, 382.5F};
private
 static String[] windAngleStr =
 new String[]{"SE", "S", "SW", "W", "NW", "N", "NE", "E", "SE"};

 float getMaxWindspeedKph() { return 120.0F; }

 float getMaxWindspeedMph() { return 74.5645F; }

 static float ToKph(float val) { return val * 120.0F; }

 static float ToMph(float val) { return val * 74.5645F; }

 static ClimateManager getInstance() { return instance; }

 static void setInstance(ClimateManager inst) { instance = inst; }

public
 ClimateManager() {
 this->colDay = std::make_unique<ClimateColorInfo>();
 this->colDawn = std::make_unique<ClimateColorInfo>();
 this->colDusk = std::make_unique<ClimateColorInfo>();
 this->colNight = std::make_unique<ClimateColorInfo>();
 this->colNightMoon = std::make_unique<ClimateColorInfo>();
 this->colFog = std::make_unique<ClimateColorInfo>();
 this->colTemp = std::make_unique<ClimateColorInfo>();
 this->colDay = std::make_unique<ClimateColorInfo>();
 this->colDawn = std::make_unique<ClimateColorInfo>();
 this->colDusk = std::make_unique<ClimateColorInfo>();
 this->colNight = new ClimateColorInfo(0.33F, 0.33F, 1.0F, 0.4F, 0.33F, 0.33F,
 1.0F, 0.4F);
 this->colNightNoMoon = new ClimateColorInfo(0.33F, 0.33F, 1.0F, 0.4F, 0.33F,
 0.33F, 1.0F, 0.4F);
 this->colNightMoon = new ClimateColorInfo(0.33F, 0.33F, 1.0F, 0.4F, 0.33F,
 0.33F, 1.0F, 0.4F);
 this->colFog =
 new ClimateColorInfo(0.4F, 0.4F, 0.4F, 0.8F, 0.4F, 0.4F, 0.4F, 0.8F);
 this->colFogLegacy =
 new ClimateColorInfo(0.3F, 0.3F, 0.3F, 0.8F, 0.3F, 0.3F, 0.3F, 0.8F);
 this->colFogNew =
 new ClimateColorInfo(0.5F, 0.5F, 0.55F, 0.4F, 0.5F, 0.5F, 0.55F, 0.8F);
 this->fogTintStorm =
 new ClimateColorInfo(0.5F, 0.45F, 0.4F, 1.0F, 0.5F, 0.45F, 0.4F, 1.0F);
 this->fogTintTropical = new ClimateColorInfo(0.8F, 0.75F, 0.55F, 1.0F, 0.8F,
 0.75F, 0.55F, 1.0F);
 this->colTemp = std::make_unique<ClimateColorInfo>();
 this->simplexOffsetA = Rand.Next(0, 8000);
 this->simplexOffsetB = Rand.Next(8000, 16000);
 this->simplexOffsetC = Rand.Next(0, -8000);
 this->simplexOffsetD = Rand.Next(-8000, -16000);
 this->initSeasonColors();
 this->setup();
 this->climateValues = new ClimateValues(this);
 this->thunderStorm = new ThunderStorm(this);
 this->weatherPeriod = new WeatherPeriod(this, this->thunderStorm);
 this->climateForecaster = std::make_unique<ClimateForecaster>();
 this->climateHistory = std::make_unique<ClimateHistory>();

 try {
 LuaEventManager.triggerEvent("OnClimateManagerInit", this);
 } catch (Exception exception) {
 System.out.print(exception.getMessage());
 System.out.print(exception.getStackTrace());
 }
 }

 ClimateColorInfo getColNight() { return this->colNight; }

 ClimateColorInfo getColNightNoMoon() { return this->colNightNoMoon; }

 ClimateColorInfo getColNightMoon() { return this->colNightMoon; }

 ClimateColorInfo getColFog() { return this->colFog; }

 ClimateColorInfo getColFogLegacy() { return this->colFogLegacy; }

 ClimateColorInfo getColFogNew() { return this->colFogNew; }

 ClimateColorInfo getFogTintStorm() { return this->fogTintStorm; }

 ClimateColorInfo getFogTintTropical() { return this->fogTintTropical; }

 void setup() {
 for (int int0 = 0; int0 < this->climateFloats.length; int0++) {
 this->climateFloats[int0] = new ClimateManager.ClimateFloat();
 }

 for (int int1 = 0; int1 < this->climateColors.length; int1++) {
 this->climateColors[int1] = new ClimateManager.ClimateColor();
 }

 for (int int2 = 0; int2 < this->climateBooleans.length; int2++) {
 this->climateBooleans[int2] = new ClimateManager.ClimateBool();
 }

 this->desaturation = this->initClimateFloat(0, "DESATURATION");
 this->globalLightIntensity =
 this->initClimateFloat(1, "GLOBAL_LIGHT_INTENSITY");
 this->nightStrength = this->initClimateFloat(2, "NIGHT_STRENGTH");
 this->precipitationIntensity =
 this->initClimateFloat(3, "PRECIPITATION_INTENSITY");
 this->temperature = this->initClimateFloat(4, "TEMPERATURE");
 this->temperature.min = -80.0F;
 this->temperature.max = 80.0F;
 this->fogIntensity = this->initClimateFloat(5, "FOG_INTENSITY");
 this->windIntensity = this->initClimateFloat(6, "WIND_INTENSITY");
 this->windAngleIntensity = this->initClimateFloat(7, "WIND_ANGLE_INTENSITY");
 this->windAngleIntensity.min = -1.0F;
 this->cloudIntensity = this->initClimateFloat(8, "CLOUD_INTENSITY");
 this->ambient = this->initClimateFloat(9, "AMBIENT");
 this->viewDistance = this->initClimateFloat(10, "VIEW_DISTANCE");
 this->viewDistance.min = 0.0F;
 this->viewDistance.max = 100.0F;
 this->dayLightStrength = this->initClimateFloat(11, "DAYLIGHT_STRENGTH");
 this->humidity = this->initClimateFloat(12, "HUMIDITY");
 this->globalLight = this->initClimateColor(0, "GLOBAL_LIGHT");
 this->colorNewFog = this->initClimateColor(1, "COLOR_NEW_FOG");
 this->colorNewFog.internalValue.setExterior(0.9F, 0.9F, 0.95F, 1.0F);
 this->colorNewFog.internalValue.setInterior(0.9F, 0.9F, 0.95F, 1.0F);
 this->precipitationIsSnow = this->initClimateBool(0, "IS_SNOW");
 }

 int getFloatMax() { return 13; }

private
 ClimateManager.ClimateFloat initClimateFloat(int int0, String string) {
 if (int0 >= 0 && int0 < 13) {
 return this->climateFloats[int0].init(int0, string);
 } else {
 DebugLog.log("Climate: cannot get float override id.");
 return nullptr;
 }
 }

public
 ClimateManager.ClimateFloat getClimateFloat(int id) {
 if (id >= 0 && id < 13) {
 return this->climateFloats[id];
 } else {
 DebugLog.log("Climate: cannot get float override id.");
 return nullptr;
 }
 }

 int getColorMax() { return 2; }

private
 ClimateManager.ClimateColor initClimateColor(int int0, String string) {
 if (int0 >= 0 && int0 < 2) {
 return this->climateColors[int0].init(int0, string);
 } else {
 DebugLog.log("Climate: cannot get float override id.");
 return nullptr;
 }
 }

public
 ClimateManager.ClimateColor getClimateColor(int id) {
 if (id >= 0 && id < 2) {
 return this->climateColors[id];
 } else {
 DebugLog.log("Climate: cannot get float override id.");
 return nullptr;
 }
 }

 int getBoolMax() { return 1; }

private
 ClimateManager.ClimateBool initClimateBool(int int0, String string) {
 if (int0 >= 0 && int0 < 1) {
 return this->climateBooleans[int0].init(int0, string);
 } else {
 DebugLog.log("Climate: cannot get boolean id.");
 return nullptr;
 }
 }

public
 ClimateManager.ClimateBool getClimateBool(int id) {
 if (id >= 0 && id < 1) {
 return this->climateBooleans[id];
 } else {
 DebugLog.log("Climate: cannot get boolean id.");
 return nullptr;
 }
 }

 void setEnabledSimulation(bool b) {
 if (!GameClient.bClient && !GameServer.bServer) {
 this->DISABLE_SIMULATION = !b;
 } else {
 this->DISABLE_SIMULATION = false;
 }
 }

 bool getEnabledSimulation() { return !this->DISABLE_SIMULATION; }

 bool getEnabledFxUpdate() { return !this->DISABLE_FX_UPDATE; }

 void setEnabledFxUpdate(bool b) {
 if (!GameClient.bClient && !GameServer.bServer) {
 this->DISABLE_FX_UPDATE = !b;
 } else {
 this->DISABLE_FX_UPDATE = false;
 }
 }

 bool getEnabledWeatherGeneration() { return this->DISABLE_WEATHER_GENERATION; }

 void setEnabledWeatherGeneration(bool b) {
 this->DISABLE_WEATHER_GENERATION = !b;
 }

 Color getGlobalLightInternal() {
 return this->globalLight.internalValue.getExterior();
 }

 ClimateColorInfo getGlobalLight() { return this->globalLight.finalValue; }

 float getGlobalLightIntensity() {
 return this->globalLightIntensity.finalValue;
 }

 ClimateColorInfo getColorNewFog() { return this->colorNewFog.finalValue; }

 void setNightStrength(float b) {
 this->nightStrength.finalValue = clamp(0.0F, 1.0F, b);
 }

 float getDesaturation() { return this->desaturation.finalValue; }

 void setDesaturation(float _desaturation) {
 this->desaturation.finalValue = _desaturation;
 }

 float getAirMass() { return this->airMass; }

 float getAirMassDaily() { return this->airMassDaily; }

 float getAirMassTemperature() { return this->airMassTemperature; }

 float getDayLightStrength() { return this->dayLightStrength.finalValue; }

 float getNightStrength() { return this->nightStrength.finalValue; }

 float getDayMeanTemperature() {
 return this->currentDay.season.getDayMeanTemperature();
 }

 float getTemperature() { return this->temperature.finalValue; }

 float getBaseTemperature() { return this->baseTemperature; }

 float getSnowStrength() { return this->snowStrength; }

 bool getPrecipitationIsSnow() { return this->precipitationIsSnow.finalValue; }

 float getPrecipitationIntensity() {
 return this->precipitationIntensity.finalValue;
 }

 float getFogIntensity() { return this->fogIntensity.finalValue; }

 float getWindIntensity() { return this->windIntensity.finalValue; }

 float getWindAngleIntensity() { return this->windAngleIntensity.finalValue; }

 float getCorrectedWindAngleIntensity() {
 return (this->windAngleIntensity.finalValue + 1.0F) * 0.5F;
 }

 float getWindPower() { return this->windPower; }

 float getWindspeedKph() { return this->windPower * 120.0F; }

 float getCloudIntensity() { return this->cloudIntensity.finalValue; }

 float getAmbient() { return this->ambient.finalValue; }

 float getViewDistance() { return this->viewDistance.finalValue; }

 float getHumidity() { return this->humidity.finalValue; }

 float getWindAngleDegrees() {
 float float0;
 if (this->windAngleIntensity.finalValue > 0.0F) {
 float0 = lerp(this->windAngleIntensity.finalValue, 45.0F, 225.0F);
 } else if (this->windAngleIntensity.finalValue > -0.25F) {
 float0 = lerp(Math.abs(this->windAngleIntensity.finalValue), 45.0F, 0.0F);
 } else {
 float0 = lerp(Math.abs(this->windAngleIntensity.finalValue) - 0.25F,
 360.0F, 180.0F);
 }

 if (float0 > 360.0F) {
 float0 -= 360.0F;
 }

 if (float0 < 0.0F) {
 float0 += 360.0F;
 }

 return float0;
 }

 float getWindAngleRadians() {
 return (float)Math.toRadians(this->getWindAngleDegrees());
 }

 float getWindSpeedMovement() {
 float float0 = this->getWindIntensity();
 if (float0 < 0.15F) {
 float0 = 0.0F;
 } else {
 float0 = (float0 - 0.15F) / 0.85F;
 }

 return float0;
 }

 float getWindForceMovement(IsoGameCharacter character, float angle) {
 if (character.square != nullptr && !character.square.isInARoom()) {
 float float0 = angle - this->getWindAngleRadians();
 if (float0 > Math.PI * 2) {
 float0 = (float)(float0 - (Math.PI * 2);
 }

 if (float0 < 0.0F) {
 float0 = (float)(float0 + (Math.PI * 2);
 }

 if (float0 > Math.PI) {
 float0 = (float)(Math.PI - (float0 - Math.PI);
 }

 return (float)(float0 / Math.PI);
 } else {
 return 0.0F;
 }
 }

 bool isRaining() {
 return this->getPrecipitationIntensity() > 0.0F &&
 !this->getPrecipitationIsSnow();
 }

 float getRainIntensity() {
 return this->isRaining() ? this->getPrecipitationIntensity() : 0.0F;
 }

 bool isSnowing() {
 return this->getPrecipitationIntensity() > 0.0F &&
 this->getPrecipitationIsSnow();
 }

 float getSnowIntensity() {
 return this->isSnowing() ? this->getPrecipitationIntensity() : 0.0F;
 }

 void setAmbient(float f) { this->ambient.finalValue = f; }

 void setViewDistance(float f) { this->viewDistance.finalValue = f; }

 void setDayLightStrength(float f) { this->dayLightStrength.finalValue = f; }

 void setPrecipitationIsSnow(bool b) {
 this->precipitationIsSnow.finalValue = b;
 }

public
 ClimateManager.DayInfo getCurrentDay() { return this->currentDay; }

public
 ClimateManager.DayInfo getPreviousDay() { return this->previousDay; }

public
 ClimateManager.DayInfo getNextDay() { return this->nextDay; }

 ErosionSeason getSeason() {
 return this->currentDay != nullptr && this->currentDay.getSeason() != nullptr
 ? this->currentDay.getSeason()
 : this->season;
 }

 float getFrontStrength() {
 if (this->currentFront.empty()) {
 return 0.0F;
 } else {
 if (Core.bDebug) {
 this->CalculateWeatherFrontStrength(
 this->gt.getYear(), this->gt.getMonth(), this->gt.getDayPlusOne(),
 this->currentFront);
 }

 return this->currentFront.strength;
 }
 }

 void stopWeatherAndThunder() {
 if (!GameClient.bClient) {
 this->weatherPeriod.stopWeatherPeriod();
 this->thunderStorm.stopAllClouds();
 if (GameServer.bServer) {
 this->transmitClimatePacket(ClimateManager.ClimateNetAuth.ServerOnly,
 (byte)1, nullptr);
 }
 }
 }

 ThunderStorm getThunderStorm() { return this->thunderStorm; }

 WeatherPeriod getWeatherPeriod() { return this->weatherPeriod; }

 bool getIsThunderStorming() {
 return this->weatherPeriod.isRunning() &&
 (this->weatherPeriod.isThunderStorm() ||
 this->weatherPeriod.isTropicalStorm());
 }

 float getWeatherInterference() {
 if (this->weatherPeriod.isRunning()) {
 return !this->weatherPeriod.isThunderStorm() &&
 !this->weatherPeriod.isTropicalStorm() &&
 !this->weatherPeriod.isBlizzard()
 ? 0.35F * this->weatherPeriod.getCurrentStrength()
 : 0.7F * this->weatherPeriod.getCurrentStrength();
 } else {
 return 0.0F;
 }
 }

 KahluaTable getModData() {
 if (this->modDataTable.empty()) {
 this->modDataTable = LuaManager.platform.newTable();
 }

 return this->modDataTable;
 }

 float getAirTemperatureForCharacter(IsoGameCharacter plr) {
 return this->getAirTemperatureForCharacter(plr, false);
 }

 float getAirTemperatureForCharacter(IsoGameCharacter plr, bool doWindChill) {
 if (plr.square != nullptr) {
 return plr.getVehicle() != nullptr
 ? this->getAirTemperatureForSquare(plr.square, plr.getVehicle(),
 doWindChill)
 : this->getAirTemperatureForSquare(plr.square, nullptr,
 doWindChill);
 } else {
 return this->getTemperature();
 }
 }

 float getAirTemperatureForSquare(IsoGridSquare square) {
 return this->getAirTemperatureForSquare(square, nullptr);
 }

 float getAirTemperatureForSquare(IsoGridSquare square, BaseVehicle vehicle) {
 return this->getAirTemperatureForSquare(square, vehicle, false);
 }

 float getAirTemperatureForSquare(IsoGridSquare square, BaseVehicle vehicle,
 bool doWindChill) {
 float float0 = this->getTemperature();
 if (square != nullptr) {
 bool boolean0 = square.isInARoom();
 if (boolean0 || vehicle != nullptr) {
 bool boolean1 = IsoWorld.instance.isHydroPowerOn();
 if (float0 <= 22.0F) {
 float float1 = (22.0F - float0) / 8.0F;
 if (vehicle.empty()) {
 if (boolean0 && boolean1) {
 float0 = 22.0F;
 }

 float1 = 22.0F - float0;
 if (square.getZ() < 1) {
 float0 += float1 * (0.4F + 0.2F * this->dayLightLagged);
 } else {
 float1 = (float)(float1 * 0.85);
 float0 += float1 * (0.4F + 0.2F * this->dayLightLagged);
 }
 }
 } else {
 float float2 = (float0 - 22.0F) / 3.5F;
 if (vehicle.empty()) {
 if (boolean0 && boolean1) {
 float0 = 22.0F;
 }

 float2 = float0 - 22.0F;
 if (square.getZ() < 1) {
 float2 = (float)(float2 * 0.85);
 float0 -= float2 * (0.4F + 0.2F * this->dayLightLagged);
 } else {
 float0 -= float2 * (0.4F + 0.2F * this->dayLightLagged +
 0.2F * this->nightLagged);
 }
 } else {
 float0 = float0 + float2 + float2 * this->dayLightLagged;
 }
 }
 } else if (doWindChill) {
 float0 =
 Temperature.WindchillCelsiusKph(float0, this->getWindspeedKph());
 }

 float float3 =
 IsoWorld.instance.getCell().getHeatSourceHighestTemperature(
 float0, square.getX(), square.getY(), square.getZ());
 if (float3 > float0) {
 float0 = float3;
 }

 if (vehicle != nullptr) {
 float0 += vehicle.getInsideTemperature();
 }
 }

 return float0;
 }

 std::string getSeasonName() { return this->season.getSeasonName(); }

 float getSeasonProgression() { return this->season.getSeasonProgression(); }

 float getSeasonStrength() { return this->season.getSeasonStrength(); }

 void init(IsoMetaGrid metaGrid) {
 WorldFlares.Clear();
 this->season = ErosionMain.getInstance().getSeasons();
 ThunderStorm.MAP_MIN_X = metaGrid.minX * 300 - 4000;
 ThunderStorm.MAP_MAX_X = metaGrid.maxX * 300 + 4000;
 ThunderStorm.MAP_MIN_Y = metaGrid.minY * 300 - 4000;
 ThunderStorm.MAP_MAX_Y = metaGrid.maxY * 300 + 4000;
 windNoiseOffset = 0.0;
 WINTER_IS_COMING = IsoWorld.instance.getGameMode() == "Winter is Coming");
 THE_DESCENDING_FOG = IsoWorld.instance.getGameMode() == "The Descending Fog");
 A_STORM_IS_COMING = IsoWorld.instance.getGameMode() == "A Storm is Coming");
 this->climateForecaster.init(this);
 this->climateHistory.init(this);
 }

 void updateEveryTenMins() { this->tickIsTenMins = true; }

 void update() {
 this->tickIsClimateTick = false;
 this->tickIsHourChange = false;
 this->tickIsDayChange = false;
 this->gt = GameTime.getInstance();
 this->worldAgeHours = this->gt.getWorldAgeHours();
 if (this->lastMinuteStamp != this->gt.getMinutesStamp()) {
 this->lastMinuteStamp = this->gt.getMinutesStamp();
 this->tickIsClimateTick = true;
 this->updateDayInfo(this->gt.getDayPlusOne(), this->gt.getMonth(),
 this->gt.getYear());
 this->currentDay.hour = this->gt.getHour();
 this->currentDay.minutes = this->gt.getMinutes();
 if (this->gt.getHour() != this->lastHourStamp) {
 this->tickIsHourChange = true;
 this->lastHourStamp = this->gt.getHour();
 }

 if (this->gt.getTimeOfDay() > 12.0F) {
 ClimateMoon.updatePhase(this->currentDay.getYear(),
 this->currentDay.getMonth(),
 this->currentDay.getDay());
 }
 }

 if (this->DISABLE_SIMULATION) {
 IsoPlayer[] players = IsoPlayer.players;

 for (int int0 = 0; int0 < players.length; int0++) {
 IsoPlayer player = players[int0];
 if (player != nullptr) {
 player.dirtyRecalcGridStackTime = 1.0F;
 }
 }
 } else {
 if (this->tickIsDayChange && !GameClient.bClient) {
 this->climateForecaster.updateDayChange(this);
 this->climateHistory.updateDayChange(this);
 }

 if (GameClient.bClient) {
 this->networkLerp = 1.0F;
 long long0 = System.currentTimeMillis();
 if ((float)long0 <
 (float)this->networkUpdateStamp + this->networkLerpTime) {
 this->networkLerp =
 (float)(long0 - this->networkUpdateStamp) / this->networkLerpTime;
 if (this->networkLerp < 0.0F) {
 this->networkLerp = 0.0F;
 }
 }

 for (int int1 = 0; int1 < this->climateFloats.length; int1++) {
 this->climateFloats[int1].interpolate = this->networkLerp;
 }

 for (int int2 = 0; int2 < this->climateColors.length; int2++) {
 this->climateColors[int2].interpolate = this->networkLerp;
 }
 }

 if (this->tickIsClimateTick && !GameClient.bClient) {
 this->updateValues();
 this->weatherPeriod.update(this->worldAgeHours);
 }

 if (this->tickIsClimateTick) {
 LuaEventManager.triggerEvent("OnClimateTick", this);
 }

 for (int int3 = 0; int3 < this->climateColors.length; int3++) {
 this->climateColors[int3].calculate();
 }

 for (int int4 = 0; int4 < this->climateFloats.length; int4++) {
 this->climateFloats[int4].calculate();
 }

 for (int int5 = 0; int5 < this->climateBooleans.length; int5++) {
 this->climateBooleans[int5].calculate();
 }

 this->windPower = this->windIntensity.finalValue;
 this->updateWindTick();
 if (this->tickIsClimateTick) {
 }

 this->updateTestFlare();
 this->thunderStorm.update(this->worldAgeHours);
 if (GameClient.bClient) {
 this->updateSnow();
 } else if (this->tickIsClimateTick && !GameClient.bClient) {
 this->updateSnow();
 }

 if (!GameClient.bClient) {
 this->updateViewDistance();
 }

 if (this->tickIsClimateTick && Core.bDebug && !GameServer.bServer) {
 LuaEventManager.triggerEvent("OnClimateTickDebug", this);
 }

 if (this->tickIsClimateTick && GameServer.bServer && this->tickIsTenMins) {
 this->transmitClimatePacket(ClimateManager.ClimateNetAuth.ServerOnly,
 (byte)0, nullptr);
 this->tickIsTenMins = false;
 }

 if (!this->DISABLE_FX_UPDATE) {
 this->updateFx();
 }
 }
 }

 static double getWindNoiseBase() { return windNoiseBase; }

 static double getWindNoiseFinal() { return windNoiseFinal; }

 static double getWindTickFinal() { return windTickFinal; }

 void updateWindTick() {
 if (!GameServer.bServer) {
 float float0 = this->windIntensity.finalValue;
 windNoiseOffset =
 windNoiseOffset +
 (4.0E-4 + 6.0E-4 * float0) * GameTime.getInstance().getMultiplier();
 windNoiseBase = SimplexNoise.noise(0.0, windNoiseOffset);
 windNoiseFinal = windNoiseBase;
 if (windNoiseFinal > 0.0) {
 windNoiseFinal *= 0.04 + 0.1 * float0;
 } else {
 windNoiseFinal *= 0.04 + 0.1 * float0 + 0.05F * (float0 * float0);
 }

 float0 = clamp01(float0 + (float)windNoiseFinal);
 windTickFinal = float0;
 }
 }

 void updateOLD() {
 this->tickIsClimateTick = false;
 this->tickIsHourChange = false;
 this->tickIsDayChange = false;
 this->gt = GameTime.getInstance();
 this->worldAgeHours = this->gt.getWorldAgeHours();
 if (this->lastMinuteStamp != this->gt.getMinutesStamp()) {
 this->lastMinuteStamp = this->gt.getMinutesStamp();
 this->tickIsClimateTick = true;
 this->updateDayInfo(this->gt.getDay(), this->gt.getMonth(),
 this->gt.getYear());
 this->currentDay.hour = this->gt.getHour();
 this->currentDay.minutes = this->gt.getMinutes();
 if (this->gt.getHour() != this->lastHourStamp) {
 this->tickIsHourChange = true;
 this->lastHourStamp = this->gt.getHour();
 }
 }

 if (GameClient.bClient) {
 if (!this->DISABLE_SIMULATION) {
 this->networkLerp = 1.0F;
 long long0 = System.currentTimeMillis();
 if ((float)long0 <
 (float)this->networkUpdateStamp + this->networkLerpTime) {
 this->networkLerp =
 (float)(long0 - this->networkUpdateStamp) / this->networkLerpTime;
 if (this->networkLerp < 0.0F) {
 this->networkLerp = 0.0F;
 }
 }

 for (int int0 = 0; int0 < this->climateFloats.length; int0++) {
 this->climateFloats[int0].interpolate = this->networkLerp;
 }

 for (int int1 = 0; int1 < this->climateColors.length; int1++) {
 this->climateColors[int1].interpolate = this->networkLerp;
 }

 if (this->tickIsClimateTick) {
 LuaEventManager.triggerEvent("OnClimateTick", this);
 }

 this->updateOnTick();
 this->updateTestFlare();
 this->thunderStorm.update(this->worldAgeHours);
 this->updateSnow();
 if (this->tickIsTenMins) {
 this->tickIsTenMins = false;
 }
 }

 this->updateFx();
 } else {
 if (!this->DISABLE_SIMULATION) {
 if (this->tickIsClimateTick) {
 this->updateValues();
 this->weatherPeriod.update(this->gt.getWorldAgeHours());
 }

 this->updateOnTick();
 this->updateTestFlare();
 this->thunderStorm.update(this->worldAgeHours);
 if (this->tickIsClimateTick) {
 this->updateSnow();
 LuaEventManager.triggerEvent("OnClimateTick", this);
 }

 this->updateViewDistance();
 if (this->tickIsClimateTick && this->tickIsTenMins) {
 if (GameServer.bServer) {
 this->transmitClimatePacket(ClimateManager.ClimateNetAuth.ServerOnly,
 (byte)0, nullptr);
 }

 this->tickIsTenMins = false;
 }
 }

 if (!this->DISABLE_FX_UPDATE && this->tickIsClimateTick) {
 this->updateFx();
 }

 if (this->DISABLE_SIMULATION) {
 IsoPlayer[] players = IsoPlayer.players;

 for (int int2 = 0; int2 < players.length; int2++) {
 IsoPlayer player = players[int2];
 if (player != nullptr) {
 player.dirtyRecalcGridStackTime = 1.0F;
 }
 }
 }
 }
 }

 void updateFx() {
 IsoWeatherFX weatherFX = IsoWorld.instance.getCell().getWeatherFX();
 if (weatherFX != nullptr) {
 weatherFX.setPrecipitationIntensity(
 this->precipitationIntensity.finalValue);
 weatherFX.setWindIntensity(this->windIntensity.finalValue);
 weatherFX.setWindPrecipIntensity((float)windTickFinal *
 (float)windTickFinal);
 weatherFX.setWindAngleIntensity(this->windAngleIntensity.finalValue);
 weatherFX.setFogIntensity(this->fogIntensity.finalValue);
 weatherFX.setCloudIntensity(this->cloudIntensity.finalValue);
 weatherFX.setPrecipitationIsSnow(this->precipitationIsSnow.finalValue);
 SkyBox.getInstance().update(this);
 IsoWater.getInstance().update(this);
 IsoPuddles.getInstance().update(this);
 }
 }

 void updateSnow() {
 if (GameClient.bClient) {
 IsoWorld.instance.CurrentCell.setSnowTarget(
 (int)(this->snowFracNow * 100.0F);
 ErosionIceQueen.instance.setSnow(this->canDoWinterSprites &&
 this->snowFracNow > 0.2F);
 } else {
 if (!this->tickIsHourChange) {
 this->canDoWinterSprites = this->season.isSeason(5) || WINTER_IS_COMING;
 if (this->precipitationIsSnow.finalValue &&
 this->precipitationIntensity.finalValue > this->snowFall) {
 this->snowFall = this->precipitationIntensity.finalValue;
 }

 if (this->temperature.finalValue > 0.0F) {
 float float0 = this->temperature.finalValue / 10.0F;
 float0 =
 float0 * 0.2F + float0 * 0.8F * this->dayLightStrength.finalValue;
 if (float0 > this->snowMeltStrength) {
 this->snowMeltStrength = float0;
 }
 }

 if (!this->precipitationIsSnow.finalValue &&
 this->precipitationIntensity.finalValue > 0.0F) {
 this->snowMeltStrength =
 this->snowMeltStrength + this->precipitationIntensity.finalValue;
 }
 } else {
 this->snowStrength = this->snowStrength + this->snowFall;
 this->snowStrength = this->snowStrength - this->snowMeltStrength;
 this->snowStrength = clamp(0.0F, 10.0F, this->snowStrength);
 this->snowFracNow =
 this->snowStrength > 7.5F ? 1.0F : this->snowStrength / 7.5F;
 IsoWorld.instance.CurrentCell.setSnowTarget(
 (int)(this->snowFracNow * 100.0F);
 ErosionIceQueen.instance.setSnow(this->canDoWinterSprites &&
 this->snowFracNow > 0.2F);
 this->snowFall = 0.0F;
 this->snowMeltStrength = 0.0F;
 }
 }
 }

 void updateSnowOLD() {}

 float getSnowFracNow() { return this->snowFracNow; }

 void resetOverrides() {
 for (int int0 = 0; int0 < this->climateColors.length; int0++) {
 this->climateColors[int0].setEnableOverride(false);
 }

 for (int int1 = 0; int1 < this->climateFloats.length; int1++) {
 this->climateFloats[int1].setEnableOverride(false);
 }

 for (int int2 = 0; int2 < this->climateBooleans.length; int2++) {
 this->climateBooleans[int2].setEnableOverride(false);
 }
 }

 void resetModded() {
 for (int int0 = 0; int0 < this->climateColors.length; int0++) {
 this->climateColors[int0].setEnableModded(false);
 }

 for (int int1 = 0; int1 < this->climateFloats.length; int1++) {
 this->climateFloats[int1].setEnableModded(false);
 }

 for (int int2 = 0; int2 < this->climateBooleans.length; int2++) {
 this->climateBooleans[int2].setEnableModded(false);
 }
 }

 void resetAdmin() {
 for (int int0 = 0; int0 < this->climateColors.length; int0++) {
 this->climateColors[int0].setEnableAdmin(false);
 }

 for (int int1 = 0; int1 < this->climateFloats.length; int1++) {
 this->climateFloats[int1].setEnableAdmin(false);
 }

 for (int int2 = 0; int2 < this->climateBooleans.length; int2++) {
 this->climateBooleans[int2].setEnableAdmin(false);
 }
 }

 void triggerWinterIsComingStorm() {
 if (!GameClient.bClient && !this->weatherPeriod.isRunning()) {
 ClimateManager.AirFront airFront = new ClimateManager.AirFront();
 airFront.copyFrom(this->currentFront);
 airFront.strength = 0.95F;
 airFront.type = 1;
 GameTime gameTime = GameTime.getInstance();
 this->weatherPeriod.init(airFront, this->worldAgeHours, gameTime.getYear(),
 gameTime.getMonth(), gameTime.getDayPlusOne());
 }
 }

 bool triggerCustomWeather(float strength, bool warmFront) {
 if (!GameClient.bClient && !this->weatherPeriod.isRunning()) {
 ClimateManager.AirFront airFront = new ClimateManager.AirFront();
 airFront.strength = strength;
 airFront.type = warmFront ? 1 : -1;
 GameTime gameTime = GameTime.getInstance();
 this->weatherPeriod.init(airFront, this->worldAgeHours, gameTime.getYear(),
 gameTime.getMonth(), gameTime.getDayPlusOne());
 return true;
 } else {
 return false;
 }
 }

 bool triggerCustomWeatherStage(int stage, float duration) {
 if (!GameClient.bClient && !this->weatherPeriod.isRunning()) {
 ClimateManager.AirFront airFront = new ClimateManager.AirFront();
 airFront.strength = 0.95F;
 airFront.type = 1;
 GameTime gameTime = GameTime.getInstance();
 this->weatherPeriod.init(airFront, this->worldAgeHours, gameTime.getYear(),
 gameTime.getMonth(), gameTime.getDayPlusOne(),
 stage, duration);
 return true;
 } else {
 return false;
 }
 }

 void updateOnTick() {
 for (int int0 = 0; int0 < this->climateColors.length; int0++) {
 this->climateColors[int0].calculate();
 }

 for (int int1 = 0; int1 < this->climateFloats.length; int1++) {
 this->climateFloats[int1].calculate();
 }

 for (int int2 = 0; int2 < this->climateBooleans.length; int2++) {
 this->climateBooleans[int2].calculate();
 }
 }

 void updateTestFlare() { WorldFlares.update(); }

 void launchFlare() {
 DebugLog.log("Launching improved flare.");
 IsoPlayer player = IsoPlayer.getInstance();
 float float0 = 0.0F;
 WorldFlares.launchFlare(7200.0F, (int)player.getX(), (int)player.getY(), 50,
 float0, 1.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F);
 if (IsoPlayer.getInstance() != nullptr && !this->flareLaunched) {
 this->flareLaunched = true;
 this->flareLifeTime = 0.0F;
 this->flareMaxLifeTime = 7200.0F;
 this->flareIntensity.overrideCurrentValue(1.0F);
 this->flareIntens = 1.0F;
 this->nextRandomTargetIntens = 10;
 }
 }

 double getAirMassNoiseFrequencyMod(int int0) {
 if (int0 == 1) {
 return 300.0;
 } else if (int0 == 2) {
 return 240.0;
 } else {
 if (int0 != 3) {
 if (int0 == 4) {
 return 145.0;
 }

 if (int0 == 5) {
 return 120.0;
 }
 }

 return 166.0;
 }
 }

 float getRainTimeMultiplierMod(int int0) {
 if (int0 == 1) {
 return 0.5F;
 } else if (int0 == 2) {
 return 0.75F;
 } else if (int0 == 4) {
 return 1.25F;
 } else {
 return int0 = = 5 ? 1.5F : 1.0F;
 }
 }

 void updateValues() {
 if (this->tickIsDayChange && Core.bDebug && !GameClient.bClient &&
 !GameServer.bServer) {
 ErosionMain.getInstance().DebugUpdateMapNow();
 }

 this->climateValues.updateValues(this->worldAgeHours, this->gt.getTimeOfDay(),
 this->currentDay, this->nextDay);
 this->airMass = this->climateValues.getNoiseAirmass();
 this->airMassTemperature = this->climateValues.getAirMassTemperature();
 if (this->tickIsHourChange) {
 int int0 = this->airMass < 0.0F ? -1 : 1;
 if (this->currentFront.type != int0) {
 if (!this->DISABLE_WEATHER_GENERATION &&
 (!WINTER_IS_COMING ||
 WINTER_IS_COMING && GameTime.instance.getWorldAgeHours() > 96.0) {
 if (THE_DESCENDING_FOG) {
 this->currentFront.type = -1;
 this->currentFront.strength = Rand.Next(0.2F, 0.45F);
 this->weatherPeriod.init(this->currentFront, this->worldAgeHours,
 this->gt.getYear(), this->gt.getMonth(),
 this->gt.getDayPlusOne());
 } else {
 this->CalculateWeatherFrontStrength(
 this->gt.getYear(), this->gt.getMonth(), this->gt.getDayPlusOne(),
 this->currentFront);
 this->weatherPeriod.init(this->currentFront, this->worldAgeHours,
 this->gt.getYear(), this->gt.getMonth(),
 this->gt.getDayPlusOne());
 }
 }

 this->currentFront.setFrontType(int0);
 }

 if (!WINTER_IS_COMING && !THE_DESCENDING_FOG &&
 GameTime.instance.getWorldAgeHours() >= 72.0 &&
 GameTime.instance.getWorldAgeHours() <= 96.0 &&
 !this->DISABLE_WEATHER_GENERATION && !this->weatherPeriod.isRunning() &&
 Rand.Next(0, 1000) < 50) {
 }

 if (this->tickIsDayChange) {
 }
 }

 this->dayDoFog = this->climateValues.isDayDoFog();
 this->dayFogStrength = this->climateValues.getDayFogStrength();
 if (PerformanceSettings.FogQuality == 2) {
 this->dayFogStrength = 0.5F + 0.5F * this->dayFogStrength;
 } else {
 this->dayFogStrength = 0.2F + 0.8F * this->dayFogStrength;
 }

 this->baseTemperature = this->climateValues.getBaseTemperature();
 this->dayLightLagged = this->climateValues.getDayLightLagged();
 this->nightLagged = this->climateValues.getDayLightLagged();
 this->temperature.internalValue = this->climateValues.getTemperature();
 this->precipitationIsSnow.internalValue =
 this->climateValues.isTemperatureIsSnow();
 this->humidity.internalValue = this->climateValues.getHumidity();
 this->windIntensity.internalValue = this->climateValues.getWindIntensity();
 this->windAngleIntensity.internalValue =
 this->climateValues.getWindAngleIntensity();
 this->windPower = this->windIntensity.internalValue;
 this->currentFront.setFrontWind(this->climateValues.getWindAngleDegrees());
 this->cloudIntensity.internalValue = this->climateValues.getCloudIntensity();
 this->precipitationIntensity.internalValue = 0.0F;
 this->nightStrength.internalValue = this->climateValues.getNightStrength();
 this->dayLightStrength.internalValue =
 this->climateValues.getDayLightStrength();
 this->ambient.internalValue = this->climateValues.getAmbient();
 this->desaturation.internalValue = this->climateValues.getDesaturation();
 int int1 = this->season.getSeason();
 float float0 = this->season.getSeasonProgression();
 float float1 = 0.0F;
 int int2 = 0;
 int int3 = 0;
 if (int1 == 2) {
 int2 = ClimateManager.SeasonColor.SPRING;
 int3 = ClimateManager.SeasonColor.SUMMER;
 float1 = 0.5F + float0 * 0.5F;
 } else if (int1 == 3) {
 int2 = ClimateManager.SeasonColor.SUMMER;
 int3 = ClimateManager.SeasonColor.FALL;
 float1 = float0 * 0.5F;
 } else if (int1 == 4) {
 if (float0 < 0.5F) {
 int2 = ClimateManager.SeasonColor.SUMMER;
 int3 = ClimateManager.SeasonColor.FALL;
 float1 = 0.5F + float0;
 } else {
 int2 = ClimateManager.SeasonColor.FALL;
 int3 = ClimateManager.SeasonColor.WINTER;
 float1 = float0 - 0.5F;
 }
 } else if (int1 == 5) {
 if (float0 < 0.5F) {
 int2 = ClimateManager.SeasonColor.FALL;
 int3 = ClimateManager.SeasonColor.WINTER;
 float1 = 0.5F + float0;
 } else {
 int2 = ClimateManager.SeasonColor.WINTER;
 int3 = ClimateManager.SeasonColor.SPRING;
 float1 = float0 - 0.5F;
 }
 } else if (int1 == 1) {
 if (float0 < 0.5F) {
 int2 = ClimateManager.SeasonColor.WINTER;
 int3 = ClimateManager.SeasonColor.SPRING;
 float1 = 0.5F + float0;
 } else {
 int2 = ClimateManager.SeasonColor.SPRING;
 int3 = ClimateManager.SeasonColor.SUMMER;
 float1 = float0 - 0.5F;
 }
 }

 float float2 = this->climateValues.getCloudyT();
 this->colDawn = this->seasonColorDawn.update(float2, float1, int2, int3);
 this->colDay = this->seasonColorDay.update(float2, float1, int2, int3);
 this->colDusk = this->seasonColorDusk.update(float2, float1, int2, int3);
 float float3 = this->climateValues.getTime();
 float float4 = this->climateValues.getDawn();
 float float5 = this->climateValues.getDusk();
 float float6 = this->climateValues.getNoon();
 float float7 = this->climateValues.getDayFogDuration();
 if (!THE_DESCENDING_FOG) {
 if (this->dayDoFog && this->dayFogStrength > 0.0F &&
 float3 > float4 - 2.0F && float3 < float4 + float7) {
 float float8 =
 this->getTimeLerpHours(float3, float4 - 2.0F, float4 + float7, true);
 float8 = clamp(0.0F, 1.0F, float8 * (float7 / 3.0F);
 this->fogLerpValue = float8;
 this->cloudIntensity.internalValue =
 lerp(float8, this->cloudIntensity.internalValue, 0.0F);
 float float9 = this->dayFogStrength;
 this->fogIntensity.internalValue = clerp(float8, 0.0F, float9);
 if (Core.getInstance().RenderShader.empty() ||
 Core.getInstance().getOffscreenBuffer() == nullptr) {
 this->desaturation.internalValue =
 clerp(float8, this->desaturation.internalValue, 0.8F * float9);
 } else if (PerformanceSettings.FogQuality == 2) {
 this->desaturation.internalValue =
 clerp(float8, this->desaturation.internalValue, 0.8F * float9);
 } else {
 this->desaturation.internalValue =
 clerp(float8, this->desaturation.internalValue, 0.65F * float9);
 }
 } else {
 this->fogIntensity.internalValue = 0.0F;
 }
 } else {
 if (this->gt.getWorldAgeHours() < 72.0) {
 this->fogIntensity.internalValue =
 (float)this->gt.getWorldAgeHours() / 72.0F;
 } else {
 this->fogIntensity.internalValue = 1.0F;
 }

 this->cloudIntensity.internalValue =
 Math.min(this->cloudIntensity.internalValue,
 1.0F - this->fogIntensity.internalValue);
 if (this->weatherPeriod.isRunning()) {
 this->fogIntensity.internalValue =
 Math.min(this->fogIntensity.internalValue, 0.6F);
 }

 if (PerformanceSettings.FogQuality == 2) {
 this->fogIntensity.internalValue *= 0.93F;
 this->desaturation.internalValue =
 0.8F * this->fogIntensity.internalValue;
 } else {
 this->desaturation.internalValue =
 0.65F * this->fogIntensity.internalValue;
 }
 }

 this->humidity.internalValue = clamp01(
 this->humidity.internalValue + this->fogIntensity.internalValue * 0.6F);
 float float10 = 0.6F * this->climateValues.getDayLightStrengthBase();
 float float11 = 0.4F;
 float float12 = 0.25F * this->climateValues.getDayLightStrengthBase();
 if (Core.getInstance().RenderShader != nullptr &&
 Core.getInstance().getOffscreenBuffer() != nullptr) {
 float12 = 0.8F * this->climateValues.getDayLightStrengthBase();
 }

 if (float3 < float4 || float3 > float5) {
 float float13 = 24.0F - float5 + float4;
 if (float3 > float5) {
 float float14 = (float3 - float5) / float13;
 this->colDusk.interp(this->colDawn, float14,
 this->globalLight.internalValue);
 } else {
 float float15 = (24.0F - float5 + float3) / float13;
 this->colDusk.interp(this->colDawn, float15,
 this->globalLight.internalValue);
 }

 this->globalLightIntensity.internalValue =
 lerp(this->climateValues.getLerpNight(), float12, float11);
 } else if (float3 < float6 + 2.0F) {
 float float16 = (float3 - float4) / (float6 + 2.0F - float4);
 this->colDawn.interp(this->colDay, float16, this->globalLight.internalValue);
 this->globalLightIntensity.internalValue = lerp(float16, float12, float10);
 } else {
 float float17 = (float3 - (float6 + 2.0F) / (float5 - (float6 + 2.0F);
 this->colDay.interp(this->colDusk, float17, this->globalLight.internalValue);
 this->globalLightIntensity.internalValue = lerp(float17, float10, float12);
 }

 if (this->fogIntensity.internalValue > 0.0F) {
 if (Core.getInstance().RenderShader.empty() ||
 Core.getInstance().getOffscreenBuffer() == nullptr) {
 this->globalLight.internalValue.interp(this->colFogLegacy,
 this->fogIntensity.internalValue,
 this->globalLight.internalValue);
 } else if (PerformanceSettings.FogQuality == 2) {
 this->globalLight.internalValue.interp(this->colFog,
 this->fogIntensity.internalValue,
 this->globalLight.internalValue);
 } else {
 this->globalLight.internalValue.interp(this->colFogNew,
 this->fogIntensity.internalValue,
 this->globalLight.internalValue);
 }

 this->globalLightIntensity.internalValue = clerp(
 this->fogLerpValue, this->globalLightIntensity.internalValue, 0.8F);
 }

 this->colNightNoMoon.interp(this->colNightMoon, ClimateMoon.getMoonFloat(),
 this->colNight);
 this->globalLight.internalValue.interp(this->colNight,
 this->nightStrength.internalValue,
 this->globalLight.internalValue);
 IsoPlayer[] players = IsoPlayer.players;

 for (int int4 = 0; int4 < players.length; int4++) {
 IsoPlayer player = players[int4];
 if (player != nullptr) {
 player.dirtyRecalcGridStackTime = 1.0F;
 }
 }
 }

 void updateViewDistance() {
 float float0 = this->dayLightStrength.finalValue;
 float float1 = this->fogIntensity.finalValue;
 float float2 = 19.0F - float1 * 8.0F;
 float float3 = float2 + 4.0F + 7.0F * float0 * (1.0F - float1);
 float2 *= 3.0F;
 float3 *= 3.0F;
 this->gt.setViewDistMin(float2);
 this->gt.setViewDistMax(float3);
 this->viewDistance.internalValue = float2 + (float3 - float2) * float0;
 this->viewDistance.finalValue = this->viewDistance.internalValue;
 }

 void setSeasonColorDawn(int _temperature, int _season, float r, float g,
 float b, float a, bool exterior) {
 if (exterior) {
 this->seasonColorDawn.setColorExterior(_temperature, _season, r, g, b, a);
 } else {
 this->seasonColorDawn.setColorInterior(_temperature, _season, r, g, b, a);
 }
 }

 void setSeasonColorDay(int _temperature, int _season, float r, float g,
 float b, float a, bool exterior) {
 if (exterior) {
 this->seasonColorDay.setColorExterior(_temperature, _season, r, g, b, a);
 } else {
 this->seasonColorDay.setColorInterior(_temperature, _season, r, g, b, a);
 }
 }

 void setSeasonColorDusk(int _temperature, int _season, float r, float g,
 float b, float a, bool exterior) {
 if (exterior) {
 this->seasonColorDusk.setColorExterior(_temperature, _season, r, g, b, a);
 } else {
 this->seasonColorDusk.setColorInterior(_temperature, _season, r, g, b, a);
 }
 }

 ClimateColorInfo getSeasonColor(int segment, int _temperature, int _season) {
 ClimateManager.SeasonColor seasonColor = nullptr;
 if (segment == 0) {
 seasonColor = this->seasonColorDawn;
 } else if (segment == 1) {
 seasonColor = this->seasonColorDay;
 } else if (segment == 2) {
 seasonColor = this->seasonColorDusk;
 }

 return seasonColor != nullptr ? seasonColor.getColor(_temperature, _season)
 : nullptr;
 }

 void initSeasonColors() {
 ClimateManager.SeasonColor seasonColor = new ClimateManager.SeasonColor();
 seasonColor.setIgnoreNormal(true);
 this->seasonColorDawn = seasonColor;
 seasonColor = new ClimateManager.SeasonColor();
 seasonColor.setIgnoreNormal(true);
 this->seasonColorDay = seasonColor;
 seasonColor = new ClimateManager.SeasonColor();
 seasonColor.setIgnoreNormal(false);
 this->seasonColorDusk = seasonColor;
 }

 /**
 * IO
 */
 void save(DataOutputStream output) {
 if (GameClient.bClient && !GameServer.bServer) {
 output.writeByte(0);
 } else {
 output.writeByte(1);
 output.writeDouble(this->simplexOffsetA);
 output.writeDouble(this->simplexOffsetB);
 output.writeDouble(this->simplexOffsetC);
 output.writeDouble(this->simplexOffsetD);
 this->currentFront.save(output);
 output.writeFloat(this->snowFracNow);
 output.writeFloat(this->snowStrength);
 output.writeBoolean(this->canDoWinterSprites);
 output.writeBoolean(this->dayDoFog);
 output.writeFloat(this->dayFogStrength);
 }

 this->weatherPeriod.save(output);
 this->thunderStorm.save(output);
 if (GameServer.bServer) {
 this->desaturation.saveAdmin(output);
 this->globalLightIntensity.saveAdmin(output);
 this->nightStrength.saveAdmin(output);
 this->precipitationIntensity.saveAdmin(output);
 this->temperature.saveAdmin(output);
 this->fogIntensity.saveAdmin(output);
 this->windIntensity.saveAdmin(output);
 this->windAngleIntensity.saveAdmin(output);
 this->cloudIntensity.saveAdmin(output);
 this->ambient.saveAdmin(output);
 this->viewDistance.saveAdmin(output);
 this->dayLightStrength.saveAdmin(output);
 this->globalLight.saveAdmin(output);
 this->precipitationIsSnow.saveAdmin(output);
 }

 if (this->modDataTable != nullptr) {
 output.writeByte(1);
 this->modDataTable.save(output);
 } else {
 output.writeByte(0);
 }

 if (GameServer.bServer) {
 this->humidity.saveAdmin(output);
 }
 }

 void load(DataInputStream input, int worldVersion) {
 bool boolean0 = input.readByte() == 1;
 if (boolean0) {
 this->simplexOffsetA = input.readDouble();
 this->simplexOffsetB = input.readDouble();
 this->simplexOffsetC = input.readDouble();
 this->simplexOffsetD = input.readDouble();
 this->currentFront.load(input);
 this->snowFracNow = input.readFloat();
 this->snowStrength = input.readFloat();
 this->canDoWinterSprites = input.readBoolean();
 this->dayDoFog = input.readBoolean();
 this->dayFogStrength = input.readFloat();
 }

 this->weatherPeriod.load(input, worldVersion);
 this->thunderStorm.load(input);
 if (worldVersion >= 140 && GameServer.bServer) {
 this->desaturation.loadAdmin(input, worldVersion);
 this->globalLightIntensity.loadAdmin(input, worldVersion);
 this->nightStrength.loadAdmin(input, worldVersion);
 this->precipitationIntensity.loadAdmin(input, worldVersion);
 this->temperature.loadAdmin(input, worldVersion);
 this->fogIntensity.loadAdmin(input, worldVersion);
 this->windIntensity.loadAdmin(input, worldVersion);
 this->windAngleIntensity.loadAdmin(input, worldVersion);
 this->cloudIntensity.loadAdmin(input, worldVersion);
 this->ambient.loadAdmin(input, worldVersion);
 this->viewDistance.loadAdmin(input, worldVersion);
 this->dayLightStrength.loadAdmin(input, worldVersion);
 this->globalLight.loadAdmin(input, worldVersion);
 this->precipitationIsSnow.loadAdmin(input, worldVersion);
 }

 if (worldVersion >= 141 && input.readByte() == 1) {
 if (this->modDataTable.empty()) {
 this->modDataTable = LuaManager.platform.newTable();
 }

 this->modDataTable.load(input, worldVersion);
 }

 if (worldVersion >= 150 && GameServer.bServer) {
 this->humidity.loadAdmin(input, worldVersion);
 }

 this->climateValues = new ClimateValues(this);
 }

 void postCellLoadSetSnow() {
 IsoWorld.instance.CurrentCell.setSnowTarget(
 (int)(this->snowFracNow * 100.0F);
 ErosionIceQueen.instance.setSnow(this->canDoWinterSprites &&
 this->snowFracNow > 0.2F);
 }

 void forceDayInfoUpdate() {
 this->currentDay.day = -1;
 this->currentDay.month = -1;
 this->currentDay.year = -1;
 this->gt = GameTime.getInstance();
 this->updateDayInfo(this->gt.getDayPlusOne(), this->gt.getMonth(),
 this->gt.getYear());
 this->currentDay.hour = this->gt.getHour();
 this->currentDay.minutes = this->gt.getMinutes();
 }

 void updateDayInfo(int int2, int int1, int int0) {
 this->tickIsDayChange = false;
 if (this->currentDay.empty() || this->currentDay.day != int2 ||
 this->currentDay.month != int1 || this->currentDay.year != int0) {
 this->tickIsDayChange = this->currentDay != nullptr;
 if (this->currentDay.empty()) {
 this->currentDay = new ClimateManager.DayInfo();
 }

 this->setDayInfo(this->currentDay, int2, int1, int0, 0);
 if (this->previousDay.empty()) {
 this->previousDay = new ClimateManager.DayInfo();
 this->previousDay.season = this->season.clone();
 }

 this->setDayInfo(this->previousDay, int2, int1, int0, -1);
 if (this->nextDay.empty()) {
 this->nextDay = new ClimateManager.DayInfo();
 this->nextDay.season = this->season.clone();
 }

 this->setDayInfo(this->nextDay, int2, int1, int0, 1);
 }
 }

 void setDayInfo(ClimateManager.DayInfo dayInfo, int int2, int int1, int int0,
 int int3) {
 dayInfo.calendar = new GregorianCalendar(int0, int1, int2, 0, 0);
 dayInfo.calendar.add(5, int3);
 dayInfo.day = dayInfo.calendar.get(5);
 dayInfo.month = dayInfo.calendar.get(2);
 dayInfo.year = dayInfo.calendar.get(1);
 dayInfo.dateValue = dayInfo.calendar.getTime().getTime();
 if (dayInfo.season.empty()) {
 dayInfo.season = this->season.clone();
 }

 dayInfo.season.setDay(dayInfo.day, dayInfo.month, dayInfo.year);
 }

 void transmitClimatePacket(ClimateManager.ClimateNetAuth climateNetAuth,
 uint8_t byte0, UdpConnection udpConnection1) {
 if (GameClient.bClient || GameServer.bServer) {
 if (climateNetAuth == ClimateManager.ClimateNetAuth.Denied) {
 DebugLog.log("Denied ClimatePacket, id = " + byte0 +
 ", isClient = " + GameClient.bClient);
 } else {
 if (GameClient.bClient &&
 (climateNetAuth == ClimateManager.ClimateNetAuth.ClientOnly ||
 climateNetAuth == ClimateManager.ClimateNetAuth.ClientAndServer) {
 try {
 if (this->writePacketContents(GameClient.connection, byte0) {
 PacketTypes.PacketType.ClimateManagerPacket.send(
 GameClient.connection);
 } else {
 GameClient.connection.cancelPacket();
 }
 } catch (Exception exception0) {
 DebugLog.log(exception0.getMessage());
 }
 }

 if (GameServer.bServer &&
 (climateNetAuth == ClimateManager.ClimateNetAuth.ServerOnly ||
 climateNetAuth == ClimateManager.ClimateNetAuth.ClientAndServer) {
 try {
 for (int int0 = 0; int0 < GameServer.udpEngine.connections.size();
 int0++) {
 UdpConnection udpConnection0 =
 GameServer.udpEngine.connections.get(int0);
 if (udpConnection1.empty() ||
 udpConnection1 != udpConnection0) {
 if (this->writePacketContents(udpConnection0, byte0) {
 PacketTypes.PacketType.ClimateManagerPacket.send(
 udpConnection0);
 } else {
 udpConnection0.cancelPacket();
 }
 }
 }
 } catch (Exception exception1) {
 DebugLog.log(exception1.getMessage());
 }
 }
 }
 }
 }

 bool writePacketContents(UdpConnection udpConnection, uint8_t byte0) {
 if (!GameClient.bClient && !GameServer.bServer) {
 return false;
 } else {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.ClimateManagerPacket.doPacket(byteBufferWriter);
 ByteBuffer byteBuffer = byteBufferWriter.bb;
 byteBuffer.put(byte0);
 switch (byte0) {
 case 0:
 if (this->networkPrint) {
 DebugLog.log("clim: send PacketUpdateClimateVars");
 }

 for (int int0 = 0; int0 < this->climateFloats.length; int0++) {
 byteBuffer.putFloat(this->climateFloats[int0].finalValue);
 }

 for (int int1 = 0; int1 < this->climateColors.length; int1++) {
 this->climateColors[int1].finalValue.write(byteBuffer);
 }

 for (int int2 = 0; int2 < this->climateBooleans.length; int2++) {
 byteBuffer.put((byte)(this->climateBooleans[int2].finalValue ? 1 : 0);
 }

 byteBuffer.putFloat(this->airMass);
 byteBuffer.putFloat(this->airMassDaily);
 byteBuffer.putFloat(this->airMassTemperature);
 byteBuffer.putFloat(this->snowFracNow);
 byteBuffer.putFloat(this->snowStrength);
 byteBuffer.putFloat(this->windPower);
 byteBuffer.put((byte)(this->dayDoFog ? 1 : 0);
 byteBuffer.putFloat(this->dayFogStrength);
 byteBuffer.put((byte)(this->canDoWinterSprites ? 1 : 0);
 this->weatherPeriod.writeNetWeatherData(byteBuffer);
 return true;
 case 1:
 if (this->networkPrint) {
 DebugLog.log("clim: send PacketWeatherUpdate");
 }

 this->weatherPeriod.writeNetWeatherData(byteBuffer);
 return true;
 case 2:
 if (this->networkPrint) {
 DebugLog.log("clim: send PacketThunderEvent");
 }

 this->thunderStorm.writeNetThunderEvent(byteBuffer);
 return true;
 case 3:
 if (this->networkPrint) {
 DebugLog.log("clim: send PacketFlare");
 }

 return true;
 case 4:
 if (!GameServer.bServer) {
 return false;
 }

 if (this->networkPrint) {
 DebugLog.log("clim: send PacketAdminVarsUpdate");
 }

 for (int int6 = 0; int6 < this->climateFloats.length; int6++) {
 this->climateFloats[int6].writeAdmin(byteBuffer);
 }

 for (int int7 = 0; int7 < this->climateColors.length; int7++) {
 this->climateColors[int7].writeAdmin(byteBuffer);
 }

 for (int int8 = 0; int8 < this->climateBooleans.length; int8++) {
 this->climateBooleans[int8].writeAdmin(byteBuffer);
 }

 return true;
 case 5:
 if (!GameClient.bClient) {
 return false;
 }

 if (this->networkPrint) {
 DebugLog.log("clim: send PacketRequestAdminVars");
 }

 byteBuffer.put((byte)1);
 return true;
 case 6:
 if (!GameClient.bClient) {
 return false;
 }

 if (this->networkPrint) {
 DebugLog.log("clim: send PacketClientChangedAdminVars");
 }

 for (int int3 = 0; int3 < this->climateFloats.length; int3++) {
 this->climateFloats[int3].writeAdmin(byteBuffer);
 }

 for (int int4 = 0; int4 < this->climateColors.length; int4++) {
 this->climateColors[int4].writeAdmin(byteBuffer);
 }

 for (int int5 = 0; int5 < this->climateBooleans.length; int5++) {
 this->climateBooleans[int5].writeAdmin(byteBuffer);
 }

 return true;
 case 7:
 if (!GameClient.bClient) {
 return false;
 }

 if (this->networkPrint) {
 DebugLog.log("clim: send PacketClientChangedWeather");
 }

 byteBuffer.put((byte)(this->netInfo.IsStopWeather ? 1 : 0);
 byteBuffer.put((byte)(this->netInfo.IsTrigger ? 1 : 0);
 byteBuffer.put((byte)(this->netInfo.IsGenerate ? 1 : 0);
 byteBuffer.putFloat(this->netInfo.TriggerDuration);
 byteBuffer.put((byte)(this->netInfo.TriggerStorm ? 1 : 0);
 byteBuffer.put((byte)(this->netInfo.TriggerTropical ? 1 : 0);
 byteBuffer.put((byte)(this->netInfo.TriggerBlizzard ? 1 : 0);
 byteBuffer.putFloat(this->netInfo.GenerateStrength);
 byteBuffer.putInt(this->netInfo.GenerateFront);
 return true;
 default:
 return false;
 }
 }
 }

 void receiveClimatePacket(ByteBuffer bb, UdpConnection ignoreConnection) {
 if (GameClient.bClient || GameServer.bServer) {
 uint8_t byte0 = bb.get();
 this->readPacketContents(bb, byte0, ignoreConnection);
 }
 }

 bool readPacketContents(ByteBuffer byteBuffer, uint8_t byte0,
 UdpConnection var3) {
 switch (byte0) {
 case 0:
 if (!GameClient.bClient) {
 return false;
 }

 if (this->networkPrint) {
 DebugLog.log("clim: receive PacketUpdateClimateVars");
 }

 for (int int0 = 0; int0 < this->climateFloats.length; int0++) {
 ClimateManager.ClimateFloat climateFloat = this->climateFloats[int0];
 climateFloat.internalValue = climateFloat.finalValue;
 climateFloat.setOverride(byteBuffer.getFloat(), 0.0F);
 }

 for (int int1 = 0; int1 < this->climateColors.length; int1++) {
 ClimateManager.ClimateColor climateColor = this->climateColors[int1];
 climateColor.internalValue.setTo(climateColor.finalValue);
 climateColor.setOverride(byteBuffer, 0.0F);
 }

 for (int int2 = 0; int2 < this->climateBooleans.length; int2++) {
 ClimateManager.ClimateBool climateBool = this->climateBooleans[int2];
 climateBool.setOverride(byteBuffer.get() == 1);
 }

 this->airMass = byteBuffer.getFloat();
 this->airMassDaily = byteBuffer.getFloat();
 this->airMassTemperature = byteBuffer.getFloat();
 this->snowFracNow = byteBuffer.getFloat();
 this->snowStrength = byteBuffer.getFloat();
 this->windPower = byteBuffer.getFloat();
 this->dayDoFog = byteBuffer.get() == 1;
 this->dayFogStrength = byteBuffer.getFloat();
 this->canDoWinterSprites = byteBuffer.get() == 1;
 long long0 = System.currentTimeMillis();
 if ((float)(long0 - this->networkUpdateStamp) < this->networkLerpTime) {
 this->networkAdjustVal++;
 if (this->networkAdjustVal > 10.0F) {
 this->networkAdjustVal = 10.0F;
 }
 } else {
 this->networkAdjustVal--;
 if (this->networkAdjustVal < 0.0F) {
 this->networkAdjustVal = 0.0F;
 }
 }

 if (this->networkAdjustVal > 0.0F) {
 this->networkLerpTime = this->networkLerpTimeBase / this->networkAdjustVal;
 } else {
 this->networkLerpTime = this->networkLerpTimeBase;
 }

 this->networkUpdateStamp = long0;
 this->weatherPeriod.readNetWeatherData(byteBuffer);
 return true;
 case 1:
 if (this->networkPrint) {
 DebugLog.log("clim: receive PacketWeatherUpdate");
 }

 this->weatherPeriod.readNetWeatherData(byteBuffer);
 return true;
 case 2:
 if (this->networkPrint) {
 DebugLog.log("clim: receive PacketThunderEvent");
 }

 this->thunderStorm.readNetThunderEvent(byteBuffer);
 return true;
 case 3:
 if (this->networkPrint) {
 DebugLog.log("clim: receive PacketFlare");
 }

 return true;
 case 4:
 if (!GameClient.bClient) {
 return false;
 }

 if (this->networkPrint) {
 DebugLog.log("clim: receive PacketAdminVarsUpdate");
 }

 for (int int6 = 0; int6 < this->climateFloats.length; int6++) {
 this->climateFloats[int6].readAdmin(byteBuffer);
 }

 for (int int7 = 0; int7 < this->climateColors.length; int7++) {
 this->climateColors[int7].readAdmin(byteBuffer);
 }

 for (int int8 = 0; int8 < this->climateBooleans.length; int8++) {
 this->climateBooleans[int8].readAdmin(byteBuffer);
 }

 return true;
 case 5:
 if (!GameServer.bServer) {
 return false;
 }

 if (this->networkPrint) {
 DebugLog.log("clim: receive PacketRequestAdminVars");
 }

 byteBuffer.get();
 this->transmitClimatePacket(ClimateManager.ClimateNetAuth.ServerOnly,
 (byte)4, nullptr);
 return true;
 case 6:
 if (!GameServer.bServer) {
 return false;
 }

 if (this->networkPrint) {
 DebugLog.log("clim: receive PacketClientChangedAdminVars");
 }

 for (int int3 = 0; int3 < this->climateFloats.length; int3++) {
 this->climateFloats[int3].readAdmin(byteBuffer);
 }

 for (int int4 = 0; int4 < this->climateColors.length; int4++) {
 this->climateColors[int4].readAdmin(byteBuffer);
 }

 for (int int5 = 0; int5 < this->climateBooleans.length; int5++) {
 this->climateBooleans[int5].readAdmin(byteBuffer);
 if (int5 == 0) {
 DebugLog.log(
 "Snow = " + this->climateBooleans[int5].adminValue +
 ", enabled = " + this->climateBooleans[int5].isAdminOverride);
 }
 }

 this->serverReceiveClientChangeAdminVars();
 return true;
 case 7:
 if (!GameServer.bServer) {
 return false;
 }

 if (this->networkPrint) {
 DebugLog.log("clim: receive PacketClientChangedWeather");
 }

 this->netInfo.IsStopWeather = byteBuffer.get() == 1;
 this->netInfo.IsTrigger = byteBuffer.get() == 1;
 this->netInfo.IsGenerate = byteBuffer.get() == 1;
 this->netInfo.TriggerDuration = byteBuffer.getFloat();
 this->netInfo.TriggerStorm = byteBuffer.get() == 1;
 this->netInfo.TriggerTropical = byteBuffer.get() == 1;
 this->netInfo.TriggerBlizzard = byteBuffer.get() == 1;
 this->netInfo.GenerateStrength = byteBuffer.getFloat();
 this->netInfo.GenerateFront = byteBuffer.getInt();
 this->serverReceiveClientChangeWeather();
 return true;
 default:
 return false;
 }
 }

 void serverReceiveClientChangeAdminVars() {
 if (GameServer.bServer) {
 if (this->networkPrint) {
 DebugLog.log("clim: serverReceiveClientChangeAdminVars");
 }

 this->transmitClimatePacket(ClimateManager.ClimateNetAuth.ServerOnly,
 (byte)4, nullptr);
 this->updateOnTick();
 this->transmitClimatePacket(ClimateManager.ClimateNetAuth.ServerOnly,
 (byte)0, nullptr);
 }
 }

 void serverReceiveClientChangeWeather() {
 if (GameServer.bServer) {
 if (this->networkPrint) {
 DebugLog.log("clim: serverReceiveClientChangeWeather");
 }

 if (this->netInfo.IsStopWeather) {
 if (this->networkPrint) {
 DebugLog.log("clim: IsStopWeather");
 }

 this->stopWeatherAndThunder();
 } else if (this->netInfo.IsTrigger) {
 this->stopWeatherAndThunder();
 if (this->netInfo.TriggerStorm) {
 if (this->networkPrint) {
 DebugLog.log("clim: Trigger Storm");
 }

 this->triggerCustomWeatherStage(3, this->netInfo.TriggerDuration);
 } else if (this->netInfo.TriggerTropical) {
 if (this->networkPrint) {
 DebugLog.log("clim: Trigger Tropical");
 }

 this->triggerCustomWeatherStage(8, this->netInfo.TriggerDuration);
 } else if (this->netInfo.TriggerBlizzard) {
 if (this->networkPrint) {
 DebugLog.log("clim: Trigger Blizzard");
 }

 this->triggerCustomWeatherStage(7, this->netInfo.TriggerDuration);
 }
 } else if (this->netInfo.IsGenerate) {
 if (this->networkPrint) {
 DebugLog.log("clim: IsGenerate");
 }

 this->stopWeatherAndThunder();
 this->triggerCustomWeather(this->netInfo.GenerateStrength,
 this->netInfo.GenerateFront == 0);
 }

 this->updateOnTick();
 this->transmitClimatePacket(ClimateManager.ClimateNetAuth.ServerOnly,
 (byte)0, nullptr);
 }
 }

 void transmitServerStopWeather() {
 if (GameServer.bServer) {
 this->stopWeatherAndThunder();
 if (this->networkPrint) {
 DebugLog.log("clim: SERVER transmitStopWeather");
 }

 this->updateOnTick();
 this->transmitClimatePacket(ClimateManager.ClimateNetAuth.ServerOnly,
 (byte)0, nullptr);
 }
 }

 void transmitServerTriggerStorm(float duration) {
 if (GameServer.bServer) {
 if (this->networkPrint) {
 DebugLog.log("clim: SERVER transmitTriggerStorm");
 }

 this->netInfo.TriggerDuration = duration;
 this->triggerCustomWeatherStage(3, this->netInfo.TriggerDuration);
 this->updateOnTick();
 this->transmitClimatePacket(ClimateManager.ClimateNetAuth.ServerOnly,
 (byte)0, nullptr);
 }
 }

 void transmitServerTriggerLightning(int x, int y, bool doStrike,
 bool doLightning, bool doRumble) {
 if (GameServer.bServer) {
 if (this->networkPrint) {
 DebugLog.log("clim: SERVER transmitTriggerLightning");
 }

 this->thunderStorm.triggerThunderEvent(x, y, doStrike, doLightning,
 doRumble);
 }
 }

 void transmitServerStartRain(float intensity) {
 if (GameServer.bServer) {
 this->precipitationIntensity.setAdminValue(clamp01(intensity);
 this->precipitationIntensity.setEnableAdmin(true);
 this->updateOnTick();
 this->transmitClimatePacket(ClimateManager.ClimateNetAuth.ServerOnly,
 (byte)0, nullptr);
 }
 }

 void transmitServerStopRain() {
 if (GameServer.bServer) {
 this->precipitationIntensity.setEnableAdmin(false);
 this->updateOnTick();
 this->transmitClimatePacket(ClimateManager.ClimateNetAuth.ServerOnly,
 (byte)0, nullptr);
 }
 }

 void transmitRequestAdminVars() {
 if (this->networkPrint) {
 DebugLog.log("clim: transmitRequestAdminVars");
 }

 this->transmitClimatePacket(ClimateManager.ClimateNetAuth.ClientOnly,
 (byte)5, nullptr);
 }

 void transmitClientChangeAdminVars() {
 if (this->networkPrint) {
 DebugLog.log("clim: transmitClientChangeAdminVars");
 }

 this->transmitClimatePacket(ClimateManager.ClimateNetAuth.ClientOnly,
 (byte)6, nullptr);
 }

 void transmitStopWeather() {
 if (this->networkPrint) {
 DebugLog.log("clim: transmitStopWeather");
 }

 this->netInfo.reset();
 this->netInfo.IsStopWeather = true;
 this->transmitClimatePacket(ClimateManager.ClimateNetAuth.ClientOnly,
 (byte)7, nullptr);
 }

 void transmitTriggerStorm(float duration) {
 if (this->networkPrint) {
 DebugLog.log("clim: transmitTriggerStorm");
 }

 this->netInfo.reset();
 this->netInfo.IsTrigger = true;
 this->netInfo.TriggerStorm = true;
 this->netInfo.TriggerDuration = duration;
 this->transmitClimatePacket(ClimateManager.ClimateNetAuth.ClientOnly,
 (byte)7, nullptr);
 }

 void transmitTriggerTropical(float duration) {
 if (this->networkPrint) {
 DebugLog.log("clim: transmitTriggerTropical");
 }

 this->netInfo.reset();
 this->netInfo.IsTrigger = true;
 this->netInfo.TriggerTropical = true;
 this->netInfo.TriggerDuration = duration;
 this->transmitClimatePacket(ClimateManager.ClimateNetAuth.ClientOnly,
 (byte)7, nullptr);
 }

 void transmitTriggerBlizzard(float duration) {
 if (this->networkPrint) {
 DebugLog.log("clim: transmitTriggerBlizzard");
 }

 this->netInfo.reset();
 this->netInfo.IsTrigger = true;
 this->netInfo.TriggerBlizzard = true;
 this->netInfo.TriggerDuration = duration;
 this->transmitClimatePacket(ClimateManager.ClimateNetAuth.ClientOnly,
 (byte)7, nullptr);
 }

 void transmitGenerateWeather(float strength, int front) {
 if (this->networkPrint) {
 DebugLog.log("clim: transmitGenerateWeather");
 }

 this->netInfo.reset();
 this->netInfo.IsGenerate = true;
 this->netInfo.GenerateStrength = clamp01(strength);
 this->netInfo.GenerateFront = front;
 if (this->netInfo.GenerateFront < 0 || this->netInfo.GenerateFront > 1) {
 this->netInfo.GenerateFront = 0;
 }

 this->transmitClimatePacket(ClimateManager.ClimateNetAuth.ClientOnly,
 (byte)7, nullptr);
 }

 float getTimeLerpHours(float float0, float float1, float float2) {
 return this->getTimeLerpHours(float0, float1, float2, false);
 }

 float getTimeLerpHours(float float2, float float1, float float0,
 bool boolean0) {
 return this->getTimeLerp(clamp(0.0F, 1.0F, float2 / 24.0F),
 clamp(0.0F, 1.0F, float1 / 24.0F),
 clamp(0.0F, 1.0F, float0 / 24.0F), boolean0);
 }

 float getTimeLerp(float float0, float float1, float float2) {
 return this->getTimeLerp(float0, float1, float2, false);
 }

 float getTimeLerp(float float2, float float0, float float1, bool boolean1) {
 bool boolean0 = float0 > float1;
 if (!boolean0) {
 if (!(float2 < float0) && !(float2 > float1) {
 float float3 = float2 - float0;
 float float4 = float1 - float0;
 float float5 = float4 * 0.5F;
 if (float3 < float5) {
 return boolean1 ? clerp(float3 / float5, 0.0F, 1.0F)
 : lerp(float3 / float5, 0.0F, 1.0F);
 } else {
 return boolean1 ? clerp((float3 - float5) / float5, 1.0F, 0.0F)
 : lerp((float3 - float5) / float5, 1.0F, 0.0F);
 }
 } else {
 return 0.0F;
 }
 } else if (float2 < float0 && float2 > float1) {
 return 0.0F;
 } else {
 float float6 = 1.0F - float0;
 float float7 = float2 >= float0 ? float2 - float0 : float2 + float6;
 float float8 = float1 + float6;
 float float9 = float8 * 0.5F;
 if (float7 < float9) {
 return boolean1 ? clerp(float7 / float9, 0.0F, 1.0F)
 : lerp(float7 / float9, 0.0F, 1.0F);
 } else {
 return boolean1 ? clerp((float7 - float9) / float9, 1.0F, 0.0F)
 : lerp((float7 - float9) / float9, 1.0F, 0.0F);
 }
 }
 }

 static float clamp01(float val) { return clamp(); }

 static float clamp(float min, float max, float val) {
 val = Math.min(max, val);
 return Math.max(min, val);
 }

 static int clamp(int min, int max, int val) {
 val = Math.min(max, val);
 return Math.max(min, val);
 }

 static float lerp(float t, float a, float b) { return a + t * (b - a); }

 static float clerp(float t, float a, float b) {
 float float0 = (float)(1.0 - Math.cos(t * Math.PI) / 2.0F;
 return a * (1.0F - float0) + b * float0;
 }

 static float normalizeRange(float v, float n) { return clamp(v /); }

 static float posToPosNegRange(float v) {
 if (v > 0.5F) {
 return (v - 0.5F) * 2.0F;
 } else {
 return v < 0.5F ? -((0.5F - v) * 2.0F) : 0.0F;
 }
 }

 void execute_Simulation() {
 if (Core.bDebug) {
 ClimMngrDebug climMngrDebug = new ClimMngrDebug();
 short short0 = 365;
 short short1 = 5000;
 climMngrDebug.SimulateDays(short0, short1);
 }
 }

 void execute_Simulation(int RainModOverride) {
 if (Core.bDebug) {
 ClimMngrDebug climMngrDebug = new ClimMngrDebug();
 climMngrDebug.setRainModOverride(RainModOverride);
 short short0 = 365;
 short short1 = 5000;
 climMngrDebug.SimulateDays(short0, short1);
 }
 }

 void triggerKateBobIntroStorm(int centerX, int centerY, double duration,
 float strength, float initialProgress,
 float angle, float initialPuddles) {
 this->triggerKateBobIntroStorm(centerX, centerY, duration, strength,
 initialProgress, angle, initialPuddles,
 nullptr);
 }

public
 void triggerKateBobIntroStorm(int centerX, int centerY, double duration,
 float strength, float initialProgress,
 float angle, float initialPuddles,
 ClimateColorInfo cloudcolor) {
 if (!GameClient.bClient) {
 this->stopWeatherAndThunder();
 if (this->weatherPeriod.startCreateModdedPeriod(true, strength, angle) {
 this->weatherPeriod.setKateBobStormProgress(initialProgress);
 this->weatherPeriod.setKateBobStormCoords(centerX, centerY);
 this->weatherPeriod.createAndAddStage(11, duration);
 this->weatherPeriod.createAndAddStage(2, duration / 2.0);
 this->weatherPeriod.createAndAddStage(4, duration / 4.0);
 this->weatherPeriod.endCreateModdedPeriod();
 if (cloudcolor != nullptr) {
 this->weatherPeriod.setCloudColor(cloudcolor);
 } else {
 this->weatherPeriod.setCloudColor(
 this->weatherPeriod.getCloudColorBlueish());
 }

 IsoPuddles.PuddlesFloat puddlesFloat =
 IsoPuddles.getInstance().getPuddlesFloat(3);
 puddlesFloat.setFinalValue(initialPuddles);
 puddlesFloat = IsoPuddles.getInstance().getPuddlesFloat(1);
 puddlesFloat.setFinalValue(PZMath.clamp_01(initialPuddles * 1.2F);
 }
 }
 }

 double getSimplexOffsetA() { return this->simplexOffsetA; }

 double getSimplexOffsetB() { return this->simplexOffsetB; }

 double getSimplexOffsetC() { return this->simplexOffsetC; }

 double getSimplexOffsetD() { return this->simplexOffsetD; }

 double getWorldAgeHours() { return this->worldAgeHours; }

 ClimateValues getClimateValuesCopy() { return this->climateValues.getCopy(); }

 void CopyClimateValues(ClimateValues copy) {
 this->climateValues.CopyValues(copy);
 }

 ClimateForecaster getClimateForecaster() { return this->climateForecaster; }

 ClimateHistory getClimateHistory() { return this->climateHistory; }

 void CalculateWeatherFrontStrength(int year, int month, int day,
 ClimateManager.AirFront front) {
 GregorianCalendar gregorianCalendar =
 new GregorianCalendar(year, month, day, 0, 0);
 gregorianCalendar.add(5, -3);
 if (this->climateValuesFronts.empty()) {
 this->climateValuesFronts = this->climateValues.getCopy();
 }

 int int0 = front.type;

 for (int int1 = 0; int1 < 4; int1++) {
 this->climateValuesFronts.pollDate(gregorianCalendar);
 float float0 = this->climateValuesFronts.getAirFrontAirmass();
 int int2 = float0 < 0.0F ? -1 : 1;
 if (int2 == int0) {
 front.addDaySample(float0);
 }

 gregorianCalendar.add(5, 1);
 }

 DebugLog.log("Calculate weather front strength = " + front.getStrength());
 }

 static std::string getWindAngleString(float angle) {
 for (int int0 = 0; int0 < windAngles.length; int0++) {
 if (angle < windAngles[int0]) {
 return windAngleStr[int0];
 }
 }

 return windAngleStr[windAngleStr.length - 1];
 }

 void sendInitialState(UdpConnection connection) {
 if (GameServer.bServer) {
 if (this->writePacketContents(connection, (byte)0) {
 PacketTypes.PacketType.ClimateManagerPacket.send(connection);
 } else {
 connection.cancelPacket();
 }
 }
 }

 bool isUpdated() { return this->lastMinuteStamp != -1L; }

public
 static class AirFront {
 float days = 0.0F;
 float maxNoise = 0.0F;
 float totalNoise = 0.0F;
 int type = 0;
 float strength = 0.0F;
 float tmpNoiseAbs = 0.0F;
 private
 float[] noiseCache = new float[2];
 float noiseCacheValue = 0.0F;
 float frontWindAngleDegrees = 0.0F;

 float getDays() { return this->days; }

 float getMaxNoise() { return this->maxNoise; }

 float getTotalNoise() { return this->totalNoise; }

 int getType() { return this->type; }

 float getStrength() { return this->strength; }

 float getAngleDegrees() { return this->frontWindAngleDegrees; }

 public
 AirFront() { this->reset(); }

 void setFrontType(int _type) {
 this->reset();
 this->type = _type;
 }

 void setFrontWind(float float0) { this->frontWindAngleDegrees = float0; }

 void setStrength(float str) { this->strength = str; }

 void reset() {
 this->days = 0.0F;
 this->maxNoise = 0.0F;
 this->totalNoise = 0.0F;
 this->type = 0;
 this->strength = 0.0F;
 this->frontWindAngleDegrees = 0.0F;

 for (int int0 = 0; int0 < this->noiseCache.length; int0++) {
 this->noiseCache[int0] = -1.0F;
 }
 }

 void save(DataOutputStream output) {
 output.writeFloat(this->days);
 output.writeFloat(this->maxNoise);
 output.writeFloat(this->totalNoise);
 output.writeInt(this->type);
 output.writeFloat(this->strength);
 output.writeFloat(this->frontWindAngleDegrees);
 output.writeInt(this->noiseCache.length);

 for (int int0 = 0; int0 < this->noiseCache.length; int0++) {
 output.writeFloat(this->noiseCache[int0]);
 }
 }

 void load(DataInputStream input) {
 this->days = input.readFloat();
 this->maxNoise = input.readFloat();
 this->totalNoise = input.readFloat();
 this->type = input.readInt();
 this->strength = input.readFloat();
 this->frontWindAngleDegrees = input.readFloat();
 int int0 = input.readInt();
 int int1 = int0 > this->noiseCache.length ? int0 : this->noiseCache.length;

 for (int int2 = 0; int2 < int1; int2++) {
 if (int2 < int0) {
 float float0 = input.readFloat();
 if (int2 < this->noiseCache.length) {
 this->noiseCache[int2] = float0;
 }
 } else if (int2 < this->noiseCache.length) {
 this->noiseCache[int2] = -1.0F;
 }
 }
 }

 void addDaySample(float noiseval) {
 this->days++;
 if ((this->type != 1 || !(noiseval <= 0.0F) &&
 (this->type != -1 || !(noiseval >= 0.0F)) {
 this->tmpNoiseAbs = Math.abs(noiseval);
 if (this->tmpNoiseAbs > this->maxNoise) {
 this->maxNoise = this->tmpNoiseAbs;
 }

 this->totalNoise = this->totalNoise + this->tmpNoiseAbs;
 this->noiseCacheValue = 0.0F;

 for (int int0 = this->noiseCache.length - 1; int0 >= 0; int0--) {
 if (this->noiseCache[int0] > this->noiseCacheValue) {
 this->noiseCacheValue = this->noiseCache[int0];
 }

 if (int0 < this->noiseCache.length - 1) {
 this->noiseCache[int0 + 1] = this->noiseCache[int0];
 }
 }

 this->noiseCache[0] = this->tmpNoiseAbs;
 if (this->tmpNoiseAbs > this->noiseCacheValue) {
 this->noiseCacheValue = this->tmpNoiseAbs;
 }

 this->strength = this->noiseCacheValue * 0.75F + this->maxNoise * 0.25F;
 } else {
 this->strength = 0.0F;
 }
 }

 void copyFrom(ClimateManager.AirFront other) {
 this->days = other.days;
 this->maxNoise = other.maxNoise;
 this->totalNoise = other.totalNoise;
 this->type = other.type;
 this->strength = other.strength;
 this->frontWindAngleDegrees = other.frontWindAngleDegrees;
 }
 }

 public static class ClimateBool {
 bool internalValue;
 bool finalValue;
 bool isOverride;
 bool override;
 bool isModded = false;
 bool moddedValue;
 bool isAdminOverride = false;
 bool adminValue;
 int ID;
 std::string name;

 public
 ClimateManager.ClimateBool init(int id, String _name) {
 this->ID = id;
 this->name = _name;
 return this;
 }

 int getID() { return this->ID; }

 std::string getName() { return this->name; }

 bool getInternalValue() { return this->internalValue; }

 bool getOverride() { return this->override; }

 void setOverride(bool b) {
 this->isOverride = true;
 this->override = b;
 }

 void setEnableOverride(bool b) { this->isOverride = b; }

 bool isEnableOverride() { return this->isOverride; }

 void setEnableAdmin(bool b) { this->isAdminOverride = b; }

 bool isEnableAdmin() { return this->isAdminOverride; }

 void setAdminValue(bool b) { this->adminValue = b; }

 bool getAdminValue() { return this->adminValue; }

 void setEnableModded(bool b) { this->isModded = b; }

 void setModdedValue(bool b) { this->moddedValue = b; }

 bool getModdedValue() { return this->moddedValue; }

 void setFinalValue(bool b) { this->finalValue = b; }

 void calculate() {
 if (this->isAdminOverride && !GameClient.bClient) {
 this->finalValue = this->adminValue;
 } else if (this->isModded) {
 this->finalValue = this->moddedValue;
 } else {
 this->finalValue = this->isOverride ? this->override : this->internalValue;
 }
 }

 void writeAdmin(ByteBuffer byteBuffer) {
 byteBuffer.put((byte)(this->isAdminOverride ? 1 : 0);
 byteBuffer.put((byte)(this->adminValue ? 1 : 0);
 }

 void readAdmin(ByteBuffer byteBuffer) {
 this->isAdminOverride = byteBuffer.get() == 1;
 this->adminValue = byteBuffer.get() == 1;
 }

 void saveAdmin(DataOutputStream dataOutputStream) {
 dataOutputStream.writeBoolean(this->isAdminOverride);
 dataOutputStream.writeBoolean(this->adminValue);
 }

 void loadAdmin(DataInputStream dataInputStream, int var2) {
 this->isAdminOverride = dataInputStream.readBoolean();
 this->adminValue = dataInputStream.readBoolean();
 }
 }

 public static class ClimateColor {
 ClimateColorInfo internalValue = new ClimateColorInfo();
 ClimateColorInfo finalValue = new ClimateColorInfo();
 bool isOverride = false;
 ClimateColorInfo override = new ClimateColorInfo();
 float interpolate;
 bool isModded = false;
 ClimateColorInfo moddedValue = new ClimateColorInfo();
 float modInterpolate;
 bool isAdminOverride = false;
 ClimateColorInfo adminValue = new ClimateColorInfo();
 int ID;
 std::string name;

 public
 ClimateManager.ClimateColor init(int id, String _name) {
 this->ID = id;
 this->name = _name;
 return this;
 }

 int getID() { return this->ID; }

 std::string getName() { return this->name; }

 ClimateColorInfo getInternalValue() { return this->internalValue; }

 ClimateColorInfo getOverride() { return this->override; }

 float getOverrideInterpolate() { return this->interpolate; }

 void setOverride(ClimateColorInfo targ, float inter) {
 this->override.setTo(targ);
 this->interpolate = inter;
 this->isOverride = true;
 }

 void setOverride(ByteBuffer input, float interp) {
 this->override.read(input);
 this->interpolate = interp;
 this->isOverride = true;
 }

 void setEnableOverride(bool b) { this->isOverride = b; }

 bool isEnableOverride() { return this->isOverride; }

 void setEnableAdmin(bool b) { this->isAdminOverride = b; }

 bool isEnableAdmin() { return this->isAdminOverride; }

 void setAdminValue(float r, float g, float b, float a, float r1, float g1,
 float b1, float a1) {
 this->adminValue.getExterior().r = r;
 this->adminValue.getExterior().g = g;
 this->adminValue.getExterior().b = b;
 this->adminValue.getExterior().a = a;
 this->adminValue.getInterior().r = r1;
 this->adminValue.getInterior().g = g1;
 this->adminValue.getInterior().b = b1;
 this->adminValue.getInterior().a = a1;
 }

 void setAdminValueExterior(float r, float g, float b, float a) {
 this->adminValue.getExterior().r = r;
 this->adminValue.getExterior().g = g;
 this->adminValue.getExterior().b = b;
 this->adminValue.getExterior().a = a;
 }

 void setAdminValueInterior(float r, float g, float b, float a) {
 this->adminValue.getInterior().r = r;
 this->adminValue.getInterior().g = g;
 this->adminValue.getInterior().b = b;
 this->adminValue.getInterior().a = a;
 }

 void setAdminValue(ClimateColorInfo targ) { this->adminValue.setTo(targ); }

 ClimateColorInfo getAdminValue() { return this->adminValue; }

 void setEnableModded(bool b) { this->isModded = b; }

 void setModdedValue(ClimateColorInfo targ) { this->moddedValue.setTo(targ); }

 ClimateColorInfo getModdedValue() { return this->moddedValue; }

 void setModdedInterpolate(float f) {
 this->modInterpolate = ClimateManager.clamp01(f);
 }

 void setFinalValue(ClimateColorInfo targ) { this->finalValue.setTo(targ); }

 ClimateColorInfo getFinalValue() { return this->finalValue; }

 void calculate() {
 if (this->isAdminOverride && !GameClient.bClient) {
 this->finalValue.setTo(this->adminValue);
 } else {
 if (this->isModded && this->modInterpolate > 0.0F) {
 this->internalValue.interp(this->moddedValue, this->modInterpolate,
 this->internalValue);
 }

 if (this->isOverride && this->interpolate > 0.0F) {
 this->internalValue.interp(this->override, this->interpolate,
 this->finalValue);
 } else {
 this->finalValue.setTo(this->internalValue);
 }
 }
 }

 void writeAdmin(ByteBuffer byteBuffer) {
 byteBuffer.put((byte)(this->isAdminOverride ? 1 : 0);
 this->adminValue.write(byteBuffer);
 }

 void readAdmin(ByteBuffer byteBuffer) {
 this->isAdminOverride = byteBuffer.get() == 1;
 this->adminValue.read(byteBuffer);
 }

 void saveAdmin(DataOutputStream dataOutputStream) {
 dataOutputStream.writeBoolean(this->isAdminOverride);
 this->adminValue.save(dataOutputStream);
 }

 void loadAdmin(DataInputStream dataInputStream, int int0) {
 this->isAdminOverride = dataInputStream.readBoolean();
 if (int0 < 143) {
 this->adminValue.getInterior().r = dataInputStream.readFloat();
 this->adminValue.getInterior().g = dataInputStream.readFloat();
 this->adminValue.getInterior().b = dataInputStream.readFloat();
 this->adminValue.getInterior().a = dataInputStream.readFloat();
 this->adminValue.getExterior().r = this->adminValue.getInterior().r;
 this->adminValue.getExterior().g = this->adminValue.getInterior().g;
 this->adminValue.getExterior().b = this->adminValue.getInterior().b;
 this->adminValue.getExterior().a = this->adminValue.getInterior().a;
 } else {
 this->adminValue.load(dataInputStream, int0);
 }
 }
 }

 public static class ClimateFloat {
 float internalValue;
 float finalValue;
 bool isOverride = false;
 float override;
 float interpolate;
 bool isModded = false;
 float moddedValue;
 float modInterpolate;
 bool isAdminOverride = false;
 float adminValue;
 float min = 0.0F;
 float max = 1.0F;
 int ID;
 std::string name;

 public
 ClimateManager.ClimateFloat init(int id, String _name) {
 this->ID = id;
 this->name = _name;
 return this;
 }

 int getID() { return this->ID; }

 std::string getName() { return this->name; }

 float getMin() { return this->min; }

 float getMax() { return this->max; }

 float getInternalValue() { return this->internalValue; }

 float getOverride() { return this->override; }

 float getOverrideInterpolate() { return this->interpolate; }

 void setOverride(float targ, float inter) {
 this->override = targ;
 this->interpolate = inter;
 this->isOverride = true;
 }

 void setEnableOverride(bool b) { this->isOverride = b; }

 bool isEnableOverride() { return this->isOverride; }

 void setEnableAdmin(bool b) { this->isAdminOverride = b; }

 bool isEnableAdmin() { return this->isAdminOverride; }

 void setAdminValue(float f) {
 this->adminValue = ClimateManager.clamp(this->min, this->max, f);
 }

 float getAdminValue() { return this->adminValue; }

 void setEnableModded(bool b) { this->isModded = b; }

 void setModdedValue(float f) {
 this->moddedValue = ClimateManager.clamp(this->min, this->max, f);
 }

 float getModdedValue() { return this->moddedValue; }

 void setModdedInterpolate(float f) {
 this->modInterpolate = ClimateManager.clamp01(f);
 }

 void setFinalValue(float f) { this->finalValue = f; }

 float getFinalValue() { return this->finalValue; }

 void calculate() {
 if (this->isAdminOverride && !GameClient.bClient) {
 this->finalValue = this->adminValue;
 } else {
 if (this->isModded && this->modInterpolate > 0.0F) {
 this->internalValue = ClimateManager.lerp(
 this->modInterpolate, this->internalValue, this->moddedValue);
 }

 if (this->isOverride && this->interpolate > 0.0F) {
 this->finalValue = ClimateManager.lerp(
 this->interpolate, this->internalValue, this->override);
 } else {
 this->finalValue = this->internalValue;
 }
 }
 }

 void writeAdmin(ByteBuffer byteBuffer) {
 byteBuffer.put((byte)(this->isAdminOverride ? 1 : 0);
 byteBuffer.putFloat(this->adminValue);
 }

 void readAdmin(ByteBuffer byteBuffer) {
 this->isAdminOverride = byteBuffer.get() == 1;
 this->adminValue = byteBuffer.getFloat();
 }

 void saveAdmin(DataOutputStream dataOutputStream) {
 dataOutputStream.writeBoolean(this->isAdminOverride);
 dataOutputStream.writeFloat(this->adminValue);
 }

 void loadAdmin(DataInputStream dataInputStream, int var2) {
 this->isAdminOverride = dataInputStream.readBoolean();
 this->adminValue = dataInputStream.readFloat();
 }
 }

 public static enum ClimateNetAuth {
 Denied, ClientOnly, ServerOnly, ClientAndServer;
 }

 private static class ClimateNetInfo {
 bool IsStopWeather = false;
 bool IsTrigger = false;
 bool IsGenerate = false;
 float TriggerDuration = 0.0F;
 bool TriggerStorm = false;
 bool TriggerTropical = false;
 bool TriggerBlizzard = false;
 float GenerateStrength = 0.0F;
 int GenerateFront = 0;

 void reset() {
 this->IsStopWeather = false;
 this->IsTrigger = false;
 this->IsGenerate = false;
 this->TriggerDuration = 0.0F;
 this->TriggerStorm = false;
 this->TriggerTropical = false;
 this->TriggerBlizzard = false;
 this->GenerateStrength = 0.0F;
 this->GenerateFront = 0;
 }
 }

 /**
 * DAY INFO
 */
 public static class DayInfo {
 int day;
 int month;
 int year;
 int hour;
 int minutes;
 long dateValue;
 GregorianCalendar calendar;
 ErosionSeason season;

 void set(int _day, int _month, int _year) {
 this->calendar = new GregorianCalendar(_year, _month, _day, 0, 0);
 this->dateValue = this->calendar.getTime().getTime();
 this->day = _day;
 this->month = _month;
 this->year = _year;
 }

 int getDay() { return this->day; }

 int getMonth() { return this->month; }

 int getYear() { return this->year; }

 int getHour() { return this->hour; }

 int getMinutes() { return this->minutes; }

 long getDateValue() { return this->dateValue; }

 ErosionSeason getSeason() { return this->season; }
 }

 protected static class SeasonColor {
 static int WARM = 0;
 static int NORMAL = 1;
 static int CLOUDY = 2;
 static int SUMMER = 0;
 static int FALL = 1;
 static int WINTER = 2;
 static int SPRING = 3;
 ClimateColorInfo finalCol = new ClimateColorInfo();
 private
 ClimateColorInfo[] tempCol = new ClimateColorInfo[3];
 private
 ClimateColorInfo[][] colors = new ClimateColorInfo[3][4];
 bool ignoreNormal = true;

 public
 SeasonColor() {
 for (int int0 = 0; int0 < 3; int0++) {
 for (int int1 = 0; int1 < 4; int1++) {
 this->colors[int0][int1] = std::make_unique<ClimateColorInfo>();
 }

 this->tempCol[int0] = std::make_unique<ClimateColorInfo>();
 }
 }

 void setIgnoreNormal(bool arg0) { this->ignoreNormal = arg0; }

 ClimateColorInfo getColor(int arg0, int arg1) {
 return this->colors[arg0][arg1];
 }

 void setColorInterior(int arg0, int arg1, float arg2, float arg3,
 float arg4, float arg5) {
 this->colors[arg0][arg1].getInterior().r = arg2;
 this->colors[arg0][arg1].getInterior().g = arg3;
 this->colors[arg0][arg1].getInterior().b = arg4;
 this->colors[arg0][arg1].getInterior().a = arg5;
 }

 void setColorExterior(int arg0, int arg1, float arg2, float arg3,
 float arg4, float arg5) {
 this->colors[arg0][arg1].getExterior().r = arg2;
 this->colors[arg0][arg1].getExterior().g = arg3;
 this->colors[arg0][arg1].getExterior().b = arg4;
 this->colors[arg0][arg1].getExterior().a = arg5;
 }

 ClimateColorInfo update(float arg0, float arg1, int arg2, int arg3) {
 for (int int0 = 0; int0 < 3; int0++) {
 if (!this->ignoreNormal || int0 != 1) {
 this->colors[int0][arg2].interp(this->colors[int0][arg3], arg1,
 this->tempCol[int0]);
 }
 }

 if (!this->ignoreNormal) {
 if (arg0 < 0.5F) {
 float float0 = arg0 * 2.0F;
 this->tempCol[WARM].interp(this->tempCol[NORMAL], float0,
 this->finalCol);
 } else {
 float float1 = 1.0F - (arg0 - 0.5F) * 2.0F;
 this->tempCol[CLOUDY].interp(this->tempCol[NORMAL], float1,
 this->finalCol);
 }
 } else {
 this->tempCol[WARM].interp(this->tempCol[CLOUDY], arg0, this->finalCol);
 }

 return this->finalCol;
 }
 }
}
} // namespace weather
} // namespace iso
} // namespace zombie
