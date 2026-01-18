#include "zombie/network/ServerSettings.h"

namespace zombie {
namespace network {

public ServerSettings::ServerSettings(const std::string& _name) {
 // TODO: Implement ServerSettings
 return nullptr;
}

std::string ServerSettings::getName() {
 // TODO: Implement getName
 return "";
}

void ServerSettings::resetToDefault() {
 // TODO: Implement resetToDefault
}

bool ServerSettings::loadFiles() {
 // TODO: Implement loadFiles
 return false;
}

bool ServerSettings::saveFiles() {
 // TODO: Implement saveFiles
 return false;
}

new ServerSettings::SpawnRegions() {
 // TODO: Implement SpawnRegions
 return nullptr;
}

new ServerSettings::SpawnRegions() {
 // TODO: Implement SpawnRegions
 return nullptr;
}

bool ServerSettings::tryDeleteFile(const std::string& string) {
 // TODO: Implement tryDeleteFile
 return false;
}

bool ServerSettings::deleteFiles() {
 // TODO: Implement deleteFiles
 return false;
}

bool ServerSettings::duplicateFiles(const std::string& newName) {
 // TODO: Implement duplicateFiles
 return false;
}

bool ServerSettings::rename(const std::string& newName) {
 // TODO: Implement rename
 return false;
}

ServerOptions ServerSettings::getServerOptions() {
 // TODO: Implement getServerOptions
 return nullptr;
}

SandboxOptions ServerSettings::getSandboxOptions() {
 // TODO: Implement getSandboxOptions
 return nullptr;
}

int ServerSettings::getNumSpawnRegions() {
 // TODO: Implement getNumSpawnRegions
 return 0;
}

std::string ServerSettings::getSpawnRegionName(int index) {
 // TODO: Implement getSpawnRegionName
 return "";
}

std::string ServerSettings::getSpawnRegionFile(int index) {
 // TODO: Implement getSpawnRegionFile
 return "";
}

void ServerSettings::clearSpawnRegions() {
 // TODO: Implement clearSpawnRegions
}

void ServerSettings::addSpawnRegion(const std::string& _name, const std::string& file) {
 // TODO: Implement addSpawnRegion
}

void ServerSettings::removeSpawnRegion(int index) {
 // TODO: Implement removeSpawnRegion
}

KahluaTable ServerSettings::loadSpawnPointsFile(const std::string& file) {
 // TODO: Implement loadSpawnPointsFile
 return nullptr;
}

bool ServerSettings::saveSpawnPointsFile(const std::string& file, KahluaTable professionsTable) {
 // TODO: Implement saveSpawnPointsFile
 return false;
}

bool ServerSettings::isValid() {
 // TODO: Implement isValid
 return false;
}

std::string ServerSettings::getErrorMsg() {
 // TODO: Implement getErrorMsg
 return "";
}

} // namespace network
} // namespace zombie
