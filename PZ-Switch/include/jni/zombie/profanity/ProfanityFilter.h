#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/profanity/locales/Locale.h"
#include "zombie/profanity/locales/LocaleChinese.h"
#include "zombie/profanity/locales/LocaleEnglish.h"
#include "zombie/profanity/locales/LocaleGerman.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace profanity {


class ProfanityFilter {
:
    static bool DEBUG = false;
   private Map<String, Locale> locales = std::make_unique<HashMap<>>();
    Locale locale;
    Locale localeDefault;
    Pattern prePattern;
    bool enabled = true;
    static std::string LOCALES_DIR = "media" + File.separator + "profanity" + File.separator + "locales" + File.separator;
    static ProfanityFilter instance;

    static ProfanityFilter getInstance() const {
      if (instance == nullptr) {
         instance = std::make_unique<ProfanityFilter>();
      }

    return instance;
   }

    private ProfanityFilter() {
      this.addLocale(new LocaleEnglish("EN"), true);
      this.addLocale(new LocaleGerman("GER"));
      this.addLocale(new LocaleChinese("CHIN"));
      this.prePattern = Pattern.compile("(?<spaced>(?:(?:\\s|\\W)[\\w\\$@](?=\\s|\\W)){2,20})|(?<word>[\\w'\\$@_-]+)");
   }

    static void printDebug(std::string_view var0) {
      if (DEBUG) {
         System.out.println(var0);
      }
   }

    void enable(bool var1) {
      this.enabled = var1;
   }

    bool isEnabled() {
      return this.enabled;
   }

    int getFilterWordsCount() const noexcept {
      return this.locale != nullptr ? this.locale.getFilterWordsCount() : 0;
   }

    void addLocale(Locale var1) {
      this.addLocale(var1, false);
   }

    void addLocale(Locale var1, bool var2) {
      this.locales.put(var1.getID(), var1);
      if (var2) {
         this.locale = var1;
         this.localeDefault = var1;
      }
   }

    Locale getLocale() const {
      return this.locale;
   }

    void addWhiteListWord(std::string_view var1) {
      if (this.locale != nullptr) {
         this.locale.addWhiteListWord(var1);
      }
   }

    void removeWhiteListWord(std::string_view var1) {
      if (this.locale != nullptr) {
         this.locale.removeWhiteListWord(var1);
      }
   }

    void addFilterWord(std::string_view var1) {
      if (this.locale != nullptr) {
         this.locale.addFilterWord(var1);
      }
   }

    void removeFilterWord(std::string_view var1) {
      if (this.locale != nullptr) {
         this.locale.removeFilterWord(var1);
      }
   }

    void setLocale(std::string_view var1) {
      if (this.locales.containsKey(var1)) {
         this.locale = this.locales.get(var1);
      } else {
         this.locale = this.localeDefault;
      }
   }

    std::string filterString(std::string_view var1) {
      if (this.enabled && this.locale != nullptr && var1 != nullptr && this.locale.getFilterWordsCount() > 0) {
         try {
    StringBuffer var2 = new StringBuffer();
    Matcher var3 = this.prePattern.matcher(var1);

            while (var3.find()) {
               if (var3.group("word") != nullptr) {
                  var3.appendReplacement(var2, Matcher.quoteReplacement(this.locale.filterWord(var3.group("word"), true)));
               } else if (var3.group("spaced") != nullptr) {
                  var3.appendReplacement(var2, Matcher.quoteReplacement(" " + this.locale.filterWord(var3.group("spaced").replaceAll("\\s+", ""))));
               }
            }

            var3.appendTail(var2);
            return var2.toString();
         } catch (Exception var4) {
            System.out.println("Profanity failed for: " + var1);
         }
      }

    return var1;
   }

    std::string validateString(std::string_view var1) {
      return this.validateString(var1, true, true, true);
   }

    std::string validateString(std::string_view var1, bool var2, bool var3, bool var4) {
      if (this.enabled && this.locale != nullptr && var1 != nullptr && this.locale.getFilterWordsCount() > 0) {
         try {
    void* var5 = nullptr;
    bool var6 = false;
    StringBuilder var7 = new StringBuilder();
    Matcher var8 = this.prePattern.matcher(var1);

            while (var8.find()) {
               if (var2 && var8.group("word") != nullptr) {
                  var5 = this.locale.validateWord(var8.group("word"), var3);
                  if (var5 != nullptr) {
                     if (var6) {
                        var7.append(", ");
                     }

                     var7.append((String)var5);
                     var6 = true;
                  }
               } else if (var4 && var8.group("spaced") != nullptr) {
                  var5 = this.locale.validateWord(var8.group("spaced").replaceAll("\\s+", ""), false);
                  if (var5 != nullptr) {
                     if (var6) {
                        var7.append(", ");
                     }

                     var7.append((String)var5);
                     var6 = true;
                  }
               }
            }

            return var6 ? var7.toString() : nullptr;
         } catch (Exception var9) {
            System.out.println("Profanity validate string failed for: " + var1);
            var9.printStackTrace();
         }
      }

      return "Failed to parse string :(.";
   }
}
} // namespace profanity
} // namespace zombie
