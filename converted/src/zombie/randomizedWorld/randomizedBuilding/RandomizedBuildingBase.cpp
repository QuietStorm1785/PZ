#include "zombie/randomizedWorld/randomizedBuilding/RandomizedBuildingBase.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedBuilding {

void RandomizedBuildingBase::randomizeBuilding(BuildingDef def) {
  // TODO: Implement randomizeBuilding
}

void RandomizedBuildingBase::init() {
  // TODO: Implement init
}

void RandomizedBuildingBase::initAllRBMapChance() {
  // TODO: Implement initAllRBMapChance
}

bool RandomizedBuildingBase::isValid(BuildingDef def, bool force) {
  // TODO: Implement isValid
  return false;
}

void RandomizedBuildingBase::customizeStartingHouse(BuildingDef var1) {
  // TODO: Implement customizeStartingHouse
}

int RandomizedBuildingBase::getMinimumDays() {
  // TODO: Implement getMinimumDays
  return 0;
}

void RandomizedBuildingBase::setMinimumDays(int minimumDays) {
  // TODO: Implement setMinimumDays
}

int RandomizedBuildingBase::getMinimumRooms() {
  // TODO: Implement getMinimumRooms
  return 0;
}

void RandomizedBuildingBase::setMinimumRooms(int minimumRooms) {
  // TODO: Implement setMinimumRooms
}

void RandomizedBuildingBase::ChunkLoaded(IsoBuilding building) {
  // TODO: Implement ChunkLoaded
}

int RandomizedBuildingBase::getChance() {
  // TODO: Implement getChance
  return 0;
}

void RandomizedBuildingBase::setChance(int _chance) {
  // TODO: Implement setChance
}

bool RandomizedBuildingBase::isAlwaysDo() {
  // TODO: Implement isAlwaysDo
  return false;
}

void RandomizedBuildingBase::setAlwaysDo(bool _alwaysDo) {
  // TODO: Implement setAlwaysDo
}

RandomizedBuildingBase RandomizedBuildingBase::getRandomStory() {
  // TODO: Implement getRandomStory
  return nullptr;
}

HandWeapon RandomizedBuildingBase::addRandomRangedWeapon(
    ItemContainer container, bool addBulletsInGun, bool addBoxInContainer,
    bool attachPart) {
  // TODO: Implement addRandomRangedWeapon
  return nullptr;
}

void RandomizedBuildingBase::spawnItemsInContainers(
    BuildingDef def, const std::string &distribName, int _chance) {
  // TODO: Implement spawnItemsInContainers
}

void RandomizedBuildingBase::removeAllZombies(BuildingDef buildingDef) {
  // TODO: Implement removeAllZombies
}

IsoWindow RandomizedBuildingBase::getWindow(IsoGridSquare sq) {
  // TODO: Implement getWindow
  return nullptr;
}

IsoDoor RandomizedBuildingBase::getDoor(IsoGridSquare sq) {
  // TODO: Implement getDoor
  return nullptr;
}

void RandomizedBuildingBase::addBarricade(IsoGridSquare sq, int numPlanks) {
  // TODO: Implement addBarricade
}

InventoryItem RandomizedBuildingBase::addWorldItem(const std::string &item,
                                                   IsoGridSquare sq,
                                                   float xoffset, float yoffset,
                                                   float zoffset) {
  // TODO: Implement addWorldItem
  return nullptr;
}

InventoryItem RandomizedBuildingBase::addWorldItem(const std::string &item,
                                                   IsoGridSquare sq,
                                                   float xoffset, float yoffset,
                                                   float zoffset, int worldZ) {
  // TODO: Implement addWorldItem
  return nullptr;
}

InventoryItem RandomizedBuildingBase::addWorldItem(const std::string &item,
                                                   IsoGridSquare sq,
                                                   IsoObject obj) {
  // TODO: Implement addWorldItem
  return nullptr;
}

bool RandomizedBuildingBase::isTableFor3DItems(IsoObject obj,
                                               IsoGridSquare sq) {
  // TODO: Implement isTableFor3DItems
  return false;
}

public
RandomizedBuildingBase::HumanCorpse(IsoCell cell, float float0, float float1,
                                    float float2) {
  // TODO: Implement HumanCorpse
  return nullptr;
}

void RandomizedBuildingBase::dressInNamedOutfit(const std::string &string) {
  // TODO: Implement dressInNamedOutfit
}

HumanVisual RandomizedBuildingBase::getHumanVisual() {
  // TODO: Implement getHumanVisual
  return nullptr;
}

HumanVisual RandomizedBuildingBase::getVisual() {
  // TODO: Implement getVisual
  return nullptr;
}

void RandomizedBuildingBase::Dressup(SurvivorDesc var1) {
  // TODO: Implement Dressup
}

bool RandomizedBuildingBase::isSkeleton() {
  // TODO: Implement isSkeleton
  return false;
}

} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
