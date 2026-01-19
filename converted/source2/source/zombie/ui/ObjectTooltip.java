package zombie.ui;

import java.util.Stack;
import zombie.characters.IsoGameCharacter;
import zombie.core.Core;
import zombie.core.textures.Texture;
import zombie.inventory.InventoryItem;
import zombie.iso.IsoObject;
import zombie.ui.ObjectTooltip.Layout;

public final class ObjectTooltip extends UIElement {
   public static float alphaStep = 0.1F;
   public boolean bIsItem = false;
   public InventoryItem Item = null;
   public IsoObject Object;
   float alpha = 0.0F;
   int showDelay = 0;
   float targetAlpha = 0.0F;
   Texture texture;
   public int padRight = 5;
   public int padBottom = 5;
   private IsoGameCharacter character;
   private boolean measureOnly;
   private float weightOfStack = 0.0F;
   private static int lineSpacing = 14;
   private static String fontSize = "Small";
   private static UIFont font = UIFont.Small;
   private static Stack<Layout> freeLayouts = new Stack<>();

   public ObjectTooltip() {
      this.texture = Texture.getSharedTexture("black");
      this.width = 130.0F;
      this.height = 130.0F;
      this.defaultDraw = false;
      lineSpacing = TextManager.instance.getFontFromEnum(font).getLineHeight();
      checkFont();
   }

   public static void checkFont() {
      if (!fontSize.equals(Core.getInstance().getOptionTooltipFont())) {
         fontSize = Core.getInstance().getOptionTooltipFont();
         if ("Large".equals(fontSize)) {
            font = UIFont.Large;
         } else if ("Medium".equals(fontSize)) {
            font = UIFont.Medium;
         } else {
            font = UIFont.Small;
         }

         lineSpacing = TextManager.instance.getFontFromEnum(font).getLineHeight();
      }
   }

   public UIFont getFont() {
      return font;
   }

   public int getLineSpacing() {
      return lineSpacing;
   }

   public void DrawText(UIFont var1, String var2, double var3, double var5, double var7, double var9, double var11, double var13) {
      if (!this.measureOnly) {
         super.DrawText(var1, var2, var3, var5, var7, var9, var11, var13);
      }
   }

   public void DrawTextCentre(UIFont var1, String var2, double var3, double var5, double var7, double var9, double var11, double var13) {
      if (!this.measureOnly) {
         super.DrawTextCentre(var1, var2, var3, var5, var7, var9, var11, var13);
      }
   }

   public void DrawTextRight(UIFont var1, String var2, double var3, double var5, double var7, double var9, double var11, double var13) {
      if (!this.measureOnly) {
         super.DrawTextRight(var1, var2, var3, var5, var7, var9, var11, var13);
      }
   }

   public void DrawValueRight(int var1, int var2, int var3, boolean var4) {
      Integer var5 = var1;
      String var6 = var5.toString();
      float var7 = 0.3F;
      float var8 = 1.0F;
      float var9 = 0.2F;
      float var10 = 1.0F;
      if (var1 > 0) {
         var6 = "+" + var6;
      }

      if (var1 < 0 && var4 || var1 > 0 && !var4) {
         var7 = 0.8F;
         var8 = 0.3F;
         var9 = 0.2F;
      }

      this.DrawTextRight(font, var6, var2, var3, var7, var8, var9, var10);
   }

   public void DrawValueRightNoPlus(int var1, int var2, int var3) {
      Integer var4 = var1;
      String var5 = var4.toString();
      float var6 = 1.0F;
      float var7 = 1.0F;
      float var8 = 1.0F;
      float var9 = 1.0F;
      this.DrawTextRight(font, var5, var2, var3, var6, var7, var8, var9);
   }

   public void DrawValueRightNoPlus(float var1, int var2, int var3) {
      Float var4 = var1;
      var4 = (int)((var4.floatValue() + 0.01) * 10.0) / 10.0F;
      String var5 = var4.toString();
      float var6 = 1.0F;
      float var7 = 1.0F;
      float var8 = 1.0F;
      float var9 = 1.0F;
      this.DrawTextRight(font, var5, var2, var3, var6, var7, var8, var9);
   }

   public void DrawTextureScaled(Texture var1, double var2, double var4, double var6, double var8, double var10) {
      if (!this.measureOnly) {
         super.DrawTextureScaled(var1, var2, var4, var6, var8, var10);
      }
   }

   public void DrawTextureScaledAspect(Texture var1, double var2, double var4, double var6, double var8, double var10, double var12, double var14, double var16) {
      if (!this.measureOnly) {
         super.DrawTextureScaledAspect(var1, var2, var4, var6, var8, var10, var12, var14, var16);
      }
   }

   public void DrawProgressBar(int var1, int var2, int var3, int var4, float var5, double var6, double var8, double var10, double var12) {
      if (!this.measureOnly) {
         if (var5 < 0.0F) {
            var5 = 0.0F;
         }

         if (var5 > 1.0F) {
            var5 = 1.0F;
         }

         int var14 = (int)Math.floor(var3 * var5);
         if (var5 > 0.0F && var14 == 0) {
            var14 = 1;
         }

         this.DrawTextureScaledColor(null, (double)var1, (double)var2, (double)var14, 3.0, var6, var8, var10, var12);
         this.DrawTextureScaledColor(null, (double)var1 + var14, (double)var2, (double)var3 - var14, 3.0, 0.25, 0.25, 0.25, 1.0);
      }
   }

   public Boolean onMouseMove(double var1, double var3) {
      this.setX(this.getX() + var1);
      this.setY(this.getY() + var3);
      return Boolean.FALSE;
   }

   public void onMouseMoveOutside(double var1, double var3) {
      this.setX(this.getX() + var1);
      this.setY(this.getY() + var3);
   }

   public void render() {
      if (this.isVisible()) {
         if (!(this.alpha <= 0.0F)) {
            if (!this.bIsItem && this.Object != null && this.Object.haveSpecialTooltip()) {
               this.Object.DoSpecialTooltip(this, this.Object.square);
            }

            super.render();
         }
      }
   }

   public void show(IsoObject var1, double var2, double var4) {
      this.bIsItem = false;
      this.Object = var1;
      this.setX(var2);
      this.setY(var4);
      this.targetAlpha = 0.5F;
      this.showDelay = 15;
      this.alpha = 0.0F;
   }

   public void hide() {
      this.Object = null;
      this.showDelay = 0;
      this.setVisible(false);
   }

   public void update() {
      if (!(this.alpha <= 0.0F) || this.targetAlpha != 0.0F) {
         if (this.showDelay > 0) {
            if (--this.showDelay == 0) {
               this.setVisible(true);
            }
         } else {
            if (this.alpha < this.targetAlpha) {
               this.alpha = this.alpha + alphaStep;
               if (this.alpha > 0.5F) {
                  this.alpha = 0.5F;
               }
            } else if (this.alpha > this.targetAlpha) {
               this.alpha = this.alpha - alphaStep;
               if (this.alpha < this.targetAlpha) {
                  this.alpha = this.targetAlpha;
               }
            }
         }
      }
   }

   void show(InventoryItem var1, int var2, int var3) {
      this.Object = null;
      this.Item = var1;
      this.bIsItem = true;
      this.setX(this.getX());
      this.setY(this.getY());
      this.targetAlpha = 0.5F;
      this.showDelay = 15;
      this.alpha = 0.0F;
      this.setVisible(true);
   }

   public void adjustWidth(int var1, String var2) {
      int var3 = TextManager.instance.MeasureStringX(font, var2);
      if (var1 + var3 + this.padRight > this.width) {
         this.setWidth(var1 + var3 + this.padRight);
      }
   }

   public Layout beginLayout() {
      Layout var1 = null;
      if (freeLayouts.isEmpty()) {
         var1 = new Layout();
      } else {
         var1 = freeLayouts.pop();
      }

      return var1;
   }

   public void endLayout(Layout var1) {
      while (var1 != null) {
         Layout var2 = var1.next;
         var1.free();
         freeLayouts.push(var1);
         var1 = var2;
      }
   }

   public Texture getTexture() {
      return this.texture;
   }

   public void setCharacter(IsoGameCharacter var1) {
      this.character = var1;
   }

   public IsoGameCharacter getCharacter() {
      return this.character;
   }

   public void setMeasureOnly(boolean var1) {
      this.measureOnly = var1;
   }

   public boolean isMeasureOnly() {
      return this.measureOnly;
   }

   public float getWeightOfStack() {
      return this.weightOfStack;
   }

   public void setWeightOfStack(float var1) {
      this.weightOfStack = var1;
   }
}
