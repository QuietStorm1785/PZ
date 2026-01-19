package zombie.profanity.locales;

import java.util.regex.Matcher;
import zombie.profanity.Phonizer;

class LocaleGerman$1 extends Phonizer {
   LocaleGerman$1(LocaleGerman var1, String var2, String var3) {
      super(var2, var3);
      this.this$0 = var1;
   }

   public void execute(Matcher var1, StringBuffer var2) {
      if (var1.group(this.getName()) != null) {
         var1.appendReplacement(var2, "S");
      }
   }
}
