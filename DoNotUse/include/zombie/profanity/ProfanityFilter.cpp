#pragma once
#include <sstream>
#include <stack>
#include <string>
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
public:
    static bool DEBUG = false;
   private Map<std::string, Locale> locales = std::make_unique<std::unordered_map<>>();
    Locale locale;
    Locale localeDefault;
    Pattern prePattern;
    bool enabled = true;
    static std::string LOCALES_DIR = "media" + File.separator + "profanity" + File.separator + "locales" + File.separator;
    static ProfanityFilter instance;

    static ProfanityFilter getInstance() {
      if (instance == nullptr) {
         instance = std::make_unique<ProfanityFilter>();
      }

    return instance;
   }

    private ProfanityFilter() {
      this.addLocale(std::make_shared<LocaleEnglish>("EN"), true);
      this.addLocale(std::make_shared<LocaleGerman>("GER"));
      this.addLocale(std::make_shared<LocaleChinese>("CHIN"));
      this.prePattern = Pattern.compile("(?<spaced>(?:(?:\\s|\\W)[\\w\\$@](?=\\s|\\W)){2,20})|(?<word>[\\w'\\$@_-]+)");
   }

    static void printDebug(const std::string& var0) {
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

    int getFilterWordsCount() {
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

    Locale getLocale() {
      return this.locale;
   }

    void addWhiteListWord(const std::string& var1) {
      if (this.locale != nullptr) {
         this.locale.addWhiteListWord(var1);
      }
   }

    void removeWhiteListWord(const std::string& var1) {
      if (this.locale != nullptr) {
         this.locale.removeWhiteListWord(var1);
      }
   }

    void addFilterWord(const std::string& var1) {
      if (this.locale != nullptr) {
         this.locale.addFilterWord(var1);
      }
   }

    void removeFilterWord(const std::string& var1) {
      if (this.locale != nullptr) {
         this.locale.removeFilterWord(var1);
      }
   }

    void setLocale(const std::string& var1) {
      if (this.locales.containsKey(var1)) {
         this.locale = this.locales.get(var1);
      } else {
         this.locale = this.localeDefault;
      }
   }

    std::string filterString(const std::string& var1) {
      if (this.enabled && this.locale != nullptr && var1 != nullptr && this.locale.getFilterWordsCount() > 0) {
         try {
    std::stringstream var2 = new std::stringstream();
    Matcher var3 = this.prePattern.matcher(var1);

            while (var3.find()) {
               if (var3.group("word") != nullptr) {
                  var3.appendReplacement(var2, Matcher.quoteReplacement(this.locale.filterWord(var3.group("word"), true)));
               } else if (var3.group("spaced") != nullptr) {
                  var3.appendReplacement(var2, Matcher.quoteReplacement(" " + this.locale.filterWord(var3.group("spaced").replaceAll("\\s+", ""))));
               }
            }

            var3.appendTail(var2);
            return var2;
         } catch (Exception var4) {
            System.out.println("Profanity failed for: " + var1);
         }
      }

    return var1;
   }

    std::string validateString(const std::string& var1) {
      return this.validateString(var1, true, true, true);
   }

    std::string validateString(const std::string& var1, bool var2, bool var3, bool var4) {
      if (this.enabled && this.locale != nullptr && var1 != nullptr && this.locale.getFilterWordsCount() > 0) {
         try {
    void* var5 = nullptr;
    bool var6 = false;
    std::stringstream var7 = new std::stringstream();
    Matcher var8 = this.prePattern.matcher(var1);

            while (var8.find()) {
               if (var2 && var8.group("word") != nullptr) {
                  var5 = this.locale.validateWord(var8.group("word"), var3);
                  if (var5 != nullptr) {
                     if (var6) {
                        var7.append(", ");
                     }

                     var7.append((std::string)var5);
                     var6 = true;
                  }
               } else if (var4 && var8.group("spaced") != nullptr) {
                  var5 = this.locale.validateWord(var8.group("spaced").replaceAll("\\s+", ""), false);
                  if (var5 != nullptr) {
                     if (var6) {
                        var7.append(", ");
                     }

                     var7.append((std::string)var5);
                     var6 = true;
                  }
               }
            }

            return var6 ? var7 : nullptr;
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
