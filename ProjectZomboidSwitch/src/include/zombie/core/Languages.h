#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/gameStates/ChooseGameInfo.h"
#include "zombie/gameStates/ChooseGameInfo/Mod.h"
#include "zombie/util/Lambda.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {


class Languages {
public:
    static const Languages instance = std::make_shared<Languages>();
   private const std::vector<Language> m_languages = std::make_unique<std::vector<>>();
    Language m_defaultLanguage = std::make_shared<Language>(0, "EN", "English", "UTF-8", nullptr, false);

    public Languages() {
      this.m_languages.push_back(this.m_defaultLanguage);
   }

    void init() {
      this.m_languages.clear();
      this.m_defaultLanguage = std::make_shared<Language>(0, "EN", "English", "UTF-8", nullptr, false);
      this.m_languages.push_back(this.m_defaultLanguage);
      this.loadTranslateDirectory(ZomboidFileSystem.instance.getMediaPath("lua/shared/Translate"));

      for (std::string var2 : ZomboidFileSystem.instance.getModIDs()) {
    Mod var3 = ChooseGameInfo.getAvailableModDetails(var2);
         if (var3 != nullptr) {
    File var4 = std::make_shared<File>(var3.getDir(), "media/lua/shared/Translate");
            if (var4.isDirectory()) {
               this.loadTranslateDirectory(var4.getAbsolutePath());
            }
         }
      }
   }

    Language getDefaultLanguage() {
      return this.m_defaultLanguage;
   }

    int getNumLanguages() {
      return this.m_languages.size();
   }

    Language getByIndex(int var1) {
      return var1 >= 0 && var1 < this.m_languages.size() ? this.m_languages.get(var1) : nullptr;
   }

    Language getByName(const std::string& var1) {
      return (Language)PZArrayUtil.find(this.m_languages, Lambda.predicate(var1, (var0, var1x) -> var0.name().equalsIgnoreCase(var1x)));
   }

    int getIndexByName(const std::string& var1) {
      return PZArrayUtil.indexOf(this.m_languages, Lambda.predicate(var1, (var0, var1x) -> var0.name().equalsIgnoreCase(var1x)));
   }

    void loadTranslateDirectory(const std::string& var1) {
    Filter var2 = var0 -> Files.isDirectory(var0) && Files.exists(var0.resolve("language.txt"));
    Path var3 = FileSystems.getDefault().getPath(var1);
      if (Files.exists(var3)) {
         try (DirectoryStream var4 = Files.newDirectoryStream(var3, var2)) {
    for (auto& var6 : var4)    LanguageFileData var7 = this.loadLanguageDirectory(var6.toAbsolutePath());
               if (var7 != nullptr) {
    int var8 = this.getIndexByName(var7.name);
                  if (var8 == -1) {
    Language var9 = std::make_shared<Language>(this.m_languages.size(), var7.name, var7.text, var7.charset, var7.base, var7.azerty);
                     this.m_languages.push_back(var9);
                  } else {
    Language var13 = std::make_shared<Language>(var8, var7.name, var7.text, var7.charset, var7.base, var7.azerty);
                     this.m_languages.set(var8, var13);
                     if (var7.name == this.m_defaultLanguage.name())) {
                        this.m_defaultLanguage = var13;
                     }
                  }
               }
            }
         } catch (Exception var12) {
            ExceptionLogger.logException(var12);
         }
      }
   }

    LanguageFileData loadLanguageDirectory(Path var1) {
    std::string var2 = var1.getFileName();
    LanguageFileData var3 = std::make_shared<LanguageFileData>();
      var3.name = var2;
    LanguageFile var4 = std::make_shared<LanguageFile>();
    std::string var5 = var1.resolve("language.txt");
      return !var4.read(var5, var3) ? nullptr : var3;
   }
}
} // namespace core
} // namespace zombie
