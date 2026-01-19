package zombie.ui;

import java.util.Arrays;
import zombie.core.Rand;
import zombie.core.fonts.AngelCodeFont;
import zombie.core.textures.Texture;

final class TextDrawObject$DrawElement {
   private String text = "";
   private String scrambleText = "";
   private float currentScrambleVal = 0.0F;
   private UIFont f = UIFont.AutoNormSmall;
   private AngelCodeFont font = null;
   private float R = 1.0F;
   private float G = 1.0F;
   private float B = 1.0F;
   private int w = 0;
   private int h = 0;
   private boolean isImage = false;
   private boolean useFont = false;
   private boolean useColor = false;
   private Texture tex = null;
   private boolean isTextImage = false;
   private int charWidth = 0;

   private TextDrawObject$DrawElement() {
   }

   private void reset() {
      this.text = "";
      this.scrambleText = "";
      this.f = UIFont.AutoNormSmall;
      this.font = null;
      this.R = 1.0F;
      this.G = 1.0F;
      this.B = 1.0F;
      this.w = 0;
      this.h = 0;
      this.isImage = false;
      this.useFont = false;
      this.useColor = false;
      this.tex = null;
      this.isTextImage = false;
      this.charWidth = 0;
   }

   private void addText(String var1) {
      this.text = this.text + var1;
      this.charWidth = this.text.length();
   }

   private void scrambleText(float var1) {
      if (var1 != this.currentScrambleVal) {
         this.currentScrambleVal = var1;
         int var2 = (int)(var1 * 100.0F);
         String[] var3 = this.text.split("\\s+");
         this.scrambleText = "";

         for (String var7 : var3) {
            int var8 = Rand.Next(100);
            if (var8 > var2) {
               this.scrambleText = this.scrambleText + var7 + " ";
            } else {
               char[] var9 = new char[var7.length()];
               Arrays.fill(var9, ".".charAt(0));
               this.scrambleText = this.scrambleText + new String(var9) + " ";
            }
         }
      }
   }

   private void trim() {
      this.text = this.text.trim();
   }

   private TextDrawObject$DrawElement softclone() {
      TextDrawObject$DrawElement var1 = new TextDrawObject$DrawElement();
      if (this.useColor) {
         var1.R = this.R;
         var1.G = this.G;
         var1.B = this.B;
         var1.useColor = this.useColor;
      }

      if (this.useFont) {
         var1.f = this.f;
         var1.font = this.font;
         var1.useFont = this.useFont;
      }

      return var1;
   }
}
