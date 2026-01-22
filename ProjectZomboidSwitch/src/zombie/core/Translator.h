#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/characters/skills/PerkFactory.h"
#include "zombie/core/Translator/News.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {


class Translator {
public:
   private static std::vector<Language> availableLanguage = nullptr;
    static bool debug = false;
    static FileWriter debugFile = nullptr;
    static bool debugErrors = false;
   private static const std::unordered_set<std::string> debugItemEvolvedRecipeName = std::make_unique<std::unordered_set<>>();
   private static const std::unordered_set<std::string> debugItem = std::make_unique<std::unordered_set<>>();
   private static const std::unordered_set<std::string> debugMultiStageBuild = std::make_unique<std::unordered_set<>>();
   private static const std::unordered_set<std::string> debugRecipe = std::make_unique<std::unordered_set<>>();
   private static const std::unordered_map<std::string, std::string> moodles = std::make_unique<std::unordered_map<>>();
   private static const std::unordered_map<std::string, std::string> ui = std::make_unique<std::unordered_map<>>();
   private static const std::unordered_map<std::string, std::string> survivalGuide = std::make_unique<std::unordered_map<>>();
   private static const std::unordered_map<std::string, std::string> contextMenu = std::make_unique<std::unordered_map<>>();
   private static const std::unordered_map<std::string, std::string> farming = std::make_unique<std::unordered_map<>>();
   private static const std::unordered_map<std::string, std::string> recipe = std::make_unique<std::unordered_map<>>();
   private static const std::unordered_map<std::string, std::string> igui = std::make_unique<std::unordered_map<>>();
   private static const std::unordered_map<std::string, std::string> sandbox = std::make_unique<std::unordered_map<>>();
   private static const std::unordered_map<std::string, std::string> tooltip = std::make_unique<std::unordered_map<>>();
   private static const std::unordered_map<std::string, std::string> challenge = std::make_unique<std::unordered_map<>>();
   private static const std::unordered_set<std::string> missing = std::make_unique<std::unordered_set<>>();
   private static std::vector<std::string> azertyLanguages = nullptr;
   private static const std::unordered_map<std::string, std::string> news = std::make_unique<std::unordered_map<>>();
   private static const std::unordered_map<std::string, std::string> stash = std::make_unique<std::unordered_map<>>();
   private static const std::unordered_map<std::string, std::string> multiStageBuild = std::make_unique<std::unordered_map<>>();
   private static const std::unordered_map<std::string, std::string> moveables = std::make_unique<std::unordered_map<>>();
   private static const std::unordered_map<std::string, std::string> makeup = std::make_unique<std::unordered_map<>>();
   private static const std::unordered_map<std::string, std::string> gameSound = std::make_unique<std::unordered_map<>>();
   private static const std::unordered_map<std::string, std::string> dynamicRadio = std::make_unique<std::unordered_map<>>();
   private static const std::unordered_map<std::string, std::string> items = std::make_unique<std::unordered_map<>>();
   private static const std::unordered_map<std::string, std::string> itemName = std::make_unique<std::unordered_map<>>();
   private static const std::unordered_map<std::string, std::string> itemEvolvedRecipeName = std::make_unique<std::unordered_map<>>();
   private static const std::unordered_map<std::string, std::string> recordedMedia = std::make_unique<std::unordered_map<>>();
   private static const std::unordered_map<std::string, std::string> recordedMedia_EN = std::make_unique<std::unordered_map<>>();
    static Language language = nullptr;
    static const std::string newsHeader = "<IMAGE:media/ui/dot.png> <SIZE:small> ";

    static void loadFiles() {
      language = nullptr;
      availableLanguage = nullptr;
    File var0 = std::make_shared<File>(ZomboidFileSystem.instance.getCacheDir() + File.separator + "translationProblems.txt");
      if (debug) {
         try {
            if (debugFile != nullptr) {
               debugFile.close();
            }

            debugFile = std::make_shared<FileWriter>(var0);
         } catch (IOException var2) {
            var2.printStackTrace();
         }
      }

      moodles.clear();
      ui.clear();
      survivalGuide.clear();
      items.clear();
      itemName.clear();
      contextMenu.clear();
      farming.clear();
      recipe.clear();
      igui.clear();
      sandbox.clear();
      tooltip.clear();
      challenge.clear();
      news.clear();
      missing.clear();
      stash.clear();
      multiStageBuild.clear();
      moveables.clear();
      makeup.clear();
      gameSound.clear();
      dynamicRadio.clear();
      itemEvolvedRecipeName.clear();
      recordedMedia.clear();
      DebugLog.log("translator: language is " + getLanguage());
      debugErrors = false;
      fillMapFromFile("Tooltip", tooltip);
      fillMapFromFile("IG_UI", igui);
      fillMapFromFile("Recipes", recipe);
      fillMapFromFile("Farming", farming);
      fillMapFromFile("ContextMenu", contextMenu);
      fillMapFromFile("SurvivalGuide", survivalGuide);
      fillMapFromFile("UI", ui);
      fillMapFromFile("Items", items);
      fillMapFromFile("ItemName", itemName);
      fillMapFromFile("Moodles", moodles);
      fillMapFromFile("Sandbox", sandbox);
      fillMapFromFile("Challenge", challenge);
      fillMapFromFile("Stash", stash);
      fillMapFromFile("MultiStageBuild", multiStageBuild);
      fillMapFromFile("Moveables", moveables);
      fillMapFromFile("MakeUp", makeup);
      fillMapFromFile("GameSound", gameSound);
      fillMapFromFile("DynamicRadio", dynamicRadio);
      fillMapFromFile("EvolvedRecipeName", itemEvolvedRecipeName);
      fillMapFromFile("Recorded_Media", recordedMedia);
      fillNewsFromFile(news);
      if (debug) {
         if (debugErrors) {
            DebugLog.log("translator: errors detected, please see " + var0.getAbsolutePath());
         }

         debugItemEvolvedRecipeName.clear();
         debugItem.clear();
         debugMultiStageBuild.clear();
         debugRecipe.clear();
      }

      PerkFactory.initTranslations();
   }

    static void fillNewsFromFile(std::string> var0) {
    std::unordered_map var1 = new std::unordered_map();
    std::vector var2 = ZomboidFileSystem.instance.getModIDs();

      for (int var3 = 0; var3 < var2.size(); var3++) {
    std::string var4 = ZomboidFileSystem.instance.getModDir((std::string)var2.get(var3));
         if (var4 != nullptr) {
            tryFillNewsFromFile(var4, var0, var1, getLanguage());
            if (getLanguage() != getDefaultLanguage()) {
               tryFillNewsFromFile(var4, var0, var1, getDefaultLanguage());
            }
         }
      }

      tryFillNewsFromFile(".", var0, var1, getLanguage());
      if (getLanguage() != getDefaultLanguage()) {
         tryFillNewsFromFile(".", var0, var1, getDefaultLanguage());
      }

      for (News var6 : var1.values()) {
         var0.put("News_" + var6.version + "_Disclaimer", var6.toRichText());
      }

      var1.clear();
   }

    static void tryFillNewsFromFile(const std::string& var0, std::string> var1, News> var2, Language var3) {
      File var4 = std::make_shared<File>(
         var0
            + File.separator
            + "media"
            + File.separator
            + "lua"
            + File.separator
            + "shared"
            + File.separator
            + "Translate"
            + File.separator
            + var3
            + File.separator
            + "News_"
            + var3
            + ".txt"
      );
      if (var4.exists()) {
         doNews(var4, var2, var3);
      }
   }

    static void doNews(File var0, News> var1, Language var2) {
      try (
    FileInputStream var3 = std::make_shared<FileInputStream>(var0);
    InputStreamReader var4 = std::make_shared<InputStreamReader>(var3, Charset.forName(var2.charset()));
    BufferedReader var5 = std::make_shared<BufferedReader>(var4);
      ) {
    News var6 = nullptr;
    std::vector var7 = nullptr;

    std::string var8;
         while ((var8 = var5.readLine()) != nullptr) {
            if (!var8.trim().empty()) {
               if (var8.startsWith("[VERSION]")) {
    std::string var9 = var8.replaceFirst("\\[VERSION\\]", "").trim();
                  if (var1.containsKey(var9)) {
                     var6 = nullptr;
                     var7 = nullptr;
                  } else {
                     var1.put(var9, var6 = std::make_shared<News>(var9));
                     var7 = nullptr;
                  }
               }

               if (var6 != nullptr) {
                  if (var8.startsWith("[SECTION]")) {
    std::string var17 = var8.replaceFirst("\\[SECTION\\]", "").trim();
                     var7 = var6.getOrCreateSectionList(var17);
                  } else if (var8.startsWith("[NEWS]")) {
                     var7 = var6.getOrCreateSectionList("[New]");
                  } else if (var8.startsWith("[BALANCE]")) {
                     var7 = var6.getOrCreateSectionList("[Balance]");
                  } else if (var8.startsWith("[BUG FIX]")) {
                     var7 = var6.getOrCreateSectionList("[Bug Fix]");
                  } else if (var7 != nullptr) {
                     addNewsLine(var8, var7);
                  }
               }
            }
         }
      } catch (Exception var16) {
         ExceptionLogger.logException(var16);
      }
   }

    static void addNewsLine(const std::string& var0, std::vector<std::string> var1) {
      if (var0.startsWith("[BOLD]")) {
         var0 = var0.replaceFirst("\\[BOLD\\]", "<IMAGE:media/ui/dot.png> <SIZE:medium>");
         var1.push_back(var0 + " <LINE> ");
      } else if (var0.startsWith("[DOT2]")) {
         var0 = var0.replaceFirst("\\[DOT2\\]", "<IMAGE:media/ui/dot2.png> <SIZE:small>");
         var1.push_back(var0 + " <LINE> ");
      } else if (var0.startsWith("[NODOT]")) {
         var0 = var0.replaceFirst("\\[NODOT\\]", " <SIZE:small> ");
         var0 = var0 + " <LINE> ";
         var1.push_back(var0);
      } else {
    uint8_t var2 = 7;
         var1.push_back("<IMAGE:media/ui/dot.png> <SIZE:small> " + " <INDENT:%d> ".formatted(21 - var2) + var0 + " <INDENT:0> <LINE> ");
      }
   }

   public static std::vector<std::string> getNewsVersions() {
    std::vector var0 = new std::vector();
      var0.addAll(news.keySet());

      for (int var1 = 0; var1 < var0.size(); var1++) {
    std::string var2 = (std::string)var0.get(var1);
         var2 = var2.replace("News_", "");
         var2 = var2.replace("_Disclaimer", "");
         var0.set(var1, var2);
      }

      Collections.sort(var0);
    return var0;
   }

    static void tryFillMapFromFile(const std::string& var0, const std::string& var1, std::string> var2, Language var3) {
      File var4 = std::make_shared<File>(
         var0
            + File.separator
            + "media"
            + File.separator
            + "lua"
            + File.separator
            + "shared"
            + File.separator
            + "Translate"
            + File.separator
            + var3
            + File.separator
            + var1
            + "_"
            + var3
            + ".txt"
      );
      if (var4.exists()) {
         parseFile(var4, var2, var3);
      }
   }

    static void tryFillMapFromMods(const std::string& var0, std::string> var1, Language var2) {
    std::vector var3 = ZomboidFileSystem.instance.getModIDs();

      for (int var4 = var3.size() - 1; var4 >= 0; var4--) {
    std::string var5 = ZomboidFileSystem.instance.getModDir((std::string)var3.get(var4));
         if (var5 != nullptr) {
            tryFillMapFromFile(var5, var0, var1, var2);
         }
      }
   }

    static void addLanguageToList(Language var0, std::vector<Language> var1) {
      if (var0 != nullptr) {
         if (!var1.contains(var0)) {
            var1.push_back(var0);
            if (var0.base() != nullptr) {
               var0 = Languages.instance.getByName(var0.base());
               addLanguageToList(var0, var1);
            }
         }
      }
   }

    static void fillMapFromFile(const std::string& var0, std::string> var1) {
    std::vector var2 = new std::vector();
      addLanguageToList(getLanguage(), var2);
      addLanguageToList(getDefaultLanguage(), var2);

      for (int var3 = 0; var3 < var2.size(); var3++) {
    Language var4 = (Language)var2.get(var3);
         tryFillMapFromMods(var0, var1, var4);
         tryFillMapFromFile(ZomboidFileSystem.instance.base.getPath(), var0, var1, var4);
      }

      var2.clear();
   }

    static void parseFile(File var0, std::string> var1, Language var2) {
    std::string var3 = nullptr;

      try (
    FileInputStream var4 = std::make_shared<FileInputStream>(var0);
    InputStreamReader var5 = std::make_shared<InputStreamReader>(var4, Charset.forName(var2.charset()));
    BufferedReader var6 = std::make_shared<BufferedReader>(var5);
      ) {
         var6.readLine();
    bool var7 = false;
    std::string var8 = "";
    std::string var9 = "";
    int var10 = 1;
    std::string var11 = var0.getName().replace("_" + getDefaultLanguage(), "_" + getLanguage());

         while ((var3 = var6.readLine()) != nullptr) {
            var10++;

            try {
               if (var3.contains("=") && var3.contains("\"")) {
                  if (var3.trim().startsWith("Recipe_")) {
                     var8 = var3.split("=")[0].replaceAll("Recipe_", "").replaceAll("_", " ").trim();
                     var9 = var3.split("=")[1];
                     var9 = var9.substr(var9.indexOf("\"") + 1, var9.lastIndexOf("\""));
                  } else if (var3.trim().startsWith("DisplayName")) {
                     std::string[] var12 = var3.split("=");
                     if (var3.trim().startsWith("DisplayName_")) {
                        var8 = var12[0].replaceAll("DisplayName_", "").trim();
                     } else {
                        var8 = var12[0].replaceAll("DisplayName", "").trim();
                     }

                     if ("Anti_depressants" == var8)) {
                        var8 = "Antidepressants";
                     }

                     var9 = var12[1];
                     var9 = var9.substr(var9.indexOf("\"") + 1, var9.lastIndexOf("\""));
                  } else if (var3.trim().startsWith("EvolvedRecipeName_")) {
                     std::string[] var24 = var3.split("=");
                     var8 = var24[0].replaceAll("EvolvedRecipeName_", "").trim();
                     var9 = var24[1];
    int var13 = var9.indexOf("\"");
    int var14 = var9.lastIndexOf("\"");
                     var9 = var9.substr(var13 + 1, var14);
                  } else if (var3.trim().startsWith("ItemName_")) {
                     std::string[] var25 = var3.split("=");
                     var8 = var25[0].replaceAll("ItemName_", "").trim();
                     var9 = var25[1];
    int var27 = var9.indexOf("\"");
    int var28 = var9.lastIndexOf("\"");
                     var9 = var9.substr(var27 + 1, var28);
                  } else {
                     var8 = var3.split("=")[0].trim();
                     var9 = var3.substr(var3.indexOf("=") + 1);
                     var9 = var9.substr(var9.indexOf("\"") + 1, var9.lastIndexOf("\""));
                     if (var3.contains("..")) {
                        var7 = true;
                     }
                  }
               } else if (var3.contains("--") || var3.trim().empty() || !var3.trim().endsWith("..") && !var7) {
                  var7 = false;
               } else {
                  var7 = true;
                  var9 = var9 + var3.substr(var3.indexOf("\"") + 1, var3.lastIndexOf("\""));
               }

               if (!var7 || !var3.trim().endsWith("..")) {
                  if (!var8.empty()) {
                     if (!var1.containsKey(var8)) {
                        var1.put(var8, var9);
                        if (var1 == recordedMedia && var2 == getDefaultLanguage()) {
                           recordedMedia_EN.put(var8, var9);
                        }

                        if (debug && var2 == getDefaultLanguage() && getLanguage() != getDefaultLanguage()) {
                           if (var11 != nullptr) {
                              debugwrite(var11 + "\r\n");
                              var11 = nullptr;
                           }

                           debugwrite("\t" + var8 + " = \"" + var9 + "\",\r\n");
                           debugErrors = true;
                        }
                     } else if (debug && var2 == getDefaultLanguage() && getLanguage() != getDefaultLanguage()) {
    std::string var26 = (std::string)var1.get(var8);
                        if (countSubstitutions(var26) != countSubstitutions(var9)) {
                           debugwrite(
                              "wrong number of % substitutions in "
                                 + var8
                                 + "    "
                                 + getDefaultLanguage()
                                 + "=\""
                                 + var9
                                 + "\"    "
                                 + getLanguage()
                                 + "=\""
                                 + var26
                                 + "\"\r\n"
                           );
                           debugErrors = true;
                        }
                     }
                  }

                  var7 = false;
                  var9 = "";
                  var8 = "";
               }
            } catch (Exception var18) {
               if (debug) {
                  if (var11 != nullptr) {
                     debugwrite(var11 + "\r\n");
                     var11 = nullptr;
                  }

                  debugwrite("line " + var10 + ": " + var8 + " = " + var9 + "\r\n");
                  if (debugFile != nullptr) {
                     var18.printStackTrace(std::make_shared<PrintWriter>(debugFile));
                  }

                  debugwrite("\r\n");
                  debugErrors = true;
               }
            }
         }
      } catch (Exception var22) {
         var22.printStackTrace();
      }
   }

    static std::string getText(const std::string& var0) {
    return getTextInternal();
   }

    static std::string getTextOrNull(const std::string& var0) {
    return getTextInternal();
   }

    static std::string getTextInternal(const std::string& var0, bool var1) {
      if (ui == nullptr) {
         loadFiles();
      }

    std::string var2 = nullptr;
      if (var0.startsWith("UI_")) {
         var2 = ui.get(var0);
      } else if (var0.startsWith("Moodles_")) {
         var2 = moodles.get(var0);
      } else if (var0.startsWith("SurvivalGuide_")) {
         var2 = survivalGuide.get(var0);
      } else if (var0.startsWith("Farming_")) {
         var2 = farming.get(var0);
      } else if (var0.startsWith("IGUI_")) {
         var2 = igui.get(var0);
      } else if (var0.startsWith("ContextMenu_")) {
         var2 = contextMenu.get(var0);
      } else if (var0.startsWith("GameSound_")) {
         var2 = gameSound.get(var0);
      } else if (var0.startsWith("Sandbox_")) {
         var2 = sandbox.get(var0);
      } else if (var0.startsWith("Tooltip_")) {
         var2 = tooltip.get(var0);
      } else if (var0.startsWith("Challenge_")) {
         var2 = challenge.get(var0);
      } else if (var0.startsWith("MakeUp")) {
         var2 = makeup.get(var0);
      } else if (var0.startsWith("News_")) {
         var2 = news.get(var0);
      } else if (var0.startsWith("Stash_")) {
         var2 = stash.get(var0);
      } else if (var0.startsWith("RM_")) {
         var2 = recordedMedia.get(var0);
      }

    std::string var3 = Core.bDebug && DebugOptions.instance.TranslationPrefix.getValue() ? "*" : nullptr;
      if (var2 == nullptr) {
         if (var1) {
    return nullptr;
         }

         if (!missing.contains(var0)) {
            if (Core.bDebug) {
               DebugLog.log("ERROR: Missing translation \"" + var0 + "\"");
            }

            if (debug) {
               debugwrite("ERROR: Missing translation \"" + var0 + "\"\r\n");
            }

            missing.push_back(var0);
         }

         var2 = var0;
         var3 = Core.bDebug && DebugOptions.instance.TranslationPrefix.getValue() ? "!" : nullptr;
      }

      if (var2.contains("<br>")) {
         return var2.replaceAll("<br>", "\n");
      } else {
    return var3 = = nullptr ? var2 : var3 + var2;
      }
   }

    static int countSubstitutions(const std::string& var0) {
    int var1 = 0;
      if (var0.contains("%1")) {
         var1++;
      }

      if (var0.contains("%2")) {
         var1++;
      }

      if (var0.contains("%3")) {
         var1++;
      }

      if (var0.contains("%4")) {
         var1++;
      }

    return var1;
   }

    static std::string subst(const std::string& var0, const std::string& var1, void* var2) {
      if (var2 != nullptr) {
         if (dynamic_cast<double*>(var2) != nullptr) {
    double var3 = (double)var2;
            var0 = var0.replaceAll(var1, var3 == (long)var3 ? int64_t.toString((long)var3) : var2);
         } else {
            var0 = var0.replaceAll(var1, Matcher.quoteReplacement(var2));
         }
      }

    return var0;
   }

    static std::string getText(const std::string& var0, void* var1) {
    std::string var2 = getText(var0);
    return subst();
   }

    static std::string getText(const std::string& var0, void* var1, void* var2) {
    std::string var3 = getText(var0);
      var3 = subst(var3, "%1", var1);
    return subst();
   }

    static std::string getText(const std::string& var0, void* var1, void* var2, void* var3) {
    std::string var4 = getText(var0);
      var4 = subst(var4, "%1", var1);
      var4 = subst(var4, "%2", var2);
    return subst();
   }

    static std::string getText(const std::string& var0, void* var1, void* var2, void* var3, void* var4) {
    std::string var5 = getText(var0);
      var5 = subst(var5, "%1", var1);
      var5 = subst(var5, "%2", var2);
      var5 = subst(var5, "%3", var3);
    return subst();
   }

    static std::string getTextOrNull(const std::string& var0, void* var1) {
    std::string var2 = getTextOrNull(var0);
    return var2 = = nullptr ? nullptr : subst(var2, "%1", var1);
   }

    static std::string getTextOrNull(const std::string& var0, void* var1, void* var2) {
    std::string var3 = getTextOrNull(var0);
      if (var3 == nullptr) {
    return nullptr;
      } else {
         var3 = subst(var3, "%1", var1);
    return subst();
      }
   }

    static std::string getTextOrNull(const std::string& var0, void* var1, void* var2, void* var3) {
    std::string var4 = getTextOrNull(var0);
      if (var4 == nullptr) {
    return nullptr;
      } else {
         var4 = subst(var4, "%1", var1);
         var4 = subst(var4, "%2", var2);
    return subst();
      }
   }

    static std::string getTextOrNull(const std::string& var0, void* var1, void* var2, void* var3, void* var4) {
    std::string var5 = getTextOrNull(var0);
      if (var5 == nullptr) {
    return nullptr;
      } else {
         var5 = subst(var5, "%1", var1);
         var5 = subst(var5, "%2", var2);
         var5 = subst(var5, "%3", var3);
    return subst();
      }
   }

    static std::string getDefaultText(const std::string& var0) {
    return changeSomeStuff();
   }

    static std::string changeSomeStuff(const std::string& var0) {
    return var0;
   }

    static void setLanguage(Language var0) {
      if (var0 == nullptr) {
         var0 = getDefaultLanguage();
      }

      language = var0;
   }

    static void setLanguage(int var0) {
    Language var1 = Languages.instance.getByIndex(var0);
      setLanguage(var1);
   }

    static Language getLanguage() {
      if (language == nullptr) {
    std::string var0 = Core.getInstance().getOptionLanguageName();
         if (!StringUtils.isNullOrWhitespace(var0)) {
            language = Languages.instance.getByName(var0);
         }
      }

      if (language == nullptr) {
         language = Languages.instance.getByName(System.getProperty("user.language").toUpperCase());
      }

      if (language == nullptr) {
         language = getDefaultLanguage();
      }

    return language;
   }

    static std::string getCharset() {
    return getLanguage();
   }

   public static std::vector<Language> getAvailableLanguage() {
      if (availableLanguage == nullptr) {
         availableLanguage = std::make_unique<std::vector<>>();

         for (int var0 = 0; var0 < Languages.instance.getNumLanguages(); var0++) {
            availableLanguage.push_back(Languages.instance.getByIndex(var0));
         }
      }

    return availableLanguage;
   }

    static std::string getDisplayItemName(const std::string& var0) {
    void* var1 = nullptr;
      var1 = items.get(var0.replaceAll(" ", "_").replaceAll("-", "_"));
      return (std::string)(var1 == nullptr ? var0 : var1);
   }

    static std::string getItemNameFromFullType(const std::string& var0) {
      if (!var0.contains(".")) {
         throw IllegalArgumentException("fullType must contain \".\" i.e. module.type");
      } else {
    std::string var1 = itemName.get(var0);
         if (var1 == nullptr) {
            if (debug && getLanguage() != getDefaultLanguage() && !debugItem.contains(var0)) {
               debugItem.push_back(var0);
            }

    Item var2 = ScriptManager.instance.getItem(var0);
            if (var2 == nullptr) {
               var1 = var0;
            } else {
               var1 = var2.getDisplayName();
            }

            itemName.put(var0, var1);
         }

    return var1;
      }
   }

    static void setDefaultItemEvolvedRecipeName(const std::string& var0, const std::string& var1) {
      if (getLanguage() == getDefaultLanguage()) {
         if (!var0.contains(".")) {
            throw IllegalArgumentException("fullType must contain \".\" i.e. module.type");
         } else if (!itemEvolvedRecipeName.containsKey(var0)) {
            itemEvolvedRecipeName.put(var0, var1);
         }
      }
   }

    static std::string getItemEvolvedRecipeName(const std::string& var0) {
      if (!var0.contains(".")) {
         throw IllegalArgumentException("fullType must contain \".\" i.e. module.type");
      } else {
    std::string var1 = itemEvolvedRecipeName.get(var0);
         if (var1 == nullptr) {
            if (debug && getLanguage() != getDefaultLanguage() && !debugItemEvolvedRecipeName.contains(var0)) {
               debugItemEvolvedRecipeName.push_back(var0);
            }

    Item var2 = ScriptManager.instance.getItem(var0);
            if (var2 == nullptr) {
               var1 = var0;
            } else {
               var1 = var2.getDisplayName();
            }

            itemEvolvedRecipeName.put(var0, var1);
         }

    return var1;
      }
   }

    static std::string getMoveableDisplayName(const std::string& var0) {
    std::string var1 = var0.replaceAll(" ", "_").replaceAll("-", "_").replaceAll("'", "").replaceAll("\\.", "");
    std::string var2 = moveables.get(var1);
      if (var2 == nullptr) {
         return Core.bDebug && DebugOptions.instance.TranslationPrefix.getValue() ? "!" + var0 : var0;
      } else {
         return Core.bDebug && DebugOptions.instance.TranslationPrefix.getValue() ? "*" + var2 : var2;
      }
   }

    static std::string getMoveableDisplayNameOrNull(const std::string& var0) {
    std::string var1 = var0.replaceAll(" ", "_").replaceAll("-", "_").replaceAll("'", "").replaceAll("\\.", "");
    std::string var2 = moveables.get(var1);
      if (var2 == nullptr) {
    return nullptr;
      } else {
         return Core.bDebug && DebugOptions.instance.TranslationPrefix.getValue() ? "*" + var2 : var2;
      }
   }

    static std::string getMultiStageBuild(const std::string& var0) {
    std::string var1 = multiStageBuild.get("MultiStageBuild_" + var0);
      if (var1 == nullptr) {
         if (debug && getLanguage() != getDefaultLanguage() && !debugMultiStageBuild.contains(var0)) {
            debugMultiStageBuild.push_back(var0);
         }

    return var0;
      } else {
    return var1;
      }
   }

    static std::string getRecipeName(const std::string& var0) {
    std::string var1 = nullptr;
      var1 = recipe.get(var0);
      if (var1 != nullptr && !var1.empty()) {
    return var1;
      } else {
         if (debug && getLanguage() != getDefaultLanguage() && !debugRecipe.contains(var0)) {
            debugRecipe.push_back(var0);
         }

    return var0;
      }
   }

    static Language getDefaultLanguage() {
      return Languages.instance.getDefaultLanguage();
   }

    static void debugItemEvolvedRecipeNames() {
      if (debug && !debugItemEvolvedRecipeName.empty()) {
         debugwrite("EvolvedRecipeName_" + getLanguage() + ".txt\r\n");
    std::vector var0 = new std::vector();
         var0.addAll(debugItemEvolvedRecipeName);
         Collections.sort(var0);

    for (auto& var2 : var0)            debugwrite("\tEvolvedRecipeName_" + var2 + " = \"" + itemEvolvedRecipeName.get(var2) + "\",\r\n");
         }

         debugItemEvolvedRecipeName.clear();
      }
   }

    static void debugItemNames() {
      if (debug && !debugItem.empty()) {
         debugwrite("ItemName_" + getLanguage() + ".txt\r\n");
    std::vector var0 = new std::vector();
         var0.addAll(debugItem);
         Collections.sort(var0);

    for (auto& var2 : var0)            debugwrite("\tItemName_" + var2 + " = \"" + itemName.get(var2) + "\",\r\n");
         }

         debugItem.clear();
      }
   }

    static void debugMultiStageBuildNames() {
      if (debug && !debugMultiStageBuild.empty()) {
         debugwrite("MultiStageBuild_" + getLanguage() + ".txt\r\n");
    std::vector var0 = new std::vector();
         var0.addAll(debugMultiStageBuild);
         Collections.sort(var0);

    for (auto& var2 : var0)            debugwrite("\tMultiStageBuild_" + var2 + " = \"\",\r\n");
         }

         debugMultiStageBuild.clear();
      }
   }

    static void debugRecipeNames() {
      if (debug && !debugRecipe.empty()) {
         debugwrite("Recipes_" + getLanguage() + ".txt\r\n");
    std::vector var0 = new std::vector();
         var0.addAll(debugRecipe);
         Collections.sort(var0);

    for (auto& var2 : var0)            debugwrite("\tRecipe_" + var2.replace(" ", "_") + " = \"\",\r\n");
         }

         debugRecipe.clear();
      }
   }

    static void debugwrite(const std::string& var0) {
      if (debugFile != nullptr) {
         try {
            debugFile.write(var0);
            debugFile.flush();
         } catch (IOException var2) {
         }
      }
   }

   public static std::vector<std::string> getAzertyMap() {
      if (azertyLanguages == nullptr) {
         azertyLanguages = std::make_unique<std::vector<>>();
         azertyLanguages.push_back("FR");
      }

    return azertyLanguages;
   }

    static std::string getRadioText(const std::string& var0) {
    std::string var1 = dynamicRadio.get(var0);
    return var1 = = nullptr ? var0 : var1;
   }

    static std::string getTextMediaEN(const std::string& var0) {
      if (ui == nullptr) {
         loadFiles();
      }

    std::string var1 = nullptr;
      if (var0.startsWith("RM_")) {
         var1 = recordedMedia_EN.get(var0);
      }

    std::string var2 = Core.bDebug && DebugOptions.instance.TranslationPrefix.getValue() ? "*" : nullptr;
      if (var1 == nullptr) {
         if (!missing.contains(var0) && Core.bDebug) {
            if (Core.bDebug) {
               DebugLog.log("ERROR: Missing translation \"" + var0 + "\"");
            }

            if (debug) {
               debugwrite("ERROR: Missing translation \"" + var0 + "\"\r\n");
            }

            missing.push_back(var0);
         }

         var1 = var0;
         var2 = Core.bDebug && DebugOptions.instance.TranslationPrefix.getValue() ? "!" : nullptr;
      }

      if (var1.contains("<br>")) {
         return var1.replaceAll("<br>", "\n");
      } else {
    return var2 = = nullptr ? var1 : var2 + var1;
      }
   }
}
} // namespace core
} // namespace zombie
