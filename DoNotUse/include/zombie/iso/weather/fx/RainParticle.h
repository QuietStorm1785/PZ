#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/iso/weather/fx/RainParticle/RenderPoints.h"

namespace zombie {
namespace iso {
namespace weather {
namespace fx {


class RainParticle : public WeatherParticle {
public:
    double angleRadians = 0.0;
    float lastAngle = -1.0F;
    float lastIntensity = -1.0F;
    float angleOffset = 0.0F;
    float alphaMod = 0.0F;
    float incarnateAlpha = 1.0F;
    float life = 0.0F;
    RenderPoints rp;
    bool angleUpdate = false;
    float tmpAngle = 0.0F;

    public RainParticle(Texture var1, int var2) {
      super(var1);
      if (var2 > 6) {
         this.bounds.setSize(Rand.Next(1, 2), var2);
      } else {
         this.bounds.setSize(1, var2);
      }

      this.oWidth = this.bounds.getWidth();
      this.oHeight = this.bounds.getHeight();
      this.recalcSizeOnZoom = true;
      this.zoomMultiW = 0.0F;
      this.zoomMultiH = 2.0F;
      this.setLife();
      this.rp = std::make_shared<RenderPoints>(this);
      this.rp.setDimensions(this.oWidth, this.oHeight);
   }

    void setLife() {
      this.life = Rand.Next(20, 60);
   }

    void update(float var1) {
      this.angleUpdate = false;
      if (this.updateZoomSize()) {
         this.rp.setDimensions(this.oWidth, this.oHeight);
         this.angleUpdate = true;
      }

      if (this.angleUpdate || this.lastAngle != IsoWeatherFX.instance.windAngle || this.lastIntensity != IsoWeatherFX.instance.windPrecipIntensity.value()) {
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
         this.lastIntensity = IsoWeatherFX.instance.windPrecipIntensity.value();
         this.angleUpdate = true;
      }

      this.position.x = this.position.x + this.velocity.x * (1.0F + IsoWeatherFX.instance.windSpeed * 0.1F) * var1;
      this.position.y = this.position.y + this.velocity.y * (1.0F + IsoWeatherFX.instance.windSpeed * 0.1F) * var1;
      this.life--;
      if (this.life < 0.0F) {
         this.setLife();
         this.incarnateAlpha = 0.0F;
         this.position.set(Rand.Next(0, this.parent.getWidth()), Rand.Next(0, this.parent.getHeight()));
      }

      if (this.incarnateAlpha < 1.0F) {
         this.incarnateAlpha += 0.035F;
         if (this.incarnateAlpha > 1.0F) {
            this.incarnateAlpha = 1.0F;
         }
      }

      super.update(var1, false);
      this.bounds.setLocation((int)this.position.x, (int)this.position.y);
      if (this.angleUpdate) {
         this.tmpAngle += 90.0F;
         if (this.tmpAngle > 360.0F) {
            this.tmpAngle -= 360.0F;
         }

         if (this.tmpAngle < 0.0F) {
            this.tmpAngle += 360.0F;
         }

         this.angleRadians = Math.toRadians(this.tmpAngle);
         this.rp.rotate(this.angleRadians);
      }

      this.alphaMod = 1.0F - 0.2F * IsoWeatherFX.instance.windIntensity.value();
      this.renderAlpha = this.alpha * this.alphaMod * this.alphaFadeMod.value() * IsoWeatherFX.instance.indoorsAlphaMod.value() * this.incarnateAlpha;
      this.renderAlpha *= 0.55F;
      if (IsoWeatherFX.instance.playerIndoors) {
         this.renderAlpha *= 0.5F;
      }
   }

    void render(float var1, float var2) {
    double var3 = var1 + this.bounds.getX();
    double var5 = var2 + this.bounds.getY();
      SpriteRenderer.instance
         .render(
            this.texture,
            var3 + this.rp.getX(0),
            var5 + this.rp.getY(0),
            var3 + this.rp.getX(1),
            var5 + this.rp.getY(1),
            var3 + this.rp.getX(2),
            var5 + this.rp.getY(2),
            var3 + this.rp.getX(3),
            var5 + this.rp.getY(3),
            this.color.r,
            this.color.g,
            this.color.b,
            this.renderAlpha,
            nullptr
         );
   }
}
} // namespace fx
} // namespace weather
} // namespace iso
} // namespace zombie
