package zombie.scripting;

import java.io.File;
import java.util.Comparator;

class ScriptManager$1 implements Comparator<String> {
   ScriptManager$1(ScriptManager var1) {
      this.this$0 = var1;
   }

   public int compare(String var1, String var2) {
      String var3 = new File(var1).getName();
      String var4 = new File(var2).getName();
      if (var3.startsWith("template_") && !var4.startsWith("template_")) {
         return -1;
      } else {
         return !var3.startsWith("template_") && var4.startsWith("template_") ? 1 : var1.compareTo(var2);
      }
   }
}
