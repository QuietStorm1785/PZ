package zombie.sandbox;

import zombie.core.math.PZMath;
import zombie.scripting.ScriptParser.Block;
import zombie.scripting.ScriptParser.Value;
import zombie.util.StringUtils;

public class CustomSandboxOption {
   public final String m_id;
   public String m_page;
   public String m_translation;

   CustomSandboxOption(String var1) {
      this.m_id = var1;
   }

   static double getValueDouble(Block var0, String var1, double var2) {
      Value var4 = var0.getValue(var1);
      return var4 == null ? var2 : PZMath.tryParseDouble(var4.getValue().trim(), var2);
   }

   static float getValueFloat(Block var0, String var1, float var2) {
      Value var3 = var0.getValue(var1);
      return var3 == null ? var2 : PZMath.tryParseFloat(var3.getValue().trim(), var2);
   }

   static int getValueInt(Block var0, String var1, int var2) {
      Value var3 = var0.getValue(var1);
      return var3 == null ? var2 : PZMath.tryParseInt(var3.getValue().trim(), var2);
   }

   boolean parseCommon(Block var1) {
      Value var2 = var1.getValue("page");
      if (var2 != null) {
         this.m_page = StringUtils.discardNullOrWhitespace(var2.getValue().trim());
      }

      Value var3 = var1.getValue("translation");
      if (var3 != null) {
         this.m_translation = StringUtils.discardNullOrWhitespace(var3.getValue().trim());
      }

      return true;
   }
}
