package zombie.ui;

import zombie.core.PerformanceSettings;
import zombie.iso.IsoCamera;

class UIManager$FadeInfo {
   public int playerIndex;
   public boolean bFadeBeforeUI = false;
   public float FadeAlpha = 0.0F;
   public int FadeTime = 2;
   public int FadeTimeMax = 2;
   public boolean FadingOut = false;

   public UIManager$FadeInfo(int var1) {
      this.playerIndex = var1;
   }

   public boolean isFadeBeforeUI() {
      return this.bFadeBeforeUI;
   }

   public void setFadeBeforeUI(boolean var1) {
      this.bFadeBeforeUI = var1;
   }

   public float getFadeAlpha() {
      return this.FadeAlpha;
   }

   public void setFadeAlpha(float var1) {
      this.FadeAlpha = var1;
   }

   public int getFadeTime() {
      return this.FadeTime;
   }

   public void setFadeTime(int var1) {
      this.FadeTime = var1;
   }

   public int getFadeTimeMax() {
      return this.FadeTimeMax;
   }

   public void setFadeTimeMax(int var1) {
      this.FadeTimeMax = var1;
   }

   public boolean isFadingOut() {
      return this.FadingOut;
   }

   public void setFadingOut(boolean var1) {
      this.FadingOut = var1;
   }

   public void FadeIn(int var1) {
      this.setFadeTimeMax((int)(var1 * 30 * (PerformanceSettings.getLockFPS() / 30.0F)));
      this.setFadeTime(this.getFadeTimeMax());
      this.setFadingOut(false);
   }

   public void FadeOut(int var1) {
      this.setFadeTimeMax((int)(var1 * 30 * (PerformanceSettings.getLockFPS() / 30.0F)));
      this.setFadeTime(this.getFadeTimeMax());
      this.setFadingOut(true);
   }

   public void update() {
      this.setFadeTime(this.getFadeTime() - 1);
   }

   public void render() {
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
