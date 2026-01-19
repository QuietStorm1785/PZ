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
public:
    static const int VERSION1 = 1;
    static const int VERSION = 1;

    bool write(const std::string& var1, ActiveMods var2) {
      if (Core.getInstance().isNoSave()) {
    return false;
      } else {
    auto var3 = std::make_shared<File>(var1);

         try {
            try (
    auto var4 = std::make_shared<FileWriter>(var3);
    auto var5 = std::make_shared<BufferedWriter>(var4);
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
    auto var2 = std::make_shared<Block>();
      var2.setValue("VERSION", String.valueOf(1));
    Block var3 = var2.addBlock("mods", null);
    std::vector var4 = var1.getMods();

      for (int var5 = 0; var5 < var4.size(); var5++) {
         var3.addValue("mod", static_cast<String>(var4).get(var5));
      }

    Block var9 = var2.addBlock("maps", null);
    std::vector var6 = var1.getMapOrder();

      for (int var7 = 0; var7 < var6.size(); var7++) {
         var9.addValue("map", static_cast<String>(var6).get(var7));
      }

    auto var10 = std::make_shared<StringBuilder>();
    std::string var8 = System.lineSeparator();
      var2.prettyPrintElements(0, var10, var8);
      return var10.toString();
   }

    bool read(const std::string& var1, ActiveMods var2) {
      var2.clear();

      try {
         try (
    auto var3 = std::make_shared<FileReader>(var1);
    auto var4 = std::make_shared<BufferedReader>(var3);
         ) {
    auto var5 = std::make_shared<StringBuilder>();

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
    Block var6 = var3.getBlock("mods", null);
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

    Block var13 = var3.getBlock("maps", null);
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
