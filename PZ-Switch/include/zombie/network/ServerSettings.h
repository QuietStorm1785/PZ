#pragma once
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/SandboxOptions.h"
#include "zombie/core/Translator.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/profanity/ProfanityFilter.h"
#include "zombie/util/StringUtils.h"
#include <cstdint>
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

class ServerSettings {
public:
 std::string name;
 ServerOptions serverOptions;
 SandboxOptions sandboxOptions;
protected
 ArrayList<SpawnRegions.Region> spawnRegions;
protected
 ArrayList<SpawnRegions.Profession> spawnPoints;
 bool valid = true;
 std::string errorMsg = nullptr;

public
 ServerSettings(const std::string &_name) {
 this->errorMsg = nullptr;
 this->valid = true;
 this->name = _name;
 std::string string =
 ProfanityFilter.getInstance().validateString(_name, true, true, true);
 if (!StringUtils.isNullOrEmpty(string) {
 this->errorMsg = Translator.getText("UI_BadWordCheck", string);
 this->valid = false;
 }
 }

 std::string getName() { return this->name; }

 void resetToDefault() {
 this->serverOptions = std::make_unique<ServerOptions>();
 this->sandboxOptions = std::make_unique<SandboxOptions>();
 this->spawnRegions =
 std::make_unique<SpawnRegions>().getDefaultServerRegions();
 this->spawnPoints = nullptr;
 }

 bool loadFiles() {
 this->serverOptions = std::make_unique<ServerOptions>();
 this->serverOptions.loadServerTextFile(this->name);
 this->sandboxOptions = std::make_unique<SandboxOptions>();
 this->sandboxOptions.loadServerLuaFile(this->name);
 this->sandboxOptions.loadServerZombiesFile(this->name);
 SpawnRegions spawnRegionsx = new SpawnRegions();
 this->spawnRegions = spawnRegionsx.loadRegionsFile(
 ServerSettingsManager.instance.getNameInSettingsFolder(
 this->name + "_spawnregions.lua"));
 if (this->spawnRegions.empty()) {
 this->spawnRegions = spawnRegionsx.getDefaultServerRegions();
 }

 this->spawnPoints = spawnRegionsx.loadPointsFile(
 ServerSettingsManager.instance.getNameInSettingsFolder(
 this->name + "_spawnpoints.lua"));
 return true;
 }

 bool saveFiles() {
 if (this->serverOptions.empty()) {
 return false;
 } else {
 this->serverOptions.saveServerTextFile(this->name);
 this->sandboxOptions.saveServerLuaFile(this->name);
 if (this->spawnRegions != nullptr) {
 new SpawnRegions();
 }

 if (this->spawnPoints != nullptr) {
 new SpawnRegions();
 }

 this->tryDeleteFile(this->name + "_zombies.ini");
 return true;
 }
 }

 bool tryDeleteFile(const std::string &string) {
 try {
 File file = new File(
 ServerSettingsManager.instance.getNameInSettingsFolder(string);
 if (file.exists()) {
 DebugLog.log("deleting " + file.getAbsolutePath());
 file.delete();
 }

 return true;
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 return false;
 }
 }

 bool deleteFiles() {
 this->tryDeleteFile(this->name + ".ini");
 this->tryDeleteFile(this->name + "_SandboxVars.lua");
 this->tryDeleteFile(this->name + "_spawnregions.lua");
 this->tryDeleteFile(this->name + "_spawnpoints.lua");
 this->tryDeleteFile(this->name + "_zombies.ini");
 return true;
 }

 bool duplicateFiles(const std::string &newName) {
 if (!ServerSettingsManager.instance.isValidNewName(newName) {
 return false;
 } else {
 ServerSettings serverSettings = new ServerSettings(this->name);
 serverSettings.loadFiles();
 if (serverSettings.spawnRegions != nullptr) {
 for (SpawnRegions.Region region : serverSettings.spawnRegions) {
 if (region.serverfile != nullptr &&
 region.serverfile == this->name + "_spawnpoints.lua")) {
 region.serverfile = newName + "_spawnpoints.lua";
 }
 }
 }

 serverSettings.name = newName;
 serverSettings.saveFiles();
 return true;
 }
 }

 bool rename(const std::string &newName) {
 if (!ServerSettingsManager.instance.isValidNewName(newName) {
 return false;
 } else {
 this->loadFiles();
 this->deleteFiles();
 if (this->spawnRegions != nullptr) {
 for (SpawnRegions.Region region : this->spawnRegions) {
 if (region.serverfile != nullptr &&
 region.serverfile == this->name + "_spawnpoints.lua")) {
 region.serverfile = newName + "_spawnpoints.lua";
 }
 }
 }

 this->name = newName;
 this->saveFiles();
 return true;
 }
 }

 ServerOptions getServerOptions() { return this->serverOptions; }

 SandboxOptions getSandboxOptions() { return this->sandboxOptions; }

 int getNumSpawnRegions() { return this->spawnRegions.size(); }

 std::string getSpawnRegionName(int index) {
 return this->spawnRegions.get(index).name;
 }

 std::string getSpawnRegionFile(int index) {
 SpawnRegions.Region region = this->spawnRegions.get(index);
 return region.file != nullptr ? region.file : region.serverfile;
 }

 void clearSpawnRegions() { this->spawnRegions.clear(); }

 void addSpawnRegion(const std::string &_name, const std::string &file) {
 if (_name != nullptr && file != nullptr) {
 SpawnRegions.Region region = new SpawnRegions.Region();
 region.name = _name;
 if (file.startsWith("media")) {
 region.file = file;
 } else {
 region.serverfile = file;
 }

 this->spawnRegions.add(region);
 } else {
 throw std::make_unique<NullPointerException>();
 }
 }

 void removeSpawnRegion(int index) { this->spawnRegions.remove(index); }

 KahluaTable loadSpawnPointsFile(const std::string &file) {
 SpawnRegions spawnRegionsx = new SpawnRegions();
 return spawnRegionsx.loadPointsTable(
 ServerSettingsManager.instance.getNameInSettingsFolder(file);
 }

 bool saveSpawnPointsFile(const std::string &file,
 KahluaTable professionsTable) {
 SpawnRegions spawnRegionsx = new SpawnRegions();
 return spawnRegionsx.savePointsTable(
 ServerSettingsManager.instance.getNameInSettingsFolder(file),
 professionsTable);
 }

 bool isValid() { return this->valid; }

 std::string getErrorMsg() { return this->errorMsg; }
}
} // namespace network
} // namespace zombie
