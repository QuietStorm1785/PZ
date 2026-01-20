#pragma once
#include <sstream>
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
public:
    static std::stringstream stringBuilder = new std::stringstream();

    static int readBlock(const std::string& var0, int var1, Block var2) {
    int var3;
      for (var3 = var1; var3 < var0.length(); var3++) {
         if (var0.charAt(var3) == '{') {
    Block var4 = std::make_shared<Block>();
            var2.children.push_back(var4);
            var2.elements.push_back(var4);
    std::string var5 = var0.substr(var1, var3).trim();
            std::string[] var6 = var5.split("\\s+");
            var4.type = var6[0];
            var4.id = var6.length > 1 ? var6[1] : nullptr;
            var3 = readBlock(var0, var3 + 1, var4);
            var1 = var3;
         } else {
            if (var0.charAt(var3) == '}') {
               return var3 + 1;
            }

            if (var0.charAt(var3) == ',') {
    Value var7 = std::make_shared<Value>();
               var7.string = var0.substr(var1, var3);
               var2.values.push_back(var7);
               var2.elements.push_back(var7);
               var1 = var3 + 1;
            }
         }
      }

    return var3;
   }

    static Block parse(const std::string& var0) {
    Block var1 = std::make_shared<Block>();
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

      var0 = stringBuilder;
      stringBuilder.setLength(0);
    return var0;
   }

   public static std::vector<std::string> parseTokens(std::string var0) {
    std::vector var1 = new std::vector();

      while (true) {
    int var2 = 0;
    int var3 = 0;
    int var4 = 0;
         if (var0.indexOf("}", var3 + 1) == -1) {
            if (var0.trim().length() > 0) {
               var1.push_back(var0.trim());
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

         var1.push_back(var0.substr(0, var3 + 1).trim());
         var0 = var0.substr(var3 + 1);
      }
   }
}
} // namespace scripting
} // namespace zombie
