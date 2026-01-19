package zombie.characters.skills;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;
import se.krka.kahlua.vm.KahluaTable;
import zombie.ZomboidFileSystem;
import zombie.Lua.LuaManager;
import zombie.characters.skills.PerkFactory.Perk;
import zombie.characters.skills.PerkFactory.Perks;
import zombie.core.logger.ExceptionLogger;
import zombie.core.math.PZMath;
import zombie.debug.DebugLog;
import zombie.gameStates.ChooseGameInfo;
import zombie.gameStates.ChooseGameInfo.Mod;
import zombie.scripting.ScriptParser;
import zombie.scripting.ScriptParser.Block;
import zombie.scripting.ScriptParser.Value;
import zombie.util.StringUtils;

public final class CustomPerks {
   private static final int VERSION1 = 1;
   private static final int VERSION = 1;
   public static final CustomPerks instance = new CustomPerks();
   private final ArrayList<CustomPerk> m_perks = new ArrayList<>();

   public void init() {
      ArrayList var1 = ZomboidFileSystem.instance.getModIDs();

      for (int var2 = 0; var2 < var1.size(); var2++) {
         String var3 = (String)var1.get(var2);
         Mod var4 = ChooseGameInfo.getAvailableModDetails(var3);
         if (var4 != null) {
            File var5 = new File(var4.getDir() + File.separator + "media" + File.separator + "perks.txt");
            if (var5.exists() && !var5.isDirectory()) {
               this.readFile(var5.getAbsolutePath());
            }
         }
      }

      for (CustomPerk var9 : this.m_perks) {
         Perk var11 = Perks.FromString(var9.m_id);
         if (var11 == null || var11 == Perks.None || var11 == Perks.MAX) {
            var11 = new Perk(var9.m_id);
            var11.setCustom();
         }
      }

      for (CustomPerk var10 : this.m_perks) {
         Perk var13 = Perks.FromString(var10.m_id);
         Perk var14 = Perks.FromString(var10.m_parent);
         if (var14 == null || var14 == Perks.None || var14 == Perks.MAX) {
            var14 = Perks.None;
         }

         int[] var6 = var10.m_xp;
         PerkFactory.AddPerk(
            var13, var10.m_translation, var14, var6[0], var6[1], var6[2], var6[3], var6[4], var6[5], var6[6], var6[7], var6[8], var6[9], var10.m_bPassive
         );
      }
   }

   public void initLua() {
      KahluaTable var1 = (KahluaTable)LuaManager.env.rawget("Perks");

      for (CustomPerk var3 : this.m_perks) {
         Perk var4 = Perks.FromString(var3.m_id);
         var1.rawset(var4.getId(), var4);
      }
   }

   public static void Reset() {
      instance.m_perks.clear();
   }

   private boolean readFile(String var1) {
      try {
         boolean var6;
         try (
            FileReader var2 = new FileReader(var1);
            BufferedReader var3 = new BufferedReader(var2);
         ) {
            StringBuilder var4 = new StringBuilder();

            for (String var5 = var3.readLine(); var5 != null; var5 = var3.readLine()) {
               var4.append(var5);
            }

            this.parse(var4.toString());
            var6 = true;
         }

         return var6;
      } catch (FileNotFoundException var11) {
         return false;
      } catch (Exception var12) {
         ExceptionLogger.logException(var12);
         return false;
      }
   }

   private void parse(String var1) {
      var1 = ScriptParser.stripComments(var1);
      Block var2 = ScriptParser.parse(var1);
      int var3 = -1;
      Value var4 = var2.getValue("VERSION");
      if (var4 != null) {
         var3 = PZMath.tryParseInt(var4.getValue(), -1);
      }

      if (var3 >= 1 && var3 <= 1) {
         for (Block var6 : var2.children) {
            if (!var6.type.equalsIgnoreCase("perk")) {
               throw new RuntimeException("unknown block type \"" + var6.type + "\"");
            }

            CustomPerk var7 = this.parsePerk(var6);
            if (var7 == null) {
               DebugLog.General.warn("failed to parse custom perk \"%s\"", new Object[]{var6.id});
            } else {
               this.m_perks.add(var7);
            }
         }
      } else {
         throw new RuntimeException("invalid or missing VERSION");
      }
   }

   private CustomPerk parsePerk(Block var1) {
      if (StringUtils.isNullOrWhitespace(var1.id)) {
         DebugLog.General.warn("missing or empty perk id");
         return null;
      } else {
         CustomPerk var2 = new CustomPerk(var1.id);
         Value var3 = var1.getValue("parent");
         if (var3 != null && !StringUtils.isNullOrWhitespace(var3.getValue())) {
            var2.m_parent = var3.getValue().trim();
         }

         Value var4 = var1.getValue("translation");
         if (var4 != null) {
            var2.m_translation = StringUtils.discardNullOrWhitespace(var4.getValue().trim());
         }

         if (StringUtils.isNullOrWhitespace(var2.m_translation)) {
            var2.m_translation = var2.m_id;
         }

         Value var5 = var1.getValue("passive");
         if (var5 != null) {
            var2.m_bPassive = StringUtils.tryParseBoolean(var5.getValue().trim());
         }

         for (int var6 = 1; var6 <= 10; var6++) {
            Value var7 = var1.getValue("xp" + var6);
            if (var7 != null) {
               int var8 = PZMath.tryParseInt(var7.getValue().trim(), -1);
               if (var8 > 0) {
                  var2.m_xp[var6 - 1] = var8;
               }
            }
         }

         return var2;
      }
   }
}
