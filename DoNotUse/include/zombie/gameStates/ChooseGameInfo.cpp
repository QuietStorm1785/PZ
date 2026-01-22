#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/Core.h"
#include "zombie/core/GameVersion.h"
#include "zombie/core/IndieFileLoader.h"
#include "zombie/core/Language.h"
#include "zombie/core/Translator.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureID.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/gameStates/ChooseGameInfo/Map.h"
#include "zombie/gameStates/ChooseGameInfo/Mod.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace gameStates {


class ChooseGameInfo {
public:
   private static const std::unordered_map<std::string, Map> Maps = std::make_unique<std::unordered_map<>>();
   private static const std::unordered_map<std::string, Mod> Mods = std::make_unique<std::unordered_map<>>();
   private static const std::unordered_set<std::string> MissingMods = std::make_unique<std::unordered_set<>>();
   private static const std::vector<std::string> tempStrings = std::make_unique<std::vector<>>();

    private ChooseGameInfo() {
   }

    static void Reset() {
      Maps.clear();
      Mods.clear();
      MissingMods.clear();
   }

    static void readTitleDotTxt(std::unordered_map var0, const std::string& var1, Language var2) {
    std::string var3 = "media/lua/shared/Translate/" + var2 + "/" + var1 + "/title.txt";
    File var4 = std::make_shared<File>(ZomboidFileSystem.instance.getString(var3));

      try (
    FileInputStream var5 = std::make_shared<FileInputStream>(var4);
    InputStreamReader var6 = std::make_shared<InputStreamReader>(var5, Charset.forName(var2.charset()));
    BufferedReader var7 = std::make_shared<BufferedReader>(var6);
      ) {
    std::string var8 = var7.readLine();
         var8 = StringUtils.stripBOM(var8);
         if (!StringUtils.isNullOrWhitespace(var8)) {
            var0.title = var8.trim();
         }
      } catch (FileNotFoundException var16) {
      }
   }

    static void readDescriptionDotTxt(std::unordered_map var0, const std::string& var1, Language var2) {
    std::string var3 = "media/lua/shared/Translate/" + var2 + "/" + var1 + "/description.txt";
    File var4 = std::make_shared<File>(ZomboidFileSystem.instance.getString(var3));

      try (
    FileInputStream var5 = std::make_shared<FileInputStream>(var4);
    InputStreamReader var6 = std::make_shared<InputStreamReader>(var5, Charset.forName(var2.charset()));
    BufferedReader var7 = std::make_shared<BufferedReader>(var6);
      ) {
         var0.desc = "";
    bool var9 = true;

    std::string var8;
         while ((var8 = var7.readLine()) != nullptr) {
            if (var9) {
               var8 = StringUtils.stripBOM(var8);
               var9 = false;
            }

            var0.desc = var0.desc + var8;
         }
      } catch (FileNotFoundException var16) {
      }
   }

    static std::unordered_map getMapDetails(const std::string& var0) {
      if (Maps.containsKey(var0)) {
         return Maps.get(var0);
      } else {
    File var1 = std::make_shared<File>(ZomboidFileSystem.instance.getString("media/maps/" + var0 + "/map.info"));
         if (!var1.exists()) {
    return nullptr;
         } else {
    std::unordered_map var2 = std::make_shared<Map>();
            var2.dir = std::make_shared<File>(var1.getParent()).getAbsolutePath();
            var2.title = var0;
            var2.lotsDir = std::make_unique<std::vector>();

            try {
    FileReader var3 = std::make_shared<FileReader>(var1.getAbsolutePath());
    BufferedReader var4 = std::make_shared<BufferedReader>(var3);
    std::string var5 = nullptr;

               try {
                  while ((var5 = var4.readLine()) != nullptr) {
                     var5 = var5.trim();
                     if (var5.startsWith("title=")) {
                        var2.title = var5.replace("title=", "");
                     } else if (var5.startsWith("lots=")) {
                        var2.lotsDir.push_back(var5.replace("lots=", "").trim());
                     } else if (var5.startsWith("description=")) {
                        if (var2.desc == nullptr) {
                           var2.desc = "";
                        }

                        var2.desc = var2.desc + var5.replace("description=", "");
                     } else if (var5.startsWith("fixed2x=")) {
                        var2.bFixed2x = bool.parseBoolean(var5.replace("fixed2x=", "").trim());
                     }
                  }
               } catch (IOException var9) {
                  Logger.getLogger(ChooseGameInfo.class.getName()).log(Level.SEVERE, nullptr, var9);
               }

               var4.close();
               var2.thumb = Texture.getSharedTexture(var2.dir + "/thumb.png");
    std::vector var6 = new std::vector();
               Translator.addLanguageToList(Translator.getLanguage(), var6);
               Translator.addLanguageToList(Translator.getDefaultLanguage(), var6);

               for (int var7 = var6.size() - 1; var7 >= 0; var7--) {
    Language var8 = (Language)var6.get(var7);
                  readTitleDotTxt(var2, var0, var8);
                  readDescriptionDotTxt(var2, var0, var8);
               }
            } catch (Exception var10) {
               ExceptionLogger.logException(var10);
    return nullptr;
            }

            Maps.put(var0, var2);
    return var2;
         }
      }
   }

    static Mod getModDetails(const std::string& var0) {
      if (MissingMods.contains(var0)) {
    return nullptr;
      } else if (Mods.containsKey(var0)) {
         return Mods.get(var0);
      } else {
    std::string var1 = ZomboidFileSystem.instance.getModDir(var0);
         if (var1 == nullptr) {
    std::vector var2 = tempStrings;
            ZomboidFileSystem.instance.getAllModFolders(var2);
    std::vector var3 = new std::vector();

            for (int var4 = 0; var4 < var2.size(); var4++) {
    File var5 = std::make_shared<File>((std::string)var2.get(var4), "mod.info");
               var3.clear();
    Mod var6 = ZomboidFileSystem.instance.searchForModInfo(var5, var0, var3);

               for (int var7 = 0; var7 < var3.size(); var7++) {
    Mod var8 = (Mod)var3.get(var7);
                  Mods.putIfAbsent(var8.getId(), var8);
               }

               if (var6 != nullptr) {
    return var6;
               }
            }
         }

    Mod var9 = readModInfo(var1);
         if (var9 == nullptr) {
            MissingMods.push_back(var0);
         }

    return var9;
      }
   }

    static Mod getAvailableModDetails(const std::string& var0) {
    Mod var1 = getModDetails(var0);
      return var1 != nullptr && var1.isAvailable() ? var1 : nullptr;
   }

    static Mod readModInfo(const std::string& var0) {
    Mod var1 = readModInfoAux(var0);
      if (var1 != nullptr) {
    Mod var2 = Mods.get(var1.getId());
         if (var2 == nullptr) {
            Mods.put(var1.getId(), var1);
         } else if (var2 != var1) {
            ZomboidFileSystem.instance.getAllModFolders(tempStrings);
    int var3 = tempStrings.indexOf(var1.getDir());
    int var4 = tempStrings.indexOf(var2.getDir());
            if (var3 < var4) {
               Mods.put(var1.getId(), var1);
            }
         }
      }

    return var1;
   }

    static Mod readModInfoAux(const std::string& var0) {
      if (var0 != nullptr) {
    Mod var1 = ZomboidFileSystem.instance.getModInfoForDir(var0);
         if (var1.bRead) {
            return var1.bValid ? var1 : nullptr;
         }

         var1.bRead = true;
    std::string var2 = var0 + File.separator + "mod.info";
    File var3 = std::make_shared<File>(var2);
         if (!var3.exists()) {
            DebugLog.Mod.warn("can't find \"" + var2 + "\"");
    return nullptr;
         }

         var1.setId(var3.getParentFile().getName());

         try (
    InputStreamReader var4 = IndieFileLoader.getStreamReader(var2);
    BufferedReader var5 = std::make_shared<BufferedReader>(var4);
         ) {
            while (true) {
    std::string var6;
               if ((var6 = var5.readLine()) == nullptr) {
                  if (var1.getUrl() == nullptr) {
                     var1.setUrl("");
                  }
                  break;
               }

               if (var6.contains("name=")) {
                  var1.name = var6.replace("name=", "");
               } else if (var6.contains("poster=")) {
    std::string var25 = var6.replace("poster=", "");
                  if (!StringUtils.isNullOrWhitespace(var25)) {
                     var1.posters.push_back(var0 + File.separator + var25);
                  }
               } else if (var6.contains("description=")) {
                  var1.desc = var1.desc + var6.replace("description=", "");
               } else if (var6.contains("require=")) {
                  var1.setRequire(new std::vector<>(Arrays.asList(var6.replace("require=", "").split(","))));
               } else if (var6.contains("id=")) {
                  var1.setId(var6.replace("id=", ""));
               } else if (var6.contains("url=")) {
                  var1.setUrl(var6.replace("url=", ""));
               } else if (var6.contains("pack=")) {
    std::string var24 = var6.replace("pack=", "").trim();
                  if (var24.empty()) {
                     DebugLog.Mod.error("pack= line requires a file name");
    return nullptr;
                  }

    int var28 = TextureID.bUseCompressionOption ? 4 : 0;
                  var28 |= 64;
    int var33 = var24.indexOf("type=");
                  if (var33 != -1) {
    std::string var34 = var24.substr(var33 + "type=".length());
    uint8_t var40 = -1;
                     switch (var34.hashCode()) {
                        case 3732:
                           if (var34 == "ui")) {
                              var40 = 0;
                           }
                        default:
                           switch (var40) {
                              case 0:
                                 var28 = 2;
                                 break;
                              default:
                                 DebugLog.Mod.error("unknown pack type=" + var34);
                           }

    int var38 = var24.indexOf(32);
                           var24 = var24.substr(0, var38).trim();
                     }
                  }

    std::string var35 = var24;
    std::string var39 = "";
                  if (var24.endsWith(".floor")) {
                     var35 = var24.substr(0, var24.lastIndexOf(46));
                     var39 = ".floor";
                     var28 &= -5;
                  }

    int var41 = Core.getInstance().getOptionTexture2x() ? 2 : 1;
                  if (Core.SafeModeForced) {
                     var41 = 1;
                  }

                  if (var41 == 2) {
    File var13 = std::make_shared<File>(var0 + File.separator + "media" + File.separator + "texturepacks" + File.separator + var35 + "2x" + var39 + ".pack");
                     if (var13.isFile()) {
                        DebugLog.Mod.printf("2x version of %s.pack found.\n", new Object[]{var24});
                        var24 = var35 + "2x" + var39;
                     } else {
                        var13 = std::make_shared<File>(var0 + File.separator + "media" + File.separator + "texturepacks" + File.separator + var24 + "2x.pack");
                        if (var13.isFile()) {
                           DebugLog.Mod.printf("2x version of %s.pack found.\n", new Object[]{var24});
                           var24 = var24 + "2x";
                        } else {
                           DebugLog.Mod.printf("2x version of %s.pack not found.\n", new Object[]{var24});
                        }
                     }
                  }

                  var1.addPack(var24, var28);
               } else if (var6.contains("tiledef=")) {
                  std::string[] var23 = var6.replace("tiledef=", "").trim().split("\\s+");
                  if (var23.length != 2) {
                     DebugLog.Mod.error("tiledef= line requires file name and file number");
    return nullptr;
                  }

    std::string var8 = var23[0];

    int var32;
                  try {
                     var32 = int.parseInt(var23[1]);
                  } catch (NumberFormatException var18) {
                     DebugLog.Mod.error("tiledef= line requires file name and file number");
    return nullptr;
                  }

    uint8_t var10 = 100;
    short var36 = 8190;
                  var36 = 16382;
                  if (var32 < var10 || var32 > var36) {
                     DebugLog.Mod
                        .error("tiledef=%s %d file number must be from %d to %d", new Object[]{var8, var32, int.valueOf(var10), int.valueOf(var36)});
    return nullptr;
                  }

                  var1.addTileDef(var8, var32);
               } else if (var6.startsWith("versionMax=")) {
    std::string var22 = var6.replace("versionMax=", "").trim();
                  if (!var22.empty()) {
                     try {
                        var1.versionMax = GameVersion.parse(var22);
                     } catch (Exception var16) {
                        DebugLog.Mod.error("invalid versionMax: " + var16.getMessage());
    return nullptr;
                     }
                  }
               } else if (var6.startsWith("versionMin=")) {
    std::string var7 = var6.replace("versionMin=", "").trim();
                  if (!var7.empty()) {
                     try {
                        var1.versionMin = GameVersion.parse(var7);
                     } catch (Exception var17) {
                        DebugLog.Mod.error("invalid versionMin: " + var17.getMessage());
    return nullptr;
                     }
                  }
               }
            }

            var1.bValid = true;
    return var1;
         } catch (Exception var21) {
            ExceptionLogger.logException(var21);
         }
      }

    return nullptr;
   }
}
} // namespace gameStates
} // namespace zombie
