#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/core/textures/Texture.h"

namespace zombie {
namespace iso {
namespace weather {
namespace fx {


class SnowParticle : public WeatherParticle {
public:
    double angleRadians = 0.0;
    float lastAngle = -1.0F;
    float lastIntensity = -1.0F;
    float angleOffset = 0.0F;
    float alphaMod = 0.0F;
    float incarnateAlpha = 1.0F;
    float life = 0.0F;
    float fadeTime = 80.0F;
    float tmpAngle = 0.0F;

    public SnowParticle(Texture var1) {
      super(var1);
      this.recalcSizeOnZoom = true;
      this.zoomMultiW = 1.0F;
      this.zoomMultiH = 1.0F;
   }

    void setLife() {
      this.life = this.fadeTime + Rand.Next(60, 500);
   }

    void update(float var1) {
      if (this.lastAngle != IsoWeatherFX.instance.windAngle || this.lastIntensity != IsoWeatherFX.instance.windPrecipIntensity.value()) {
         this.tmpAngle = IsoWeatherFX.instance.windAngle + (this.angleOffset - this.angleOffset * 0.5F * IsoWeatherFX.instance.windPrecipIntensity.value());
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

      if (this.life >= this.fadeTime) {
         this.position.x = this.position.x + this.velocity.x * IsoWeatherFX.instance.windSpeed * var1;
         this.position.y = this.position.y + this.velocity.y * IsoWeatherFX.instance.windSpeed * var1;
      } else {
         this.incarnateAlpha = this.life / this.fadeTime;
      }

      this.life--;
      if (this.life < 0.0F) {
         this.setLife();
         this.incarnateAlpha = 0.0F;
         this.position.set(Rand.Next(0, this.parent.getWidth()), Rand.Next(0, this.parent.getHeight()));
      }

      if (this.incarnateAlpha < 1.0F) {
         this.incarnateAlpha += 0.05F;
         if (this.incarnateAlpha > 1.0F) {
            this.incarnateAlpha = 1.0F;
         }
      }

      super.update(var1);
      this.updateZoomSize();
      this.alphaMod = 1.0F - 0.2F * IsoWeatherFX.instance.windIntensity.value();
      this.renderAlpha = this.alpha * this.alphaMod * this.alphaFadeMod.value() * IsoWeatherFX.instance.indoorsAlphaMod.value() * this.incarnateAlpha;
      this.renderAlpha *= 0.7F;
   }

    void render(float var1, float var2) {
      super.render(var1, var2);
   }
}
} // namespace fx
} // namespace weather
} // namespace iso
} // namespace zombie
