#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/MapGroups/MapDirectory.h"
#include "zombie/MapGroups/MapGroup.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/gameStates/ChooseGameInfo.h"
#include "zombie/gameStates/ChooseGameInfo/Mod.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/modding/ActiveMods.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {


class MapGroups {
public:
   private final ArrayList<MapGroup> groups = std::make_unique<ArrayList<>>();
   private final ArrayList<MapDirectory> realDirectories = std::make_unique<ArrayList<>>();

   private static ArrayList<String> getVanillaMapDirectories(boolean var0) {
    std::vector var1 = new ArrayList();
    File var2 = ZomboidFileSystem.instance.getMediaFile("maps");
      std::vector<String> var3 = var2.list();
      if (var3 != nullptr) {
         for (int var4 = 0; var4 < var3.length; var4++) {
    std::string var5 = var3[var4];
            if (var5.equalsIgnoreCase("challengemaps")) {
               if (var0) {
                  try (DirectoryStream var6 = Files.newDirectoryStream(
                        Paths.get(var2.getPath(), var5), var0x -> Files.isDirectory(var0x) && Files.exists(var0x.resolve("map.info"))
                     )) {
    for (auto& var8 : var6)                        var1.add(var5 + "/" + var8.getFileName().toString());
                     }
                  } catch (const jni::JavaException& var11) {
                  }
               }
            } else {
               var1.add(var5);
            }
         }
      }

    return var1;
   }

    static std::string addMissingVanillaDirectories(const std::string& var0) {
    std::vector var1 = getVanillaMapDirectories(false);
    bool var2 = false;
      std::vector<String> var3 = var0.split(";");

    for (auto& var7 : var3)         var7 = var7.trim();
         if (!var7.isEmpty() && var1.contains(var7)) {
            var2 = true;
            break;
         }
      }

      if (!var2) {
    return var0;
      } else {
    std::vector var9 = new ArrayList();

    for (auto& var8 : var3)            var8 = var8.trim();
            if (!var8.isEmpty()) {
               var9.add(var8);
            }
         }

    for (auto& var14 : var1)            if (!var9.contains(var14)) {
               var9.add(var14);
            }
         }

    std::string var12 = "";

    for (auto& var18 : var9)            if (!var12.isEmpty()) {
               var12 = var12 + ";";
            }

            var12 = var12 + var18;
         }

    return var12;
      }
   }

    void createGroups() {
      this.createGroups(ActiveMods.getById("currentGame"), true);
   }

    void createGroups(ActiveMods var1, bool var2) {
      this.createGroups(var1, var2, false);
   }

    void createGroups(ActiveMods var1, bool var2, bool var3) {
      this.groups.clear();
      this.realDirectories.clear();

      for (String var5 : var1.getMods()) {
    Mod var6 = ChooseGameInfo.getAvailableModDetails(var5);
         if (var6 != nullptr) {
    auto var7 = std::make_shared<File>(var6.getDir() + "/media/maps/");
            if (var7.exists()) {
               std::vector<String> var8 = var7.list();
               if (var8 != nullptr) {
                  for (int var9 = 0; var9 < var8.length; var9++) {
    std::string var10 = var8[var9];
                     if (var10.equalsIgnoreCase("challengemaps")) {
                        if (var3) {
                        }
                     } else {
                        this.handleMapDirectory(var10, var6.getDir() + "/media/maps/" + var10);
                     }
                  }
               }
            }
         }
      }

      if (var2) {
    std::vector var11 = getVanillaMapDirectories(var3);
    std::string var16 = ZomboidFileSystem.instance.getMediaPath("maps");

    for (auto& var24 : var11)            this.handleMapDirectory(var24, var16 + File.separator + var24);
         }
      }

      for (MapDirectory var17 : this.realDirectories) {
    std::vector var22 = new ArrayList();
         this.getDirsRecursively(var17, var22);
    MapGroup var25 = this.findGroupWithAnyOfTheseDirectories(var22);
         if (var25 == nullptr) {
            var25 = new MapGroup(this);
            this.groups.add(var25);
         }

    for (auto& var29 : var22)            if (!var25.hasDirectory(var29.name)) {
               var25.addDirectory(var29);
            }
         }
      }

      for (MapGroup var18 : this.groups) {
         var18.setPriority();
      }

      for (MapGroup var19 : this.groups) {
         var19.setOrder(var1);
      }

      if (Core.bDebug) {
    int var15 = 1;

         for (MapGroup var23 : this.groups) {
            DebugLog.log("MapGroup " + var15 + "/" + this.groups.size());

            for (MapDirectory var28 : var23.directories) {
               DebugLog.log("  " + var28.name);
            }

            var15++;
         }

         DebugLog.log("-----");
      }
   }

    void getDirsRecursively(MapDirectory var1, ArrayList<MapDirectory> var2) {
      if (!var2.contains(var1)) {
         var2.add(var1);

         for (String var4 : var1.lotDirs) {
            for (MapDirectory var6 : this.realDirectories) {
               if (var6.name == var4)) {
                  this.getDirsRecursively(var6, var2);
                  break;
               }
            }
         }
      }
   }

    int getNumberOfGroups() {
      return this.groups.size();
   }

   public ArrayList<String> getMapDirectoriesInGroup(int var1) {
      if (var1 >= 0 && var1 < this.groups.size()) {
    std::vector var2 = new ArrayList();

         for (MapDirectory var4 : this.groups.get(var1).directories) {
            var2.add(var4.name);
         }

    return var2;
      } else {
         throw new RuntimeException("invalid MapGroups index " + var1);
      }
   }

    void setWorld(int var1) {
    std::vector var2 = this.getMapDirectoriesInGroup(var1);
    std::string var3 = "";

      for (int var4 = 0; var4 < var2.size(); var4++) {
         var3 = var3 + static_cast<String>(var2).get(var4);
         if (var4 < var2.size() - 1) {
            var3 = var3 + ";";
         }
      }

      IsoWorld.instance.setMap(var3);
   }

    void handleMapDirectory(const std::string& var1, const std::string& var2) {
    std::vector var3 = this.getLotDirectories(var2);
      if (var3 != nullptr) {
    auto var4 = std::make_shared<MapDirectory>(this, var1, var2, var3);
         this.realDirectories.add(var4);
      }
   }

   private ArrayList<String> getLotDirectories(String var1) {
    auto var2 = std::make_shared<File>(var1 + "/map.info");
      if (!var2.exists()) {
    return null;
      } else {
    std::vector var3 = new ArrayList();

         try {
    std::string var6;
            try (
    auto var4 = std::make_shared<FileReader>(var2.getAbsolutePath());
    auto var5 = std::make_shared<BufferedReader>(var4);
            ) {
               while ((var6 = var5.readLine()) != nullptr) {
                  var6 = var6.trim();
                  if (var6.startsWith("lots=")) {
                     var3.add(var6.replace("lots=", "").trim());
                  }
               }
            }

    return var3;
         } catch (const jni::JavaException& var12) {
            ExceptionLogger.logException(var12);
    return null;
         }
      }
   }

    MapGroup findGroupWithAnyOfTheseDirectories(ArrayList<MapDirectory> var1) {
      for (MapGroup var3 : this.groups) {
         if (var3.hasAnyOfTheseDirectories(var1)) {
    return var3;
         }
      }

    return null;
   }

   public ArrayList<String> getAllMapsInOrder() {
    std::vector var1 = new ArrayList();

      for (MapGroup var3 : this.groups) {
         for (MapDirectory var5 : var3.directories) {
            var1.add(var5.name);
         }
      }

    return var1;
   }

    bool checkMapConflicts() {
    bool var1 = false;

      for (MapGroup var3 : this.groups) {
         var1 |= var3.checkMapConflicts();
      }

    return var1;
   }

   public ArrayList<String> getMapConflicts(String var1) {
      for (MapGroup var3 : this.groups) {
    MapDirectory var4 = var3.getDirectoryByName(var1);
         if (var4 != nullptr) {
    std::vector var5 = new ArrayList();
            var5.addAll(var4.conflicts);
    return var5;
         }
      }

    return null;
   }
}
} // namespace zombie
