#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace scripting {


class ScriptParsingUtils {
public:
   public static String[] SplitExceptInbetween(String var0, String var1, String var2) {
    std::stack var3 = new Stack();
    bool var4 = false;

      while (var0.contains(var1)) {
         if (!var4) {
    int var10 = var0.indexOf(var1);
    int var12 = var0.indexOf(var2);
            if (var12 == -1) {
               String[] var15 = var0.split(var1);

               for (int var18 = 0; var18 < var15.length; var18++) {
                  var3.add(var15[var18].trim());
               }

               var15 = new String[var3.size()];

               for (int var19 = 0; var19 < var3.size(); var19++) {
                  var15[var19] = (String)var3.get(var19);
               }

    return var15;
            }

            if (var10 == -1) {
               String[] var14 = new String[var3.size()];
               if (!var0.trim().isEmpty()) {
                  var3.add(var0.trim());
               }

               for (int var17 = 0; var17 < var3.size(); var17++) {
                  var14[var17] = (String)var3.get(var17);
               }

    return var14;
            }

            if (var10 < var12) {
               var3.add(var0.substring(0, var10));
               var0 = var0.substring(var10 + 1);
            } else {
               var4 = true;
            }
         } else {
    int var5 = var0.indexOf(var2);
    int var6 = var0.indexOf(var2);
    int var7 = var0.indexOf(var2, var0.indexOf(var2) + 1);
    int var8 = var0.indexOf(var1, var7 + 1);
            if (var8 == -1) {
               break;
            }

    std::string var9 = var0.substring(0, var8).trim();
            if (!var9.isEmpty()) {
               var3.add(var9);
            }

            var0 = var0.substring(var8 + 1);
            var4 = false;
         }
      }

      if (!var0.trim().isEmpty()) {
         var3.add(var0.trim());
      }

      String[] var11 = new String[var3.size()];

      for (int var13 = 0; var13 < var3.size(); var13++) {
         var11[var13] = (String)var3.get(var13);
      }

    return var11;
   }

   public static String[] SplitExceptInbetween(String var0, String var1, String var2, String var3) {
    int var5 = 0;
    int var6 = 0;
    int var7 = 0;
    int var8 = 0;
      var8 = 0;
      var5 = 0;
      var6 = 0;
      var7 = 0;
    std::stack var9 = new Stack();
      if (var0.indexOf(var2, var5) == -1) {
         return var0.split(var1);
      } else {
         do {
            var5 = var0.indexOf(var2, var5 + 1);
            var6 = var0.indexOf(var3, var6 + 1);
            var7 = var0.indexOf(var1, var7 + 1);
            if (var7 == -1) {
               var9.add(var0.trim());
               var0 = "";
            } else if ((var7 < var5 || var5 == -1 && var7 != -1) && var8 == 0) {
               var9.add(var0.substring(0, var7));
               var0 = var0.substring(var7 + 1);
               var5 = 0;
               var6 = 0;
               var7 = 0;
            } else if ((var6 >= var5 || var6 == -1) && var5 != -1) {
               if (var5 != -1 && var6 == -1) {
                  var6 = var5;
                  var8++;
               } else if (var5 != -1 && var6 != -1 && var5 < var6 && (var5 > var7 || var6 < var7)) {
                  var9.add(var0.substring(0, var7));
                  var0 = var0.substring(var7 + 1);
                  var5 = 0;
                  var6 = 0;
                  var7 = 0;
               }
            } else {
               var5 = var6;
               if (--var8 == 0) {
                  var9.add(var0.substring(0, var6 + 1));
                  var0 = var0.substring(var6 + 1);
                  var5 = 0;
                  var6 = 0;
                  var7 = 0;
               }
            }
         } while (var0.trim().length() > 0);

         if (!var0.trim().isEmpty()) {
            var9.add(var0.trim());
         }

         String[] var10 = new String[var9.size()];

         for (int var11 = 0; var11 < var9.size(); var11++) {
            var10[var11] = ((String)var9.get(var11)).trim();
         }

    return var10;
      }
   }
}
} // namespace scripting
} // namespace zombie
