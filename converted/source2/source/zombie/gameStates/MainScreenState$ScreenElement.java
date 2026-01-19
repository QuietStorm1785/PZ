package zombie.gameStates;

import zombie.core.Core;
import zombie.core.textures.Texture;
import zombie.ui.TextManager;

public class MainScreenState$ScreenElement {
   public float alpha = 0.0F;
   public float alphaStep = 0.2F;
   public boolean jumpBack = true;
   public float sx = 0.0F;
   public float sy = 0.0F;
   public float targetAlpha = 0.0F;
   public Texture tex;
   public int TicksTillTargetAlpha = 0;
   public float x = 0.0F;
   public int xCount = 1;
   public float xVel = 0.0F;
   public float xVelO = 0.0F;
   public float y = 0.0F;
   public float yVel = 0.0F;
   public float yVelO = 0.0F;

   public MainScreenState$ScreenElement(Texture var1, int var2, int var3, float var4, float var5, int var6) {
      this.x = this.sx = var2;
      this.y = this.sy = var3 - var1.getHeight() * MainScreenState.totalScale;
      this.xVel = var4;
      this.yVel = var5;
      this.tex = var1;
      this.xCount = var6;
   }

   public void render() {
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

   public void setY(float var1) {
      this.y = this.sy = var1 - this.tex.getHeight() * MainScreenState.totalScale;
   }

   public void update() {
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
