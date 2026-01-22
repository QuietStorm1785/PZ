#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/scripting/ScriptParser.h"
#include "zombie/scripting/ScriptParser/Block.h"
#include "zombie/scripting/ScriptParser/Value.h"
#include "zombie/util/StringUtils.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace ui {


class FontsFile {
public:
    static const int VERSION1 = 1;
    static const int VERSION = 1;

    bool read(const std::string& var1, FontsFileFont> var2) {
      try {
    bool var7;
         try (
    FileReader var3 = std::make_shared<FileReader>(var1);
    BufferedReader var4 = std::make_shared<BufferedReader>(var3);
         ) {
    std::stringstream var5 = new std::stringstream();

            for (std::string var6 = var4.readLine(); var6 != nullptr; var6 = var4.readLine()) {
               var5.append(var6);
            }

            this.fromString(var5, var2);
            var7 = true;
         }

    return var7;
      } catch (FileNotFoundException var12) {
    return false;
      } catch (Exception var13) {
         ExceptionLogger.logException(var13);
    return false;
      }
   }

    void fromString(const std::string& var1, FontsFileFont> var2) {
      var1 = ScriptParser.stripComments(var1);
    Block var3 = ScriptParser.parse(var1);
    int var4 = -1;
    Value var5 = var3.getValue("VERSION");
      if (var5 != nullptr) {
         var4 = PZMath.tryParseInt(var5.getValue(), -1);
      }

      if (var4 >= 1 && var4 <= 1) {
         for (Block var7 : var3.children) {
            if (!var7.type.equalsIgnoreCase("font")) {
               throw RuntimeException("unknown block type \"" + var7.type + "\"");
            }

            if (StringUtils.isNullOrWhitespace(var7.id)) {
               DebugLog.General.warn("missing or empty font id");
            } else {
    Value var8 = var7.getValue("fnt");
    Value var9 = var7.getValue("img");
               if (var8 != nullptr && !StringUtils.isNullOrWhitespace(var8.getValue())) {
    FontsFileFont var10 = std::make_shared<FontsFileFont>();
                  var10.id = var7.id;
                  var10.fnt = var8.getValue().trim();
                  if (var9 != nullptr && !StringUtils.isNullOrWhitespace(var9.getValue())) {
                     var10.img = var9.getValue().trim();
                  }

                  var2.put(var10.id, var10);
               } else {
                  DebugLog.General.warn("missing or empty value \"fnt\"");
               }
            }
         }
      } else {
         throw RuntimeException("invalid or missing VERSION");
      }
   }
}
} // namespace ui
} // namespace zombie
