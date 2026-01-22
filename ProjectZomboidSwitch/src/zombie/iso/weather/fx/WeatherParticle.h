#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/util/Rectangle.h"
#include "zombie/core/Color.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/Vector2.h"

namespace zombie {
namespace iso {
namespace weather {
namespace fx {


class WeatherParticle {
public:
    ParticleRectangle parent;
    Rectangle bounds;
    Texture texture;
    Color color = Color.white;
    Vector2 position = std::make_shared<Vector2>(0.0F, 0.0F);
    Vector2 velocity = std::make_shared<Vector2>(0.0F, 0.0F);
    float alpha = 1.0F;
    float speed = 0.0F;
    SteppedUpdateFloat alphaFadeMod = std::make_shared<SteppedUpdateFloat>(0.0F, 0.1F, 0.0F, 1.0F);
    float renderAlpha = 0.0F;
    float oWidth;
    float oHeight;
    float zoomMultiW = 0.0F;
    float zoomMultiH = 0.0F;
    bool recalcSizeOnZoom = false;
    float lastZoomMod = -1.0F;

    public WeatherParticle(Texture var1) {
      this.texture = var1;
      this.bounds = std::make_shared<Rectangle>(0, 0, var1.getWidth(), var1.getHeight());
      this.oWidth = this.bounds.getWidth();
      this.oHeight = this.bounds.getHeight();
   }

    public WeatherParticle(Texture var1, int var2, int var3) {
      this.texture = var1;
      this.bounds = std::make_shared<Rectangle>(0, 0, var2, var3);
      this.oWidth = this.bounds.getWidth();
      this.oHeight = this.bounds.getHeight();
   }

    void setParent(ParticleRectangle var1) {
      this.parent = var1;
   }

    void update(float var1) {
      this.update(var1, true);
   }

    void update(float var1, bool var2) {
      this.alphaFadeMod.update(var1);
      if (this.position.x > this.parent.getWidth()) {
         this.position.x = this.position.x - (int)(this.position.x / this.parent.getWidth()) * this.parent.getWidth();
      } else if (this.position.x < 0.0F) {
         this.position.x = this.position.x - (int)((this.position.x - this.parent.getWidth()) / this.parent.getWidth()) * this.parent.getWidth();
      }

      if (this.position.y > this.parent.getHeight()) {
         this.position.y = this.position.y - (int)(this.position.y / this.parent.getHeight()) * this.parent.getHeight();
      } else if (this.position.y < 0.0F) {
         this.position.y = this.position.y - (int)((this.position.y - this.parent.getHeight()) / this.parent.getHeight()) * this.parent.getHeight();
      }

      if (var2) {
         this.bounds.setLocation((int)this.position.x - this.bounds.getWidth() / 2, (int)this.position.y - this.bounds.getHeight() / 2);
      }
   }

    bool updateZoomSize() {
      if (this.recalcSizeOnZoom && this.lastZoomMod != IsoWeatherFX.ZoomMod) {
         this.lastZoomMod = IsoWeatherFX.ZoomMod;
         this.oWidth = this.bounds.getWidth();
         this.oHeight = this.bounds.getHeight();
         if (this.lastZoomMod > 0.0F) {
            this.oWidth = this.oWidth * (1.0F + IsoWeatherFX.ZoomMod * this.zoomMultiW);
            this.oHeight = this.oHeight * (1.0F + IsoWeatherFX.ZoomMod * this.zoomMultiH);
         }

    return true;
      } else {
    return false;
      }
   }

    bool isOnScreen(float var1, float var2) {
    int var3 = IsoCamera.frameState.OffscreenWidth;
    int var4 = IsoCamera.frameState.OffscreenHeight;
    float var5 = var1 + this.bounds.getX();
    float var6 = var2 + this.bounds.getY();
    float var7 = var5 + this.oWidth;
    float var8 = var6 + this.oHeight;
      return var5 >= var3 || var7 <= 0.0F ? false : !(var6 >= var4) && !(var8 <= 0.0F);
   }

    void render(float var1, float var2) {
      SpriteRenderer.instance
         .render(
            this.texture,
            var1 + this.bounds.getX(),
            var2 + this.bounds.getY(),
            this.oWidth,
            this.oHeight,
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
