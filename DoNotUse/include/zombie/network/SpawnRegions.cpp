#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "se/krka/kahlua/vm/LuaClosure.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/SpawnRegions/1.h"
#include "zombie/network/SpawnRegions/Point.h"
#include "zombie/network/SpawnRegions/Profession.h"
#include "zombie/network/SpawnRegions/Region.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace network {


class SpawnRegions {
public:
    Region parseRegionTable(KahluaTable var1) {
    void* var2 = var1.rawget("name");
    void* var3 = var1.rawget("file");
    void* var4 = var1.rawget("serverfile");
      if (dynamic_cast<std*>(var2) != nullptr::string && dynamic_cast<std*>(var3) != nullptr::string) {
    Region var6 = std::make_shared<Region>();
         var6.name = (std::string)var2;
         var6.file = (std::string)var3;
    return var6;
      } else if (dynamic_cast<std*>(var2) != nullptr::string && dynamic_cast<std*>(var4) != nullptr::string) {
    Region var5 = std::make_shared<Region>();
         var5.name = (std::string)var2;
         var5.serverfile = (std::string)var4;
    return var5;
      } else {
    return nullptr;
      }
   }

   private std::vector<Profession> parseProfessionsTable(KahluaTable var1) {
    std::vector var2 = nullptr;
    KahluaTableIterator var3 = var1.iterator();

      while (var3.advance()) {
    void* var4 = var3.getKey();
    void* var5 = var3.getValue();
         if (dynamic_cast<std*>(var4) != nullptr::string && dynamic_cast<KahluaTable*>(var5) != nullptr) {
    std::vector var6 = this.parsePointsTable((KahluaTable)var5);
            if (var6 != nullptr) {
    Profession var7 = std::make_shared<Profession>();
               var7.name = (std::string)var4;
               var7.points = var6;
               if (var2 == nullptr) {
                  var2 = std::make_unique<std::vector>();
               }

               var2.push_back(var7);
            }
         }
      }

    return var2;
   }

   private std::vector<Point> parsePointsTable(KahluaTable var1) {
    std::vector var2 = nullptr;
    KahluaTableIterator var3 = var1.iterator();

      while (var3.advance()) {
    void* var4 = var3.getValue();
         if (dynamic_cast<KahluaTable*>(var4) != nullptr) {
    Point var5 = this.parsePointTable((KahluaTable)var4);
            if (var5 != nullptr) {
               if (var2 == nullptr) {
                  var2 = std::make_unique<std::vector>();
               }

               var2.push_back(var5);
            }
         }
      }

    return var2;
   }

    Point parsePointTable(KahluaTable var1) {
    void* var2 = var1.rawget("worldX");
    void* var3 = var1.rawget("worldY");
    void* var4 = var1.rawget("posX");
    void* var5 = var1.rawget("posY");
    void* var6 = var1.rawget("posZ");
      if (dynamic_cast<double*>(var2) != nullptr && dynamic_cast<double*>(var3) != nullptr && dynamic_cast<double*>(var4) != nullptr && dynamic_cast<double*>(var5) != nullptr) {
    Point var7 = std::make_shared<Point>();
         var7.worldX = ((double)var2).intValue();
         var7.worldY = ((double)var3).intValue();
         var7.posX = ((double)var4).intValue();
         var7.posY = ((double)var5).intValue();
         var7.posZ = dynamic_cast<double*>(var6) != nullptr ? ((double)var6).intValue() : 0;
    return var7;
      } else {
    return nullptr;
      }
   }

   public std::vector<Region> loadRegionsFile(std::string var1) {
    File var2 = std::make_shared<File>(var1);
      if (!var2.exists()) {
    return nullptr;
      } else {
         try {
            LuaManager.env.rawset("SpawnRegions", nullptr);
            LuaManager.loaded.remove(var2.getAbsolutePath().replace("\\", "/"));
            LuaManager.RunLua(var2.getAbsolutePath());
    void* var3 = LuaManager.env.rawget("SpawnRegions");
            if (dynamic_cast<LuaClosure*>(var3) != nullptr) {
               Object[] var4 = LuaManager.caller.pcall(LuaManager.thread, var3, new Object[0]);
               if (var4.length > 1 && var4[1] instanceof KahluaTable) {
    std::vector var5 = new std::vector();
    KahluaTableIterator var6 = ((KahluaTable)var4[1]).iterator();

                  while (var6.advance()) {
    void* var7 = var6.getValue();
                     if (dynamic_cast<KahluaTable*>(var7) != nullptr) {
    Region var8 = this.parseRegionTable((KahluaTable)var7);
                        if (var8 != nullptr) {
                           var5.push_back(var8);
                        }
                     }
                  }

    return var5;
               }
            }

    return nullptr;
         } catch (Exception var9) {
            var9.printStackTrace();
    return nullptr;
         }
      }
   }

    std::string fmtKey(const std::string& var1) {
      if (var1.contains("\\")) {
         var1 = var1.replace("\\", "\\\\");
      }

      if (var1.contains("\"")) {
         var1 = var1.replace("\"", "\\\"");
      }

      if (var1.contains(" ") || var1.contains("\\")) {
         var1 = "\"" + var1 + "\"";
      }

      return var1.startsWith("\"") ? "[" + var1 + "]" : var1;
   }

    std::string fmtValue(const std::string& var1) {
      if (var1.contains("\\")) {
         var1 = var1.replace("\\", "\\\\");
      }

      if (var1.contains("\"")) {
         var1 = var1.replace("\"", "\\\"");
      }

      return "\"" + var1 + "\"";
   }

    bool saveRegionsFile(const std::string& var1, std::vector<Region> var2) {
    File var3 = std::make_shared<File>(var1);
      DebugLog.log("writing " + var1);

      try {
    bool var15;
         try (FileWriter var4 = std::make_shared<FileWriter>(var3)) {
    std::string var5 = System.lineSeparator();
            var4.write("function SpawnRegions()" + var5);
            var4.write("\treturn {" + var5);

    for (auto& var7 : var2)               if (var7.file != nullptr) {
                  var4.write("\t\t{ name = " + this.fmtValue(var7.name) + ", file = " + this.fmtValue(var7.file) + " }," + var5);
               } else if (var7.serverfile != nullptr) {
                  var4.write("\t\t{ name = " + this.fmtValue(var7.name) + ", serverfile = " + this.fmtValue(var7.serverfile) + " }," + var5);
               } else if (var7.professions != nullptr) {
                  var4.write("\t\t{ name = " + this.fmtValue(var7.name) + "," + var5);
                  var4.write("\t\t\tpoints = {" + var5);

                  for (Profession var9 : var7.professions) {
                     var4.write("\t\t\t\t" + this.fmtKey(var9.name) + " = {" + var5);

                     for (Point var11 : var9.points) {
                        var4.write(
                           "\t\t\t\t\t{ worldX = "
                              + var11.worldX
                              + ", worldY = "
                              + var11.worldY
                              + ", posX = "
                              + var11.posX
                              + ", posY = "
                              + var11.posY
                              + ", posZ = "
                              + var11.posZ
                              + " },"
                              + var5
                        );
                     }

                     var4.write("\t\t\t\t}," + var5);
                  }

                  var4.write("\t\t\t}" + var5);
                  var4.write("\t\t}," + var5);
               }
            }

            var4.write("\t}" + var5);
            var4.write("end" + System.lineSeparator());
            var15 = true;
         }

    return var15;
      } catch (Exception var14) {
         var14.printStackTrace();
    return false;
      }
   }

   public std::vector<Profession> loadPointsFile(std::string var1) {
    File var2 = std::make_shared<File>(var1);
      if (!var2.exists()) {
    return nullptr;
      } else {
         try {
            LuaManager.env.rawset("SpawnPoints", nullptr);
            LuaManager.loaded.remove(var2.getAbsolutePath().replace("\\", "/"));
            LuaManager.RunLua(var2.getAbsolutePath());
    void* var3 = LuaManager.env.rawget("SpawnPoints");
            if (dynamic_cast<LuaClosure*>(var3) != nullptr) {
               Object[] var4 = LuaManager.caller.pcall(LuaManager.thread, var3, new Object[0]);
               if (var4.length > 1 && var4[1] instanceof KahluaTable) {
                  return this.parseProfessionsTable((KahluaTable)var4[1]);
               }
            }

    return nullptr;
         } catch (Exception var6) {
            var6.printStackTrace();
    return nullptr;
         }
      }
   }

    bool savePointsFile(const std::string& var1, std::vector<Profession> var2) {
    File var3 = std::make_shared<File>(var1);
      DebugLog.log("writing " + var1);

      try {
    bool var13;
         try (FileWriter var4 = std::make_shared<FileWriter>(var3)) {
    std::string var5 = System.lineSeparator();
            var4.write("function SpawnPoints()" + var5);
            var4.write("\treturn {" + var5);

    for (auto& var7 : var2)               var4.write("\t\t" + this.fmtKey(var7.name) + " = {" + var5);

               for (Point var9 : var7.points) {
                  var4.write(
                     "\t\t\t{ worldX = "
                        + var9.worldX
                        + ", worldY = "
                        + var9.worldY
                        + ", posX = "
                        + var9.posX
                        + ", posY = "
                        + var9.posY
                        + ", posZ = "
                        + var9.posZ
                        + " },"
                        + var5
                  );
               }

               var4.write("\t\t}," + var5);
            }

            var4.write("\t}" + var5);
            var4.write("end" + System.lineSeparator());
            var13 = true;
         }

    return var13;
      } catch (Exception var12) {
         var12.printStackTrace();
    return false;
      }
   }

    KahluaTable loadPointsTable(const std::string& var1) {
    std::vector var2 = this.loadPointsFile(var1);
      if (var2 == nullptr) {
    return nullptr;
      } else {
    KahluaTable var3 = LuaManager.platform.newTable();

         for (int var4 = 0; var4 < var2.size(); var4++) {
    Profession var5 = (Profession)var2.get(var4);
    KahluaTable var6 = LuaManager.platform.newTable();

            for (int var7 = 0; var7 < var5.points.size(); var7++) {
    Point var8 = (Point)var5.points.get(var7);
    KahluaTable var9 = LuaManager.platform.newTable();
               var9.rawset("worldX", (double)var8.worldX);
               var9.rawset("worldY", (double)var8.worldY);
               var9.rawset("posX", (double)var8.posX);
               var9.rawset("posY", (double)var8.posY);
               var9.rawset("posZ", (double)var8.posZ);
               var6.rawset(var7 + 1, var9);
            }

            var3.rawset(var5.name, var6);
         }

    return var3;
      }
   }

    bool savePointsTable(const std::string& var1, KahluaTable var2) {
    std::vector var3 = this.parseProfessionsTable(var2);
      return var3 != nullptr ? this.savePointsFile(var1, var3) : false;
   }

   public std::vector<Region> getDefaultServerRegions() {
    std::vector var1 = new std::vector();
    1 var2 = std::make_shared<1>(this);
    std::string var3 = ZomboidFileSystem.instance.getMediaPath("maps");
    Path var4 = FileSystems.getDefault().getPath(var3);
      if (!Files.exists(var4)) {
    return var1;
      } else {
         try (DirectoryStream var5 = Files.newDirectoryStream(var4, var2)) {
    for (auto& var7 : var5)    Region var8 = std::make_shared<Region>();
               var8.name = var7.getFileName();
               var8.file = "media/maps/" + var8.name + "/spawnpoints.lua";
               var1.push_back(var8);
            }
         } catch (Exception var11) {
            var11.printStackTrace();
         }

    return var1;
      }
   }

   public std::vector<Profession> getDefaultServerPoints() {
    std::vector var1 = new std::vector();
    Profession var2 = std::make_shared<Profession>();
      var2.name = "unemployed";
      var2.points = std::make_unique<std::vector>();
      var1.push_back(var2);
    Point var3 = std::make_shared<Point>();
      var3.worldX = 40;
      var3.worldY = 22;
      var3.posX = 67;
      var3.posY = 201;
      var3.posZ = 0;
      var2.points.push_back(var3);
    return var1;
   }
}
} // namespace network
} // namespace zombie
