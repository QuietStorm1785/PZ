#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Core.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/scripting/ScriptParser.h"
#include "zombie/scripting/ScriptParser/Block.h"
#include "zombie/scripting/ScriptParser/Value.h"
#include "zombie/util/StringUtils.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace modding {


class ActiveModsFile {
:
    static const int VERSION1 = 1;
    static const int VERSION = 1;

    bool write(const std::string& var1, ActiveMods var2) {
      if (Core.getInstance().isNoSave()) {
    return false;
      } else {
    File var3 = new File(var1);

         try {
            try (
    FileWriter var4 = new FileWriter(var3);
    BufferedWriter var5 = new BufferedWriter(var4);
            ) {
    std::string var6 = this.toString(var2);
               var5.write(var6);
            }

    return true;
         } catch (Exception var12) {
            ExceptionLogger.logException(var12);
    return false;
         }
      }
   }

    std::string toString(ActiveMods var1) {
    Block var2 = new Block();
      var2.setValue("VERSION", String.valueOf(1));
    Block var3 = var2.addBlock("mods", nullptr);
    std::vector var4 = var1.getMods();

      for (int var5 = 0; var5 < var4.size(); var5++) {
         var3.addValue("mod", (String)var4.get(var5));
      }

    Block var9 = var2.addBlock("maps", nullptr);
    std::vector var6 = var1.getMapOrder();

      for (int var7 = 0; var7 < var6.size(); var7++) {
         var9.addValue("map", (String)var6.get(var7));
      }

    StringBuilder var10 = new StringBuilder();
    std::string var8 = System.lineSeparator();
      var2.prettyPrintElements(0, var10, var8);
      return var10.toString();
   }

    bool read(const std::string& var1, ActiveMods var2) {
      var2.clear();

      try {
         try (
    FileReader var3 = new FileReader(var1);
    BufferedReader var4 = new BufferedReader(var3);
         ) {
    StringBuilder var5 = new StringBuilder();

            for (String var6 = var4.readLine(); var6 != nullptr; var6 = var4.readLine()) {
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

    void fromString(const std::string& var1, ActiveMods var2) {
      var1 = ScriptParser.stripComments(var1);
    Block var3 = ScriptParser.parse(var1);
    int var4 = -1;
    Value var5 = var3.getValue("VERSION");
      if (var5 != nullptr) {
         var4 = PZMath.tryParseInt(var5.getValue(), -1);
      }

      if (var4 >= 1 && var4 <= 1) {
    Block var6 = var3.getBlock("mods", nullptr);
         if (var6 != nullptr) {
            for (Value var8 : var6.values) {
    std::string var9 = var8.getKey().trim();
               if (var9.equalsIgnoreCase("mod")) {
    std::string var10 = var8.getValue().trim();
                  if (!StringUtils.isNullOrWhitespace(var10)) {
                     var2.getMods().add(var10);
                  }
               }
            }
         }

    Block var13 = var3.getBlock("maps", nullptr);
         if (var13 != nullptr) {
            for (Value var15 : var13.values) {
    std::string var16 = var15.getKey().trim();
               if (var16.equalsIgnoreCase("map")) {
    std::string var11 = var15.getValue().trim();
                  if (!StringUtils.isNullOrWhitespace(var11)) {
                     var2.getMapOrder().add(var11);
                  }
               }
            }
         }
      }
   }
}
} // namespace modding
} // namespace zombie
