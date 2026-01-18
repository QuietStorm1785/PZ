#include "zombie/MapGroups.h"

namespace zombie {

std::string
MapGroups::addMissingVanillaDirectories(const std::string &mapName) {
  // TODO: Implement addMissingVanillaDirectories
  return "";
}

void MapGroups::createGroups() {
  // TODO: Implement createGroups
}

void MapGroups::createGroups(ActiveMods activeMods, bool includeVanilla) {
  // TODO: Implement createGroups
}

void MapGroups::createGroups(ActiveMods activeMods, bool includeVanilla,
                             bool includeChallenges) {
  // TODO: Implement createGroups
}

void MapGroups::getDirsRecursively(
    MapGroups.MapDirectory mapDirectory0,
    ArrayList<MapGroups.MapDirectory> arrayList) {
  // TODO: Implement getDirsRecursively
}

int MapGroups::getNumberOfGroups() {
  // TODO: Implement getNumberOfGroups
  return 0;
}

void MapGroups::setWorld(int groupIndex) {
  // TODO: Implement setWorld
}

void MapGroups::handleMapDirectory(const std::string &string1,
                                   const std::string &string0) {
  // TODO: Implement handleMapDirectory
}

bool MapGroups::checkMapConflicts() {
  // TODO: Implement checkMapConflicts
  return false;
}

public
MapGroups::MapDirectory(const std::string &string0,
                        const std::string &string1) {
  // TODO: Implement MapDirectory
  return nullptr;
}

public
MapGroups::MapDirectory(const std::string &string0, const std::string &string1,
                        ArrayList<String> arrayList) {
  // TODO: Implement MapDirectory
  return nullptr;
}

void MapGroups::getLotHeaders(ArrayList<String> arrayList) {
  // TODO: Implement getLotHeaders
}

void MapGroups::addDirectory(const std::string &string0,
                             const std::string &string1) {
  // TODO: Implement addDirectory
}

void MapGroups::addDirectory(const std::string &string0,
                             const std::string &string1,
                             ArrayList<String> arrayList) {
  // TODO: Implement addDirectory
}

void MapGroups::addDirectory(MapGroups.MapDirectory mapDirectory) {
  // TODO: Implement addDirectory
}

bool MapGroups::hasDirectory(const std::string &string) {
  // TODO: Implement hasDirectory
  return false;
}

bool MapGroups::hasAnyOfTheseDirectories(
    ArrayList<MapGroups.MapDirectory> arrayList) {
  // TODO: Implement hasAnyOfTheseDirectories
  return false;
}

bool MapGroups::isReferencedByOtherMaps(MapGroups.MapDirectory mapDirectory1) {
  // TODO: Implement isReferencedByOtherMaps
  return false;
}

void MapGroups::getDirsRecursively(MapGroups.MapDirectory mapDirectory0,
                                   ArrayList<String> arrayList) {
  // TODO: Implement getDirsRecursively
}

void MapGroups::setPriority() {
  // TODO: Implement setPriority
}

void MapGroups::setPriority(List<String> list) {
  // TODO: Implement setPriority
}

void MapGroups::setOrder(ActiveMods activeMods) {
  // TODO: Implement setOrder
}

bool MapGroups::checkMapConflicts() {
  // TODO: Implement checkMapConflicts
  return false;
}

} // namespace zombie
