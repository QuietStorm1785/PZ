package zombie.profanity.locales;

import zombie.profanity.locales.LocaleEnglish.1;
import zombie.profanity.locales.LocaleEnglish.10;
import zombie.profanity.locales.LocaleEnglish.11;
import zombie.profanity.locales.LocaleEnglish.2;
import zombie.profanity.locales.LocaleEnglish.3;
import zombie.profanity.locales.LocaleEnglish.4;
import zombie.profanity.locales.LocaleEnglish.5;
import zombie.profanity.locales.LocaleEnglish.6;
import zombie.profanity.locales.LocaleEnglish.7;
import zombie.profanity.locales.LocaleEnglish.8;
import zombie.profanity.locales.LocaleEnglish.9;

public class LocaleEnglish extends Locale {
   public LocaleEnglish(String var1) {
      super(var1);
   }

   protected void Init() {
      this.storeVowelsAmount = 3;
      this.addFilterRawWord("ass");
      this.addPhonizer(new 1(this, "strt", "(?<strt>^(?:KN|GN|PN|AE|WR))"));
      this.addPhonizer(new 2(this, "dropY", "(?<dropY>(?<=M)B$)"));
      this.addPhonizer(new 3(this, "dropB", "(?<dropB>(?<=M)B$)"));
      this.addPhonizer(new 4(this, "z", "(?<z>Z)"));
      this.addPhonizer(new 5(this, "ck", "(?<ck>CK)"));
      this.addPhonizer(new 6(this, "q", "(?<q>Q)"));
      this.addPhonizer(new 7(this, "v", "(?<v>V)"));
      this.addPhonizer(new 8(this, "xS", "(?<xS>^X)"));
      this.addPhonizer(new 9(this, "xKS", "(?<xKS>(?<=\\w)X)"));
      this.addPhonizer(new 10(this, "ph", "(?<ph>PH)"));
      this.addPhonizer(new 11(this, "c", "(?<c>C(?=[AUOIE]))"));
   }
}
