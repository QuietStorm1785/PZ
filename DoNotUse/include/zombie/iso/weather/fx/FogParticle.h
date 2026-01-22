#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/Texture.h"

namespace zombie {
namespace iso {
namespace weather {
namespace fx {


class FogParticle : public WeatherParticle {
public:
    double angleRadians = 0.0;
    float lastAngle = -1.0F;
    float lastIntensity = -1.0F;
    float angleOffset = 0.0F;
    float alphaMod = 0.0F;
    float tmpAngle = 0.0F;

    public FogParticle(Texture var1, int var2, int var3) {
      super(var1, var2, var3);
   }

    void update(float var1) {
      if (this.lastAngle != IsoWeatherFX.instance.windAngle || this.lastIntensity != IsoWeatherFX.instance.windIntensity.value()) {
         this.tmpAngle = IsoWeatherFX.instance.windAngle + (this.angleOffset - this.angleOffset * 1.0F * IsoWeatherFX.instance.windIntensity.value());
         if (this.tmpAngle > 360.0F) {
            this.tmpAngle -= 360.0F;
         }

         if (this.tmpAngle < 0.0F) {
            this.tmpAngle += 360.0F;
         }

         this.angleRadians = Math.toRadians(this.tmpAngle);
         this.velocity.set((float)Math.cos(this.angleRadians) * this.speed, (float)Math.sin(this.angleRadians) * this.speed);
         this.lastAngle = IsoWeatherFX.instance.windAngle;
      }

      this.position.x = this.position.x + this.velocity.x * IsoWeatherFX.instance.windSpeedFog * var1;
      this.position.y = this.position.y + this.velocity.y * IsoWeatherFX.instance.windSpeedFog * var1;
      super.update(var1);
      this.alphaMod = IsoWeatherFX.instance.fogIntensity.value();
      this.renderAlpha = this.alpha * this.alphaMod * this.alphaFadeMod.value() * IsoWeatherFX.instance.indoorsAlphaMod.value();
   }
}
} // namespace fx
} // namespace weather
} // namespace iso
} // namespace zombie
