package zombie.iso.weather;

import java.util.ArrayList;
import java.util.GregorianCalendar;
import zombie.GameTime;
import zombie.iso.weather.ClimateForecaster.DayForecast;
import zombie.iso.weather.ClimateManager.AirFront;
import zombie.iso.weather.WeatherPeriod.WeatherStage;

public class ClimateForecaster {
   private static final int OffsetToday = 10;
   private ClimateValues climateValues;
   private DayForecast[] forecasts = new DayForecast[40];
   private ArrayList<DayForecast> forecastList = new ArrayList<>(40);

   public ArrayList<DayForecast> getForecasts() {
      return this.forecastList;
   }

   public DayForecast getForecast() {
      return this.getForecast(0);
   }

   public DayForecast getForecast(int var1) {
      int var2 = 10 + var1;
      return var2 >= 0 && var2 < this.forecasts.length ? this.forecasts[var2] : null;
   }

   private void populateForecastList() {
      this.forecastList.clear();

      for (int var1 = 0; var1 < this.forecasts.length; var1++) {
         this.forecastList.add(this.forecasts[var1]);
      }
   }

   protected void init(ClimateManager var1) {
      this.climateValues = var1.getClimateValuesCopy();

      for (int var2 = 0; var2 < this.forecasts.length; var2++) {
         int var3 = var2 - 10;
         DayForecast var4 = new DayForecast();
         var4.weatherPeriod = new WeatherPeriod(var1, var1.getThunderStorm());
         var4.weatherPeriod.setDummy(true);
         var4.indexOffset = var3;
         var4.airFront = new AirFront();
         this.sampleDay(var1, var4, var3);
         this.forecasts[var2] = var4;
      }

      this.populateForecastList();
   }

   protected void updateDayChange(ClimateManager var1) {
      DayForecast var2 = this.forecasts[0];

      for (int var3 = 0; var3 < this.forecasts.length; var3++) {
         if (var3 > 0 && var3 < this.forecasts.length) {
            this.forecasts[var3].indexOffset = var3 - 1 - 10;
            this.forecasts[var3 - 1] = this.forecasts[var3];
         }
      }

      var2.reset();
      this.sampleDay(var1, var2, this.forecasts.length - 1 - 10);
      var2.indexOffset = this.forecasts.length - 1 - 10;
      this.forecasts[this.forecasts.length - 1] = var2;
      this.populateForecastList();
   }

   protected void sampleDay(ClimateManager var1, DayForecast var2, int var3) {
      GameTime var4 = GameTime.getInstance();
      int var5 = var4.getYear();
      int var6 = var4.getMonth();
      int var7 = var4.getDayPlusOne();
      GregorianCalendar var8 = new GregorianCalendar(var5, var6, var7, 0, 0);
      var8.add(5, var3);
      boolean var9 = true;
      DayForecast var10 = this.getWeatherOverlap(var3 + 10, 0.0F);
      var2.weatherOverlap = var10;
      var2.weatherPeriod.stopWeatherPeriod();
      var2.name = "day: " + var8.get(1) + " - " + (var8.get(2) + 1) + " - " + var8.get(5);

      for (int var11 = 0; var11 < 24; var11++) {
         if (var11 != 0) {
            var8.add(11, 1);
         }

         this.climateValues.pollDate(var8);
         if (var11 == 0) {
            var9 = this.climateValues.getNoiseAirmass() >= 0.0F;
            var2.airFrontString = var9 ? "WARM" : "COLD";
            var2.dawn = this.climateValues.getDawn();
            var2.dusk = this.climateValues.getDusk();
            var2.dayLightHours = var2.dusk - var2.dawn;
         }

         if (!var2.weatherStarts && (var9 && this.climateValues.getNoiseAirmass() < 0.0F || !var9 && this.climateValues.getNoiseAirmass() >= 0.0F)) {
            int var12 = this.climateValues.getNoiseAirmass() >= 0.0F ? -1 : 1;
            var2.airFront.setFrontType(var12);
            var1.CalculateWeatherFrontStrength(var8.get(1), var8.get(2), var8.get(5), var2.airFront);
            var2.airFront.setFrontWind(this.climateValues.getWindAngleDegrees());
            if (var2.airFront.getStrength() >= 0.1F) {
               DayForecast var13 = this.getWeatherOverlap(var3 + 10, var11);
               float var14 = var13 != null ? var13.weatherPeriod.getTotalStrength() : -1.0F;
               if (var14 < 0.1F) {
                  var2.weatherStarts = true;
                  var2.weatherStartTime = var11;
                  var2.weatherPeriod.init(var2.airFront, this.climateValues.getCacheWorldAgeHours(), var8.get(1), var8.get(2), var8.get(5));
               }
            }

            if (!var2.weatherStarts) {
               var9 = !var9;
            }
         }

         boolean var20 = var11 > this.climateValues.getDawn() && var11 <= this.climateValues.getDusk();
         float var21 = this.climateValues.getTemperature();
         float var22 = this.climateValues.getHumidity();
         float var15 = this.climateValues.getWindAngleDegrees();
         float var16 = this.climateValues.getWindIntensity();
         float var17 = this.climateValues.getCloudIntensity();
         if (var2.weatherStarts || var2.weatherOverlap != null) {
            WeatherPeriod var18 = var2.weatherStarts ? var2.weatherPeriod : var2.weatherOverlap.weatherPeriod;
            if (var18 != null) {
               var15 = var18.getWindAngleDegrees();
               WeatherStage var19 = var18.getStageForWorldAge(this.climateValues.getCacheWorldAgeHours());
               if (var19 != null) {
                  if (!var2.weatherStages.contains(var19.getStageID())) {
                     var2.weatherStages.add(var19.getStageID());
                  }

                  switch (var19.getStageID()) {
                     case 1:
                        var2.hasHeavyRain = true;
                     case 4:
                     case 5:
                     case 6:
                     default:
                        var21 -= WeatherPeriod.getMaxTemperatureInfluence() * 0.25F;
                        var17 = 0.35F + 0.5F * var18.getTotalStrength();
                        break;
                     case 2:
                        var16 = 0.5F * var18.getTotalStrength();
                        var21 -= WeatherPeriod.getMaxTemperatureInfluence() * var16;
                        var17 = 0.5F + 0.5F * var16;
                        var2.hasHeavyRain = true;
                        break;
                     case 3:
                        var16 = 0.2F + 0.5F * var18.getTotalStrength();
                        var21 -= WeatherPeriod.getMaxTemperatureInfluence() * var16;
                        var17 = 0.5F + 0.5F * var16;
                        var2.hasStorm = true;
                        break;
                     case 7:
                        var2.chanceOnSnow = true;
                        var16 = 0.75F + 0.25F * var18.getTotalStrength();
                        var21 -= WeatherPeriod.getMaxTemperatureInfluence() * var16;
                        var17 = 0.5F + 0.5F * var16;
                        var2.hasBlizzard = true;
                        break;
                     case 8:
                        var16 = 0.4F + 0.6F * var18.getTotalStrength();
                        var21 -= WeatherPeriod.getMaxTemperatureInfluence() * var16;
                        var17 = 0.5F + 0.5F * var16;
                        var2.hasTropicalStorm = true;
                  }
               } else if (var2.weatherOverlap != null && var11 < var2.weatherEndTime) {
                  var2.weatherEndTime = var11;
               }
            }

            if (var21 < 0.0F) {
               var2.chanceOnSnow = true;
            }
         }

         var2.temperature.add(var21, var20);
         var2.humidity.add(var22, var20);
         var2.windDirection.add(var15, var20);
         var2.windPower.add(var16, var20);
         var2.cloudiness.add(var17, var20);
      }

      var2.temperature.calculate();
      var2.humidity.calculate();
      var2.windDirection.calculate();
      var2.windPower.calculate();
      var2.cloudiness.calculate();
      var2.hasFog = this.climateValues.isDayDoFog();
      var2.fogStrength = this.climateValues.getDayFogStrength();
      var2.fogDuration = this.climateValues.getDayFogDuration();
   }

   private DayForecast getWeatherOverlap(int var1, float var2) {
      int var3 = Math.max(0, var1 - 10);
      if (var3 == var1) {
         return null;
      } else {
         for (int var4 = var3; var4 < var1; var4++) {
            if (this.forecasts[var4].weatherStarts) {
               float var5 = (float)this.forecasts[var4].weatherPeriod.getDuration() / 24.0F;
               float var6 = var4 + this.forecasts[var4].weatherStartTime / 24.0F;
               var6 += var5;
               float var7 = var1 + var2 / 24.0F;
               if (var6 > var7) {
                  return this.forecasts[var4];
               }
            }
         }

         return null;
      }
   }

   public int getDaysTillFirstWeather() {
      int var1 = -1;

      for (int var2 = 10; var2 < this.forecasts.length - 1; var2++) {
         if (this.forecasts[var2].weatherStarts && var1 < 0) {
            var1 = var2;
         }
      }

      return var1;
   }
}
