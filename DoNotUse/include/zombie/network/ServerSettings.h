#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/SandboxOptions.h"
#include "zombie/core/Translator.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/SpawnRegions/Profession.h"
#include "zombie/network/SpawnRegions/Region.h"
#include "zombie/profanity/ProfanityFilter.h"
#include "zombie/util/StringUtils.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace network {


class ServerSettings {
public:
    std::string name;
    ServerOptions serverOptions;
    SandboxOptions sandboxOptions;
   protected std::vector<Region> spawnRegions;
   protected std::vector<Profession> spawnPoints;
    bool valid = true;
    std::string errorMsg = nullptr;

    public ServerSettings(const std::string& var1) {
      this.errorMsg = nullptr;
      this.valid = true;
      this.name = var1;
    std::string var2 = ProfanityFilter.getInstance().validateString(var1, true, true, true);
      if (!StringUtils.isNullOrEmpty(var2)) {
         this.errorMsg = Translator.getText("UI_BadWordCheck", var2);
         this.valid = false;
      }
   }

    std::string getName() {
      return this.name;
   }

    void resetToDefault() {
      this.serverOptions = std::make_unique<ServerOptions>();
      this.sandboxOptions = std::make_unique<SandboxOptions>();
      this.spawnRegions = std::make_unique<SpawnRegions>().getDefaultServerRegions();
      this.spawnPoints = nullptr;
   }

    bool loadFiles() {
      this.serverOptions = std::make_unique<ServerOptions>();
      this.serverOptions.loadServerTextFile(this.name);
      this.sandboxOptions = std::make_unique<SandboxOptions>();
      this.sandboxOptions.loadServerLuaFile(this.name);
      this.sandboxOptions.loadServerZombiesFile(this.name);
    SpawnRegions var1 = std::make_shared<SpawnRegions>();
      this.spawnRegions = var1.loadRegionsFile(ServerSettingsManager.instance.getNameInSettingsFolder(this.name + "_spawnregions.lua"));
      if (this.spawnRegions == nullptr) {
         this.spawnRegions = var1.getDefaultServerRegions();
      }

      this.spawnPoints = var1.loadPointsFile(ServerSettingsManager.instance.getNameInSettingsFolder(this.name + "_spawnpoints.lua"));
    return true;
   }

    bool saveFiles() {
      if (this.serverOptions == nullptr) {
    return false;
      } else {
         this.serverOptions.saveServerTextFile(this.name);
         this.sandboxOptions.saveServerLuaFile(this.name);
         if (this.spawnRegions != nullptr) {
    std::make_shared<SpawnRegions>();
         }

         if (this.spawnPoints != nullptr) {
    std::make_shared<SpawnRegions>();
         }

         this.tryDeleteFile(this.name + "_zombies.ini");
    return true;
      }
   }

    bool tryDeleteFile(const std::string& var1) {
      try {
    File var2 = std::make_shared<File>(ServerSettingsManager.instance.getNameInSettingsFolder(var1));
         if (var2.exists()) {
            DebugLog.log("deleting " + var2.getAbsolutePath());
            var2.delete();
         }

    return true;
      } catch (Exception var3) {
         ExceptionLogger.logException(var3);
    return false;
      }
   }

    bool deleteFiles() {
      this.tryDeleteFile(this.name + ".ini");
      this.tryDeleteFile(this.name + "_SandboxVars.lua");
      this.tryDeleteFile(this.name + "_spawnregions.lua");
      this.tryDeleteFile(this.name + "_spawnpoints.lua");
      this.tryDeleteFile(this.name + "_zombies.ini");
    return true;
   }

    bool duplicateFiles(const std::string& var1) {
      if (!ServerSettingsManager.instance.isValidNewName(var1)) {
    return false;
      } else {
    ServerSettings var2 = std::make_shared<ServerSettings>(this.name);
         var2.loadFiles();
         if (var2.spawnRegions != nullptr) {
            for (Region var4 : var2.spawnRegions) {
               if (var4.serverfile != nullptr && var4.serverfile == this.name + "_spawnpoints.lua")) {
                  var4.serverfile = var1 + "_spawnpoints.lua";
               }
            }
         }

         var2.name = var1;
         var2.saveFiles();
    return true;
      }
   }

    bool rename(const std::string& var1) {
      if (!ServerSettingsManager.instance.isValidNewName(var1)) {
    return false;
      } else {
         this.loadFiles();
         this.deleteFiles();
         if (this.spawnRegions != nullptr) {
            for (Region var3 : this.spawnRegions) {
               if (var3.serverfile != nullptr && var3.serverfile == this.name + "_spawnpoints.lua")) {
                  var3.serverfile = var1 + "_spawnpoints.lua";
               }
            }
         }

         this.name = var1;
         this.saveFiles();
    return true;
      }
   }

    ServerOptions getServerOptions() {
      return this.serverOptions;
   }

    SandboxOptions getSandboxOptions() {
      return this.sandboxOptions;
   }

    int getNumSpawnRegions() {
      return this.spawnRegions.size();
   }

    std::string getSpawnRegionName(int var1) {
      return this.spawnRegions.get(var1).name;
   }

    std::string getSpawnRegionFile(int var1) {
    Region var2 = this.spawnRegions.get(var1);
      return var2.file != nullptr ? var2.file : var2.serverfile;
   }

    void clearSpawnRegions() {
      this.spawnRegions.clear();
   }

    void addSpawnRegion(const std::string& var1, const std::string& var2) {
      if (var1 != nullptr && var2 != nullptr) {
    Region var3 = std::make_shared<Region>();
         var3.name = var1;
         if (var2.startsWith("media")) {
            var3.file = var2;
         } else {
            var3.serverfile = var2;
         }

         this.spawnRegions.push_back(var3);
      } else {
         throw std::make_unique<NullPointerException>();
      }
   }

    void removeSpawnRegion(int var1) {
      this.spawnRegions.remove(var1);
   }

    KahluaTable loadSpawnPointsFile(const std::string& var1) {
    SpawnRegions var2 = std::make_shared<SpawnRegions>();
      return var2.loadPointsTable(ServerSettingsManager.instance.getNameInSettingsFolder(var1));
   }

    bool saveSpawnPointsFile(const std::string& var1, KahluaTable var2) {
    SpawnRegions var3 = std::make_shared<SpawnRegions>();
      return var3.savePointsTable(ServerSettingsManager.instance.getNameInSettingsFolder(var1), var2);
   }

    bool isValid() {
      return this.valid;
   }

    std::string getErrorMsg() {
      return this.errorMsg;
   }
}
} // namespace network
} // namespace zombie
