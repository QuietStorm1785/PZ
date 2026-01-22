#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Language.h"
#include "zombie/core/Translator.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace radio {


class RadioTranslationData {
public:
    std::string filePath;
    std::string guid;
    std::string language;
    Language languageEnum;
    int version = -1;
   private const std::vector<std::string> translators = std::make_unique<std::vector<>>();
   private const Map<std::string, std::string> translations = std::make_unique<std::unordered_map<>>();

    public RadioTranslationData(const std::string& var1) {
      this.filePath = var1;
   }

    std::string getFilePath() {
      return this.filePath;
   }

    std::string getGuid() {
      return this.guid;
   }

    std::string getLanguage() {
      return this.language;
   }

    Language getLanguageEnum() {
      return this.languageEnum;
   }

    int getVersion() {
      return this.version;
   }

    int getTranslationCount() {
      return this.translations.size();
   }

   public std::vector<std::string> getTranslators() {
      return this.translators;
   }

    bool validate() {
      return this.guid != nullptr && this.language != nullptr && this.version >= 0;
   }

    bool loadTranslations() {
    bool var1 = false;
      if (Translator.getLanguage() != this.languageEnum) {
         System.out.println("Radio translations trying to load language that is not the current language...");
    return false;
      } else {
         try {
    File var2 = std::make_shared<File>(this.filePath);
            if (var2.exists() && !var2.isDirectory()) {
    BufferedReader var3 = std::make_shared<BufferedReader>(std::make_shared<InputStreamReader>(std::make_shared<FileInputStream>(this.filePath), Charset.forName(this.languageEnum.charset())));
    std::string var4 = nullptr;
    bool var5 = false;
    std::vector var6 = new std::vector();

               while ((var4 = var3.readLine()) != nullptr) {
                  var4 = var4.trim();
                  if (var4 == "[Translations]")) {
                     var5 = true;
                  } else if (var5) {
                     if (!var4 == "[Collection]")) {
                        if (var4 == "[/Translations]")) {
                           var1 = true;
                           break;
                        }

                        std::string[] var16 = var4.split("=", 2);
                        if (var16.length == 2) {
    std::string var18 = var16[0].trim();
    std::string var20 = var16[1].trim();
                           this.translations.put(var18, var20);
                        }
                     } else {
    std::string var7 = nullptr;

                        while ((var4 = var3.readLine()) != nullptr) {
                           var4 = var4.trim();
                           if (var4 == "[/Collection]")) {
                              break;
                           }

                           std::string[] var8 = var4.split("=", 2);
                           if (var8.length == 2) {
    std::string var9 = var8[0].trim();
    std::string var10 = var8[1].trim();
                              if (var9 == "text")) {
                                 var7 = var10;
                              } else if (var9 == "member")) {
                                 var6.push_back(var10);
                              }
                           }
                        }

                        if (var7 != nullptr && var6.size() > 0) {
    for (auto& var19 : var6)                              this.translations.put(var19, var7);
                           }
                        }

                        var6.clear();
                     }
                  }
               }
            }
         } catch (Exception var11) {
            var11.printStackTrace();
            var1 = false;
         }

    return var1;
      }
   }

    std::string getTranslation(const std::string& var1) {
      return this.translations.containsKey(var1) ? this.translations.get(var1) : nullptr;
   }

    static RadioTranslationData ReadFile(const std::string& var0) {
    RadioTranslationData var1 = std::make_shared<RadioTranslationData>(var0);
    File var2 = std::make_shared<File>(var0);
      if (var2.exists() && !var2.isDirectory()) {
         try (FileInputStream var3 = std::make_shared<FileInputStream>(var0)) {
    BufferedReader var4 = std::make_shared<BufferedReader>(std::make_shared<InputStreamReader>(var3));
    std::string var5 = nullptr;

            while ((var5 = var4.readLine()) != nullptr) {
               std::string[] var6 = var5.split("=");
               if (var6.length > 1) {
    std::string var7 = var6[0].trim();
    std::string var8 = "";

                  for (int var9 = 1; var9 < var6.length; var9++) {
                     var8 = var8 + var6[var9];
                  }

                  var8 = var8.trim();
                  if (var7 == "guid")) {
                     var1.guid = var8;
                  } else if (var7 == "language")) {
                     var1.language = var8;
                  } else if (var7 == "version")) {
                     var1.version = int.parseInt(var8);
                  } else if (var7 == "translator")) {
                     std::string[] var23 = var8.split(",");
                     if (var23.length > 0) {
    for (auto& var13 : var23)                           var1.translators.push_back(var13);
                        }
                     }
                  }
               }

               var5 = var5.trim();
               if (var5 == "[/Info]")) {
                  break;
               }
            }
         } catch (Exception var16) {
            var16.printStackTrace();
         }
      }

    bool var17 = false;
      if (var1.language != nullptr) {
         for (Language var21 : Translator.getAvailableLanguage()) {
            if (var21 == var1.language)) {
               var1.languageEnum = var21;
               var17 = true;
               break;
            }
         }
      }

      if (!var17 && var1.language != nullptr) {
         System.out.println("Language " + var1.language + " not found");
    return nullptr;
      } else {
         return var1.guid != nullptr && var1.language != nullptr && var1.version >= 0 ? var1 : nullptr;
      }
   }
}
} // namespace radio
} // namespace zombie
