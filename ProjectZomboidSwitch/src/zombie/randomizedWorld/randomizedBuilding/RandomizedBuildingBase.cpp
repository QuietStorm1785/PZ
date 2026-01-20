#include <string>
#include "zombie\randomizedWorld\randomizedBuilding/RandomizedBuildingBase.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedBuilding {

void RandomizedBuildingBase::randomizeBuilding(BuildingDef var1) {
    // TODO: Implement randomizeBuilding
}

void RandomizedBuildingBase::init() {
    // TODO: Implement init
}

void RandomizedBuildingBase::initAllRBMapChance() {
    // TODO: Implement initAllRBMapChance
}

bool RandomizedBuildingBase::isValid(BuildingDef var1, bool var2) {
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

void RandomizedBuildingBase::setMinimumDays(int var1) {
    // TODO: Implement setMinimumDays
}

int RandomizedBuildingBase::getMinimumRooms() {
    // TODO: Implement getMinimumRooms
    return 0;
}

void RandomizedBuildingBase::setMinimumRooms(int var1) {
    // TODO: Implement setMinimumRooms
}

void RandomizedBuildingBase::ChunkLoaded(IsoBuilding var0) {
    // TODO: Implement ChunkLoaded
}

int RandomizedBuildingBase::getChance() {
    // TODO: Implement getChance
    return 0;
}

void RandomizedBuildingBase::setChance(int var1) {
    // TODO: Implement setChance
}

bool RandomizedBuildingBase::isAlwaysDo() {
    // TODO: Implement isAlwaysDo
    return false;
}

void RandomizedBuildingBase::setAlwaysDo(bool var1) {
    // TODO: Implement setAlwaysDo
}

RandomizedBuildingBase RandomizedBuildingBase::getRandomStory() {
    // TODO: Implement getRandomStory
    return nullptr;
}

HandWeapon RandomizedBuildingBase::addRandomRangedWeapon(ItemContainer var1, bool var2, bool var3, bool var4) {
    // TODO: Implement addRandomRangedWeapon
    return nullptr;
}

void RandomizedBuildingBase::spawnItemsInContainers(BuildingDef var1, const std::string& var2, int var3) {
    // TODO: Implement spawnItemsInContainers
}

void RandomizedBuildingBase::removeAllZombies(BuildingDef var1) {
    // TODO: Implement removeAllZombies
}

IsoWindow RandomizedBuildingBase::getWindow(IsoGridSquare var1) {
    // TODO: Implement getWindow
    return nullptr;
}

IsoDoor RandomizedBuildingBase::getDoor(IsoGridSquare var1) {
    // TODO: Implement getDoor
    return nullptr;
}

void RandomizedBuildingBase::addBarricade(IsoGridSquare var1, int var2) {
    // TODO: Implement addBarricade
}

InventoryItem RandomizedBuildingBase::addWorldItem(const std::string& var1, IsoGridSquare var2, float var3, float var4, float var5) {
    // TODO: Implement addWorldItem
    return nullptr;
}

InventoryItem RandomizedBuildingBase::addWorldItem(const std::string& var1, IsoGridSquare var2, float var3, float var4, float var5, int var6) {
    // TODO: Implement addWorldItem
    return nullptr;
}

InventoryItem RandomizedBuildingBase::addWorldItem(const std::string& var1, IsoGridSquare var2, IsoObject var3) {
    // TODO: Implement addWorldItem
    return nullptr;
}

bool RandomizedBuildingBase::isTableFor3DItems(IsoObject var1, IsoGridSquare var2) {
    // TODO: Implement isTableFor3DItems
    return false;
}

} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
