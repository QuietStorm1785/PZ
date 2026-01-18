#pragma once
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ServerSettingsManager {
public:
  static const ServerSettingsManager instance = new ServerSettingsManager();
protected
  ArrayList<ServerSettings> settings = std::make_unique<ArrayList<>>();
protected
  ArrayList<String> suffixes = std::make_unique<ArrayList<>>();

  std::string getSettingsFolder() {
    return ZomboidFileSystem.instance.getCacheDir() + File.separator + "Server";
  }

  std::string getNameInSettingsFolder(const std::string &name) {
    return this.getSettingsFolder() + File.separator + name;
  }

  void readAllSettings() {
    this.settings.clear();
    File file = new File(this.getSettingsFolder());
    if (!file.exists()) {
      file.mkdirs();
    } else {
      Filter filter = std::make_unique<Filter<Path>>(){bool accept(Path path){
          std::string string = path.getFileName().toString();
      return !Files.isDirectory(path) && string.endsWith(".ini") &&
             !string.endsWith("_zombies.ini") &&
             ServerSettingsManager.this.isValidName(string.replace(".ini", ""));
    }
  };

  try(DirectoryStream directoryStream = Files.newDirectoryStream(file.toPath(),
                                                                 filter)) {
    for (auto &path : directoryStream)
      ServerSettings serverSettings =
          new ServerSettings(path.getFileName().toString().replace(".ini", ""));
    this.settings.add(serverSettings);
  }
} catch (Exception exception) {
  ExceptionLogger.logException(exception);
}
}
}

int getSettingsCount() { return this.settings.size(); }

ServerSettings getSettingsByIndex(int index) {
  return index >= 0 && index < this.settings.size() ? this.settings.get(index)
                                                    : nullptr;
}

bool isValidName(const std::string &name) {
  if (name == nullptr || name.isEmpty()) {
    return false;
  } else {
    return name.contains("/") || name.contains("\\") || name.contains(":") ||
                   name.contains(";") || name.contains("\"") ||
                   name.contains(".")
               ? false
               : !name.contains("_zombies");
  }
}

bool anyFilesExist(const std::string &string) {
  this.getSuffixes();

  for (int int0 = 0; int0 < this.suffixes.size(); int0++) {
    File file = new File(this.getSettingsFolder() + File.separator + string +
                         this.suffixes.get(int0));
    if (file.exists()) {
      return true;
    }
  }

  return false;
}

bool isValidNewName(const std::string &newName) {
  return !this.isValidName(newName) ? false : !this.anyFilesExist(newName);
}

public
ArrayList<String> getSuffixes() {
  if (this.suffixes.isEmpty()) {
    this.suffixes.add(".ini");
    this.suffixes.add("_SandboxVars.lua");
    this.suffixes.add("_spawnpoints.lua");
    this.suffixes.add("_spawnregions.lua");
    this.suffixes.add("_zombies.ini");
  }

  return this.suffixes;
}
}
} // namespace network
} // namespace zombie
