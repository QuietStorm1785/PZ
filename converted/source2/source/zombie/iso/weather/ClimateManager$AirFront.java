package zombie.iso.weather;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

public class ClimateManager$AirFront {
   private float days = 0.0F;
   private float maxNoise = 0.0F;
   private float totalNoise = 0.0F;
   private int type = 0;
   private float strength = 0.0F;
   private float tmpNoiseAbs = 0.0F;
   private float[] noiseCache = new float[2];
   private float noiseCacheValue = 0.0F;
   private float frontWindAngleDegrees = 0.0F;

   public float getDays() {
      return this.days;
   }

   public float getMaxNoise() {
      return this.maxNoise;
   }

   public float getTotalNoise() {
      return this.totalNoise;
   }

   public int getType() {
      return this.type;
   }

   public float getStrength() {
      return this.strength;
   }

   public float getAngleDegrees() {
      return this.frontWindAngleDegrees;
   }

   public ClimateManager$AirFront() {
      this.reset();
   }

   public void setFrontType(int var1) {
      this.reset();
      this.type = var1;
   }

   protected void setFrontWind(float var1) {
      this.frontWindAngleDegrees = var1;
   }

   public void setStrength(float var1) {
      this.strength = var1;
   }

   protected void reset() {
      this.days = 0.0F;
      this.maxNoise = 0.0F;
      this.totalNoise = 0.0F;
      this.type = 0;
      this.strength = 0.0F;
      this.frontWindAngleDegrees = 0.0F;

      for (int var1 = 0; var1 < this.noiseCache.length; var1++) {
         this.noiseCache[var1] = -1.0F;
      }
   }

   public void save(DataOutputStream var1) throws IOException {
      var1.writeFloat(this.days);
      var1.writeFloat(this.maxNoise);
      var1.writeFloat(this.totalNoise);
      var1.writeInt(this.type);
      var1.writeFloat(this.strength);
      var1.writeFloat(this.frontWindAngleDegrees);
      var1.writeInt(this.noiseCache.length);

      for (int var2 = 0; var2 < this.noiseCache.length; var2++) {
         var1.writeFloat(this.noiseCache[var2]);
      }
   }

   public void load(DataInputStream var1) throws IOException {
      this.days = var1.readFloat();
      this.maxNoise = var1.readFloat();
      this.totalNoise = var1.readFloat();
      this.type = var1.readInt();
      this.strength = var1.readFloat();
      this.frontWindAngleDegrees = var1.readFloat();
      int var2 = var1.readInt();
      int var3 = var2 > this.noiseCache.length ? var2 : this.noiseCache.length;

      for (int var4 = 0; var4 < var3; var4++) {
         if (var4 < var2) {
            float var5 = var1.readFloat();
            if (var4 < this.noiseCache.length) {
               this.noiseCache[var4] = var5;
            }
         } else if (var4 < this.noiseCache.length) {
            this.noiseCache[var4] = -1.0F;
         }
      }
   }

   public void addDaySample(float var1) {
      this.days++;
      if ((this.type != 1 || !(var1 <= 0.0F)) && (this.type != -1 || !(var1 >= 0.0F))) {
         this.tmpNoiseAbs = Math.abs(var1);
         if (this.tmpNoiseAbs > this.maxNoise) {
            this.maxNoise = this.tmpNoiseAbs;
         }

         this.totalNoise = this.totalNoise + this.tmpNoiseAbs;
         this.noiseCacheValue = 0.0F;

         for (int var2 = this.noiseCache.length - 1; var2 >= 0; var2--) {
            if (this.noiseCache[var2] > this.noiseCacheValue) {
               this.noiseCacheValue = this.noiseCache[var2];
            }

            if (var2 < this.noiseCache.length - 1) {
               this.noiseCache[var2 + 1] = this.noiseCache[var2];
            }
         }

         this.noiseCache[0] = this.tmpNoiseAbs;
         if (this.tmpNoiseAbs > this.noiseCacheValue) {
            this.noiseCacheValue = this.tmpNoiseAbs;
         }

         this.strength = this.noiseCacheValue * 0.75F + this.maxNoise * 0.25F;
      } else {
         this.strength = 0.0F;
      }
   }

   public void copyFrom(ClimateManager$AirFront var1) {
      this.days = var1.days;
      this.maxNoise = var1.maxNoise;
      this.totalNoise = var1.totalNoise;
      this.type = var1.type;
      this.strength = var1.strength;
      this.frontWindAngleDegrees = var1.frontWindAngleDegrees;
   }
}
