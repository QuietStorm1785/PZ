package zombie.modding;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.ArrayList;
import zombie.core.Core;
import zombie.core.logger.ExceptionLogger;
import zombie.core.math.PZMath;
import zombie.scripting.ScriptParser;
import zombie.scripting.ScriptParser.Block;
import zombie.scripting.ScriptParser.Value;
import zombie.util.StringUtils;

public final class ActiveModsFile {
   private static final int VERSION1 = 1;
   private static final int VERSION = 1;

   public boolean write(String var1, ActiveMods var2) {
      if (Core.getInstance().isNoSave()) {
         return false;
      } else {
         File var3 = new File(var1);

         try {
            try (
               FileWriter var4 = new FileWriter(var3);
               BufferedWriter var5 = new BufferedWriter(var4);
            ) {
               String var6 = this.toString(var2);
               var5.write(var6);
            }

            return true;
         } catch (Exception var12) {
            ExceptionLogger.logException(var12);
            return false;
         }
      }
   }

   private String toString(ActiveMods var1) {
      Block var2 = new Block();
      var2.setValue("VERSION", String.valueOf(1));
      Block var3 = var2.addBlock("mods", null);
      ArrayList var4 = var1.getMods();

      for (int var5 = 0; var5 < var4.size(); var5++) {
         var3.addValue("mod", (String)var4.get(var5));
      }

      Block var9 = var2.addBlock("maps", null);
      ArrayList var6 = var1.getMapOrder();

      for (int var7 = 0; var7 < var6.size(); var7++) {
         var9.addValue("map", (String)var6.get(var7));
      }

      StringBuilder var10 = new StringBuilder();
      String var8 = System.lineSeparator();
      var2.prettyPrintElements(0, var10, var8);
      return var10.toString();
   }

   public boolean read(String var1, ActiveMods var2) {
      var2.clear();

      try {
         try (
            FileReader var3 = new FileReader(var1);
            BufferedReader var4 = new BufferedReader(var3);
         ) {
            StringBuilder var5 = new StringBuilder();

            for (String var6 = var4.readLine(); var6 != null; var6 = var4.readLine()) {
               var5.append(var6);
            }

            this.fromString(var5.toString(), var2);
         }

         return true;
      } catch (FileNotFoundException var11) {
         return false;
      } catch (Exception var12) {
         ExceptionLogger.logException(var12);
         return false;
      }
   }

   private void fromString(String var1, ActiveMods var2) {
      var1 = ScriptParser.stripComments(var1);
      Block var3 = ScriptParser.parse(var1);
      int var4 = -1;
      Value var5 = var3.getValue("VERSION");
      if (var5 != null) {
         var4 = PZMath.tryParseInt(var5.getValue(), -1);
      }

      if (var4 >= 1 && var4 <= 1) {
         Block var6 = var3.getBlock("mods", null);
         if (var6 != null) {
            for (Value var8 : var6.values) {
               String var9 = var8.getKey().trim();
               if (var9.equalsIgnoreCase("mod")) {
                  String var10 = var8.getValue().trim();
                  if (!StringUtils.isNullOrWhitespace(var10)) {
                     var2.getMods().add(var10);
                  }
               }
            }
         }

         Block var13 = var3.getBlock("maps", null);
         if (var13 != null) {
            for (Value var15 : var13.values) {
               String var16 = var15.getKey().trim();
               if (var16.equalsIgnoreCase("map")) {
                  String var11 = var15.getValue().trim();
                  if (!StringUtils.isNullOrWhitespace(var11)) {
                     var2.getMapOrder().add(var11);
                  }
               }
            }
         }
      }
   }
}
