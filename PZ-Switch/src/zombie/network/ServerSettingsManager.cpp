#include "zombie/network/ServerSettingsManager.h"

namespace zombie {
namespace network {

std::string ServerSettingsManager::getSettingsFolder() {
 // TODO: Implement getSettingsFolder
 return "";
}

std::string
ServerSettingsManager::getNameInSettingsFolder(const std::string &name) {
 // TODO: Implement getNameInSettingsFolder
 return "";
}

void ServerSettingsManager::readAllSettings() {
 // TODO: Implement readAllSettings
}

bool ServerSettingsManager::accept(Path path) {
 // TODO: Implement accept
 return false;
}

int ServerSettingsManager::getSettingsCount() {
 // TODO: Implement getSettingsCount
 return 0;
}

ServerSettings ServerSettingsManager::getSettingsByIndex(int index) {
 // TODO: Implement getSettingsByIndex
 return nullptr;
}

bool ServerSettingsManager::isValidName(const std::string &name) {
 // TODO: Implement isValidName
 return false;
}

bool ServerSettingsManager::anyFilesExist(const std::string &string) {
 // TODO: Implement anyFilesExist
 return false;
}

bool ServerSettingsManager::isValidNewName(const std::string &newName) {
 // TODO: Implement isValidNewName
 return false;
}

} // namespace network
} // namespace zombie
