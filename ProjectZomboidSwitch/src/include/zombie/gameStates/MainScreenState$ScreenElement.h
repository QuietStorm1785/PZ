#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Core.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/ui/TextManager.h"

namespace zombie {
namespace gameStates {


class MainScreenState {
public:
    float alpha = 0.0F;
    float alphaStep = 0.2F;
    bool jumpBack = true;
    float sx = 0.0F;
    float sy = 0.0F;
    float targetAlpha = 0.0F;
    Texture tex;
    int TicksTillTargetAlpha = 0;
    float x = 0.0F;
    int xCount = 1;
    float xVel = 0.0F;
    float xVelO = 0.0F;
    float y = 0.0F;
    float yVel = 0.0F;
    float yVelO = 0.0F;

   public MainScreenState$ScreenElement(Texture var1, int var2, int var3, float var4, float var5, int var6) {
      this.x = this.sx = var2;
      this.y = this.sy = var3 - var1.getHeight() * MainScreenState.totalScale;
      this.xVel = var4;
      this.yVel = var5;
      this.tex = var1;
      this.xCount = var6;
   }

    void render() {
    int var1 = (int)this.x;
    int var2 = (int)this.y;

      for (int var3 = 0; var3 < this.xCount; var3++) {
         MainScreenState.DrawTexture(
            this.tex, var1, var2, (int)(this.tex.getWidth() * MainScreenState.totalScale), (int)(this.tex.getHeight() * MainScreenState.totalScale), this.alpha
         );
         var1 = (int)(var1 + this.tex.getWidth() * MainScreenState.totalScale);
      }

      TextManager.instance
         .DrawStringRight(
            Core.getInstance().getOffscreenWidth(0) - 5,
            Core.getInstance().getOffscreenHeight(0) - 15,
            "Version: " + MainScreenState.Version,
            1.0,
            1.0,
            1.0,
            1.0
         );
   }

    void setY(float var1) {
      this.y = this.sy = var1 - this.tex.getHeight() * MainScreenState.totalScale;
   }

    void update() {
      this.x = this.x + this.xVel * MainScreenState.totalScale;
      this.y = this.y + this.yVel * MainScreenState.totalScale;
      this.TicksTillTargetAlpha--;
      if (this.TicksTillTargetAlpha <= 0) {
         this.targetAlpha = 1.0F;
      }

      if (this.jumpBack && this.sx - this.x > this.tex.getWidth() * MainScreenState.totalScale) {
         this.x = this.x + this.tex.getWidth() * MainScreenState.totalScale;
      }

      if (this.alpha < this.targetAlpha) {
         this.alpha = this.alpha + this.alphaStep;
         if (this.alpha > this.targetAlpha) {
            this.alpha = this.targetAlpha;
         }
      } else if (this.alpha > this.targetAlpha) {
         this.alpha = this.alpha - this.alphaStep;
         if (this.alpha < this.targetAlpha) {
            this.alpha = this.targetAlpha;
         }
      }
   }
}
} // namespace gameStates
} // namespace zombie
