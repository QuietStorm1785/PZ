#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/characters/skills/PerkFactory/Perk.h"
#include "zombie/characters/skills/PerkFactory/Perks.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/gameStates/ChooseGameInfo.h"
#include "zombie/gameStates/ChooseGameInfo/Mod.h"
#include "zombie/scripting/ScriptParser.h"
#include "zombie/scripting/ScriptParser/Block.h"
#include "zombie/scripting/ScriptParser/Value.h"
#include "zombie/util/StringUtils.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace characters {
namespace skills {


class CustomPerks {
public:
    static const int VERSION1 = 1;
    static const int VERSION = 1;
    static const CustomPerks instance = std::make_shared<CustomPerks>();
   private const std::vector<CustomPerk> m_perks = std::make_unique<std::vector<>>();

    void init() {
    std::vector var1 = ZomboidFileSystem.instance.getModIDs();

      for (int var2 = 0; var2 < var1.size(); var2++) {
    std::string var3 = (std::string)var1.get(var2);
    Mod var4 = ChooseGameInfo.getAvailableModDetails(var3);
         if (var4 != nullptr) {
    File var5 = std::make_shared<File>(var4.getDir() + File.separator + "media" + File.separator + "perks.txt");
            if (var5.exists() && !var5.isDirectory()) {
               this.readFile(var5.getAbsolutePath());
            }
         }
      }

      for (CustomPerk var9 : this.m_perks) {
    Perk var11 = Perks.FromString(var9.m_id);
         if (var11 == nullptr || var11 == Perks.None || var11 == Perks.MAX) {
            var11 = std::make_shared<Perk>(var9.m_id);
            var11.setCustom();
         }
      }

      for (CustomPerk var10 : this.m_perks) {
    Perk var13 = Perks.FromString(var10.m_id);
    Perk var14 = Perks.FromString(var10.m_parent);
         if (var14 == nullptr || var14 == Perks.None || var14 == Perks.MAX) {
            var14 = Perks.None;
         }

         int[] var6 = var10.m_xp;
         PerkFactory.AddPerk(
            var13, var10.m_translation, var14, var6[0], var6[1], var6[2], var6[3], var6[4], var6[5], var6[6], var6[7], var6[8], var6[9], var10.m_bPassive
         );
      }
   }

    void initLua() {
    KahluaTable var1 = (KahluaTable)LuaManager.env.rawget("Perks");

      for (CustomPerk var3 : this.m_perks) {
    Perk var4 = Perks.FromString(var3.m_id);
         var1.rawset(var4.getId(), var4);
      }
   }

    static void Reset() {
      instance.m_perks.clear();
   }

    bool readFile(const std::string& var1) {
      try {
    bool var6;
         try (
    FileReader var2 = std::make_shared<FileReader>(var1);
    BufferedReader var3 = std::make_shared<BufferedReader>(var2);
         ) {
    std::stringstream var4 = new std::stringstream();

            for (std::string var5 = var3.readLine(); var5 != nullptr; var5 = var3.readLine()) {
               var4.append(var5);
            }

            this.parse(var4);
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

    void parse(const std::string& var1) {
      var1 = ScriptParser.stripComments(var1);
    Block var2 = ScriptParser.parse(var1);
    int var3 = -1;
    Value var4 = var2.getValue("VERSION");
      if (var4 != nullptr) {
         var3 = PZMath.tryParseInt(var4.getValue(), -1);
      }

      if (var3 >= 1 && var3 <= 1) {
         for (Block var6 : var2.children) {
            if (!var6.type.equalsIgnoreCase("perk")) {
               throw RuntimeException("unknown block type \"" + var6.type + "\"");
            }

    CustomPerk var7 = this.parsePerk(var6);
            if (var7 == nullptr) {
               DebugLog.General.warn("failed to parse custom perk \"%s\"", new Object[]{var6.id});
            } else {
               this.m_perks.push_back(var7);
            }
         }
      } else {
         throw RuntimeException("invalid or missing VERSION");
      }
   }

    CustomPerk parsePerk(Block var1) {
      if (StringUtils.isNullOrWhitespace(var1.id)) {
         DebugLog.General.warn("missing or empty perk id");
    return nullptr;
      } else {
    CustomPerk var2 = std::make_shared<CustomPerk>(var1.id);
    Value var3 = var1.getValue("parent");
         if (var3 != nullptr && !StringUtils.isNullOrWhitespace(var3.getValue())) {
            var2.m_parent = var3.getValue().trim();
         }

    Value var4 = var1.getValue("translation");
         if (var4 != nullptr) {
            var2.m_translation = StringUtils.discardNullOrWhitespace(var4.getValue().trim());
         }

         if (StringUtils.isNullOrWhitespace(var2.m_translation)) {
            var2.m_translation = var2.m_id;
         }

    Value var5 = var1.getValue("passive");
         if (var5 != nullptr) {
            var2.m_bPassive = StringUtils.tryParseBoolean(var5.getValue().trim());
         }

         for (int var6 = 1; var6 <= 10; var6++) {
    Value var7 = var1.getValue("xp" + var6);
            if (var7 != nullptr) {
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
} // namespace skills
} // namespace characters
} // namespace zombie
