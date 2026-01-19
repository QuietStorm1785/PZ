package zombie.scripting;

import zombie.scripting.ScriptParser.Block;
import zombie.scripting.ScriptParser.BlockElement;

public class ScriptParser$Value implements BlockElement {
   public String string;

   public Block asBlock() {
      return null;
   }

   public ScriptParser$Value asValue() {
      return this;
   }

   public void prettyPrint(int var1, StringBuilder var2, String var3) {
      for (int var4 = 0; var4 < var1; var4++) {
         var2.append('\t');
      }

      var2.append(this.string.trim());
      var2.append(',');
      var2.append(var3);
   }

   public String getKey() {
      int var1 = this.string.indexOf(61);
      return var1 == -1 ? this.string : this.string.substring(0, var1);
   }

   public String getValue() {
      int var1 = this.string.indexOf(61);
      return var1 == -1 ? "" : this.string.substring(var1 + 1);
   }
}
