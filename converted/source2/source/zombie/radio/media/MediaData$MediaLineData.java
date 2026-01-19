package zombie.radio.media;

import zombie.core.Color;
import zombie.core.Translator;

public final class MediaData$MediaLineData {
   private final String text;
   private final Color color;
   private final String codes;

   public MediaData$MediaLineData(String var1, float var2, float var3, float var4, String var5) {
      this.text = var1;
      this.codes = var5;
      if (var2 == 0.0F && var3 == 0.0F && var4 == 0.0F) {
         var2 = 1.0F;
         var3 = 1.0F;
         var4 = 1.0F;
      }

      this.color = new Color(var2, var3, var4);
   }

   public String getTranslatedText() {
      return Translator.getText(this.text);
   }

   public Color getColor() {
      return this.color;
   }

   public float getR() {
      return this.color.r;
   }

   public float getG() {
      return this.color.g;
   }

   public float getB() {
      return this.color.b;
   }

   public String getCodes() {
      return this.codes;
   }

   public String getTextGuid() {
      return this.text;
   }
}
