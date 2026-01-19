package zombie.iso;

import zombie.iso.ParticlesFire.ZoneType;

public class ParticlesFire$Zone {
   ZoneType type;
   int intensity;
   int currentParticles;
   float x0;
   float y0;
   float x1;
   float y1;
   float r;
   float fireIntensity;
   float smokeIntensity;
   float sparksIntensity;
   float vortices;
   float vorticeSpeed;
   float area;
   float temperature;
   float centerX;
   float centerY;
   float centerRp2;
   float currentVorticesCount;

   ParticlesFire$Zone(ParticlesFire var1, int var2, float var3, float var4, float var5) {
      this.this$0 = var1;
      this.type = ZoneType.Circle;
      this.intensity = var2;
      this.currentParticles = 0;
      this.x0 = var3;
      this.y0 = var4;
      this.r = var5;
      this.area = (float)(Math.PI * var5 * var5);
      this.vortices = this.intensity * 0.3F;
      this.vorticeSpeed = 0.5F;
      this.temperature = 2000.0F;
      this.centerX = var3;
      this.centerY = var4;
      this.centerRp2 = var5 * var5;
   }

   ParticlesFire$Zone(ParticlesFire var1, int var2, float var3, float var4, float var5, float var6) {
      this.this$0 = var1;
      this.type = ZoneType.Rectangle;
      this.intensity = var2;
      this.currentParticles = 0;
      if (var3 < var5) {
         this.x0 = var3;
         this.x1 = var5;
      } else {
         this.x1 = var3;
         this.x0 = var5;
      }

      if (var4 < var6) {
         this.y0 = var4;
         this.y1 = var6;
      } else {
         this.y1 = var4;
         this.y0 = var6;
      }

      this.area = (this.x1 - this.x0) * (this.y1 - this.y0);
      this.vortices = this.intensity * 0.3F;
      this.vorticeSpeed = 0.5F;
      this.temperature = 2000.0F;
      this.centerX = (this.x0 + this.x1) * 0.5F;
      this.centerY = (this.y0 + this.y1) * 0.5F;
      this.centerRp2 = (this.x1 - this.x0) * (this.x1 - this.x0);
   }

   ParticlesFire$Zone(ParticlesFire var1, int var2, float var3, float var4, float var5, float var6, float var7) {
      this.this$0 = var1;
      this.type = ZoneType.Line;
      this.intensity = var2;
      this.currentParticles = 0;
      if (var3 < var5) {
         this.x0 = var3;
         this.x1 = var5;
         this.y0 = var4;
         this.y1 = var6;
      } else {
         this.x1 = var3;
         this.x0 = var5;
         this.y1 = var4;
         this.y0 = var6;
      }

      this.r = var7;
      this.area = (float)(this.r * Math.sqrt(Math.pow(var3 - var5, 2.0) + Math.pow(var4 - var6, 2.0)));
      this.vortices = this.intensity * 0.3F;
      this.vorticeSpeed = 0.5F;
      this.temperature = 2000.0F;
      this.centerX = (this.x0 + this.x1) * 0.5F;
      this.centerY = (this.y0 + this.y1) * 0.5F;
      this.centerRp2 = (this.x1 - this.x0 + var7) * (this.x1 - this.x0 + var7) * 100.0F;
   }
}
