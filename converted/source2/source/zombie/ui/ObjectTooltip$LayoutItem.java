package zombie.ui;

import zombie.core.Core;

public class ObjectTooltip$LayoutItem {
   public String label;
   public float r0;
   public float g0;
   public float b0;
   public float a0;
   public boolean hasValue = false;
   public String value;
   public boolean rightJustify = false;
   public float r1;
   public float g1;
   public float b1;
   public float a1;
   public float progressFraction = -1.0F;
   public int labelWidth;
   public int valueWidth;
   public int valueWidthRight;
   public int progressWidth;
   public int height;

   public void reset() {
      this.label = null;
      this.value = null;
      this.hasValue = false;
      this.rightJustify = false;
      this.progressFraction = -1.0F;
   }

   public void setLabel(String var1, float var2, float var3, float var4, float var5) {
      this.label = var1;
      this.r0 = var2;
      this.b0 = var4;
      this.g0 = var3;
      this.a0 = var5;
   }

   public void setValue(String var1, float var2, float var3, float var4, float var5) {
      this.value = var1;
      this.r1 = var2;
      this.b1 = var4;
      this.g1 = var3;
      this.a1 = var5;
      this.hasValue = true;
   }

   public void setValueRight(int var1, boolean var2) {
      this.value = Integer.toString(var1);
      if (var1 > 0) {
         this.value = "+" + this.value;
      }

      if ((var1 >= 0 || !var2) && (var1 <= 0 || var2)) {
         this.r1 = Core.getInstance().getGoodHighlitedColor().getR();
         this.g1 = Core.getInstance().getGoodHighlitedColor().getG();
         this.b1 = Core.getInstance().getGoodHighlitedColor().getB();
      } else {
         this.r1 = Core.getInstance().getBadHighlitedColor().getR();
         this.g1 = Core.getInstance().getBadHighlitedColor().getG();
         this.b1 = Core.getInstance().getBadHighlitedColor().getB();
      }

      this.a1 = 1.0F;
      this.hasValue = true;
      this.rightJustify = true;
   }

   public void setValueRightNoPlus(float var1) {
      var1 = (int)((var1 + 0.005F) * 100.0F) / 100.0F;
      this.value = Float.toString(var1);
      this.r1 = 1.0F;
      this.g1 = 1.0F;
      this.b1 = 1.0F;
      this.a1 = 1.0F;
      this.hasValue = true;
      this.rightJustify = true;
   }

   public void setValueRightNoPlus(int var1) {
      this.value = Integer.toString(var1);
      this.r1 = 1.0F;
      this.g1 = 1.0F;
      this.b1 = 1.0F;
      this.a1 = 1.0F;
      this.hasValue = true;
      this.rightJustify = true;
   }

   public void setProgress(float var1, float var2, float var3, float var4, float var5) {
      this.progressFraction = var1;
      this.r1 = var2;
      this.b1 = var4;
      this.g1 = var3;
      this.a1 = var5;
      this.hasValue = true;
   }

   public void calcSizes() {
      this.labelWidth = this.valueWidth = this.valueWidthRight = this.progressWidth = 0;
      if (this.label != null) {
         this.labelWidth = TextManager.instance.MeasureStringX(ObjectTooltip.font, this.label);
      }

      if (this.hasValue) {
         if (this.value != null) {
            int var1 = TextManager.instance.MeasureStringX(ObjectTooltip.font, this.value);
            this.valueWidth = this.rightJustify ? 0 : var1;
            this.valueWidthRight = this.rightJustify ? var1 : 0;
         } else if (this.progressFraction != -1.0F) {
            this.progressWidth = 80;
         }
      }

      int var4 = 1;
      if (this.label != null) {
         int var2 = 1;

         for (int var3 = 0; var3 < this.label.length(); var3++) {
            if (this.label.charAt(var3) == '\n') {
               var2++;
            }
         }

         var4 = Math.max(var4, var2);
      }

      if (this.hasValue && this.value != null) {
         int var5 = 1;

         for (int var6 = 0; var6 < this.value.length(); var6++) {
            if (this.value.charAt(var6) == '\n') {
               var5++;
            }
         }

         var4 = Math.max(var4, var5);
      }

      this.height = var4 * ObjectTooltip.lineSpacing;
   }

   public void render(int var1, int var2, int var3, int var4, ObjectTooltip var5) {
      if (this.label != null) {
         var5.DrawText(ObjectTooltip.font, this.label, var1, var2, this.r0, this.g0, this.b0, this.a0);
      }

      if (this.value != null) {
         if (this.rightJustify) {
            var5.DrawTextRight(ObjectTooltip.font, this.value, var1 + var3 + var4, var2, this.r1, this.g1, this.b1, this.a1);
         } else {
            var5.DrawText(ObjectTooltip.font, this.value, var1 + var3, var2, this.r1, this.g1, this.b1, this.a1);
         }
      }

      if (this.progressFraction != -1.0F) {
         var5.DrawProgressBar(
            var1 + var3, var2 + ObjectTooltip.lineSpacing / 2 - 1, this.progressWidth, 2, this.progressFraction, this.r1, this.g1, this.b1, this.a1
         );
      }
   }
}
