#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {
namespace weather {

class ClimateForecaster {
public:
    float dayMin;
    float dayMax;
    float dayMean;
    int dayMeanTicks;
    float nightMin;
    float nightMax;
    float nightMean;
    int nightMeanTicks;
    float totalMin;
    float totalMax;
    float totalMean;
    int totalMeanTicks;

   public ClimateForecaster$ForecastValue() {
      this.reset();
   }

    float getDayMin() {
      return this.dayMin;
   }

    float getDayMax() {
      return this.dayMax;
   }

    float getDayMean() {
      return this.dayMean;
   }

    float getNightMin() {
      return this.nightMin;
   }

    float getNightMax() {
      return this.nightMax;
   }

    float getNightMean() {
      return this.nightMean;
   }

    float getTotalMin() {
      return this.totalMin;
   }

    float getTotalMax() {
      return this.totalMax;
   }

    float getTotalMean() {
      return this.totalMean;
   }

    void add(float var1, bool var2) {
      if (var2) {
         if (var1 < this.dayMin) {
            this.dayMin = var1;
         }

         if (var1 > this.dayMax) {
            this.dayMax = var1;
         }

         this.dayMean += var1;
         this.dayMeanTicks++;
      } else {
         if (var1 < this.nightMin) {
            this.nightMin = var1;
         }

         if (var1 > this.nightMax) {
            this.nightMax = var1;
         }

         this.nightMean += var1;
         this.nightMeanTicks++;
      }

      if (var1 < this.totalMin) {
         this.totalMin = var1;
      }

      if (var1 > this.totalMax) {
         this.totalMax = var1;
      }

      this.totalMean += var1;
      this.totalMeanTicks++;
   }

    void calculate() {
      if (this.totalMeanTicks <= 0) {
         this.totalMean = 0.0F;
      } else {
         this.totalMean = this.totalMean / this.totalMeanTicks;
      }

      if (this.dayMeanTicks <= 0) {
         this.dayMin = this.totalMin;
         this.dayMax = this.totalMax;
         this.dayMean = this.totalMean;
      } else {
         this.dayMean = this.dayMean / this.dayMeanTicks;
      }

      if (this.nightMeanTicks <= 0) {
         this.nightMin = this.totalMin;
         this.nightMax = this.totalMax;
         this.nightMean = this.totalMean;
      } else {
         this.nightMean = this.nightMean / this.nightMeanTicks;
      }
   }

    void reset() {
      this.dayMin = 10000.0F;
      this.dayMax = -10000.0F;
      this.dayMean = 0.0F;
      this.dayMeanTicks = 0;
      this.nightMin = 10000.0F;
      this.nightMax = -10000.0F;
      this.nightMean = 0.0F;
      this.nightMeanTicks = 0;
      this.totalMin = 10000.0F;
      this.totalMax = -10000.0F;
      this.totalMean = 0.0F;
      this.totalMeanTicks = 0;
   }
}
} // namespace weather
} // namespace iso
} // namespace zombie
