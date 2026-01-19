package zombie.ui;

import java.util.ArrayList;
import zombie.core.SpriteRenderer;
import zombie.core.fonts.AngelCodeFont;
import zombie.core.textures.Texture;
import zombie.input.JoypadManager;
import zombie.input.Mouse;
import zombie.ui.RadialMenu.Slice;
import zombie.util.StringUtils;

public final class RadialMenu extends UIElement {
   protected int outerRadius = 200;
   protected int innerRadius = 100;
   protected ArrayList<Slice> slices = new ArrayList<>();
   protected int highlight = -1;
   protected int joypad = -1;
   protected UITransition transition = new UITransition();
   protected UITransition select = new UITransition();
   protected UITransition deselect = new UITransition();
   protected int selectIndex = -1;
   protected int deselectIndex = -1;

   public RadialMenu(int var1, int var2, int var3, int var4) {
      this.setX(var1);
      this.setY(var2);
      this.setWidth(var4 * 2);
      this.setHeight(var4 * 2);
      this.innerRadius = var3;
      this.outerRadius = var4;
   }

   public void update() {
   }

   public void render() {
      if (this.isVisible()) {
         this.transition.setIgnoreUpdateTime(true);
         this.transition.setFadeIn(true);
         this.transition.update();
         if (!this.slices.isEmpty()) {
            float var1 = this.transition.fraction();
            float var2 = this.innerRadius * 0.85F + this.innerRadius * var1 * 0.15F;
            float var3 = this.outerRadius * 0.85F + this.outerRadius * var1 * 0.15F;

            for (int var4 = 0; var4 < 48; var4++) {
               float var5 = 7.5F;
               double var6 = Math.toRadians(var4 * var5);
               double var8 = Math.toRadians((var4 + 1) * var5);
               double var10 = this.x + this.width / 2.0F;
               double var12 = this.y + this.height / 2.0F;
               double var14 = this.x + this.width / 2.0F;
               double var16 = this.y + this.height / 2.0F;
               double var18 = this.x + this.width / 2.0F + var3 * (float)Math.cos(var6);
               double var20 = this.y + this.height / 2.0F + var3 * (float)Math.sin(var6);
               double var22 = this.x + this.width / 2.0F + var3 * (float)Math.cos(var8);
               double var24 = this.y + this.height / 2.0F + var3 * (float)Math.sin(var8);
               if (var4 == 47) {
                  var24 = var16;
               }

               float var26 = 0.1F;
               float var27 = 0.1F;
               float var28 = 0.1F;
               float var29 = 0.45F + 0.45F * var1;
               SpriteRenderer.instance
                  .renderPoly(
                     (float)var10, (float)var12, (float)var18, (float)var20, (float)var22, (float)var24, (float)var14, (float)var16, var26, var27, var28, var29
                  );
            }

            float var40 = 360.0F / Math.max(this.slices.size(), 2);
            float var41 = this.slices.size() == 1 ? 0.0F : 1.5F;
            int var42 = this.highlight;
            if (var42 == -1) {
               if (this.joypad != -1) {
                  var42 = this.getSliceIndexFromJoypad(this.joypad);
               } else {
                  var42 = this.getSliceIndexFromMouse(Mouse.getXA() - this.getAbsoluteX().intValue(), Mouse.getYA() - this.getAbsoluteY().intValue());
               }
            }

            Slice var7 = this.getSlice(var42);
            if (var7 != null && var7.isEmpty()) {
               var42 = -1;
            }

            if (var42 != this.selectIndex) {
               this.select.reset();
               this.select.setIgnoreUpdateTime(true);
               if (this.selectIndex != -1) {
                  this.deselectIndex = this.selectIndex;
                  this.deselect.reset();
                  this.deselect.setFadeIn(false);
                  this.deselect.init(66.666664F, true);
               }

               this.selectIndex = var42;
            }

            this.select.update();
            this.deselect.update();
            float var43 = this.getStartAngle() - 180.0F;

            for (int var9 = 0; var9 < this.slices.size(); var9++) {
               int var44 = Math.max(6, 48 / Math.max(this.slices.size(), 2));

               for (int var11 = 0; var11 < var44; var11++) {
                  double var46 = Math.toRadians(var43 + var9 * var40 + var11 * var40 / var44 + (var11 == 0 ? var41 : 0.0F));
                  double var48 = Math.toRadians(var43 + var9 * var40 + (var11 + 1) * var40 / var44 - (var11 == var44 - 1 ? var41 : 0.0F));
                  double var50 = Math.toRadians(var43 + var9 * var40 + var11 * var40 / var44 + (var11 == 0 ? var41 / 2.0F : 0.0F));
                  double var51 = Math.toRadians(var43 + var9 * var40 + (var11 + 1) * var40 / var44 - (var11 == var44 - 1 ? var41 / 1.5 : 0.0));
                  double var52 = this.x + this.width / 2.0F + var2 * (float)Math.cos(var46);
                  double var53 = this.y + this.height / 2.0F + var2 * (float)Math.sin(var46);
                  double var54 = this.x + this.width / 2.0F + var2 * (float)Math.cos(var48);
                  double var55 = this.y + this.height / 2.0F + var2 * (float)Math.sin(var48);
                  double var56 = this.x + this.width / 2.0F + var3 * (float)Math.cos(var50);
                  double var30 = this.y + this.height / 2.0F + var3 * (float)Math.sin(var50);
                  double var32 = this.x + this.width / 2.0F + var3 * (float)Math.cos(var51);
                  double var34 = this.y + this.height / 2.0F + var3 * (float)Math.sin(var51);
                  float var36 = 1.0F;
                  float var37 = 1.0F;
                  float var38 = 1.0F;
                  float var39 = 0.025F;
                  if (var9 == var42) {
                     var39 = 0.25F + 0.25F * this.select.fraction();
                  } else if (var9 == this.deselectIndex) {
                     var39 = 0.025F + 0.475F * this.deselect.fraction();
                  }

                  SpriteRenderer.instance
                     .renderPoly(
                        (float)var52,
                        (float)var53,
                        (float)var56,
                        (float)var30,
                        (float)var32,
                        (float)var34,
                        (float)var54,
                        (float)var55,
                        var36,
                        var37,
                        var38,
                        var39
                     );
               }

               Texture var45 = this.slices.get(var9).texture;
               if (var45 != null) {
                  double var47 = Math.toRadians(var43 + var9 * var40 + var40 / 2.0F);
                  float var49 = 0.0F + this.width / 2.0F + (var2 + (var3 - var2) / 2.0F) * (float)Math.cos(var47);
                  float var15 = 0.0F + this.height / 2.0F + (var2 + (var3 - var2) / 2.0F) * (float)Math.sin(var47);
                  this.DrawTexture(var45, var49 - var45.getWidth() / 2 - var45.offsetX, var15 - var45.getHeight() / 2 - var45.offsetY, var1);
               }
            }

            if (var7 != null && !StringUtils.isNullOrWhitespace(var7.text)) {
               this.formatTextInsideCircle(var7.text);
            }
         }
      }
   }

   private void formatTextInsideCircle(String var1) {
      UIFont var2 = UIFont.Medium;
      AngelCodeFont var3 = TextManager.instance.getFontFromEnum(var2);
      int var4 = var3.getLineHeight();
      int var5 = 1;

      for (int var6 = 0; var6 < var1.length(); var6++) {
         if (var1.charAt(var6) == '\n') {
            var5++;
         }
      }

      if (var5 > 1) {
         int var12 = var5 * var4;
         int var7 = this.getAbsoluteX().intValue() + (int)this.width / 2;
         int var8 = this.getAbsoluteY().intValue() + (int)this.height / 2 - var12 / 2;
         int var9 = 0;

         for (int var10 = 0; var10 < var1.length(); var10++) {
            if (var1.charAt(var10) == '\n') {
               int var11 = var3.getWidth(var1, var9, var10);
               var3.drawString(var7 - var11 / 2, var8, var1, 1.0F, 1.0F, 1.0F, 1.0F, var9, var10 - 1);
               var9 = var10 + 1;
               var8 += var4;
            }
         }

         if (var9 < var1.length()) {
            int var13 = var3.getWidth(var1, var9, var1.length() - 1);
            var3.drawString(var7 - var13 / 2, var8, var1, 1.0F, 1.0F, 1.0F, 1.0F, var9, var1.length() - 1);
         }
      } else {
         this.DrawTextCentre(var2, var1, this.width / 2.0F, this.height / 2.0F - var4 / 2, 1.0, 1.0, 1.0, 1.0);
      }
   }

   public void clear() {
      this.slices.clear();
      this.transition.reset();
      this.transition.init(66.666664F, false);
      this.selectIndex = -1;
      this.deselectIndex = -1;
   }

   public void addSlice(String var1, Texture var2) {
      Slice var3 = new Slice();
      var3.text = var1;
      var3.texture = var2;
      this.slices.add(var3);
   }

   private Slice getSlice(int var1) {
      return var1 >= 0 && var1 < this.slices.size() ? this.slices.get(var1) : null;
   }

   public void setSliceText(int var1, String var2) {
      Slice var3 = this.getSlice(var1);
      if (var3 != null) {
         var3.text = var2;
      }
   }

   public void setSliceTexture(int var1, Texture var2) {
      Slice var3 = this.getSlice(var1);
      if (var3 != null) {
         var3.texture = var2;
      }
   }

   private float getStartAngle() {
      float var1 = 360.0F / Math.max(this.slices.size(), 2);
      return 90.0F - var1 / 2.0F;
   }

   public int getSliceIndexFromMouse(int var1, int var2) {
      float var3 = 0.0F + this.width / 2.0F;
      float var4 = 0.0F + this.height / 2.0F;
      double var5 = Math.sqrt(Math.pow(var1 - var3, 2.0) + Math.pow(var2 - var4, 2.0));
      if (!(var5 > this.outerRadius) && !(var5 < this.innerRadius)) {
         double var7 = Math.atan2(var2 - var4, var1 - var3) + Math.PI;
         double var9 = Math.toDegrees(var7);
         float var11 = 360.0F / Math.max(this.slices.size(), 2);
         return var9 < this.getStartAngle() ? (int)((var9 + 360.0 - this.getStartAngle()) / var11) : (int)((var9 - this.getStartAngle()) / var11);
      } else {
         return -1;
      }
   }

   public int getSliceIndexFromJoypad(int var1) {
      float var2 = JoypadManager.instance.getAimingAxisX(var1);
      float var3 = JoypadManager.instance.getAimingAxisY(var1);
      if (!(Math.abs(var2) > 0.3F) && !(Math.abs(var3) > 0.3F)) {
         return -1;
      } else {
         double var4 = Math.atan2(-var3, -var2);
         double var6 = Math.toDegrees(var4);
         float var8 = 360.0F / Math.max(this.slices.size(), 2);
         return var6 < this.getStartAngle() ? (int)((var6 + 360.0 - this.getStartAngle()) / var8) : (int)((var6 - this.getStartAngle()) / var8);
      }
   }

   public void setJoypad(int var1) {
      this.joypad = var1;
   }
}
