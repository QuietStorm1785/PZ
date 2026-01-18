#include "zombie/gameStates/ChooseGameInfo.h"

namespace zombie {
namespace gameStates {

private
ChooseGameInfo::ChooseGameInfo() {
 // TODO: Implement ChooseGameInfo
 return nullptr;
}

void ChooseGameInfo::Reset() {
 // TODO: Implement Reset
}

void ChooseGameInfo::readTitleDotTxt(ChooseGameInfo.Map map,
 const std::string &string1,
 Language language) {
 // TODO: Implement readTitleDotTxt
}

void ChooseGameInfo::readDescriptionDotTxt(ChooseGameInfo.Map map,
 const std::string &string1,
 Language language) {
 // TODO: Implement readDescriptionDotTxt
}

std::string ChooseGameInfo::getDirectory() {
 // TODO: Implement getDirectory
 return "";
}

void ChooseGameInfo::setDirectory(const std::string &string) {
 // TODO: Implement setDirectory
}

Texture ChooseGameInfo::getThumbnail() {
 // TODO: Implement getThumbnail
 return nullptr;
}

void ChooseGameInfo::setThumbnail(Texture texture) {
 // TODO: Implement setThumbnail
}

std::string ChooseGameInfo::getTitle() {
 // TODO: Implement getTitle
 return "";
}

void ChooseGameInfo::setTitle(const std::string &string) {
 // TODO: Implement setTitle
}

std::string ChooseGameInfo::getDescription() {
 // TODO: Implement getDescription
 return "";
}

void ChooseGameInfo::setDescription(const std::string &string) {
 // TODO: Implement setDescription
}

bool ChooseGameInfo::isFixed2x() {
 // TODO: Implement isFixed2x
 return false;
}

void ChooseGameInfo::setFixed2x(bool boolean0) {
 // TODO: Implement setFixed2x
}

public
ChooseGameInfo::Mod(const std::string &_dir) {
 // TODO: Implement Mod
 return nullptr;
}

Texture ChooseGameInfo::getTexture() {
 // TODO: Implement getTexture
 return nullptr;
}

void ChooseGameInfo::setTexture(Texture _tex) {
 // TODO: Implement setTexture
}

int ChooseGameInfo::getPosterCount() {
 // TODO: Implement getPosterCount
 return 0;
}

std::string ChooseGameInfo::getPoster(int index) {
 // TODO: Implement getPoster
 return "";
}

std::string ChooseGameInfo::getName() {
 // TODO: Implement getName
 return "";
}

void ChooseGameInfo::setName(const std::string &_name) {
 // TODO: Implement setName
}

std::string ChooseGameInfo::getDir() {
 // TODO: Implement getDir
 return "";
}

std::string ChooseGameInfo::getDescription() {
 // TODO: Implement getDescription
 return "";
}

void ChooseGameInfo::setRequire(ArrayList<String> _require) {
 // TODO: Implement setRequire
}

std::string ChooseGameInfo::getId() {
 // TODO: Implement getId
 return "";
}

void ChooseGameInfo::setId(const std::string &_id) {
 // TODO: Implement setId
}

bool ChooseGameInfo::isAvailable() {
 // TODO: Implement isAvailable
 return false;
}

bool ChooseGameInfo::isAvailableSelf() {
 // TODO: Implement isAvailableSelf
 return false;
}

bool ChooseGameInfo::isAvailableRequired(ArrayList<String> arrayList) {
 // TODO: Implement isAvailableRequired
 return false;
}

void ChooseGameInfo::setAvailable(bool _available) {
 // TODO: Implement setAvailable
}

std::string ChooseGameInfo::getUrl() {
 // TODO: Implement getUrl
 return "";
}

void ChooseGameInfo::setUrl(const std::string &_url) {
 // TODO: Implement setUrl
}

GameVersion ChooseGameInfo::getVersionMin() {
 // TODO: Implement getVersionMin
 return nullptr;
}

GameVersion ChooseGameInfo::getVersionMax() {
 // TODO: Implement getVersionMax
 return nullptr;
}

void ChooseGameInfo::addPack(const std::string &_name, int flags) {
 // TODO: Implement addPack
}

void ChooseGameInfo::addTileDef(const std::string &_name, int fileNumber) {
 // TODO: Implement addTileDef
}

std::string ChooseGameInfo::getWorkshopID() {
 // TODO: Implement getWorkshopID
 return "";
}

public
ChooseGameInfo::PackFile(const std::string &string, int int0) {
 // TODO: Implement PackFile
 return nullptr;
}

public
ChooseGameInfo::SpawnOrigin(int int0, int int1, int int2, int int3) {
 // TODO: Implement SpawnOrigin
 return nullptr;
}

public
ChooseGameInfo::TileDef(const std::string &string, int int0) {
 // TODO: Implement TileDef
 return nullptr;
}

} // namespace gameStates
} // namespace zombie
