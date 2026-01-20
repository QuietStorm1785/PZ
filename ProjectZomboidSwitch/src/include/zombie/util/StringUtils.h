#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace util {


class StringUtils {
public:
    static const std::string s_emptyString = "";
    static const char UTF8_BOM = '\ufeff';

    static bool isNullOrEmpty(const std::string& var0) {
    return var0 = = nullptr || var0.length() == 0;
   }

    static bool isNullOrWhitespace(const std::string& var0) {
    return isNullOrEmpty();
   }

    static bool isWhitespace(const std::string& var0) {
    int var1 = var0.length();
      if (var1 <= 0) {
    return false;
      } else {
    int var2 = 0;
    int var3 = var1 / 2;

         for (int var4 = var1 - 1; var2 <= var3; var4--) {
            if (!char.isWhitespace(var0.charAt(var2)) || !char.isWhitespace(var0.charAt(var4))) {
    return false;
            }

            var2++;
         }

    return true;
      }
   }

    static std::string discardNullOrWhitespace(const std::string& var0) {
    return isNullOrWhitespace();
   }

    static std::string trimPrefix(const std::string& var0, const std::string& var1) {
      return var0.startsWith(var1) ? var0.substr(var1.length()) : var0;
   }

    static std::string trimSuffix(const std::string& var0, const std::string& var1) {
      return var0.endsWith(var1) ? var0.substr(0, var0.length() - var1.length()) : var0;
   }

    static bool equals(const std::string& var0, const std::string& var1) {
    return var0 = = var1 ? true : var0 != nullptr && var0 == var1);
   }

    static bool startsWithIgnoreCase(const std::string& var0, const std::string& var1) {
      return var0.regionMatches(true, 0, var1, 0, var1.length());
   }

    static bool endsWithIgnoreCase(const std::string& var0, const std::string& var1) {
    int var2 = var1.length();
      return var0.regionMatches(true, var0.length() - var2, var1, 0, var2);
   }

    static bool containsIgnoreCase(const std::string& var0, const std::string& var1) {
      for (int var2 = var0.length() - var1.length(); var2 >= 0; var2--) {
         if (var0.regionMatches(true, var2, var1, 0, var1.length())) {
    return true;
         }
      }

    return false;
   }

    static bool equalsIgnoreCase(const std::string& var0, const std::string& var1) {
    return var0 = = var1 ? true : var0 != nullptr && var0.equalsIgnoreCase(var1);
   }

    static bool tryParseBoolean(const std::string& var0) {
      if (isNullOrWhitespace(var0)) {
    return false;
      } else {
    std::string var1 = var0.trim();
         return var1.equalsIgnoreCase("true") || var1 == "1") || var1 == "1.0");
      }
   }

    static bool isBoolean(const std::string& var0) {
    std::string var1 = var0.trim();
      return var1.equalsIgnoreCase("true") || var1 == "1") || var1 == "1.0")
         ? true
         : var1.equalsIgnoreCase("false") || var1 == "0") || var1 == "0.0");
   }

    static bool contains(std::string[] var0, const std::string& var1, bool> var2) {
    return indexOf();
   }

    static int indexOf(std::string[] var0, const std::string& var1, bool> var2) {
    int var3 = -1;

      for (int var4 = 0; var4 < var0.length; var4++) {
         if ((bool)var2.apply(var0[var4], var1)) {
            var3 = var4;
            break;
         }
      }

    return var3;
   }

    static std::string indent(const std::string& var0) {
    return indent();
   }

    static std::string indent(const std::string& var0, const std::string& var1, const std::string& var2) {
    std::string var3 = System.lineSeparator();
    return indent();
   }

    static std::string indent(const std::string& var0, const std::string& var1, const std::string& var2, const std::string& var3) {
      if (isNullOrEmpty(var0)) {
    return var0;
      } else {
    int var4 = var0.length();
    std::stringstream var5 = new std::stringstream(var4);
    std::stringstream var6 = new std::stringstream(var4);
    int var7 = 0;

         for (int var8 = 0; var8 < var4; var8++) {
    char var9 = var0.charAt(var8);
            switch (var9) {
               case '\n':
                  var5.append((CharSequence)var6);
                  var5.append(var1);
                  var6.setLength(0);
                  var7++;
               case '\r':
                  break;
               default:
                  if (var6.length() == 0) {
                     if (var7 == 0) {
                        var6.append(var2);
                     } else {
                        var6.append(var3);
                     }
                  }

                  var6.append(var9);
            }
         }

         var5.append((CharSequence)var6);
         var6.setLength(0);
         return var5;
      }
   }

    static std::string leftJustify(const std::string& var0, int var1) {
      if (var0 == nullptr) {
    return leftJustify();
      } else {
    int var2 = var0.length();
         if (var2 >= var1) {
    return var0;
         } else {
    int var3 = var1 - var2;
            char[] var4 = new char[var3];

            for (int var5 = 0; var5 < var3; var5++) {
               var4[var5] = ' ';
            }

    std::string var6 = new std::string(var4);
            return var0 + var6;
         }
      }
   }

    static std::string moduleDotType(const std::string& var0, const std::string& var1) {
      if (var1 == nullptr) {
    return nullptr;
      } else {
         return var1.contains(".") ? var1 : var0 + "." + var1;
      }
   }

    static std::string stripBOM(const std::string& var0) {
      return var0 != nullptr && var0.length() > 0 && var0.charAt(0) == '\ufeff' ? var0.substr(1) : var0;
   }

    static bool containsDoubleDot(const std::string& var0) {
    return isNullOrEmpty();
   }
}
} // namespace util
} // namespace zombie
