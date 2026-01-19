package zombie.iso.weather;

public class ClimateForecaster$ForecastValue {
   private float dayMin;
   private float dayMax;
   private float dayMean;
   private int dayMeanTicks;
   private float nightMin;
   private float nightMax;
   private float nightMean;
   private int nightMeanTicks;
   private float totalMin;
   private float totalMax;
   private float totalMean;
   private int totalMeanTicks;

   public ClimateForecaster$ForecastValue() {
      this.reset();
   }

   public float getDayMin() {
      return this.dayMin;
   }

   public float getDayMax() {
      return this.dayMax;
   }

   public float getDayMean() {
      return this.dayMean;
   }

   public float getNightMin() {
      return this.nightMin;
   }

   public float getNightMax() {
      return this.nightMax;
   }

   public float getNightMean() {
      return this.nightMean;
   }

   public float getTotalMin() {
      return this.totalMin;
   }

   public float getTotalMax() {
      return this.totalMax;
   }

   public float getTotalMean() {
      return this.totalMean;
   }

   protected void add(float var1, boolean var2) {
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

   protected void calculate() {
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

   protected void reset() {
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
