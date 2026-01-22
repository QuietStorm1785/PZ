#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/network/ServerSettingsManager/1.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace network {


class ServerSettingsManager {
public:
    static const ServerSettingsManager instance = std::make_shared<ServerSettingsManager>();
   protected std::vector<ServerSettings> settings = std::make_unique<std::vector<>>();
   protected std::vector<std::string> suffixes = std::make_unique<std::vector<>>();

    std::string getSettingsFolder() {
      return ZomboidFileSystem.instance.getCacheDir() + File.separator + "Server";
   }

    std::string getNameInSettingsFolder(const std::string& var1) {
      return this.getSettingsFolder() + File.separator + var1;
   }

    void readAllSettings() {
      this.settings.clear();
    File var1 = std::make_shared<File>(this.getSettingsFolder());
      if (!var1.exists()) {
         var1.mkdirs();
      } else {
    1 var2 = std::make_shared<1>(this);

         try (DirectoryStream var3 = Files.newDirectoryStream(var1.toPath(), var2)) {
    for (auto& var5 : var3)    ServerSettings var6 = std::make_shared<ServerSettings>(var5.getFileName().replace(".ini", ""));
               this.settings.push_back(var6);
            }
         } catch (Exception var9) {
            ExceptionLogger.logException(var9);
         }
      }
   }

    int getSettingsCount() {
      return this.settings.size();
   }

    ServerSettings getSettingsByIndex(int var1) {
      return var1 >= 0 && var1 < this.settings.size() ? this.settings.get(var1) : nullptr;
   }

    bool isValidName(const std::string& var1) {
      if (var1 == nullptr || var1.empty()) {
    return false;
      } else {
         return var1.contains("/") || var1.contains("\\") || var1.contains(":") || var1.contains(";") || var1.contains("\"") || var1.contains(".")
            ? false
            : !var1.contains("_zombies");
      }
   }

    bool anyFilesExist(const std::string& var1) {
      this.getSuffixes();

      for (int var2 = 0; var2 < this.suffixes.size(); var2++) {
    File var3 = std::make_shared<File>(this.getSettingsFolder() + File.separator + var1 + this.suffixes.get(var2));
         if (var3.exists()) {
    return true;
         }
      }

    return false;
   }

    bool isValidNewName(const std::string& var1) {
      return !this.isValidName(var1) ? false : !this.anyFilesExist(var1);
   }

   public std::vector<std::string> getSuffixes() {
      if (this.suffixes.empty()) {
         this.suffixes.push_back(".ini");
         this.suffixes.push_back("_SandboxVars.lua");
         this.suffixes.push_back("_spawnpoints.lua");
         this.suffixes.push_back("_spawnregions.lua");
         this.suffixes.push_back("_zombies.ini");
      }

      return this.suffixes;
   }
}
} // namespace network
} // namespace zombie
