#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
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
#include "zombie/iso/IsoPuddles/PuddlesFloat.h"
#include "zombie/iso/IsoWater.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/sprite/SkyBox.h"
#include "zombie/iso/weather/ClimateManager/AirFront.h"
#include "zombie/iso/weather/ClimateManager/ClimateBool.h"
#include "zombie/iso/weather/ClimateManager/ClimateColor.h"
#include "zombie/iso/weather/ClimateManager/ClimateFloat.h"
#include "zombie/iso/weather/ClimateManager/ClimateNetAuth.h"
#include "zombie/iso/weather/ClimateManager/ClimateNetInfo.h"
#include "zombie/iso/weather/ClimateManager/DayInfo.h"
#include "zombie/iso/weather/ClimateManager/SeasonColor.h"
#include "zombie/iso/weather/dbg/ClimMngrDebug.h"
#include "zombie/iso/weather/fx/IsoWeatherFX.h"
#include "zombie/iso/weather/fx/SteppedUpdateFloat.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/vehicles/BaseVehicle.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace weather {


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
    AirFront currentFront = std::make_shared<AirFront>();
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
    static ClimateManager instance = std::make_shared<ClimateManager>();
    static bool WINTER_IS_COMING = false;
    static bool THE_DESCENDING_FOG = false;
    static bool A_STORM_IS_COMING = false;
    ClimateValues climateValues;
    ClimateForecaster climateForecaster;
    ClimateHistory climateHistory;
    float dayLightLagged = 0.0F;
    float nightLagged = 0.0F;
    ClimateFloat desaturation;
    ClimateFloat globalLightIntensity;
    ClimateFloat nightStrength;
    ClimateFloat precipitationIntensity;
    ClimateFloat temperature;
    ClimateFloat fogIntensity;
    ClimateFloat windIntensity;
    ClimateFloat windAngleIntensity;
    ClimateFloat cloudIntensity;
    ClimateFloat ambient;
    ClimateFloat viewDistance;
    ClimateFloat dayLightStrength;
    ClimateFloat humidity;
    ClimateColor globalLight;
    ClimateColor colorNewFog;
    ClimateBool precipitationIsSnow;
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
   private const ClimateFloat[] climateFloats = new ClimateFloat[13];
    static const int COLOR_GLOBAL_LIGHT = 0;
    static const int COLOR_NEW_FOG = 1;
    static const int COLOR_MAX = 2;
   private const ClimateColor[] climateColors = new ClimateColor[2];
    static const int BOOL_IS_SNOW = 0;
    static const int BOOL_MAX = 1;
   private const ClimateBool[] climateBooleans = new ClimateBool[1];
    static const float AVG_FAV_AIR_TEMPERATURE = 22.0F;
    static double windNoiseOffset = 0.0;
    static double windNoiseBase = 0.0;
    static double windNoiseFinal = 0.0;
    static double windTickFinal = 0.0;
    ClimateColorInfo colFlare = std::make_shared<ClimateColorInfo>(1.0F, 0.0F, 0.0F, 1.0F, 1.0F, 0.0F, 0.0F, 1.0F);
    bool flareLaunched = false;
    SteppedUpdateFloat flareIntensity = std::make_shared<SteppedUpdateFloat>(0.0F, 0.01F, 0.0F, 1.0F);
    float flareIntens;
    float flareMaxLifeTime;
    float flareLifeTime;
    int nextRandomTargetIntens = 10;
    float fogLerpValue = 0.0F;
    SeasonColor seasonColorDawn;
    SeasonColor seasonColorDay;
    SeasonColor seasonColorDusk;
    DayInfo previousDay;
    DayInfo currentDay;
    DayInfo nextDay;
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
    ClimateNetInfo netInfo = std::make_shared<ClimateNetInfo>();
    ClimateValues climateValuesFronts;
   private static float[] windAngles = new float[]{22.5F, 67.5F, 112.5F, 157.5F, 202.5F, 247.5F, 292.5F, 337.5F, 382.5F};
   private static std::string[] windAngleStr = new std::string[]{"SE", "S", "SW", "W", "NW", "N", "NE", "E", "SE"};

    float getMaxWindspeedKph() {
      return 120.0F;
   }

    float getMaxWindspeedMph() {
      return 74.5645F;
   }

    static float ToKph(float var0) {
      return var0 * 120.0F;
   }

    static float ToMph(float var0) {
      return var0 * 74.5645F;
   }

    static ClimateManager getInstance() {
    return instance;
   }

    static void setInstance(ClimateManager var0) {
      instance = var0;
   }

    public ClimateManager() {
      this.colDay = std::make_unique<ClimateColorInfo>();
      this.colDawn = std::make_unique<ClimateColorInfo>();
      this.colDusk = std::make_unique<ClimateColorInfo>();
      this.colNight = std::make_unique<ClimateColorInfo>();
      this.colNightMoon = std::make_unique<ClimateColorInfo>();
      this.colFog = std::make_unique<ClimateColorInfo>();
      this.colTemp = std::make_unique<ClimateColorInfo>();
      this.colDay = std::make_unique<ClimateColorInfo>();
      this.colDawn = std::make_unique<ClimateColorInfo>();
      this.colDusk = std::make_unique<ClimateColorInfo>();
      this.colNight = std::make_shared<ClimateColorInfo>(0.33F, 0.33F, 1.0F, 0.4F, 0.33F, 0.33F, 1.0F, 0.4F);
      this.colNightNoMoon = std::make_shared<ClimateColorInfo>(0.33F, 0.33F, 1.0F, 0.4F, 0.33F, 0.33F, 1.0F, 0.4F);
      this.colNightMoon = std::make_shared<ClimateColorInfo>(0.33F, 0.33F, 1.0F, 0.4F, 0.33F, 0.33F, 1.0F, 0.4F);
      this.colFog = std::make_shared<ClimateColorInfo>(0.4F, 0.4F, 0.4F, 0.8F, 0.4F, 0.4F, 0.4F, 0.8F);
      this.colFogLegacy = std::make_shared<ClimateColorInfo>(0.3F, 0.3F, 0.3F, 0.8F, 0.3F, 0.3F, 0.3F, 0.8F);
      this.colFogNew = std::make_shared<ClimateColorInfo>(0.5F, 0.5F, 0.55F, 0.4F, 0.5F, 0.5F, 0.55F, 0.8F);
      this.fogTintStorm = std::make_shared<ClimateColorInfo>(0.5F, 0.45F, 0.4F, 1.0F, 0.5F, 0.45F, 0.4F, 1.0F);
      this.fogTintTropical = std::make_shared<ClimateColorInfo>(0.8F, 0.75F, 0.55F, 1.0F, 0.8F, 0.75F, 0.55F, 1.0F);
      this.colTemp = std::make_unique<ClimateColorInfo>();
      this.simplexOffsetA = Rand.Next(0, 8000);
      this.simplexOffsetB = Rand.Next(8000, 16000);
      this.simplexOffsetC = Rand.Next(0, -8000);
      this.simplexOffsetD = Rand.Next(-8000, -16000);
      this.initSeasonColors();
      this.setup();
      this.climateValues = std::make_shared<ClimateValues>(this);
      this.thunderStorm = std::make_shared<ThunderStorm>(this);
      this.weatherPeriod = std::make_shared<WeatherPeriod>(this, this.thunderStorm);
      this.climateForecaster = std::make_unique<ClimateForecaster>();
      this.climateHistory = std::make_unique<ClimateHistory>();

      try {
         LuaEventManager.triggerEvent("OnClimateManagerInit", this);
      } catch (Exception var2) {
         System.out.print(var2.getMessage());
         System.out.print(var2.getStackTrace());
      }
   }

    ClimateColorInfo getColNight() {
      return this.colNight;
   }

    ClimateColorInfo getColNightNoMoon() {
      return this.colNightNoMoon;
   }

    ClimateColorInfo getColNightMoon() {
      return this.colNightMoon;
   }

    ClimateColorInfo getColFog() {
      return this.colFog;
   }

    ClimateColorInfo getColFogLegacy() {
      return this.colFogLegacy;
   }

    ClimateColorInfo getColFogNew() {
      return this.colFogNew;
   }

    ClimateColorInfo getFogTintStorm() {
      return this.fogTintStorm;
   }

    ClimateColorInfo getFogTintTropical() {
      return this.fogTintTropical;
   }

    void setup() {
      for (int var1 = 0; var1 < this.climateFloats.length; var1++) {
         this.climateFloats[var1] = std::make_unique<ClimateFloat>();
      }

      for (int var2 = 0; var2 < this.climateColors.length; var2++) {
         this.climateColors[var2] = std::make_unique<ClimateColor>();
      }

      for (int var3 = 0; var3 < this.climateBooleans.length; var3++) {
         this.climateBooleans[var3] = std::make_unique<ClimateBool>();
      }

      this.desaturation = this.initClimateFloat(0, "DESATURATION");
      this.globalLightIntensity = this.initClimateFloat(1, "GLOBAL_LIGHT_INTENSITY");
      this.nightStrength = this.initClimateFloat(2, "NIGHT_STRENGTH");
      this.precipitationIntensity = this.initClimateFloat(3, "PRECIPITATION_INTENSITY");
      this.temperature = this.initClimateFloat(4, "TEMPERATURE");
      this.temperature.min = -80.0F;
      this.temperature.max = 80.0F;
      this.fogIntensity = this.initClimateFloat(5, "FOG_INTENSITY");
      this.windIntensity = this.initClimateFloat(6, "WIND_INTENSITY");
      this.windAngleIntensity = this.initClimateFloat(7, "WIND_ANGLE_INTENSITY");
      this.windAngleIntensity.min = -1.0F;
      this.cloudIntensity = this.initClimateFloat(8, "CLOUD_INTENSITY");
      this.ambient = this.initClimateFloat(9, "AMBIENT");
      this.viewDistance = this.initClimateFloat(10, "VIEW_DISTANCE");
      this.viewDistance.min = 0.0F;
      this.viewDistance.max = 100.0F;
      this.dayLightStrength = this.initClimateFloat(11, "DAYLIGHT_STRENGTH");
      this.humidity = this.initClimateFloat(12, "HUMIDITY");
      this.globalLight = this.initClimateColor(0, "GLOBAL_LIGHT");
      this.colorNewFog = this.initClimateColor(1, "COLOR_NEW_FOG");
      this.colorNewFog.internalValue.setExterior(0.9F, 0.9F, 0.95F, 1.0F);
      this.colorNewFog.internalValue.setInterior(0.9F, 0.9F, 0.95F, 1.0F);
      this.precipitationIsSnow = this.initClimateBool(0, "IS_SNOW");
   }

    int getFloatMax() {
    return 13;
   }

    ClimateFloat initClimateFloat(int var1, const std::string& var2) {
      if (var1 >= 0 && var1 < 13) {
         return this.climateFloats[var1].init(var1, var2);
      } else {
         DebugLog.log("Climate: cannot get float override id.");
    return nullptr;
      }
   }

    ClimateFloat getClimateFloat(int var1) {
      if (var1 >= 0 && var1 < 13) {
         return this.climateFloats[var1];
      } else {
         DebugLog.log("Climate: cannot get float override id.");
    return nullptr;
      }
   }

    int getColorMax() {
    return 2;
   }

    ClimateColor initClimateColor(int var1, const std::string& var2) {
      if (var1 >= 0 && var1 < 2) {
         return this.climateColors[var1].init(var1, var2);
      } else {
         DebugLog.log("Climate: cannot get float override id.");
    return nullptr;
      }
   }

    ClimateColor getClimateColor(int var1) {
      if (var1 >= 0 && var1 < 2) {
         return this.climateColors[var1];
      } else {
         DebugLog.log("Climate: cannot get float override id.");
    return nullptr;
      }
   }

    int getBoolMax() {
    return 1;
   }

    ClimateBool initClimateBool(int var1, const std::string& var2) {
      if (var1 >= 0 && var1 < 1) {
         return this.climateBooleans[var1].init(var1, var2);
      } else {
         DebugLog.log("Climate: cannot get boolean id.");
    return nullptr;
      }
   }

    ClimateBool getClimateBool(int var1) {
      if (var1 >= 0 && var1 < 1) {
         return this.climateBooleans[var1];
      } else {
         DebugLog.log("Climate: cannot get boolean id.");
    return nullptr;
      }
   }

    void setEnabledSimulation(bool var1) {
      if (!GameClient.bClient && !GameServer.bServer) {
         this.DISABLE_SIMULATION = !var1;
      } else {
         this.DISABLE_SIMULATION = false;
      }
   }

    bool getEnabledSimulation() {
      return !this.DISABLE_SIMULATION;
   }

    bool getEnabledFxUpdate() {
      return !this.DISABLE_FX_UPDATE;
   }

    void setEnabledFxUpdate(bool var1) {
      if (!GameClient.bClient && !GameServer.bServer) {
         this.DISABLE_FX_UPDATE = !var1;
      } else {
         this.DISABLE_FX_UPDATE = false;
      }
   }

    bool getEnabledWeatherGeneration() {
      return this.DISABLE_WEATHER_GENERATION;
   }

    void setEnabledWeatherGeneration(bool var1) {
      this.DISABLE_WEATHER_GENERATION = !var1;
   }

    Color getGlobalLightInternal() {
      return this.globalLight.internalValue.getExterior();
   }

    ClimateColorInfo getGlobalLight() {
      return this.globalLight.finalValue;
   }

    float getGlobalLightIntensity() {
      return this.globalLightIntensity.finalValue;
   }

    ClimateColorInfo getColorNewFog() {
      return this.colorNewFog.finalValue;
   }

    void setNightStrength(float var1) {
      this.nightStrength.finalValue = clamp(0.0F, 1.0F, var1);
   }

    float getDesaturation() {
      return this.desaturation.finalValue;
   }

    void setDesaturation(float var1) {
      this.desaturation.finalValue = var1;
   }

    float getAirMass() {
      return this.airMass;
   }

    float getAirMassDaily() {
      return this.airMassDaily;
   }

    float getAirMassTemperature() {
      return this.airMassTemperature;
   }

    float getDayLightStrength() {
      return this.dayLightStrength.finalValue;
   }

    float getNightStrength() {
      return this.nightStrength.finalValue;
   }

    float getDayMeanTemperature() {
      return this.currentDay.season.getDayMeanTemperature();
   }

    float getTemperature() {
      return this.temperature.finalValue;
   }

    float getBaseTemperature() {
      return this.baseTemperature;
   }

    float getSnowStrength() {
      return this.snowStrength;
   }

    bool getPrecipitationIsSnow() {
      return this.precipitationIsSnow.finalValue;
   }

    float getPrecipitationIntensity() {
      return this.precipitationIntensity.finalValue;
   }

    float getFogIntensity() {
      return this.fogIntensity.finalValue;
   }

    float getWindIntensity() {
      return this.windIntensity.finalValue;
   }

    float getWindAngleIntensity() {
      return this.windAngleIntensity.finalValue;
   }

    float getCorrectedWindAngleIntensity() {
      return (this.windAngleIntensity.finalValue + 1.0F) * 0.5F;
   }

    float getWindPower() {
      return this.windPower;
   }

    float getWindspeedKph() {
      return this.windPower * 120.0F;
   }

    float getCloudIntensity() {
      return this.cloudIntensity.finalValue;
   }

    float getAmbient() {
      return this.ambient.finalValue;
   }

    float getViewDistance() {
      return this.viewDistance.finalValue;
   }

    float getHumidity() {
      return this.humidity.finalValue;
   }

    float getWindAngleDegrees() {
    float var1;
      if (this.windAngleIntensity.finalValue > 0.0F) {
         var1 = lerp(this.windAngleIntensity.finalValue, 45.0F, 225.0F);
      } else if (this.windAngleIntensity.finalValue > -0.25F) {
         var1 = lerp(Math.abs(this.windAngleIntensity.finalValue), 45.0F, 0.0F);
      } else {
         var1 = lerp(Math.abs(this.windAngleIntensity.finalValue) - 0.25F, 360.0F, 180.0F);
      }

      if (var1 > 360.0F) {
         var1 -= 360.0F;
      }

      if (var1 < 0.0F) {
         var1 += 360.0F;
      }

    return var1;
   }

    float getWindAngleRadians() {
      return (float)Math.toRadians(this.getWindAngleDegrees());
   }

    float getWindSpeedMovement() {
    float var1 = this.getWindIntensity();
      if (var1 < 0.15F) {
         var1 = 0.0F;
      } else {
         var1 = (var1 - 0.15F) / 0.85F;
      }

    return var1;
   }

    float getWindForceMovement(IsoGameCharacter var1, float var2) {
      if (var1.square != nullptr && !var1.square.isInARoom()) {
    float var3 = var2 - this.getWindAngleRadians();
         if (var3 > Math.PI * 2) {
            var3 = (float)(var3 - (Math.PI * 2));
         }

         if (var3 < 0.0F) {
            var3 = (float)(var3 + (Math.PI * 2));
         }

         if (var3 > Math.PI) {
            var3 = (float)(Math.PI - (var3 - Math.PI));
         }

         return (float)(var3 / Math.PI);
      } else {
         return 0.0F;
      }
   }

    bool isRaining() {
      return this.getPrecipitationIntensity() > 0.0F && !this.getPrecipitationIsSnow();
   }

    float getRainIntensity() {
      return this.isRaining() ? this.getPrecipitationIntensity() : 0.0F;
   }

    bool isSnowing() {
      return this.getPrecipitationIntensity() > 0.0F && this.getPrecipitationIsSnow();
   }

    float getSnowIntensity() {
      return this.isSnowing() ? this.getPrecipitationIntensity() : 0.0F;
   }

    void setAmbient(float var1) {
      this.ambient.finalValue = var1;
   }

    void setViewDistance(float var1) {
      this.viewDistance.finalValue = var1;
   }

    void setDayLightStrength(float var1) {
      this.dayLightStrength.finalValue = var1;
   }

    void setPrecipitationIsSnow(bool var1) {
      this.precipitationIsSnow.finalValue = var1;
   }

    DayInfo getCurrentDay() {
      return this.currentDay;
   }

    DayInfo getPreviousDay() {
      return this.previousDay;
   }

    DayInfo getNextDay() {
      return this.nextDay;
   }

    ErosionSeason getSeason() {
      return this.currentDay != nullptr && this.currentDay.getSeason() != nullptr ? this.currentDay.getSeason() : this.season;
   }

    float getFrontStrength() {
      if (this.currentFront == nullptr) {
         return 0.0F;
      } else {
         if (Core.bDebug) {
            this.CalculateWeatherFrontStrength(this.gt.getYear(), this.gt.getMonth(), this.gt.getDayPlusOne(), this.currentFront);
         }

         return this.currentFront.strength;
      }
   }

    void stopWeatherAndThunder() {
      if (!GameClient.bClient) {
         this.weatherPeriod.stopWeatherPeriod();
         this.thunderStorm.stopAllClouds();
         if (GameServer.bServer) {
            this.transmitClimatePacket(ClimateNetAuth.ServerOnly, (byte)1, nullptr);
         }
      }
   }

    ThunderStorm getThunderStorm() {
      return this.thunderStorm;
   }

    WeatherPeriod getWeatherPeriod() {
      return this.weatherPeriod;
   }

    bool getIsThunderStorming() {
      return this.weatherPeriod.isRunning() && (this.weatherPeriod.isThunderStorm() || this.weatherPeriod.isTropicalStorm());
   }

    float getWeatherInterference() {
      if (this.weatherPeriod.isRunning()) {
         return !this.weatherPeriod.isThunderStorm() && !this.weatherPeriod.isTropicalStorm() && !this.weatherPeriod.isBlizzard()
            ? 0.35F * this.weatherPeriod.getCurrentStrength()
            : 0.7F * this.weatherPeriod.getCurrentStrength();
      } else {
         return 0.0F;
      }
   }

    KahluaTable getModData() {
      if (this.modDataTable == nullptr) {
         this.modDataTable = LuaManager.platform.newTable();
      }

      return this.modDataTable;
   }

    float getAirTemperatureForCharacter(IsoGameCharacter var1) {
      return this.getAirTemperatureForCharacter(var1, false);
   }

    float getAirTemperatureForCharacter(IsoGameCharacter var1, bool var2) {
      if (var1.square != nullptr) {
         return var1.getVehicle() != nullptr
            ? this.getAirTemperatureForSquare(var1.square, var1.getVehicle(), var2)
            : this.getAirTemperatureForSquare(var1.square, nullptr, var2);
      } else {
         return this.getTemperature();
      }
   }

    float getAirTemperatureForSquare(IsoGridSquare var1) {
      return this.getAirTemperatureForSquare(var1, nullptr);
   }

    float getAirTemperatureForSquare(IsoGridSquare var1, BaseVehicle var2) {
      return this.getAirTemperatureForSquare(var1, var2, false);
   }

    float getAirTemperatureForSquare(IsoGridSquare var1, BaseVehicle var2, bool var3) {
    float var4 = this.getTemperature();
      if (var1 != nullptr) {
    bool var5 = var1.isInARoom();
         if (var5 || var2 != nullptr) {
    bool var6 = IsoWorld.instance.isHydroPowerOn();
            if (var4 <= 22.0F) {
    float var7 = (22.0F - var4) / 8.0F;
               if (var2 == nullptr) {
                  if (var5 && var6) {
                     var4 = 22.0F;
                  }

                  var7 = 22.0F - var4;
                  if (var1.getZ() < 1) {
                     var4 += var7 * (0.4F + 0.2F * this.dayLightLagged);
                  } else {
                     var7 = (float)(var7 * 0.85);
                     var4 += var7 * (0.4F + 0.2F * this.dayLightLagged);
                  }
               }
            } else {
    float var11 = (var4 - 22.0F) / 3.5F;
               if (var2 == nullptr) {
                  if (var5 && var6) {
                     var4 = 22.0F;
                  }

                  var11 = var4 - 22.0F;
                  if (var1.getZ() < 1) {
                     var11 = (float)(var11 * 0.85);
                     var4 -= var11 * (0.4F + 0.2F * this.dayLightLagged);
                  } else {
                     var4 -= var11 * (0.4F + 0.2F * this.dayLightLagged + 0.2F * this.nightLagged);
                  }
               } else {
                  var4 = var4 + var11 + var11 * this.dayLightLagged;
               }
            }
         } else if (var3) {
            var4 = Temperature.WindchillCelsiusKph(var4, this.getWindspeedKph());
         }

    float var8 = IsoWorld.instance.getCell().getHeatSourceHighestTemperature(var4, var1.getX(), var1.getY(), var1.getZ());
         if (var8 > var4) {
            var4 = var8;
         }

         if (var2 != nullptr) {
            var4 += var2.getInsideTemperature();
         }
      }

    return var4;
   }

    std::string getSeasonName() {
      return this.season.getSeasonName();
   }

    float getSeasonProgression() {
      return this.season.getSeasonProgression();
   }

    float getSeasonStrength() {
      return this.season.getSeasonStrength();
   }

    void init(IsoMetaGrid var1) {
      WorldFlares.Clear();
      this.season = ErosionMain.getInstance().getSeasons();
      ThunderStorm.MAP_MIN_X = var1.minX * 300 - 4000;
      ThunderStorm.MAP_MAX_X = var1.maxX * 300 + 4000;
      ThunderStorm.MAP_MIN_Y = var1.minY * 300 - 4000;
      ThunderStorm.MAP_MAX_Y = var1.maxY * 300 + 4000;
      windNoiseOffset = 0.0;
      WINTER_IS_COMING = IsoWorld.instance.getGameMode() == "Winter is Coming");
      THE_DESCENDING_FOG = IsoWorld.instance.getGameMode() == "The Descending Fog");
      A_STORM_IS_COMING = IsoWorld.instance.getGameMode() == "A Storm is Coming");
      this.climateForecaster.init(this);
      this.climateHistory.init(this);
   }

    void updateEveryTenMins() {
      this.tickIsTenMins = true;
   }

    void update() {
      this.tickIsClimateTick = false;
      this.tickIsHourChange = false;
      this.tickIsDayChange = false;
      this.gt = GameTime.getInstance();
      this.worldAgeHours = this.gt.getWorldAgeHours();
      if (this.lastMinuteStamp != this.gt.getMinutesStamp()) {
         this.lastMinuteStamp = this.gt.getMinutesStamp();
         this.tickIsClimateTick = true;
         this.updateDayInfo(this.gt.getDayPlusOne(), this.gt.getMonth(), this.gt.getYear());
         this.currentDay.hour = this.gt.getHour();
         this.currentDay.minutes = this.gt.getMinutes();
         if (this.gt.getHour() != this.lastHourStamp) {
            this.tickIsHourChange = true;
            this.lastHourStamp = this.gt.getHour();
         }

         if (this.gt.getTimeOfDay() > 12.0F) {
            ClimateMoon.updatePhase(this.currentDay.getYear(), this.currentDay.getMonth(), this.currentDay.getDay());
         }
      }

      if (this.DISABLE_SIMULATION) {
         IsoPlayer[] var7 = IsoPlayer.players;

         for (int var2 = 0; var2 < var7.length; var2++) {
    IsoPlayer var9 = var7[var2];
            if (var9 != nullptr) {
               var9.dirtyRecalcGridStackTime = 1.0F;
            }
         }
      } else {
         if (this.tickIsDayChange && !GameClient.bClient) {
            this.climateForecaster.updateDayChange(this);
            this.climateHistory.updateDayChange(this);
         }

         if (GameClient.bClient) {
            this.networkLerp = 1.0F;
    long var1 = System.currentTimeMillis();
            if ((float)var1 < (float)this.networkUpdateStamp + this.networkLerpTime) {
               this.networkLerp = (float)(var1 - this.networkUpdateStamp) / this.networkLerpTime;
               if (this.networkLerp < 0.0F) {
                  this.networkLerp = 0.0F;
               }
            }

            for (int var3 = 0; var3 < this.climateFloats.length; var3++) {
               this.climateFloats[var3].interpolate = this.networkLerp;
            }

            for (int var8 = 0; var8 < this.climateColors.length; var8++) {
               this.climateColors[var8].interpolate = this.networkLerp;
            }
         }

         if (this.tickIsClimateTick && !GameClient.bClient) {
            this.updateValues();
            this.weatherPeriod.update(this.worldAgeHours);
         }

         if (this.tickIsClimateTick) {
            LuaEventManager.triggerEvent("OnClimateTick", this);
         }

         for (int var4 = 0; var4 < this.climateColors.length; var4++) {
            this.climateColors[var4].calculate();
         }

         for (int var5 = 0; var5 < this.climateFloats.length; var5++) {
            this.climateFloats[var5].calculate();
         }

         for (int var6 = 0; var6 < this.climateBooleans.length; var6++) {
            this.climateBooleans[var6].calculate();
         }

         this.windPower = this.windIntensity.finalValue;
         this.updateWindTick();
         if (this.tickIsClimateTick) {
         }

         this.updateTestFlare();
         this.thunderStorm.update(this.worldAgeHours);
         if (GameClient.bClient) {
            this.updateSnow();
         } else if (this.tickIsClimateTick && !GameClient.bClient) {
            this.updateSnow();
         }

         if (!GameClient.bClient) {
            this.updateViewDistance();
         }

         if (this.tickIsClimateTick && Core.bDebug && !GameServer.bServer) {
            LuaEventManager.triggerEvent("OnClimateTickDebug", this);
         }

         if (this.tickIsClimateTick && GameServer.bServer && this.tickIsTenMins) {
            this.transmitClimatePacket(ClimateNetAuth.ServerOnly, (byte)0, nullptr);
            this.tickIsTenMins = false;
         }

         if (!this.DISABLE_FX_UPDATE) {
            this.updateFx();
         }
      }
   }

    static double getWindNoiseBase() {
    return windNoiseBase;
   }

    static double getWindNoiseFinal() {
    return windNoiseFinal;
   }

    static double getWindTickFinal() {
    return windTickFinal;
   }

    void updateWindTick() {
      if (!GameServer.bServer) {
    float var1 = this.windIntensity.finalValue;
         windNoiseOffset = windNoiseOffset + (4.0E-4 + 6.0E-4 * var1) * GameTime.getInstance().getMultiplier();
         windNoiseBase = SimplexNoise.noise(0.0, windNoiseOffset);
         windNoiseFinal = windNoiseBase;
         if (windNoiseFinal > 0.0) {
            windNoiseFinal *= 0.04 + 0.1 * var1;
         } else {
            windNoiseFinal *= 0.04 + 0.1 * var1 + 0.05F * (var1 * var1);
         }

         var1 = clamp01(var1 + (float)windNoiseFinal);
         windTickFinal = var1;
      }
   }

    void updateOLD() {
      this.tickIsClimateTick = false;
      this.tickIsHourChange = false;
      this.tickIsDayChange = false;
      this.gt = GameTime.getInstance();
      this.worldAgeHours = this.gt.getWorldAgeHours();
      if (this.lastMinuteStamp != this.gt.getMinutesStamp()) {
         this.lastMinuteStamp = this.gt.getMinutesStamp();
         this.tickIsClimateTick = true;
         this.updateDayInfo(this.gt.getDay(), this.gt.getMonth(), this.gt.getYear());
         this.currentDay.hour = this.gt.getHour();
         this.currentDay.minutes = this.gt.getMinutes();
         if (this.gt.getHour() != this.lastHourStamp) {
            this.tickIsHourChange = true;
            this.lastHourStamp = this.gt.getHour();
         }
      }

      if (GameClient.bClient) {
         if (!this.DISABLE_SIMULATION) {
            this.networkLerp = 1.0F;
    long var1 = System.currentTimeMillis();
            if ((float)var1 < (float)this.networkUpdateStamp + this.networkLerpTime) {
               this.networkLerp = (float)(var1 - this.networkUpdateStamp) / this.networkLerpTime;
               if (this.networkLerp < 0.0F) {
                  this.networkLerp = 0.0F;
               }
            }

            for (int var3 = 0; var3 < this.climateFloats.length; var3++) {
               this.climateFloats[var3].interpolate = this.networkLerp;
            }

            for (int var5 = 0; var5 < this.climateColors.length; var5++) {
               this.climateColors[var5].interpolate = this.networkLerp;
            }

            if (this.tickIsClimateTick) {
               LuaEventManager.triggerEvent("OnClimateTick", this);
            }

            this.updateOnTick();
            this.updateTestFlare();
            this.thunderStorm.update(this.worldAgeHours);
            this.updateSnow();
            if (this.tickIsTenMins) {
               this.tickIsTenMins = false;
            }
         }

         this.updateFx();
      } else {
         if (!this.DISABLE_SIMULATION) {
            if (this.tickIsClimateTick) {
               this.updateValues();
               this.weatherPeriod.update(this.gt.getWorldAgeHours());
            }

            this.updateOnTick();
            this.updateTestFlare();
            this.thunderStorm.update(this.worldAgeHours);
            if (this.tickIsClimateTick) {
               this.updateSnow();
               LuaEventManager.triggerEvent("OnClimateTick", this);
            }

            this.updateViewDistance();
            if (this.tickIsClimateTick && this.tickIsTenMins) {
               if (GameServer.bServer) {
                  this.transmitClimatePacket(ClimateNetAuth.ServerOnly, (byte)0, nullptr);
               }

               this.tickIsTenMins = false;
            }
         }

         if (!this.DISABLE_FX_UPDATE && this.tickIsClimateTick) {
            this.updateFx();
         }

         if (this.DISABLE_SIMULATION) {
            IsoPlayer[] var4 = IsoPlayer.players;

            for (int var2 = 0; var2 < var4.length; var2++) {
    IsoPlayer var6 = var4[var2];
               if (var6 != nullptr) {
                  var6.dirtyRecalcGridStackTime = 1.0F;
               }
            }
         }
      }
   }

    void updateFx() {
    IsoWeatherFX var1 = IsoWorld.instance.getCell().getWeatherFX();
      if (var1 != nullptr) {
         var1.setPrecipitationIntensity(this.precipitationIntensity.finalValue);
         var1.setWindIntensity(this.windIntensity.finalValue);
         var1.setWindPrecipIntensity((float)windTickFinal * (float)windTickFinal);
         var1.setWindAngleIntensity(this.windAngleIntensity.finalValue);
         var1.setFogIntensity(this.fogIntensity.finalValue);
         var1.setCloudIntensity(this.cloudIntensity.finalValue);
         var1.setPrecipitationIsSnow(this.precipitationIsSnow.finalValue);
         SkyBox.getInstance().update(this);
         IsoWater.getInstance().update(this);
         IsoPuddles.getInstance().update(this);
      }
   }

    void updateSnow() {
      if (GameClient.bClient) {
         IsoWorld.instance.CurrentCell.setSnowTarget((int)(this.snowFracNow * 100.0F));
         ErosionIceQueen.instance.setSnow(this.canDoWinterSprites && this.snowFracNow > 0.2F);
      } else {
         if (!this.tickIsHourChange) {
            this.canDoWinterSprites = this.season.isSeason(5) || WINTER_IS_COMING;
            if (this.precipitationIsSnow.finalValue && this.precipitationIntensity.finalValue > this.snowFall) {
               this.snowFall = this.precipitationIntensity.finalValue;
            }

            if (this.temperature.finalValue > 0.0F) {
    float var1 = this.temperature.finalValue / 10.0F;
               var1 = var1 * 0.2F + var1 * 0.8F * this.dayLightStrength.finalValue;
               if (var1 > this.snowMeltStrength) {
                  this.snowMeltStrength = var1;
               }
            }

            if (!this.precipitationIsSnow.finalValue && this.precipitationIntensity.finalValue > 0.0F) {
               this.snowMeltStrength = this.snowMeltStrength + this.precipitationIntensity.finalValue;
            }
         } else {
            this.snowStrength = this.snowStrength + this.snowFall;
            this.snowStrength = this.snowStrength - this.snowMeltStrength;
            this.snowStrength = clamp(0.0F, 10.0F, this.snowStrength);
            this.snowFracNow = this.snowStrength > 7.5F ? 1.0F : this.snowStrength / 7.5F;
            IsoWorld.instance.CurrentCell.setSnowTarget((int)(this.snowFracNow * 100.0F));
            ErosionIceQueen.instance.setSnow(this.canDoWinterSprites && this.snowFracNow > 0.2F);
            this.snowFall = 0.0F;
            this.snowMeltStrength = 0.0F;
         }
      }
   }

    void updateSnowOLD() {
   }

    float getSnowFracNow() {
      return this.snowFracNow;
   }

    void resetOverrides() {
      for (int var1 = 0; var1 < this.climateColors.length; var1++) {
         this.climateColors[var1].setEnableOverride(false);
      }

      for (int var2 = 0; var2 < this.climateFloats.length; var2++) {
         this.climateFloats[var2].setEnableOverride(false);
      }

      for (int var3 = 0; var3 < this.climateBooleans.length; var3++) {
         this.climateBooleans[var3].setEnableOverride(false);
      }
   }

    void resetModded() {
      for (int var1 = 0; var1 < this.climateColors.length; var1++) {
         this.climateColors[var1].setEnableModded(false);
      }

      for (int var2 = 0; var2 < this.climateFloats.length; var2++) {
         this.climateFloats[var2].setEnableModded(false);
      }

      for (int var3 = 0; var3 < this.climateBooleans.length; var3++) {
         this.climateBooleans[var3].setEnableModded(false);
      }
   }

    void resetAdmin() {
      for (int var1 = 0; var1 < this.climateColors.length; var1++) {
         this.climateColors[var1].setEnableAdmin(false);
      }

      for (int var2 = 0; var2 < this.climateFloats.length; var2++) {
         this.climateFloats[var2].setEnableAdmin(false);
      }

      for (int var3 = 0; var3 < this.climateBooleans.length; var3++) {
         this.climateBooleans[var3].setEnableAdmin(false);
      }
   }

    void triggerWinterIsComingStorm() {
      if (!GameClient.bClient && !this.weatherPeriod.isRunning()) {
    AirFront var1 = std::make_shared<AirFront>();
         var1.copyFrom(this.currentFront);
         var1.strength = 0.95F;
         var1.type = 1;
    GameTime var2 = GameTime.getInstance();
         this.weatherPeriod.init(var1, this.worldAgeHours, var2.getYear(), var2.getMonth(), var2.getDayPlusOne());
      }
   }

    bool triggerCustomWeather(float var1, bool var2) {
      if (!GameClient.bClient && !this.weatherPeriod.isRunning()) {
    AirFront var3 = std::make_shared<AirFront>();
         var3.strength = var1;
         var3.type = var2 ? 1 : -1;
    GameTime var4 = GameTime.getInstance();
         this.weatherPeriod.init(var3, this.worldAgeHours, var4.getYear(), var4.getMonth(), var4.getDayPlusOne());
    return true;
      } else {
    return false;
      }
   }

    bool triggerCustomWeatherStage(int var1, float var2) {
      if (!GameClient.bClient && !this.weatherPeriod.isRunning()) {
    AirFront var3 = std::make_shared<AirFront>();
         var3.strength = 0.95F;
         var3.type = 1;
    GameTime var4 = GameTime.getInstance();
         this.weatherPeriod.init(var3, this.worldAgeHours, var4.getYear(), var4.getMonth(), var4.getDayPlusOne(), var1, var2);
    return true;
      } else {
    return false;
      }
   }

    void updateOnTick() {
      for (int var1 = 0; var1 < this.climateColors.length; var1++) {
         this.climateColors[var1].calculate();
      }

      for (int var2 = 0; var2 < this.climateFloats.length; var2++) {
         this.climateFloats[var2].calculate();
      }

      for (int var3 = 0; var3 < this.climateBooleans.length; var3++) {
         this.climateBooleans[var3].calculate();
      }
   }

    void updateTestFlare() {
      WorldFlares.update();
   }

    void launchFlare() {
      DebugLog.log("Launching improved flare.");
    IsoPlayer var1 = IsoPlayer.getInstance();
    float var2 = 0.0F;
      WorldFlares.launchFlare(7200.0F, (int)var1.getX(), (int)var1.getY(), 50, var2, 1.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F);
      if (IsoPlayer.getInstance() != nullptr && !this.flareLaunched) {
         this.flareLaunched = true;
         this.flareLifeTime = 0.0F;
         this.flareMaxLifeTime = 7200.0F;
         this.flareIntensity.overrideCurrentValue(1.0F);
         this.flareIntens = 1.0F;
         this.nextRandomTargetIntens = 10;
      }
   }

    double getAirMassNoiseFrequencyMod(int var1) {
      if (var1 == 1) {
         return 300.0;
      } else if (var1 == 2) {
         return 240.0;
      } else {
         if (var1 != 3) {
            if (var1 == 4) {
               return 145.0;
            }

            if (var1 == 5) {
               return 120.0;
            }
         }

         return 166.0;
      }
   }

    float getRainTimeMultiplierMod(int var1) {
      if (var1 == 1) {
         return 0.5F;
      } else if (var1 == 2) {
         return 0.75F;
      } else if (var1 == 4) {
         return 1.25F;
      } else {
    return var1 = = 5 ? 1.5F : 1.0F;
      }
   }

    void updateValues() {
      if (this.tickIsDayChange && Core.bDebug && !GameClient.bClient && !GameServer.bServer) {
         ErosionMain.getInstance().DebugUpdateMapNow();
      }

      this.climateValues.updateValues(this.worldAgeHours, this.gt.getTimeOfDay(), this.currentDay, this.nextDay);
      this.airMass = this.climateValues.getNoiseAirmass();
      this.airMassTemperature = this.climateValues.getAirMassTemperature();
      if (this.tickIsHourChange) {
    int var1 = this.airMass < 0.0F ? -1 : 1;
         if (this.currentFront.type != var1) {
            if (!this.DISABLE_WEATHER_GENERATION && (!WINTER_IS_COMING || WINTER_IS_COMING && GameTime.instance.getWorldAgeHours() > 96.0)) {
               if (THE_DESCENDING_FOG) {
                  this.currentFront.type = -1;
                  this.currentFront.strength = Rand.Next(0.2F, 0.45F);
                  this.weatherPeriod.init(this.currentFront, this.worldAgeHours, this.gt.getYear(), this.gt.getMonth(), this.gt.getDayPlusOne());
               } else {
                  this.CalculateWeatherFrontStrength(this.gt.getYear(), this.gt.getMonth(), this.gt.getDayPlusOne(), this.currentFront);
                  this.weatherPeriod.init(this.currentFront, this.worldAgeHours, this.gt.getYear(), this.gt.getMonth(), this.gt.getDayPlusOne());
               }
            }

            this.currentFront.setFrontType(var1);
         }

         if (!WINTER_IS_COMING
            && !THE_DESCENDING_FOG
            && GameTime.instance.getWorldAgeHours() >= 72.0
            && GameTime.instance.getWorldAgeHours() <= 96.0
            && !this.DISABLE_WEATHER_GENERATION
            && !this.weatherPeriod.isRunning()
            && Rand.Next(0, 1000) < 50) {
         }

         if (this.tickIsDayChange) {
         }
      }

      this.dayDoFog = this.climateValues.isDayDoFog();
      this.dayFogStrength = this.climateValues.getDayFogStrength();
      if (PerformanceSettings.FogQuality == 2) {
         this.dayFogStrength = 0.5F + 0.5F * this.dayFogStrength;
      } else {
         this.dayFogStrength = 0.2F + 0.8F * this.dayFogStrength;
      }

      this.baseTemperature = this.climateValues.getBaseTemperature();
      this.dayLightLagged = this.climateValues.getDayLightLagged();
      this.nightLagged = this.climateValues.getDayLightLagged();
      this.temperature.internalValue = this.climateValues.getTemperature();
      this.precipitationIsSnow.internalValue = this.climateValues.isTemperatureIsSnow();
      this.humidity.internalValue = this.climateValues.getHumidity();
      this.windIntensity.internalValue = this.climateValues.getWindIntensity();
      this.windAngleIntensity.internalValue = this.climateValues.getWindAngleIntensity();
      this.windPower = this.windIntensity.internalValue;
      this.currentFront.setFrontWind(this.climateValues.getWindAngleDegrees());
      this.cloudIntensity.internalValue = this.climateValues.getCloudIntensity();
      this.precipitationIntensity.internalValue = 0.0F;
      this.nightStrength.internalValue = this.climateValues.getNightStrength();
      this.dayLightStrength.internalValue = this.climateValues.getDayLightStrength();
      this.ambient.internalValue = this.climateValues.getAmbient();
      this.desaturation.internalValue = this.climateValues.getDesaturation();
    int var19 = this.season.getSeason();
    float var2 = this.season.getSeasonProgression();
    float var3 = 0.0F;
    int var4 = 0;
    int var5 = 0;
      if (var19 == 2) {
         var4 = SeasonColor.SPRING;
         var5 = SeasonColor.SUMMER;
         var3 = 0.5F + var2 * 0.5F;
      } else if (var19 == 3) {
         var4 = SeasonColor.SUMMER;
         var5 = SeasonColor.FALL;
         var3 = var2 * 0.5F;
      } else if (var19 == 4) {
         if (var2 < 0.5F) {
            var4 = SeasonColor.SUMMER;
            var5 = SeasonColor.FALL;
            var3 = 0.5F + var2;
         } else {
            var4 = SeasonColor.FALL;
            var5 = SeasonColor.WINTER;
            var3 = var2 - 0.5F;
         }
      } else if (var19 == 5) {
         if (var2 < 0.5F) {
            var4 = SeasonColor.FALL;
            var5 = SeasonColor.WINTER;
            var3 = 0.5F + var2;
         } else {
            var4 = SeasonColor.WINTER;
            var5 = SeasonColor.SPRING;
            var3 = var2 - 0.5F;
         }
      } else if (var19 == 1) {
         if (var2 < 0.5F) {
            var4 = SeasonColor.WINTER;
            var5 = SeasonColor.SPRING;
            var3 = 0.5F + var2;
         } else {
            var4 = SeasonColor.SPRING;
            var5 = SeasonColor.SUMMER;
            var3 = var2 - 0.5F;
         }
      }

    float var6 = this.climateValues.getCloudyT();
      this.colDawn = this.seasonColorDawn.update(var6, var3, var4, var5);
      this.colDay = this.seasonColorDay.update(var6, var3, var4, var5);
      this.colDusk = this.seasonColorDusk.update(var6, var3, var4, var5);
    float var7 = this.climateValues.getTime();
    float var8 = this.climateValues.getDawn();
    float var9 = this.climateValues.getDusk();
    float var10 = this.climateValues.getNoon();
    float var11 = this.climateValues.getDayFogDuration();
      if (!THE_DESCENDING_FOG) {
         if (this.dayDoFog && this.dayFogStrength > 0.0F && var7 > var8 - 2.0F && var7 < var8 + var11) {
    float var12 = this.getTimeLerpHours(var7, var8 - 2.0F, var8 + var11, true);
            var12 = clamp(0.0F, 1.0F, var12 * (var11 / 3.0F));
            this.fogLerpValue = var12;
            this.cloudIntensity.internalValue = lerp(var12, this.cloudIntensity.internalValue, 0.0F);
    float var13 = this.dayFogStrength;
            this.fogIntensity.internalValue = clerp(var12, 0.0F, var13);
            if (Core.getInstance().RenderShader == nullptr || Core.getInstance().getOffscreenBuffer() == nullptr) {
               this.desaturation.internalValue = clerp(var12, this.desaturation.internalValue, 0.8F * var13);
            } else if (PerformanceSettings.FogQuality == 2) {
               this.desaturation.internalValue = clerp(var12, this.desaturation.internalValue, 0.8F * var13);
            } else {
               this.desaturation.internalValue = clerp(var12, this.desaturation.internalValue, 0.65F * var13);
            }
         } else {
            this.fogIntensity.internalValue = 0.0F;
         }
      } else {
         if (this.gt.getWorldAgeHours() < 72.0) {
            this.fogIntensity.internalValue = (float)this.gt.getWorldAgeHours() / 72.0F;
         } else {
            this.fogIntensity.internalValue = 1.0F;
         }

         this.cloudIntensity.internalValue = Math.min(this.cloudIntensity.internalValue, 1.0F - this.fogIntensity.internalValue);
         if (this.weatherPeriod.isRunning()) {
            this.fogIntensity.internalValue = Math.min(this.fogIntensity.internalValue, 0.6F);
         }

         if (PerformanceSettings.FogQuality == 2) {
            this.fogIntensity.internalValue *= 0.93F;
            this.desaturation.internalValue = 0.8F * this.fogIntensity.internalValue;
         } else {
            this.desaturation.internalValue = 0.65F * this.fogIntensity.internalValue;
         }
      }

      this.humidity.internalValue = clamp01(this.humidity.internalValue + this.fogIntensity.internalValue * 0.6F);
    float var21 = 0.6F * this.climateValues.getDayLightStrengthBase();
    float var22 = 0.4F;
    float var14 = 0.25F * this.climateValues.getDayLightStrengthBase();
      if (Core.getInstance().RenderShader != nullptr && Core.getInstance().getOffscreenBuffer() != nullptr) {
         var14 = 0.8F * this.climateValues.getDayLightStrengthBase();
      }

      if (var7 < var8 || var7 > var9) {
    float var16 = 24.0F - var9 + var8;
         if (var7 > var9) {
    float var24 = (var7 - var9) / var16;
            this.colDusk.interp(this.colDawn, var24, this.globalLight.internalValue);
         } else {
    float var25 = (24.0F - var9 + var7) / var16;
            this.colDusk.interp(this.colDawn, var25, this.globalLight.internalValue);
         }

         this.globalLightIntensity.internalValue = lerp(this.climateValues.getLerpNight(), var14, var22);
      } else if (var7 < var10 + 2.0F) {
    float var15 = (var7 - var8) / (var10 + 2.0F - var8);
         this.colDawn.interp(this.colDay, var15, this.globalLight.internalValue);
         this.globalLightIntensity.internalValue = lerp(var15, var14, var21);
      } else {
    float var23 = (var7 - (var10 + 2.0F)) / (var9 - (var10 + 2.0F));
         this.colDay.interp(this.colDusk, var23, this.globalLight.internalValue);
         this.globalLightIntensity.internalValue = lerp(var23, var21, var14);
      }

      if (this.fogIntensity.internalValue > 0.0F) {
         if (Core.getInstance().RenderShader == nullptr || Core.getInstance().getOffscreenBuffer() == nullptr) {
            this.globalLight.internalValue.interp(this.colFogLegacy, this.fogIntensity.internalValue, this.globalLight.internalValue);
         } else if (PerformanceSettings.FogQuality == 2) {
            this.globalLight.internalValue.interp(this.colFog, this.fogIntensity.internalValue, this.globalLight.internalValue);
         } else {
            this.globalLight.internalValue.interp(this.colFogNew, this.fogIntensity.internalValue, this.globalLight.internalValue);
         }

         this.globalLightIntensity.internalValue = clerp(this.fogLerpValue, this.globalLightIntensity.internalValue, 0.8F);
      }

      this.colNightNoMoon.interp(this.colNightMoon, ClimateMoon.getMoonFloat(), this.colNight);
      this.globalLight.internalValue.interp(this.colNight, this.nightStrength.internalValue, this.globalLight.internalValue);
      IsoPlayer[] var26 = IsoPlayer.players;

      for (int var17 = 0; var17 < var26.length; var17++) {
    IsoPlayer var18 = var26[var17];
         if (var18 != nullptr) {
            var18.dirtyRecalcGridStackTime = 1.0F;
         }
      }
   }

    void updateViewDistance() {
    float var1 = this.dayLightStrength.finalValue;
    float var2 = this.fogIntensity.finalValue;
    float var3 = 19.0F - var2 * 8.0F;
    float var4 = var3 + 4.0F + 7.0F * var1 * (1.0F - var2);
      var3 *= 3.0F;
      var4 *= 3.0F;
      this.gt.setViewDistMin(var3);
      this.gt.setViewDistMax(var4);
      this.viewDistance.internalValue = var3 + (var4 - var3) * var1;
      this.viewDistance.finalValue = this.viewDistance.internalValue;
   }

    void setSeasonColorDawn(int var1, int var2, float var3, float var4, float var5, float var6, bool var7) {
      if (var7) {
         this.seasonColorDawn.setColorExterior(var1, var2, var3, var4, var5, var6);
      } else {
         this.seasonColorDawn.setColorInterior(var1, var2, var3, var4, var5, var6);
      }
   }

    void setSeasonColorDay(int var1, int var2, float var3, float var4, float var5, float var6, bool var7) {
      if (var7) {
         this.seasonColorDay.setColorExterior(var1, var2, var3, var4, var5, var6);
      } else {
         this.seasonColorDay.setColorInterior(var1, var2, var3, var4, var5, var6);
      }
   }

    void setSeasonColorDusk(int var1, int var2, float var3, float var4, float var5, float var6, bool var7) {
      if (var7) {
         this.seasonColorDusk.setColorExterior(var1, var2, var3, var4, var5, var6);
      } else {
         this.seasonColorDusk.setColorInterior(var1, var2, var3, var4, var5, var6);
      }
   }

    ClimateColorInfo getSeasonColor(int var1, int var2, int var3) {
    SeasonColor var4 = nullptr;
      if (var1 == 0) {
         var4 = this.seasonColorDawn;
      } else if (var1 == 1) {
         var4 = this.seasonColorDay;
      } else if (var1 == 2) {
         var4 = this.seasonColorDusk;
      }

      return var4 != nullptr ? var4.getColor(var2, var3) : nullptr;
   }

    void initSeasonColors() {
    SeasonColor var1 = std::make_shared<SeasonColor>();
      var1.setIgnoreNormal(true);
      this.seasonColorDawn = var1;
      var1 = std::make_unique<SeasonColor>();
      var1.setIgnoreNormal(true);
      this.seasonColorDay = var1;
      var1 = std::make_unique<SeasonColor>();
      var1.setIgnoreNormal(false);
      this.seasonColorDusk = var1;
   }

    void save(DataOutputStream var1) {
      if (GameClient.bClient && !GameServer.bServer) {
         var1.writeByte(0);
      } else {
         var1.writeByte(1);
         var1.writeDouble(this.simplexOffsetA);
         var1.writeDouble(this.simplexOffsetB);
         var1.writeDouble(this.simplexOffsetC);
         var1.writeDouble(this.simplexOffsetD);
         this.currentFront.save(var1);
         var1.writeFloat(this.snowFracNow);
         var1.writeFloat(this.snowStrength);
         var1.writeBoolean(this.canDoWinterSprites);
         var1.writeBoolean(this.dayDoFog);
         var1.writeFloat(this.dayFogStrength);
      }

      this.weatherPeriod.save(var1);
      this.thunderStorm.save(var1);
      if (GameServer.bServer) {
         this.desaturation.saveAdmin(var1);
         this.globalLightIntensity.saveAdmin(var1);
         this.nightStrength.saveAdmin(var1);
         this.precipitationIntensity.saveAdmin(var1);
         this.temperature.saveAdmin(var1);
         this.fogIntensity.saveAdmin(var1);
         this.windIntensity.saveAdmin(var1);
         this.windAngleIntensity.saveAdmin(var1);
         this.cloudIntensity.saveAdmin(var1);
         this.ambient.saveAdmin(var1);
         this.viewDistance.saveAdmin(var1);
         this.dayLightStrength.saveAdmin(var1);
         this.globalLight.saveAdmin(var1);
         this.precipitationIsSnow.saveAdmin(var1);
      }

      if (this.modDataTable != nullptr) {
         var1.writeByte(1);
         this.modDataTable.save(var1);
      } else {
         var1.writeByte(0);
      }

      if (GameServer.bServer) {
         this.humidity.saveAdmin(var1);
      }
   }

    void load(DataInputStream var1, int var2) {
    bool var3 = var1.readByte() == 1;
      if (var3) {
         this.simplexOffsetA = var1.readDouble();
         this.simplexOffsetB = var1.readDouble();
         this.simplexOffsetC = var1.readDouble();
         this.simplexOffsetD = var1.readDouble();
         this.currentFront.load(var1);
         this.snowFracNow = var1.readFloat();
         this.snowStrength = var1.readFloat();
         this.canDoWinterSprites = var1.readBoolean();
         this.dayDoFog = var1.readBoolean();
         this.dayFogStrength = var1.readFloat();
      }

      this.weatherPeriod.load(var1, var2);
      this.thunderStorm.load(var1);
      if (var2 >= 140 && GameServer.bServer) {
         this.desaturation.loadAdmin(var1, var2);
         this.globalLightIntensity.loadAdmin(var1, var2);
         this.nightStrength.loadAdmin(var1, var2);
         this.precipitationIntensity.loadAdmin(var1, var2);
         this.temperature.loadAdmin(var1, var2);
         this.fogIntensity.loadAdmin(var1, var2);
         this.windIntensity.loadAdmin(var1, var2);
         this.windAngleIntensity.loadAdmin(var1, var2);
         this.cloudIntensity.loadAdmin(var1, var2);
         this.ambient.loadAdmin(var1, var2);
         this.viewDistance.loadAdmin(var1, var2);
         this.dayLightStrength.loadAdmin(var1, var2);
         this.globalLight.loadAdmin(var1, var2);
         this.precipitationIsSnow.loadAdmin(var1, var2);
      }

      if (var2 >= 141 && var1.readByte() == 1) {
         if (this.modDataTable == nullptr) {
            this.modDataTable = LuaManager.platform.newTable();
         }

         this.modDataTable.load(var1, var2);
      }

      if (var2 >= 150 && GameServer.bServer) {
         this.humidity.loadAdmin(var1, var2);
      }

      this.climateValues = std::make_shared<ClimateValues>(this);
   }

    void postCellLoadSetSnow() {
      IsoWorld.instance.CurrentCell.setSnowTarget((int)(this.snowFracNow * 100.0F));
      ErosionIceQueen.instance.setSnow(this.canDoWinterSprites && this.snowFracNow > 0.2F);
   }

    void forceDayInfoUpdate() {
      this.currentDay.day = -1;
      this.currentDay.month = -1;
      this.currentDay.year = -1;
      this.gt = GameTime.getInstance();
      this.updateDayInfo(this.gt.getDayPlusOne(), this.gt.getMonth(), this.gt.getYear());
      this.currentDay.hour = this.gt.getHour();
      this.currentDay.minutes = this.gt.getMinutes();
   }

    void updateDayInfo(int var1, int var2, int var3) {
      this.tickIsDayChange = false;
      if (this.currentDay == nullptr || this.currentDay.day != var1 || this.currentDay.month != var2 || this.currentDay.year != var3) {
         this.tickIsDayChange = this.currentDay != nullptr;
         if (this.currentDay == nullptr) {
            this.currentDay = std::make_unique<DayInfo>();
         }

         this.setDayInfo(this.currentDay, var1, var2, var3, 0);
         if (this.previousDay == nullptr) {
            this.previousDay = std::make_unique<DayInfo>();
            this.previousDay.season = this.season.clone();
         }

         this.setDayInfo(this.previousDay, var1, var2, var3, -1);
         if (this.nextDay == nullptr) {
            this.nextDay = std::make_unique<DayInfo>();
            this.nextDay.season = this.season.clone();
         }

         this.setDayInfo(this.nextDay, var1, var2, var3, 1);
      }
   }

    void setDayInfo(DayInfo var1, int var2, int var3, int var4, int var5) {
      var1.calendar = std::make_shared<GregorianCalendar>(var4, var3, var2, 0, 0);
      var1.calendar.push_back(5, var5);
      var1.day = var1.calendar.get(5);
      var1.month = var1.calendar.get(2);
      var1.year = var1.calendar.get(1);
      var1.dateValue = var1.calendar.getTime().getTime();
      if (var1.season == nullptr) {
         var1.season = this.season.clone();
      }

      var1.season.setDay(var1.day, var1.month, var1.year);
   }

    void transmitClimatePacket(ClimateNetAuth var1, uint8_t var2, UdpConnection var3) {
      if (GameClient.bClient || GameServer.bServer) {
         if (var1 == ClimateNetAuth.Denied) {
            DebugLog.log("Denied ClimatePacket, id = " + var2 + ", isClient = " + GameClient.bClient);
         } else {
            if (GameClient.bClient && (var1 == ClimateNetAuth.ClientOnly || var1 == ClimateNetAuth.ClientAndServer)) {
               try {
                  if (this.writePacketContents(GameClient.connection, var2)) {
                     PacketType.ClimateManagerPacket.send(GameClient.connection);
                  } else {
                     GameClient.connection.cancelPacket();
                  }
               } catch (Exception var6) {
                  DebugLog.log(var6.getMessage());
               }
            }

            if (GameServer.bServer && (var1 == ClimateNetAuth.ServerOnly || var1 == ClimateNetAuth.ClientAndServer)) {
               try {
                  for (int var4 = 0; var4 < GameServer.udpEngine.connections.size(); var4++) {
    UdpConnection var5 = (UdpConnection)GameServer.udpEngine.connections.get(var4);
                     if (var3 == nullptr || var3 != var5) {
                        if (this.writePacketContents(var5, var2)) {
                           PacketType.ClimateManagerPacket.send(var5);
                        } else {
                           var5.cancelPacket();
                        }
                     }
                  }
               } catch (Exception var7) {
                  DebugLog.log(var7.getMessage());
               }
            }
         }
      }
   }

    bool writePacketContents(UdpConnection var1, uint8_t var2) {
      if (!GameClient.bClient && !GameServer.bServer) {
    return false;
      } else {
    ByteBufferWriter var3 = var1.startPacket();
         PacketType.ClimateManagerPacket.doPacket(var3);
    ByteBuffer var4 = var3.bb;
         var4.put(var2);
         switch (var2) {
            case 0:
               if (this.networkPrint) {
                  DebugLog.log("clim: send PacketUpdateClimateVars");
               }

               for (int var11 = 0; var11 < this.climateFloats.length; var11++) {
                  var4.putFloat(this.climateFloats[var11].finalValue);
               }

               for (int var12 = 0; var12 < this.climateColors.length; var12++) {
                  this.climateColors[var12].finalValue.write(var4);
               }

               for (int var13 = 0; var13 < this.climateBooleans.length; var13++) {
                  var4.put((byte)(this.climateBooleans[var13].finalValue ? 1 : 0));
               }

               var4.putFloat(this.airMass);
               var4.putFloat(this.airMassDaily);
               var4.putFloat(this.airMassTemperature);
               var4.putFloat(this.snowFracNow);
               var4.putFloat(this.snowStrength);
               var4.putFloat(this.windPower);
               var4.put((byte)(this.dayDoFog ? 1 : 0));
               var4.putFloat(this.dayFogStrength);
               var4.put((byte)(this.canDoWinterSprites ? 1 : 0));
               this.weatherPeriod.writeNetWeatherData(var4);
    return true;
            case 1:
               if (this.networkPrint) {
                  DebugLog.log("clim: send PacketWeatherUpdate");
               }

               this.weatherPeriod.writeNetWeatherData(var4);
    return true;
            case 2:
               if (this.networkPrint) {
                  DebugLog.log("clim: send PacketThunderEvent");
               }

               this.thunderStorm.writeNetThunderEvent(var4);
    return true;
            case 3:
               if (this.networkPrint) {
                  DebugLog.log("clim: send PacketFlare");
               }

    return true;
            case 4:
               if (!GameServer.bServer) {
    return false;
               }

               if (this.networkPrint) {
                  DebugLog.log("clim: send PacketAdminVarsUpdate");
               }

               for (int var8 = 0; var8 < this.climateFloats.length; var8++) {
                  this.climateFloats[var8].writeAdmin(var4);
               }

               for (int var9 = 0; var9 < this.climateColors.length; var9++) {
                  this.climateColors[var9].writeAdmin(var4);
               }

               for (int var10 = 0; var10 < this.climateBooleans.length; var10++) {
                  this.climateBooleans[var10].writeAdmin(var4);
               }

    return true;
            case 5:
               if (!GameClient.bClient) {
    return false;
               }

               if (this.networkPrint) {
                  DebugLog.log("clim: send PacketRequestAdminVars");
               }

               var4.put((byte)1);
    return true;
            case 6:
               if (!GameClient.bClient) {
    return false;
               }

               if (this.networkPrint) {
                  DebugLog.log("clim: send PacketClientChangedAdminVars");
               }

               for (int var5 = 0; var5 < this.climateFloats.length; var5++) {
                  this.climateFloats[var5].writeAdmin(var4);
               }

               for (int var6 = 0; var6 < this.climateColors.length; var6++) {
                  this.climateColors[var6].writeAdmin(var4);
               }

               for (int var7 = 0; var7 < this.climateBooleans.length; var7++) {
                  this.climateBooleans[var7].writeAdmin(var4);
               }

    return true;
            case 7:
               if (!GameClient.bClient) {
    return false;
               }

               if (this.networkPrint) {
                  DebugLog.log("clim: send PacketClientChangedWeather");
               }

               var4.put((byte)(this.netInfo.IsStopWeather ? 1 : 0));
               var4.put((byte)(this.netInfo.IsTrigger ? 1 : 0));
               var4.put((byte)(this.netInfo.IsGenerate ? 1 : 0));
               var4.putFloat(this.netInfo.TriggerDuration);
               var4.put((byte)(this.netInfo.TriggerStorm ? 1 : 0));
               var4.put((byte)(this.netInfo.TriggerTropical ? 1 : 0));
               var4.put((byte)(this.netInfo.TriggerBlizzard ? 1 : 0));
               var4.putFloat(this.netInfo.GenerateStrength);
               var4.putInt(this.netInfo.GenerateFront);
    return true;
            default:
    return false;
         }
      }
   }

    void receiveClimatePacket(ByteBuffer var1, UdpConnection var2) {
      if (GameClient.bClient || GameServer.bServer) {
    uint8_t var3 = var1.get();
         this.readPacketContents(var1, var3, var2);
      }
   }

    bool readPacketContents(ByteBuffer var1, uint8_t var2, UdpConnection var3) {
      switch (var2) {
         case 0:
            if (!GameClient.bClient) {
    return false;
            }

            if (this.networkPrint) {
               DebugLog.log("clim: receive PacketUpdateClimateVars");
            }

            for (int var5 = 0; var5 < this.climateFloats.length; var5++) {
    ClimateFloat var4 = this.climateFloats[var5];
               var4.internalValue = var4.finalValue;
               var4.setOverride(var1.getFloat(), 0.0F);
            }

            for (int var6 = 0; var6 < this.climateColors.length; var6++) {
    ClimateColor var10 = this.climateColors[var6];
               var10.internalValue.setTo(var10.finalValue);
               var10.setOverride(var1, 0.0F);
            }

            for (int var7 = 0; var7 < this.climateBooleans.length; var7++) {
    ClimateBool var11 = this.climateBooleans[var7];
               var11.setOverride(var1.get() == 1);
            }

            this.airMass = var1.getFloat();
            this.airMassDaily = var1.getFloat();
            this.airMassTemperature = var1.getFloat();
            this.snowFracNow = var1.getFloat();
            this.snowStrength = var1.getFloat();
            this.windPower = var1.getFloat();
            this.dayDoFog = var1.get() == 1;
            this.dayFogStrength = var1.getFloat();
            this.canDoWinterSprites = var1.get() == 1;
    long var12 = System.currentTimeMillis();
            if ((float)(var12 - this.networkUpdateStamp) < this.networkLerpTime) {
               this.networkAdjustVal++;
               if (this.networkAdjustVal > 10.0F) {
                  this.networkAdjustVal = 10.0F;
               }
            } else {
               this.networkAdjustVal--;
               if (this.networkAdjustVal < 0.0F) {
                  this.networkAdjustVal = 0.0F;
               }
            }

            if (this.networkAdjustVal > 0.0F) {
               this.networkLerpTime = this.networkLerpTimeBase / this.networkAdjustVal;
            } else {
               this.networkLerpTime = this.networkLerpTimeBase;
            }

            this.networkUpdateStamp = var12;
            this.weatherPeriod.readNetWeatherData(var1);
    return true;
         case 1:
            if (this.networkPrint) {
               DebugLog.log("clim: receive PacketWeatherUpdate");
            }

            this.weatherPeriod.readNetWeatherData(var1);
    return true;
         case 2:
            if (this.networkPrint) {
               DebugLog.log("clim: receive PacketThunderEvent");
            }

            this.thunderStorm.readNetThunderEvent(var1);
    return true;
         case 3:
            if (this.networkPrint) {
               DebugLog.log("clim: receive PacketFlare");
            }

    return true;
         case 4:
            if (!GameClient.bClient) {
    return false;
            }

            if (this.networkPrint) {
               DebugLog.log("clim: receive PacketAdminVarsUpdate");
            }

            for (int var15 = 0; var15 < this.climateFloats.length; var15++) {
               this.climateFloats[var15].readAdmin(var1);
            }

            for (int var16 = 0; var16 < this.climateColors.length; var16++) {
               this.climateColors[var16].readAdmin(var1);
            }

            for (int var17 = 0; var17 < this.climateBooleans.length; var17++) {
               this.climateBooleans[var17].readAdmin(var1);
            }

    return true;
         case 5:
            if (!GameServer.bServer) {
    return false;
            }

            if (this.networkPrint) {
               DebugLog.log("clim: receive PacketRequestAdminVars");
            }

            var1.get();
            this.transmitClimatePacket(ClimateNetAuth.ServerOnly, (byte)4, nullptr);
    return true;
         case 6:
            if (!GameServer.bServer) {
    return false;
            }

            if (this.networkPrint) {
               DebugLog.log("clim: receive PacketClientChangedAdminVars");
            }

            for (int var9 = 0; var9 < this.climateFloats.length; var9++) {
               this.climateFloats[var9].readAdmin(var1);
            }

            for (int var13 = 0; var13 < this.climateColors.length; var13++) {
               this.climateColors[var13].readAdmin(var1);
            }

            for (int var14 = 0; var14 < this.climateBooleans.length; var14++) {
               this.climateBooleans[var14].readAdmin(var1);
               if (var14 == 0) {
                  DebugLog.log("Snow = " + this.climateBooleans[var14].adminValue + ", enabled = " + this.climateBooleans[var14].isAdminOverride);
               }
            }

            this.serverReceiveClientChangeAdminVars();
    return true;
         case 7:
            if (!GameServer.bServer) {
    return false;
            }

            if (this.networkPrint) {
               DebugLog.log("clim: receive PacketClientChangedWeather");
            }

            this.netInfo.IsStopWeather = var1.get() == 1;
            this.netInfo.IsTrigger = var1.get() == 1;
            this.netInfo.IsGenerate = var1.get() == 1;
            this.netInfo.TriggerDuration = var1.getFloat();
            this.netInfo.TriggerStorm = var1.get() == 1;
            this.netInfo.TriggerTropical = var1.get() == 1;
            this.netInfo.TriggerBlizzard = var1.get() == 1;
            this.netInfo.GenerateStrength = var1.getFloat();
            this.netInfo.GenerateFront = var1.getInt();
            this.serverReceiveClientChangeWeather();
    return true;
         default:
    return false;
      }
   }

    void serverReceiveClientChangeAdminVars() {
      if (GameServer.bServer) {
         if (this.networkPrint) {
            DebugLog.log("clim: serverReceiveClientChangeAdminVars");
         }

         this.transmitClimatePacket(ClimateNetAuth.ServerOnly, (byte)4, nullptr);
         this.updateOnTick();
         this.transmitClimatePacket(ClimateNetAuth.ServerOnly, (byte)0, nullptr);
      }
   }

    void serverReceiveClientChangeWeather() {
      if (GameServer.bServer) {
         if (this.networkPrint) {
            DebugLog.log("clim: serverReceiveClientChangeWeather");
         }

         if (this.netInfo.IsStopWeather) {
            if (this.networkPrint) {
               DebugLog.log("clim: IsStopWeather");
            }

            this.stopWeatherAndThunder();
         } else if (this.netInfo.IsTrigger) {
            this.stopWeatherAndThunder();
            if (this.netInfo.TriggerStorm) {
               if (this.networkPrint) {
                  DebugLog.log("clim: Trigger Storm");
               }

               this.triggerCustomWeatherStage(3, this.netInfo.TriggerDuration);
            } else if (this.netInfo.TriggerTropical) {
               if (this.networkPrint) {
                  DebugLog.log("clim: Trigger Tropical");
               }

               this.triggerCustomWeatherStage(8, this.netInfo.TriggerDuration);
            } else if (this.netInfo.TriggerBlizzard) {
               if (this.networkPrint) {
                  DebugLog.log("clim: Trigger Blizzard");
               }

               this.triggerCustomWeatherStage(7, this.netInfo.TriggerDuration);
            }
         } else if (this.netInfo.IsGenerate) {
            if (this.networkPrint) {
               DebugLog.log("clim: IsGenerate");
            }

            this.stopWeatherAndThunder();
            this.triggerCustomWeather(this.netInfo.GenerateStrength, this.netInfo.GenerateFront == 0);
         }

         this.updateOnTick();
         this.transmitClimatePacket(ClimateNetAuth.ServerOnly, (byte)0, nullptr);
      }
   }

    void transmitServerStopWeather() {
      if (GameServer.bServer) {
         this.stopWeatherAndThunder();
         if (this.networkPrint) {
            DebugLog.log("clim: SERVER transmitStopWeather");
         }

         this.updateOnTick();
         this.transmitClimatePacket(ClimateNetAuth.ServerOnly, (byte)0, nullptr);
      }
   }

    void transmitServerTriggerStorm(float var1) {
      if (GameServer.bServer) {
         if (this.networkPrint) {
            DebugLog.log("clim: SERVER transmitTriggerStorm");
         }

         this.netInfo.TriggerDuration = var1;
         this.triggerCustomWeatherStage(3, this.netInfo.TriggerDuration);
         this.updateOnTick();
         this.transmitClimatePacket(ClimateNetAuth.ServerOnly, (byte)0, nullptr);
      }
   }

    void transmitServerTriggerLightning(int var1, int var2, bool var3, bool var4, bool var5) {
      if (GameServer.bServer) {
         if (this.networkPrint) {
            DebugLog.log("clim: SERVER transmitTriggerLightning");
         }

         this.thunderStorm.triggerThunderEvent(var1, var2, var3, var4, var5);
      }
   }

    void transmitServerStartRain(float var1) {
      if (GameServer.bServer) {
         this.precipitationIntensity.setAdminValue(clamp01(var1));
         this.precipitationIntensity.setEnableAdmin(true);
         this.updateOnTick();
         this.transmitClimatePacket(ClimateNetAuth.ServerOnly, (byte)0, nullptr);
      }
   }

    void transmitServerStopRain() {
      if (GameServer.bServer) {
         this.precipitationIntensity.setEnableAdmin(false);
         this.updateOnTick();
         this.transmitClimatePacket(ClimateNetAuth.ServerOnly, (byte)0, nullptr);
      }
   }

    void transmitRequestAdminVars() {
      if (this.networkPrint) {
         DebugLog.log("clim: transmitRequestAdminVars");
      }

      this.transmitClimatePacket(ClimateNetAuth.ClientOnly, (byte)5, nullptr);
   }

    void transmitClientChangeAdminVars() {
      if (this.networkPrint) {
         DebugLog.log("clim: transmitClientChangeAdminVars");
      }

      this.transmitClimatePacket(ClimateNetAuth.ClientOnly, (byte)6, nullptr);
   }

    void transmitStopWeather() {
      if (this.networkPrint) {
         DebugLog.log("clim: transmitStopWeather");
      }

      this.netInfo.reset();
      this.netInfo.IsStopWeather = true;
      this.transmitClimatePacket(ClimateNetAuth.ClientOnly, (byte)7, nullptr);
   }

    void transmitTriggerStorm(float var1) {
      if (this.networkPrint) {
         DebugLog.log("clim: transmitTriggerStorm");
      }

      this.netInfo.reset();
      this.netInfo.IsTrigger = true;
      this.netInfo.TriggerStorm = true;
      this.netInfo.TriggerDuration = var1;
      this.transmitClimatePacket(ClimateNetAuth.ClientOnly, (byte)7, nullptr);
   }

    void transmitTriggerTropical(float var1) {
      if (this.networkPrint) {
         DebugLog.log("clim: transmitTriggerTropical");
      }

      this.netInfo.reset();
      this.netInfo.IsTrigger = true;
      this.netInfo.TriggerTropical = true;
      this.netInfo.TriggerDuration = var1;
      this.transmitClimatePacket(ClimateNetAuth.ClientOnly, (byte)7, nullptr);
   }

    void transmitTriggerBlizzard(float var1) {
      if (this.networkPrint) {
         DebugLog.log("clim: transmitTriggerBlizzard");
      }

      this.netInfo.reset();
      this.netInfo.IsTrigger = true;
      this.netInfo.TriggerBlizzard = true;
      this.netInfo.TriggerDuration = var1;
      this.transmitClimatePacket(ClimateNetAuth.ClientOnly, (byte)7, nullptr);
   }

    void transmitGenerateWeather(float var1, int var2) {
      if (this.networkPrint) {
         DebugLog.log("clim: transmitGenerateWeather");
      }

      this.netInfo.reset();
      this.netInfo.IsGenerate = true;
      this.netInfo.GenerateStrength = clamp01(var1);
      this.netInfo.GenerateFront = var2;
      if (this.netInfo.GenerateFront < 0 || this.netInfo.GenerateFront > 1) {
         this.netInfo.GenerateFront = 0;
      }

      this.transmitClimatePacket(ClimateNetAuth.ClientOnly, (byte)7, nullptr);
   }

    float getTimeLerpHours(float var1, float var2, float var3) {
      return this.getTimeLerpHours(var1, var2, var3, false);
   }

    float getTimeLerpHours(float var1, float var2, float var3, bool var4) {
      return this.getTimeLerp(clamp(0.0F, 1.0F, var1 / 24.0F), clamp(0.0F, 1.0F, var2 / 24.0F), clamp(0.0F, 1.0F, var3 / 24.0F), var4);
   }

    float getTimeLerp(float var1, float var2, float var3) {
      return this.getTimeLerp(var1, var2, var3, false);
   }

    float getTimeLerp(float var1, float var2, float var3, bool var4) {
    bool var5 = var2 > var3;
      if (!var5) {
         if (!(var1 < var2) && !(var1 > var3)) {
    float var10 = var1 - var2;
    float var11 = var3 - var2;
    float var12 = var11 * 0.5F;
            if (var10 < var12) {
               return var4 ? clerp(var10 / var12, 0.0F, 1.0F) : lerp(var10 / var12, 0.0F, 1.0F);
            } else {
               return var4 ? clerp((var10 - var12) / var12, 1.0F, 0.0F) : lerp((var10 - var12) / var12, 1.0F, 0.0F);
            }
         } else {
            return 0.0F;
         }
      } else if (var1 < var2 && var1 > var3) {
         return 0.0F;
      } else {
    float var6 = 1.0F - var2;
    float var7 = var1 >= var2 ? var1 - var2 : var1 + var6;
    float var8 = var3 + var6;
    float var9 = var8 * 0.5F;
         if (var7 < var9) {
            return var4 ? clerp(var7 / var9, 0.0F, 1.0F) : lerp(var7 / var9, 0.0F, 1.0F);
         } else {
            return var4 ? clerp((var7 - var9) / var9, 1.0F, 0.0F) : lerp((var7 - var9) / var9, 1.0F, 0.0F);
         }
      }
   }

    static float clamp01(float var0) {
    return clamp();
   }

    static float clamp(float var0, float var1, float var2) {
      var2 = Math.min(var1, var2);
      return Math.max(var0, var2);
   }

    static int clamp(int var0, int var1, int var2) {
      var2 = Math.min(var1, var2);
      return Math.max(var0, var2);
   }

    static float lerp(float var0, float var1, float var2) {
      return var1 + var0 * (var2 - var1);
   }

    static float clerp(float var0, float var1, float var2) {
    float var3 = (float)(1.0 - Math.cos(var0 * Math.PI)) / 2.0F;
      return var1 * (1.0F - var3) + var2 * var3;
   }

    static float normalizeRange(float var0, float var1) {
    return clamp(var0 /);
   }

    static float posToPosNegRange(float var0) {
      if (var0 > 0.5F) {
         return (var0 - 0.5F) * 2.0F;
      } else {
         return var0 < 0.5F ? -((0.5F - var0) * 2.0F) : 0.0F;
      }
   }

    void execute_Simulation() {
      if (Core.bDebug) {
    ClimMngrDebug var1 = std::make_shared<ClimMngrDebug>();
    short var2 = 365;
    short var3 = 5000;
         var1.SimulateDays(var2, var3);
      }
   }

    void execute_Simulation(int var1) {
      if (Core.bDebug) {
    ClimMngrDebug var2 = std::make_shared<ClimMngrDebug>();
         var2.setRainModOverride(var1);
    short var3 = 365;
    short var4 = 5000;
         var2.SimulateDays(var3, var4);
      }
   }

    void triggerKateBobIntroStorm(int var1, int var2, double var3, float var5, float var6, float var7, float var8) {
      this.triggerKateBobIntroStorm(var1, var2, var3, var5, var6, var7, var8, nullptr);
   }

    void triggerKateBobIntroStorm(int var1, int var2, double var3, float var5, float var6, float var7, float var8, ClimateColorInfo var9) {
      if (!GameClient.bClient) {
         this.stopWeatherAndThunder();
         if (this.weatherPeriod.startCreateModdedPeriod(true, var5, var7)) {
            this.weatherPeriod.setKateBobStormProgress(var6);
            this.weatherPeriod.setKateBobStormCoords(var1, var2);
            this.weatherPeriod.createAndAddStage(11, var3);
            this.weatherPeriod.createAndAddStage(2, var3 / 2.0);
            this.weatherPeriod.createAndAddStage(4, var3 / 4.0);
            this.weatherPeriod.endCreateModdedPeriod();
            if (var9 != nullptr) {
               this.weatherPeriod.setCloudColor(var9);
            } else {
               this.weatherPeriod.setCloudColor(this.weatherPeriod.getCloudColorBlueish());
            }

    PuddlesFloat var10 = IsoPuddles.getInstance().getPuddlesFloat(3);
            var10.setFinalValue(var8);
            var10 = IsoPuddles.getInstance().getPuddlesFloat(1);
            var10.setFinalValue(PZMath.clamp_01(var8 * 1.2F));
         }
      }
   }

    double getSimplexOffsetA() {
      return this.simplexOffsetA;
   }

    double getSimplexOffsetB() {
      return this.simplexOffsetB;
   }

    double getSimplexOffsetC() {
      return this.simplexOffsetC;
   }

    double getSimplexOffsetD() {
      return this.simplexOffsetD;
   }

    double getWorldAgeHours() {
      return this.worldAgeHours;
   }

    ClimateValues getClimateValuesCopy() {
      return this.climateValues.getCopy();
   }

    void CopyClimateValues(ClimateValues var1) {
      this.climateValues.CopyValues(var1);
   }

    ClimateForecaster getClimateForecaster() {
      return this.climateForecaster;
   }

    ClimateHistory getClimateHistory() {
      return this.climateHistory;
   }

    void CalculateWeatherFrontStrength(int var1, int var2, int var3, AirFront var4) {
    GregorianCalendar var5 = std::make_shared<GregorianCalendar>(var1, var2, var3, 0, 0);
      var5.push_back(5, -3);
      if (this.climateValuesFronts == nullptr) {
         this.climateValuesFronts = this.climateValues.getCopy();
      }

    int var6 = var4.type;

      for (int var7 = 0; var7 < 4; var7++) {
         this.climateValuesFronts.pollDate(var5);
    float var8 = this.climateValuesFronts.getAirFrontAirmass();
    int var9 = var8 < 0.0F ? -1 : 1;
         if (var9 == var6) {
            var4.addDaySample(var8);
         }

         var5.push_back(5, 1);
      }

      DebugLog.log("Calculate weather front strength = " + var4.getStrength());
   }

    static std::string getWindAngleString(float var0) {
      for (int var1 = 0; var1 < windAngles.length; var1++) {
         if (var0 < windAngles[var1]) {
            return windAngleStr[var1];
         }
      }

      return windAngleStr[windAngleStr.length - 1];
   }

    void sendInitialState(UdpConnection var1) {
      if (GameServer.bServer) {
         if (this.writePacketContents(var1, (byte)0)) {
            PacketType.ClimateManagerPacket.send(var1);
         } else {
            var1.cancelPacket();
         }
      }
   }

    bool isUpdated() {
      return this.lastMinuteStamp != -1L;
   }
}
} // namespace weather
} // namespace iso
} // namespace zombie
