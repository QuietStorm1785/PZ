#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/weather/ClimateForecaster/ForecastValue.h"
#include "zombie/iso/weather/ClimateManager/AirFront.h"

namespace zombie {
namespace iso {
namespace weather {


class ClimateForecaster {
public:
    int indexOffset = 0;
    std::string name = "Day x";
    WeatherPeriod weatherPeriod;
    ForecastValue temperature = std::make_shared<ForecastValue>();
    ForecastValue humidity = std::make_shared<ForecastValue>();
    ForecastValue windDirection = std::make_shared<ForecastValue>();
    ForecastValue windPower = std::make_shared<ForecastValue>();
    ForecastValue cloudiness = std::make_shared<ForecastValue>();
    bool weatherStarts = false;
    float weatherStartTime = 0.0F;
    float weatherEndTime = 24.0F;
    bool chanceOnSnow = false;
    std::string airFrontString = "";
    bool hasFog = false;
    float fogStrength = 0.0F;
    float fogDuration = 0.0F;
    AirFront airFront;
   private ClimateForecaster$DayForecast weatherOverlap;
    bool hasHeavyRain = false;
    bool hasStorm = false;
    bool hasTropicalStorm = false;
    bool hasBlizzard = false;
    float dawn = 0.0F;
    float dusk = 0.0F;
    float dayLightHours = 0.0F;
   private std::vector<int> weatherStages = std::make_unique<std::vector<>>();

    int getIndexOffset() {
      return this.indexOffset;
   }

    std::string getName() {
      return this.name;
   }

    ForecastValue getTemperature() {
      return this.temperature;
   }

    ForecastValue getHumidity() {
      return this.humidity;
   }

    ForecastValue getWindDirection() {
      return this.windDirection;
   }

    ForecastValue getWindPower() {
      return this.windPower;
   }

    ForecastValue getCloudiness() {
      return this.cloudiness;
   }

    WeatherPeriod getWeatherPeriod() {
      return this.weatherPeriod;
   }

    bool isWeatherStarts() {
      return this.weatherStarts;
   }

    float getWeatherStartTime() {
      return this.weatherStartTime;
   }

    float getWeatherEndTime() {
      return this.weatherEndTime;
   }

    bool isChanceOnSnow() {
      return this.chanceOnSnow;
   }

    std::string getAirFrontString() {
      return this.airFrontString;
   }

    bool isHasFog() {
      return this.hasFog;
   }

    AirFront getAirFront() {
      return this.airFront;
   }

   public ClimateForecaster$DayForecast getWeatherOverlap() {
      return this.weatherOverlap;
   }

    std::string getMeanWindAngleString() {
      return ClimateManager.getWindAngleString(this.windDirection.getTotalMean());
   }

    float getFogStrength() {
      return this.fogStrength;
   }

    float getFogDuration() {
      return this.fogDuration;
   }

    bool isHasHeavyRain() {
      return this.hasHeavyRain;
   }

    bool isHasStorm() {
      return this.hasStorm;
   }

    bool isHasTropicalStorm() {
      return this.hasTropicalStorm;
   }

    bool isHasBlizzard() {
      return this.hasBlizzard;
   }

   public std::vector<int> getWeatherStages() {
      return this.weatherStages;
   }

    float getDawn() {
      return this.dawn;
   }

    float getDusk() {
      return this.dusk;
   }

    float getDayLightHours() {
      return this.dayLightHours;
   }

    void reset() {
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
      this.weatherOverlap = nullptr;
      this.hasHeavyRain = false;
      this.hasStorm = false;
      this.hasTropicalStorm = false;
      this.hasBlizzard = false;
      this.weatherStages.clear();
   }
}
} // namespace weather
} // namespace iso
} // namespace zombie
