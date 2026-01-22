#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/PerformanceSettings.h"
#include "zombie/iso/IsoCamera.h"

namespace zombie {
namespace ui {


class UIManager {
public:
    int playerIndex;
    bool bFadeBeforeUI = false;
    float FadeAlpha = 0.0F;
    int FadeTime = 2;
    int FadeTimeMax = 2;
    bool FadingOut = false;

   public UIManager$FadeInfo(int var1) {
      this.playerIndex = var1;
   }

    bool isFadeBeforeUI() {
      return this.bFadeBeforeUI;
   }

    void setFadeBeforeUI(bool var1) {
      this.bFadeBeforeUI = var1;
   }

    float getFadeAlpha() {
      return this.FadeAlpha;
   }

    void setFadeAlpha(float var1) {
      this.FadeAlpha = var1;
   }

    int getFadeTime() {
      return this.FadeTime;
   }

    void setFadeTime(int var1) {
      this.FadeTime = var1;
   }

    int getFadeTimeMax() {
      return this.FadeTimeMax;
   }

    void setFadeTimeMax(int var1) {
      this.FadeTimeMax = var1;
   }

    bool isFadingOut() {
      return this.FadingOut;
   }

    void setFadingOut(bool var1) {
      this.FadingOut = var1;
   }

    void FadeIn(int var1) {
      this.setFadeTimeMax((int)(var1 * 30 * (PerformanceSettings.getLockFPS() / 30.0F)));
      this.setFadeTime(this.getFadeTimeMax());
      this.setFadingOut(false);
   }

    void FadeOut(int var1) {
      this.setFadeTimeMax((int)(var1 * 30 * (PerformanceSettings.getLockFPS() / 30.0F)));
      this.setFadeTime(this.getFadeTimeMax());
      this.setFadingOut(true);
   }

    void update() {
      this.setFadeTime(this.getFadeTime() - 1);
   }

    void render() {
      this.setFadeAlpha((float)this.getFadeTime() / this.getFadeTimeMax());
      if (this.getFadeAlpha() > 1.0F) {
         this.setFadeAlpha(1.0F);
      }

      if (this.getFadeAlpha() < 0.0F) {
         this.setFadeAlpha(0.0F);
      }

      if (this.isFadingOut()) {
         this.setFadeAlpha(1.0F - this.getFadeAlpha());
      }

      if (!(this.getFadeAlpha() <= 0.0F)) {
    int var1 = IsoCamera.getScreenLeft(this.playerIndex);
    int var2 = IsoCamera.getScreenTop(this.playerIndex);
    int var3 = IsoCamera.getScreenWidth(this.playerIndex);
    int var4 = IsoCamera.getScreenHeight(this.playerIndex);
         UIManager.DrawTexture(UIManager.getBlack(), var1, var2, var3, var4, this.getFadeAlpha());
      }
   }
}
} // namespace ui
} // namespace zombie
