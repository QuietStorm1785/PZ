package zombie.profanity.locales;

import zombie.profanity.locales.LocaleGerman.1;

public class LocaleGerman extends LocaleEnglish {
   public LocaleGerman(String var1) {
      super(var1);
   }

   protected void Init() {
      this.storeVowelsAmount = 3;
      super.Init();
      this.addPhonizer(new 1(this, "ringelS", "(?<ringelS>ÃŸ)"));
   }
}
