package zombie.iso.weather;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.GregorianCalendar;
import se.krka.kahlua.vm.KahluaTable;
import zombie.GameTime;
import zombie.Lua.LuaEventManager;
import zombie.Lua.LuaManager;
import zombie.characters.IsoGameCharacter;
import zombie.characters.IsoPlayer;
import zombie.core.Color;
import zombie.core.Core;
import zombie.core.PerformanceSettings;
import zombie.core.Rand;
import zombie.core.math.PZMath;
import zombie.core.network.ByteBufferWriter;
import zombie.core.raknet.UdpConnection;
import zombie.debug.DebugLog;
import zombie.erosion.ErosionMain;
import zombie.erosion.season.ErosionIceQueen;
import zombie.erosion.season.ErosionSeason;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoMetaGrid;
import zombie.iso.IsoPuddles;
import zombie.iso.IsoWater;
import zombie.iso.IsoWorld;
import zombie.iso.IsoPuddles.PuddlesFloat;
import zombie.iso.sprite.SkyBox;
import zombie.iso.weather.ClimateManager.AirFront;
import zombie.iso.weather.ClimateManager.ClimateBool;
import zombie.iso.weather.ClimateManager.ClimateColor;
import zombie.iso.weather.ClimateManager.ClimateFloat;
import zombie.iso.weather.ClimateManager.ClimateNetAuth;
import zombie.iso.weather.ClimateManager.ClimateNetInfo;
import zombie.iso.weather.ClimateManager.DayInfo;
import zombie.iso.weather.ClimateManager.SeasonColor;
import zombie.iso.weather.dbg.ClimMngrDebug;
import zombie.iso.weather.fx.IsoWeatherFX;
import zombie.iso.weather.fx.SteppedUpdateFloat;
import zombie.network.GameClient;
import zombie.network.GameServer;
import zombie.network.PacketTypes.PacketType;
import zombie.vehicles.BaseVehicle;

public class ClimateManager {
   private boolean DISABLE_SIMULATION = false;
   private boolean DISABLE_FX_UPDATE = false;
   private boolean DISABLE_WEATHER_GENERATION = false;
   public static final int FRONT_COLD = -1;
   public static final int FRONT_STATIONARY = 0;
   public static final int FRONT_WARM = 1;
   public static final float MAX_WINDSPEED_KPH = 120.0F;
   public static final float MAX_WINDSPEED_MPH = 74.5645F;
   private ErosionSeason season;
   private long lastMinuteStamp = -1L;
   private KahluaTable modDataTable = null;
   private float airMass;
   private float airMassDaily;
   private float airMassTemperature;
   private float baseTemperature;
   private float snowFall = 0.0F;
   private float snowStrength = 0.0F;
   private float snowMeltStrength = 0.0F;
   private float snowFracNow = 0.0F;
   boolean canDoWinterSprites = false;
   private float windPower = 0.0F;
   private WeatherPeriod weatherPeriod;
   private ThunderStorm thunderStorm;
   private double simplexOffsetA = 0.0;
   private double simplexOffsetB = 0.0;
   private double simplexOffsetC = 0.0;
   private double simplexOffsetD = 0.0;
   private boolean dayDoFog = false;
   private float dayFogStrength = 0.0F;
   private GameTime gt;
   private double worldAgeHours;
   private boolean tickIsClimateTick = false;
   private boolean tickIsDayChange = false;
   private int lastHourStamp = -1;
   private boolean tickIsHourChange = false;
   private boolean tickIsTenMins = false;
   private AirFront currentFront = new AirFront();
   private ClimateColorInfo colDay;
   private ClimateColorInfo colDusk;
   private ClimateColorInfo colDawn;
   private ClimateColorInfo colNight;
   private ClimateColorInfo colNightNoMoon;
   private ClimateColorInfo colNightMoon;
   private ClimateColorInfo colTemp;
   private ClimateColorInfo colFog;
   private ClimateColorInfo colFogLegacy;
   private ClimateColorInfo colFogNew;
   private ClimateColorInfo fogTintStorm;
   private ClimateColorInfo fogTintTropical;
   private static ClimateManager instance = new ClimateManager();
   public static boolean WINTER_IS_COMING = false;
   public static boolean THE_DESCENDING_FOG = false;
   public static boolean A_STORM_IS_COMING = false;
   private ClimateValues climateValues;
   private ClimateForecaster climateForecaster;
   private ClimateHistory climateHistory;
   float dayLightLagged = 0.0F;
   float nightLagged = 0.0F;
   protected ClimateFloat desaturation;
   protected ClimateFloat globalLightIntensity;
   protected ClimateFloat nightStrength;
   protected ClimateFloat precipitationIntensity;
   protected ClimateFloat temperature;
   protected ClimateFloat fogIntensity;
   protected ClimateFloat windIntensity;
   protected ClimateFloat windAngleIntensity;
   protected ClimateFloat cloudIntensity;
   protected ClimateFloat ambient;
   protected ClimateFloat viewDistance;
   protected ClimateFloat dayLightStrength;
   protected ClimateFloat humidity;
   protected ClimateColor globalLight;
   protected ClimateColor colorNewFog;
   protected ClimateBool precipitationIsSnow;
   public static final int FLOAT_DESATURATION = 0;
   public static final int FLOAT_GLOBAL_LIGHT_INTENSITY = 1;
   public static final int FLOAT_NIGHT_STRENGTH = 2;
   public static final int FLOAT_PRECIPITATION_INTENSITY = 3;
   public static final int FLOAT_TEMPERATURE = 4;
   public static final int FLOAT_FOG_INTENSITY = 5;
   public static final int FLOAT_WIND_INTENSITY = 6;
   public static final int FLOAT_WIND_ANGLE_INTENSITY = 7;
   public static final int FLOAT_CLOUD_INTENSITY = 8;
   public static final int FLOAT_AMBIENT = 9;
   public static final int FLOAT_VIEW_DISTANCE = 10;
   public static final int FLOAT_DAYLIGHT_STRENGTH = 11;
   public static final int FLOAT_HUMIDITY = 12;
   public static final int FLOAT_MAX = 13;
   private final ClimateFloat[] climateFloats = new ClimateFloat[13];
   public static final int COLOR_GLOBAL_LIGHT = 0;
   public static final int COLOR_NEW_FOG = 1;
   public static final int COLOR_MAX = 2;
   private final ClimateColor[] climateColors = new ClimateColor[2];
   public static final int BOOL_IS_SNOW = 0;
   public static final int BOOL_MAX = 1;
   private final ClimateBool[] climateBooleans = new ClimateBool[1];
   public static final float AVG_FAV_AIR_TEMPERATURE = 22.0F;
   private static double windNoiseOffset = 0.0;
   private static double windNoiseBase = 0.0;
   private static double windNoiseFinal = 0.0;
   private static double windTickFinal = 0.0;
   private ClimateColorInfo colFlare = new ClimateColorInfo(1.0F, 0.0F, 0.0F, 1.0F, 1.0F, 0.0F, 0.0F, 1.0F);
   private boolean flareLaunched = false;
   private SteppedUpdateFloat flareIntensity = new SteppedUpdateFloat(0.0F, 0.01F, 0.0F, 1.0F);
   private float flareIntens;
   private float flareMaxLifeTime;
   private float flareLifeTime;
   private int nextRandomTargetIntens = 10;
   float fogLerpValue = 0.0F;
   private SeasonColor seasonColorDawn;
   private SeasonColor seasonColorDay;
   private SeasonColor seasonColorDusk;
   private DayInfo previousDay;
   private DayInfo currentDay;
   private DayInfo nextDay;
   public static final byte PacketUpdateClimateVars = 0;
   public static final byte PacketWeatherUpdate = 1;
   public static final byte PacketThunderEvent = 2;
   public static final byte PacketFlare = 3;
   public static final byte PacketAdminVarsUpdate = 4;
   public static final byte PacketRequestAdminVars = 5;
   public static final byte PacketClientChangedAdminVars = 6;
   public static final byte PacketClientChangedWeather = 7;
   private float networkLerp = 0.0F;
   private long networkUpdateStamp = 0L;
   private float networkLerpTime = 5000.0F;
   private float networkLerpTimeBase = 5000.0F;
   private float networkAdjustVal = 0.0F;
   private boolean networkPrint = false;
   private ClimateNetInfo netInfo = new ClimateNetInfo();
   private ClimateValues climateValuesFronts;
   private static float[] windAngles = new float[]{22.5F, 67.5F, 112.5F, 157.5F, 202.5F, 247.5F, 292.5F, 337.5F, 382.5F};
   private static String[] windAngleStr = new String[]{"SE", "S", "SW", "W", "NW", "N", "NE", "E", "SE"};

   public float getMaxWindspeedKph() {
      return 120.0F;
   }

   public float getMaxWindspeedMph() {
      return 74.5645F;
   }

   public static float ToKph(float var0) {
      return var0 * 120.0F;
   }

   public static float ToMph(float var0) {
      return var0 * 74.5645F;
   }

   public static ClimateManager getInstance() {
      return instance;
   }

   public static void setInstance(ClimateManager var0) {
      instance = var0;
   }

   public ClimateManager() {
      this.colDay = new ClimateColorInfo();
      this.colDawn = new ClimateColorInfo();
      this.colDusk = new ClimateColorInfo();
      this.colNight = new ClimateColorInfo();
      this.colNightMoon = new ClimateColorInfo();
      this.colFog = new ClimateColorInfo();
      this.colTemp = new ClimateColorInfo();
      this.colDay = new ClimateColorInfo();
      this.colDawn = new ClimateColorInfo();
      this.colDusk = new ClimateColorInfo();
      this.colNight = new ClimateColorInfo(0.33F, 0.33F, 1.0F, 0.4F, 0.33F, 0.33F, 1.0F, 0.4F);
      this.colNightNoMoon = new ClimateColorInfo(0.33F, 0.33F, 1.0F, 0.4F, 0.33F, 0.33F, 1.0F, 0.4F);
      this.colNightMoon = new ClimateColorInfo(0.33F, 0.33F, 1.0F, 0.4F, 0.33F, 0.33F, 1.0F, 0.4F);
      this.colFog = new ClimateColorInfo(0.4F, 0.4F, 0.4F, 0.8F, 0.4F, 0.4F, 0.4F, 0.8F);
      this.colFogLegacy = new ClimateColorInfo(0.3F, 0.3F, 0.3F, 0.8F, 0.3F, 0.3F, 0.3F, 0.8F);
      this.colFogNew = new ClimateColorInfo(0.5F, 0.5F, 0.55F, 0.4F, 0.5F, 0.5F, 0.55F, 0.8F);
      this.fogTintStorm = new ClimateColorInfo(0.5F, 0.45F, 0.4F, 1.0F, 0.5F, 0.45F, 0.4F, 1.0F);
      this.fogTintTropical = new ClimateColorInfo(0.8F, 0.75F, 0.55F, 1.0F, 0.8F, 0.75F, 0.55F, 1.0F);
      this.colTemp = new ClimateColorInfo();
      this.simplexOffsetA = Rand.Next(0, 8000);
      this.simplexOffsetB = Rand.Next(8000, 16000);
      this.simplexOffsetC = Rand.Next(0, -8000);
      this.simplexOffsetD = Rand.Next(-8000, -16000);
      this.initSeasonColors();
      this.setup();
      this.climateValues = new ClimateValues(this);
      this.thunderStorm = new ThunderStorm(this);
      this.weatherPeriod = new WeatherPeriod(this, this.thunderStorm);
      this.climateForecaster = new ClimateForecaster();
      this.climateHistory = new ClimateHistory();

      try {
         LuaEventManager.triggerEvent("OnClimateManagerInit", this);
      } catch (Exception var2) {
         System.out.print(var2.getMessage());
         System.out.print(var2.getStackTrace());
      }
   }

   public ClimateColorInfo getColNight() {
      return this.colNight;
   }

   public ClimateColorInfo getColNightNoMoon() {
      return this.colNightNoMoon;
   }

   public ClimateColorInfo getColNightMoon() {
      return this.colNightMoon;
   }

   public ClimateColorInfo getColFog() {
      return this.colFog;
   }

   public ClimateColorInfo getColFogLegacy() {
      return this.colFogLegacy;
   }

   public ClimateColorInfo getColFogNew() {
      return this.colFogNew;
   }

   public ClimateColorInfo getFogTintStorm() {
      return this.fogTintStorm;
   }

   public ClimateColorInfo getFogTintTropical() {
      return this.fogTintTropical;
   }

   private void setup() {
      for (int var1 = 0; var1 < this.climateFloats.length; var1++) {
         this.climateFloats[var1] = new ClimateFloat();
      }

      for (int var2 = 0; var2 < this.climateColors.length; var2++) {
         this.climateColors[var2] = new ClimateColor();
      }

      for (int var3 = 0; var3 < this.climateBooleans.length; var3++) {
         this.climateBooleans[var3] = new ClimateBool();
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

   public int getFloatMax() {
      return 13;
   }

   private ClimateFloat initClimateFloat(int var1, String var2) {
      if (var1 >= 0 && var1 < 13) {
         return this.climateFloats[var1].init(var1, var2);
      } else {
         DebugLog.log("Climate: cannot get float override id.");
         return null;
      }
   }

   public ClimateFloat getClimateFloat(int var1) {
      if (var1 >= 0 && var1 < 13) {
         return this.climateFloats[var1];
      } else {
         DebugLog.log("Climate: cannot get float override id.");
         return null;
      }
   }

   public int getColorMax() {
      return 2;
   }

   private ClimateColor initClimateColor(int var1, String var2) {
      if (var1 >= 0 && var1 < 2) {
         return this.climateColors[var1].init(var1, var2);
      } else {
         DebugLog.log("Climate: cannot get float override id.");
         return null;
      }
   }

   public ClimateColor getClimateColor(int var1) {
      if (var1 >= 0 && var1 < 2) {
         return this.climateColors[var1];
      } else {
         DebugLog.log("Climate: cannot get float override id.");
         return null;
      }
   }

   public int getBoolMax() {
      return 1;
   }

   private ClimateBool initClimateBool(int var1, String var2) {
      if (var1 >= 0 && var1 < 1) {
         return this.climateBooleans[var1].init(var1, var2);
      } else {
         DebugLog.log("Climate: cannot get boolean id.");
         return null;
      }
   }

   public ClimateBool getClimateBool(int var1) {
      if (var1 >= 0 && var1 < 1) {
         return this.climateBooleans[var1];
      } else {
         DebugLog.log("Climate: cannot get boolean id.");
         return null;
      }
   }

   public void setEnabledSimulation(boolean var1) {
      if (!GameClient.bClient && !GameServer.bServer) {
         this.DISABLE_SIMULATION = !var1;
      } else {
         this.DISABLE_SIMULATION = false;
      }
   }

   public boolean getEnabledSimulation() {
      return !this.DISABLE_SIMULATION;
   }

   public boolean getEnabledFxUpdate() {
      return !this.DISABLE_FX_UPDATE;
   }

   public void setEnabledFxUpdate(boolean var1) {
      if (!GameClient.bClient && !GameServer.bServer) {
         this.DISABLE_FX_UPDATE = !var1;
      } else {
         this.DISABLE_FX_UPDATE = false;
      }
   }

   public boolean getEnabledWeatherGeneration() {
      return this.DISABLE_WEATHER_GENERATION;
   }

   public void setEnabledWeatherGeneration(boolean var1) {
      this.DISABLE_WEATHER_GENERATION = !var1;
   }

   public Color getGlobalLightInternal() {
      return this.globalLight.internalValue.getExterior();
   }

   public ClimateColorInfo getGlobalLight() {
      return this.globalLight.finalValue;
   }

   public float getGlobalLightIntensity() {
      return this.globalLightIntensity.finalValue;
   }

   public ClimateColorInfo getColorNewFog() {
      return this.colorNewFog.finalValue;
   }

   public void setNightStrength(float var1) {
      this.nightStrength.finalValue = clamp(0.0F, 1.0F, var1);
   }

   public float getDesaturation() {
      return this.desaturation.finalValue;
   }

   public void setDesaturation(float var1) {
      this.desaturation.finalValue = var1;
   }

   public float getAirMass() {
      return this.airMass;
   }

   public float getAirMassDaily() {
      return this.airMassDaily;
   }

   public float getAirMassTemperature() {
      return this.airMassTemperature;
   }

   public float getDayLightStrength() {
      return this.dayLightStrength.finalValue;
   }

   public float getNightStrength() {
      return this.nightStrength.finalValue;
   }

   public float getDayMeanTemperature() {
      return this.currentDay.season.getDayMeanTemperature();
   }

   public float getTemperature() {
      return this.temperature.finalValue;
   }

   public float getBaseTemperature() {
      return this.baseTemperature;
   }

   public float getSnowStrength() {
      return this.snowStrength;
   }

   public boolean getPrecipitationIsSnow() {
      return this.precipitationIsSnow.finalValue;
   }

   public float getPrecipitationIntensity() {
      return this.precipitationIntensity.finalValue;
   }

   public float getFogIntensity() {
      return this.fogIntensity.finalValue;
   }

   public float getWindIntensity() {
      return this.windIntensity.finalValue;
   }

   public float getWindAngleIntensity() {
      return this.windAngleIntensity.finalValue;
   }

   public float getCorrectedWindAngleIntensity() {
      return (this.windAngleIntensity.finalValue + 1.0F) * 0.5F;
   }

   public float getWindPower() {
      return this.windPower;
   }

   public float getWindspeedKph() {
      return this.windPower * 120.0F;
   }

   public float getCloudIntensity() {
      return this.cloudIntensity.finalValue;
   }

   public float getAmbient() {
      return this.ambient.finalValue;
   }

   public float getViewDistance() {
      return this.viewDistance.finalValue;
   }

   public float getHumidity() {
      return this.humidity.finalValue;
   }

   public float getWindAngleDegrees() {
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

   public float getWindAngleRadians() {
      return (float)Math.toRadians(this.getWindAngleDegrees());
   }

   public float getWindSpeedMovement() {
      float var1 = this.getWindIntensity();
      if (var1 < 0.15F) {
         var1 = 0.0F;
      } else {
         var1 = (var1 - 0.15F) / 0.85F;
      }

      return var1;
   }

   public float getWindForceMovement(IsoGameCharacter var1, float var2) {
      if (var1.square != null && !var1.square.isInARoom()) {
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

   public boolean isRaining() {
      return this.getPrecipitationIntensity() > 0.0F && !this.getPrecipitationIsSnow();
   }

   public float getRainIntensity() {
      return this.isRaining() ? this.getPrecipitationIntensity() : 0.0F;
   }

   public boolean isSnowing() {
      return this.getPrecipitationIntensity() > 0.0F && this.getPrecipitationIsSnow();
   }

   public float getSnowIntensity() {
      return this.isSnowing() ? this.getPrecipitationIntensity() : 0.0F;
   }

   public void setAmbient(float var1) {
      this.ambient.finalValue = var1;
   }

   public void setViewDistance(float var1) {
      this.viewDistance.finalValue = var1;
   }

   public void setDayLightStrength(float var1) {
      this.dayLightStrength.finalValue = var1;
   }

   public void setPrecipitationIsSnow(boolean var1) {
      this.precipitationIsSnow.finalValue = var1;
   }

   public DayInfo getCurrentDay() {
      return this.currentDay;
   }

   public DayInfo getPreviousDay() {
      return this.previousDay;
   }

   public DayInfo getNextDay() {
      return this.nextDay;
   }

   public ErosionSeason getSeason() {
      return this.currentDay != null && this.currentDay.getSeason() != null ? this.currentDay.getSeason() : this.season;
   }

   public float getFrontStrength() {
      if (this.currentFront == null) {
         return 0.0F;
      } else {
         if (Core.bDebug) {
            this.CalculateWeatherFrontStrength(this.gt.getYear(), this.gt.getMonth(), this.gt.getDayPlusOne(), this.currentFront);
         }

         return this.currentFront.strength;
      }
   }

   public void stopWeatherAndThunder() {
      if (!GameClient.bClient) {
         this.weatherPeriod.stopWeatherPeriod();
         this.thunderStorm.stopAllClouds();
         if (GameServer.bServer) {
            this.transmitClimatePacket(ClimateNetAuth.ServerOnly, (byte)1, null);
         }
      }
   }

   public ThunderStorm getThunderStorm() {
      return this.thunderStorm;
   }

   public WeatherPeriod getWeatherPeriod() {
      return this.weatherPeriod;
   }

   public boolean getIsThunderStorming() {
      return this.weatherPeriod.isRunning() && (this.weatherPeriod.isThunderStorm() || this.weatherPeriod.isTropicalStorm());
   }

   public float getWeatherInterference() {
      if (this.weatherPeriod.isRunning()) {
         return !this.weatherPeriod.isThunderStorm() && !this.weatherPeriod.isTropicalStorm() && !this.weatherPeriod.isBlizzard()
            ? 0.35F * this.weatherPeriod.getCurrentStrength()
            : 0.7F * this.weatherPeriod.getCurrentStrength();
      } else {
         return 0.0F;
      }
   }

   public KahluaTable getModData() {
      if (this.modDataTable == null) {
         this.modDataTable = LuaManager.platform.newTable();
      }

      return this.modDataTable;
   }

   public float getAirTemperatureForCharacter(IsoGameCharacter var1) {
      return this.getAirTemperatureForCharacter(var1, false);
   }

   public float getAirTemperatureForCharacter(IsoGameCharacter var1, boolean var2) {
      if (var1.square != null) {
         return var1.getVehicle() != null
            ? this.getAirTemperatureForSquare(var1.square, var1.getVehicle(), var2)
            : this.getAirTemperatureForSquare(var1.square, null, var2);
      } else {
         return this.getTemperature();
      }
   }

   public float getAirTemperatureForSquare(IsoGridSquare var1) {
      return this.getAirTemperatureForSquare(var1, null);
   }

   public float getAirTemperatureForSquare(IsoGridSquare var1, BaseVehicle var2) {
      return this.getAirTemperatureForSquare(var1, var2, false);
   }

   public float getAirTemperatureForSquare(IsoGridSquare var1, BaseVehicle var2, boolean var3) {
      float var4 = this.getTemperature();
      if (var1 != null) {
         boolean var5 = var1.isInARoom();
         if (var5 || var2 != null) {
            boolean var6 = IsoWorld.instance.isHydroPowerOn();
            if (var4 <= 22.0F) {
               float var7 = (22.0F - var4) / 8.0F;
               if (var2 == null) {
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
               if (var2 == null) {
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

         if (var2 != null) {
            var4 += var2.getInsideTemperature();
         }
      }

      return var4;
   }

   public String getSeasonName() {
      return this.season.getSeasonName();
   }

   public float getSeasonProgression() {
      return this.season.getSeasonProgression();
   }

   public float getSeasonStrength() {
      return this.season.getSeasonStrength();
   }

   public void init(IsoMetaGrid var1) {
      WorldFlares.Clear();
      this.season = ErosionMain.getInstance().getSeasons();
      ThunderStorm.MAP_MIN_X = var1.minX * 300 - 4000;
      ThunderStorm.MAP_MAX_X = var1.maxX * 300 + 4000;
      ThunderStorm.MAP_MIN_Y = var1.minY * 300 - 4000;
      ThunderStorm.MAP_MAX_Y = var1.maxY * 300 + 4000;
      windNoiseOffset = 0.0;
      WINTER_IS_COMING = IsoWorld.instance.getGameMode().equals("Winter is Coming");
      THE_DESCENDING_FOG = IsoWorld.instance.getGameMode().equals("The Descending Fog");
      A_STORM_IS_COMING = IsoWorld.instance.getGameMode().equals("A Storm is Coming");
      this.climateForecaster.init(this);
      this.climateHistory.init(this);
   }

   public void updateEveryTenMins() {
      this.tickIsTenMins = true;
   }

   public void update() {
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
            if (var9 != null) {
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
            this.transmitClimatePacket(ClimateNetAuth.ServerOnly, (byte)0, null);
            this.tickIsTenMins = false;
         }

         if (!this.DISABLE_FX_UPDATE) {
            this.updateFx();
         }
      }
   }

   public static double getWindNoiseBase() {
      return windNoiseBase;
   }

   public static double getWindNoiseFinal() {
      return windNoiseFinal;
   }

   public static double getWindTickFinal() {
      return windTickFinal;
   }

   private void updateWindTick() {
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

   public void updateOLD() {
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
                  this.transmitClimatePacket(ClimateNetAuth.ServerOnly, (byte)0, null);
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
               if (var6 != null) {
                  var6.dirtyRecalcGridStackTime = 1.0F;
               }
            }
         }
      }
   }

   private void updateFx() {
      IsoWeatherFX var1 = IsoWorld.instance.getCell().getWeatherFX();
      if (var1 != null) {
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

   private void updateSnow() {
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

   private void updateSnowOLD() {
   }

   public float getSnowFracNow() {
      return this.snowFracNow;
   }

   public void resetOverrides() {
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

   public void resetModded() {
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

   public void resetAdmin() {
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

   public void triggerWinterIsComingStorm() {
      if (!GameClient.bClient && !this.weatherPeriod.isRunning()) {
         AirFront var1 = new AirFront();
         var1.copyFrom(this.currentFront);
         var1.strength = 0.95F;
         var1.type = 1;
         GameTime var2 = GameTime.getInstance();
         this.weatherPeriod.init(var1, this.worldAgeHours, var2.getYear(), var2.getMonth(), var2.getDayPlusOne());
      }
   }

   public boolean triggerCustomWeather(float var1, boolean var2) {
      if (!GameClient.bClient && !this.weatherPeriod.isRunning()) {
         AirFront var3 = new AirFront();
         var3.strength = var1;
         var3.type = var2 ? 1 : -1;
         GameTime var4 = GameTime.getInstance();
         this.weatherPeriod.init(var3, this.worldAgeHours, var4.getYear(), var4.getMonth(), var4.getDayPlusOne());
         return true;
      } else {
         return false;
      }
   }

   public boolean triggerCustomWeatherStage(int var1, float var2) {
      if (!GameClient.bClient && !this.weatherPeriod.isRunning()) {
         AirFront var3 = new AirFront();
         var3.strength = 0.95F;
         var3.type = 1;
         GameTime var4 = GameTime.getInstance();
         this.weatherPeriod.init(var3, this.worldAgeHours, var4.getYear(), var4.getMonth(), var4.getDayPlusOne(), var1, var2);
         return true;
      } else {
         return false;
      }
   }

   private void updateOnTick() {
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

   private void updateTestFlare() {
      WorldFlares.update();
   }

   public void launchFlare() {
      DebugLog.log("Launching improved flare.");
      IsoPlayer var1 = IsoPlayer.getInstance();
      float var2 = 0.0F;
      WorldFlares.launchFlare(7200.0F, (int)var1.getX(), (int)var1.getY(), 50, var2, 1.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F);
      if (IsoPlayer.getInstance() != null && !this.flareLaunched) {
         this.flareLaunched = true;
         this.flareLifeTime = 0.0F;
         this.flareMaxLifeTime = 7200.0F;
         this.flareIntensity.overrideCurrentValue(1.0F);
         this.flareIntens = 1.0F;
         this.nextRandomTargetIntens = 10;
      }
   }

   protected double getAirMassNoiseFrequencyMod(int var1) {
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

   protected float getRainTimeMultiplierMod(int var1) {
      if (var1 == 1) {
         return 0.5F;
      } else if (var1 == 2) {
         return 0.75F;
      } else if (var1 == 4) {
         return 1.25F;
      } else {
         return var1 == 5 ? 1.5F : 1.0F;
      }
   }

   private void updateValues() {
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
            if (Core.getInstance().RenderShader == null || Core.getInstance().getOffscreenBuffer() == null) {
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
      if (Core.getInstance().RenderShader != null && Core.getInstance().getOffscreenBuffer() != null) {
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
         if (Core.getInstance().RenderShader == null || Core.getInstance().getOffscreenBuffer() == null) {
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
         if (var18 != null) {
            var18.dirtyRecalcGridStackTime = 1.0F;
         }
      }
   }

   private void updateViewDistance() {
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

   public void setSeasonColorDawn(int var1, int var2, float var3, float var4, float var5, float var6, boolean var7) {
      if (var7) {
         this.seasonColorDawn.setColorExterior(var1, var2, var3, var4, var5, var6);
      } else {
         this.seasonColorDawn.setColorInterior(var1, var2, var3, var4, var5, var6);
      }
   }

   public void setSeasonColorDay(int var1, int var2, float var3, float var4, float var5, float var6, boolean var7) {
      if (var7) {
         this.seasonColorDay.setColorExterior(var1, var2, var3, var4, var5, var6);
      } else {
         this.seasonColorDay.setColorInterior(var1, var2, var3, var4, var5, var6);
      }
   }

   public void setSeasonColorDusk(int var1, int var2, float var3, float var4, float var5, float var6, boolean var7) {
      if (var7) {
         this.seasonColorDusk.setColorExterior(var1, var2, var3, var4, var5, var6);
      } else {
         this.seasonColorDusk.setColorInterior(var1, var2, var3, var4, var5, var6);
      }
   }

   public ClimateColorInfo getSeasonColor(int var1, int var2, int var3) {
      SeasonColor var4 = null;
      if (var1 == 0) {
         var4 = this.seasonColorDawn;
      } else if (var1 == 1) {
         var4 = this.seasonColorDay;
      } else if (var1 == 2) {
         var4 = this.seasonColorDusk;
      }

      return var4 != null ? var4.getColor(var2, var3) : null;
   }

   private void initSeasonColors() {
      SeasonColor var1 = new SeasonColor();
      var1.setIgnoreNormal(true);
      this.seasonColorDawn = var1;
      var1 = new SeasonColor();
      var1.setIgnoreNormal(true);
      this.seasonColorDay = var1;
      var1 = new SeasonColor();
      var1.setIgnoreNormal(false);
      this.seasonColorDusk = var1;
   }

   public void save(DataOutputStream var1) throws IOException {
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

      if (this.modDataTable != null) {
         var1.writeByte(1);
         this.modDataTable.save(var1);
      } else {
         var1.writeByte(0);
      }

      if (GameServer.bServer) {
         this.humidity.saveAdmin(var1);
      }
   }

   public void load(DataInputStream var1, int var2) throws IOException {
      boolean var3 = var1.readByte() == 1;
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
         if (this.modDataTable == null) {
            this.modDataTable = LuaManager.platform.newTable();
         }

         this.modDataTable.load(var1, var2);
      }

      if (var2 >= 150 && GameServer.bServer) {
         this.humidity.loadAdmin(var1, var2);
      }

      this.climateValues = new ClimateValues(this);
   }

   public void postCellLoadSetSnow() {
      IsoWorld.instance.CurrentCell.setSnowTarget((int)(this.snowFracNow * 100.0F));
      ErosionIceQueen.instance.setSnow(this.canDoWinterSprites && this.snowFracNow > 0.2F);
   }

   public void forceDayInfoUpdate() {
      this.currentDay.day = -1;
      this.currentDay.month = -1;
      this.currentDay.year = -1;
      this.gt = GameTime.getInstance();
      this.updateDayInfo(this.gt.getDayPlusOne(), this.gt.getMonth(), this.gt.getYear());
      this.currentDay.hour = this.gt.getHour();
      this.currentDay.minutes = this.gt.getMinutes();
   }

   private void updateDayInfo(int var1, int var2, int var3) {
      this.tickIsDayChange = false;
      if (this.currentDay == null || this.currentDay.day != var1 || this.currentDay.month != var2 || this.currentDay.year != var3) {
         this.tickIsDayChange = this.currentDay != null;
         if (this.currentDay == null) {
            this.currentDay = new DayInfo();
         }

         this.setDayInfo(this.currentDay, var1, var2, var3, 0);
         if (this.previousDay == null) {
            this.previousDay = new DayInfo();
            this.previousDay.season = this.season.clone();
         }

         this.setDayInfo(this.previousDay, var1, var2, var3, -1);
         if (this.nextDay == null) {
            this.nextDay = new DayInfo();
            this.nextDay.season = this.season.clone();
         }

         this.setDayInfo(this.nextDay, var1, var2, var3, 1);
      }
   }

   protected void setDayInfo(DayInfo var1, int var2, int var3, int var4, int var5) {
      var1.calendar = new GregorianCalendar(var4, var3, var2, 0, 0);
      var1.calendar.add(5, var5);
      var1.day = var1.calendar.get(5);
      var1.month = var1.calendar.get(2);
      var1.year = var1.calendar.get(1);
      var1.dateValue = var1.calendar.getTime().getTime();
      if (var1.season == null) {
         var1.season = this.season.clone();
      }

      var1.season.setDay(var1.day, var1.month, var1.year);
   }

   protected final void transmitClimatePacket(ClimateNetAuth var1, byte var2, UdpConnection var3) {
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
                     if (var3 == null || var3 != var5) {
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

   private boolean writePacketContents(UdpConnection var1, byte var2) throws IOException {
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

   public final void receiveClimatePacket(ByteBuffer var1, UdpConnection var2) throws IOException {
      if (GameClient.bClient || GameServer.bServer) {
         byte var3 = var1.get();
         this.readPacketContents(var1, var3, var2);
      }
   }

   private boolean readPacketContents(ByteBuffer var1, byte var2, UdpConnection var3) throws IOException {
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
            this.transmitClimatePacket(ClimateNetAuth.ServerOnly, (byte)4, null);
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

   private void serverReceiveClientChangeAdminVars() {
      if (GameServer.bServer) {
         if (this.networkPrint) {
            DebugLog.log("clim: serverReceiveClientChangeAdminVars");
         }

         this.transmitClimatePacket(ClimateNetAuth.ServerOnly, (byte)4, null);
         this.updateOnTick();
         this.transmitClimatePacket(ClimateNetAuth.ServerOnly, (byte)0, null);
      }
   }

   private void serverReceiveClientChangeWeather() {
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
         this.transmitClimatePacket(ClimateNetAuth.ServerOnly, (byte)0, null);
      }
   }

   public void transmitServerStopWeather() {
      if (GameServer.bServer) {
         this.stopWeatherAndThunder();
         if (this.networkPrint) {
            DebugLog.log("clim: SERVER transmitStopWeather");
         }

         this.updateOnTick();
         this.transmitClimatePacket(ClimateNetAuth.ServerOnly, (byte)0, null);
      }
   }

   public void transmitServerTriggerStorm(float var1) {
      if (GameServer.bServer) {
         if (this.networkPrint) {
            DebugLog.log("clim: SERVER transmitTriggerStorm");
         }

         this.netInfo.TriggerDuration = var1;
         this.triggerCustomWeatherStage(3, this.netInfo.TriggerDuration);
         this.updateOnTick();
         this.transmitClimatePacket(ClimateNetAuth.ServerOnly, (byte)0, null);
      }
   }

   public void transmitServerTriggerLightning(int var1, int var2, boolean var3, boolean var4, boolean var5) {
      if (GameServer.bServer) {
         if (this.networkPrint) {
            DebugLog.log("clim: SERVER transmitTriggerLightning");
         }

         this.thunderStorm.triggerThunderEvent(var1, var2, var3, var4, var5);
      }
   }

   public void transmitServerStartRain(float var1) {
      if (GameServer.bServer) {
         this.precipitationIntensity.setAdminValue(clamp01(var1));
         this.precipitationIntensity.setEnableAdmin(true);
         this.updateOnTick();
         this.transmitClimatePacket(ClimateNetAuth.ServerOnly, (byte)0, null);
      }
   }

   public void transmitServerStopRain() {
      if (GameServer.bServer) {
         this.precipitationIntensity.setEnableAdmin(false);
         this.updateOnTick();
         this.transmitClimatePacket(ClimateNetAuth.ServerOnly, (byte)0, null);
      }
   }

   public void transmitRequestAdminVars() {
      if (this.networkPrint) {
         DebugLog.log("clim: transmitRequestAdminVars");
      }

      this.transmitClimatePacket(ClimateNetAuth.ClientOnly, (byte)5, null);
   }

   public void transmitClientChangeAdminVars() {
      if (this.networkPrint) {
         DebugLog.log("clim: transmitClientChangeAdminVars");
      }

      this.transmitClimatePacket(ClimateNetAuth.ClientOnly, (byte)6, null);
   }

   public void transmitStopWeather() {
      if (this.networkPrint) {
         DebugLog.log("clim: transmitStopWeather");
      }

      this.netInfo.reset();
      this.netInfo.IsStopWeather = true;
      this.transmitClimatePacket(ClimateNetAuth.ClientOnly, (byte)7, null);
   }

   public void transmitTriggerStorm(float var1) {
      if (this.networkPrint) {
         DebugLog.log("clim: transmitTriggerStorm");
      }

      this.netInfo.reset();
      this.netInfo.IsTrigger = true;
      this.netInfo.TriggerStorm = true;
      this.netInfo.TriggerDuration = var1;
      this.transmitClimatePacket(ClimateNetAuth.ClientOnly, (byte)7, null);
   }

   public void transmitTriggerTropical(float var1) {
      if (this.networkPrint) {
         DebugLog.log("clim: transmitTriggerTropical");
      }

      this.netInfo.reset();
      this.netInfo.IsTrigger = true;
      this.netInfo.TriggerTropical = true;
      this.netInfo.TriggerDuration = var1;
      this.transmitClimatePacket(ClimateNetAuth.ClientOnly, (byte)7, null);
   }

   public void transmitTriggerBlizzard(float var1) {
      if (this.networkPrint) {
         DebugLog.log("clim: transmitTriggerBlizzard");
      }

      this.netInfo.reset();
      this.netInfo.IsTrigger = true;
      this.netInfo.TriggerBlizzard = true;
      this.netInfo.TriggerDuration = var1;
      this.transmitClimatePacket(ClimateNetAuth.ClientOnly, (byte)7, null);
   }

   public void transmitGenerateWeather(float var1, int var2) {
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

      this.transmitClimatePacket(ClimateNetAuth.ClientOnly, (byte)7, null);
   }

   protected float getTimeLerpHours(float var1, float var2, float var3) {
      return this.getTimeLerpHours(var1, var2, var3, false);
   }

   protected float getTimeLerpHours(float var1, float var2, float var3, boolean var4) {
      return this.getTimeLerp(clamp(0.0F, 1.0F, var1 / 24.0F), clamp(0.0F, 1.0F, var2 / 24.0F), clamp(0.0F, 1.0F, var3 / 24.0F), var4);
   }

   protected float getTimeLerp(float var1, float var2, float var3) {
      return this.getTimeLerp(var1, var2, var3, false);
   }

   protected float getTimeLerp(float var1, float var2, float var3, boolean var4) {
      boolean var5 = var2 > var3;
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

   public static float clamp01(float var0) {
      return clamp(0.0F, 1.0F, var0);
   }

   public static float clamp(float var0, float var1, float var2) {
      var2 = Math.min(var1, var2);
      return Math.max(var0, var2);
   }

   public static int clamp(int var0, int var1, int var2) {
      var2 = Math.min(var1, var2);
      return Math.max(var0, var2);
   }

   public static float lerp(float var0, float var1, float var2) {
      return var1 + var0 * (var2 - var1);
   }

   public static float clerp(float var0, float var1, float var2) {
      float var3 = (float)(1.0 - Math.cos(var0 * Math.PI)) / 2.0F;
      return var1 * (1.0F - var3) + var2 * var3;
   }

   public static float normalizeRange(float var0, float var1) {
      return clamp(0.0F, 1.0F, var0 / var1);
   }

   public static float posToPosNegRange(float var0) {
      if (var0 > 0.5F) {
         return (var0 - 0.5F) * 2.0F;
      } else {
         return var0 < 0.5F ? -((0.5F - var0) * 2.0F) : 0.0F;
      }
   }

   public void execute_Simulation() {
      if (Core.bDebug) {
         ClimMngrDebug var1 = new ClimMngrDebug();
         short var2 = 365;
         short var3 = 5000;
         var1.SimulateDays(var2, var3);
      }
   }

   public void execute_Simulation(int var1) {
      if (Core.bDebug) {
         ClimMngrDebug var2 = new ClimMngrDebug();
         var2.setRainModOverride(var1);
         short var3 = 365;
         short var4 = 5000;
         var2.SimulateDays(var3, var4);
      }
   }

   public void triggerKateBobIntroStorm(int var1, int var2, double var3, float var5, float var6, float var7, float var8) {
      this.triggerKateBobIntroStorm(var1, var2, var3, var5, var6, var7, var8, null);
   }

   public void triggerKateBobIntroStorm(int var1, int var2, double var3, float var5, float var6, float var7, float var8, ClimateColorInfo var9) {
      if (!GameClient.bClient) {
         this.stopWeatherAndThunder();
         if (this.weatherPeriod.startCreateModdedPeriod(true, var5, var7)) {
            this.weatherPeriod.setKateBobStormProgress(var6);
            this.weatherPeriod.setKateBobStormCoords(var1, var2);
            this.weatherPeriod.createAndAddStage(11, var3);
            this.weatherPeriod.createAndAddStage(2, var3 / 2.0);
            this.weatherPeriod.createAndAddStage(4, var3 / 4.0);
            this.weatherPeriod.endCreateModdedPeriod();
            if (var9 != null) {
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

   public double getSimplexOffsetA() {
      return this.simplexOffsetA;
   }

   public double getSimplexOffsetB() {
      return this.simplexOffsetB;
   }

   public double getSimplexOffsetC() {
      return this.simplexOffsetC;
   }

   public double getSimplexOffsetD() {
      return this.simplexOffsetD;
   }

   public double getWorldAgeHours() {
      return this.worldAgeHours;
   }

   public ClimateValues getClimateValuesCopy() {
      return this.climateValues.getCopy();
   }

   public void CopyClimateValues(ClimateValues var1) {
      this.climateValues.CopyValues(var1);
   }

   public ClimateForecaster getClimateForecaster() {
      return this.climateForecaster;
   }

   public ClimateHistory getClimateHistory() {
      return this.climateHistory;
   }

   public void CalculateWeatherFrontStrength(int var1, int var2, int var3, AirFront var4) {
      GregorianCalendar var5 = new GregorianCalendar(var1, var2, var3, 0, 0);
      var5.add(5, -3);
      if (this.climateValuesFronts == null) {
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

         var5.add(5, 1);
      }

      DebugLog.log("Calculate weather front strength = " + var4.getStrength());
   }

   public static String getWindAngleString(float var0) {
      for (int var1 = 0; var1 < windAngles.length; var1++) {
         if (var0 < windAngles[var1]) {
            return windAngleStr[var1];
         }
      }

      return windAngleStr[windAngleStr.length - 1];
   }

   public void sendInitialState(UdpConnection var1) throws IOException {
      if (GameServer.bServer) {
         if (this.writePacketContents(var1, (byte)0)) {
            PacketType.ClimateManagerPacket.send(var1);
         } else {
            var1.cancelPacket();
         }
      }
   }

   public boolean isUpdated() {
      return this.lastMinuteStamp != -1L;
   }
}
