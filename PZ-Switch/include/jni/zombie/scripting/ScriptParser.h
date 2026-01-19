#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/scripting/ScriptParser/Block.h"
#include "zombie/scripting/ScriptParser/Value.h"

namespace zombie {
namespace scripting {


class ScriptParser {
:
    static StringBuilder stringBuilder = new StringBuilder();

    static int readBlock(const std::string& var0, int var1, Block var2) {
    int var3;
      for (var3 = var1; var3 < var0.length(); var3++) {
         if (var0.charAt(var3) == '{') {
    Block var4 = new Block();
            var2.children.add(var4);
            var2.elements.add(var4);
    std::string var5 = var0.substring(var1, var3).trim();
            String[] var6 = var5.split("\\s+");
            var4.type = var6[0];
            var4.id = var6.length > 1 ? var6[1] : nullptr;
            var3 = readBlock(var0, var3 + 1, var4);
            var1 = var3;
         } else {
            if (var0.charAt(var3) == '}') {
               return var3 + 1;
            }

            if (var0.charAt(var3) == ',') {
    Value var7 = new Value();
               var7.string = var0.substring(var1, var3);
               var2.values.add(var7);
               var2.elements.add(var7);
               var1 = var3 + 1;
            }
         }
      }

    return var3;
   }

    static Block parse(const std::string& var0) {
    Block var1 = new Block();
      readBlock(var0, 0, var1);
    return var1;
   }

    static std::string stripComments(const std::string& var0) {
      stringBuilder.setLength(0);
      stringBuilder.append(var0);
    int var1 = stringBuilder.lastIndexOf("*/");

      while (var1 != -1) {
    int var2 = stringBuilder.lastIndexOf("/*", var1 - 1);
         if (var2 == -1) {
            break;
         }

    int var3 = stringBuilder.lastIndexOf("*/", var1 - 1);

         while (var3 > var2) {
    int var4 = var2;
            var2 = stringBuilder.lastIndexOf("/*", var2 - 2);
            if (var2 == -1) {
               break;
            }

            var3 = stringBuilder.lastIndexOf("*/", var4 - 2);
         }

         if (var2 == -1) {
            break;
         }

         stringBuilder.replace(var2, var1 + 2, "");
         var1 = stringBuilder.lastIndexOf("*/", var2);
      }

      var0 = stringBuilder.toString();
      stringBuilder.setLength(0);
    return var0;
   }

    static ArrayList<String> parseTokens(String var0) {
    std::vector var1 = new ArrayList();

      while (true) {
    int var2 = 0;
    int var3 = 0;
    int var4 = 0;
         if (var0.indexOf("}", var3 + 1) == -1) {
            if (var0.trim().length() > 0) {
               var1.add(var0.trim());
            }

    return var1;
         }

         do {
            var3 = var0.indexOf("{", var3 + 1);
            var4 = var0.indexOf("}", var4 + 1);
            if ((var4 >= var3 || var4 == -1) && var3 != -1) {
               var4 = var3;
               var2++;
            } else {
               var3 = var4;
               var2--;
            }
         } while (var2 > 0);

         var1.add(var0.substring(0, var3 + 1).trim());
         var0 = var0.substring(var3 + 1);
      }
   }
}
} // namespace scripting
} // namespace zombie
