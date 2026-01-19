package zombie.iso.weather;

import java.util.ArrayList;
import zombie.iso.weather.ClimateForecaster.ForecastValue;
import zombie.iso.weather.ClimateManager.AirFront;

public class ClimateForecaster$DayForecast {
   private int indexOffset = 0;
   private String name = "Day x";
   private WeatherPeriod weatherPeriod;
   private ForecastValue temperature = new ForecastValue();
   private ForecastValue humidity = new ForecastValue();
   private ForecastValue windDirection = new ForecastValue();
   private ForecastValue windPower = new ForecastValue();
   private ForecastValue cloudiness = new ForecastValue();
   private boolean weatherStarts = false;
   private float weatherStartTime = 0.0F;
   private float weatherEndTime = 24.0F;
   private boolean chanceOnSnow = false;
   private String airFrontString = "";
   private boolean hasFog = false;
   private float fogStrength = 0.0F;
   private float fogDuration = 0.0F;
   private AirFront airFront;
   private ClimateForecaster$DayForecast weatherOverlap;
   private boolean hasHeavyRain = false;
   private boolean hasStorm = false;
   private boolean hasTropicalStorm = false;
   private boolean hasBlizzard = false;
   private float dawn = 0.0F;
   private float dusk = 0.0F;
   private float dayLightHours = 0.0F;
   private ArrayList<Integer> weatherStages = new ArrayList<>();

   public int getIndexOffset() {
      return this.indexOffset;
   }

   public String getName() {
      return this.name;
   }

   public ForecastValue getTemperature() {
      return this.temperature;
   }

   public ForecastValue getHumidity() {
      return this.humidity;
   }

   public ForecastValue getWindDirection() {
      return this.windDirection;
   }

   public ForecastValue getWindPower() {
      return this.windPower;
   }

   public ForecastValue getCloudiness() {
      return this.cloudiness;
   }

   public WeatherPeriod getWeatherPeriod() {
      return this.weatherPeriod;
   }

   public boolean isWeatherStarts() {
      return this.weatherStarts;
   }

   public float getWeatherStartTime() {
      return this.weatherStartTime;
   }

   public float getWeatherEndTime() {
      return this.weatherEndTime;
   }

   public boolean isChanceOnSnow() {
      return this.chanceOnSnow;
   }

   public String getAirFrontString() {
      return this.airFrontString;
   }

   public boolean isHasFog() {
      return this.hasFog;
   }

   public AirFront getAirFront() {
      return this.airFront;
   }

   public ClimateForecaster$DayForecast getWeatherOverlap() {
      return this.weatherOverlap;
   }

   public String getMeanWindAngleString() {
      return ClimateManager.getWindAngleString(this.windDirection.getTotalMean());
   }

   public float getFogStrength() {
      return this.fogStrength;
   }

   public float getFogDuration() {
      return this.fogDuration;
   }

   public boolean isHasHeavyRain() {
      return this.hasHeavyRain;
   }

   public boolean isHasStorm() {
      return this.hasStorm;
   }

   public boolean isHasTropicalStorm() {
      return this.hasTropicalStorm;
   }

   public boolean isHasBlizzard() {
      return this.hasBlizzard;
   }

   public ArrayList<Integer> getWeatherStages() {
      return this.weatherStages;
   }

   public float getDawn() {
      return this.dawn;
   }

   public float getDusk() {
      return this.dusk;
   }

   public float getDayLightHours() {
      return this.dayLightHours;
   }

   private void reset() {
      this.weatherPeriod.stopWeatherPeriod();
      this.temperature.reset();
      this.humidity.reset();
      this.windDirection.reset();
      this.windPower.reset();
      this.cloudiness.reset();
      this.weatherStarts = false;
      this.weatherStartTime = 0.0F;
      this.weatherEndTime = 24.0F;
      this.chanceOnSnow = false;
      this.hasFog = false;
      this.fogStrength = 0.0F;
      this.fogDuration = 0.0F;
      this.weatherOverlap = null;
      this.hasHeavyRain = false;
      this.hasStorm = false;
      this.hasTropicalStorm = false;
      this.hasBlizzard = false;
      this.weatherStages.clear();
   }
}
