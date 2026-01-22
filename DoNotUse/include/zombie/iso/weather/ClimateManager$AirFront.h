#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace weather {


class ClimateManager {
public:
    float days = 0.0F;
    float maxNoise = 0.0F;
    float totalNoise = 0.0F;
    int type = 0;
    float strength = 0.0F;
    float tmpNoiseAbs = 0.0F;
   private float[] noiseCache = new float[2];
    float noiseCacheValue = 0.0F;
    float frontWindAngleDegrees = 0.0F;

    float getDays() {
      return this.days;
   }

    float getMaxNoise() {
      return this.maxNoise;
   }

    float getTotalNoise() {
      return this.totalNoise;
   }

    int getType() {
      return this.type;
   }

    float getStrength() {
      return this.strength;
   }

    float getAngleDegrees() {
      return this.frontWindAngleDegrees;
   }

   public ClimateManager$AirFront() {
      this.reset();
   }

    void setFrontType(int var1) {
      this.reset();
      this.type = var1;
   }

    void setFrontWind(float var1) {
      this.frontWindAngleDegrees = var1;
   }

    void setStrength(float var1) {
      this.strength = var1;
   }

    void reset() {
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

    void save(DataOutputStream var1) {
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

    void load(DataInputStream var1) {
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

    void addDaySample(float var1) {
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

    void copyFrom(ClimateManager$AirFront var1) {
      this.days = var1.days;
      this.maxNoise = var1.maxNoise;
      this.totalNoise = var1.totalNoise;
      this.type = var1.type;
      this.strength = var1.strength;
      this.frontWindAngleDegrees = var1.frontWindAngleDegrees;
   }
}
} // namespace weather
} // namespace iso
} // namespace zombie
