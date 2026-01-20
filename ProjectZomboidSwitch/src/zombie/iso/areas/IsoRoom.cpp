#include <string>
#include <vector>
#include "zombie\iso\areas/IsoRoom.h"

namespace zombie {
namespace iso {
namespace areas {

IsoBuilding IsoRoom::getBuilding() {
    // TODO: Implement getBuilding
    return nullptr;
}

std::string IsoRoom::getName() {
    // TODO: Implement getName
    return "";
}

IsoBuilding IsoRoom::CreateBuilding(IsoCell var1) {
    // TODO: Implement CreateBuilding
    return nullptr;
}

bool IsoRoom::isInside(int var1, int var2, int var3) {
    // TODO: Implement isInside
    return false;
}

IsoGridSquare IsoRoom::getFreeTile() {
    // TODO: Implement getFreeTile
    return nullptr;
}

void IsoRoom::AddToBuilding(IsoBuilding var1) {
    // TODO: Implement AddToBuilding
}

void IsoRoom::setWaterSources(std::vector<IsoObject> var1) {
    // TODO: Implement setWaterSources
}

bool IsoRoom::hasWater() {
    // TODO: Implement hasWater
    return false;
}

void IsoRoom::useWater() {
    // TODO: Implement useWater
}

void IsoRoom::addSquare(IsoGridSquare var1) {
    // TODO: Implement addSquare
}

void IsoRoom::refreshSquares() {
    // TODO: Implement refreshSquares
}

void IsoRoom::addExitTo(IsoGridSquare var1, IsoGridSquare var2) {
    // TODO: Implement addExitTo
}

IsoRoomExit IsoRoom::getExitAt(int var1, int var2, int var3) {
    // TODO: Implement getExitAt
    return nullptr;
}

void IsoRoom::removeSquare(IsoGridSquare var1) {
    // TODO: Implement removeSquare
}

void IsoRoom::spawnZombies() {
    // TODO: Implement spawnZombies
}

void IsoRoom::onSee() {
    // TODO: Implement onSee
}

IsoGridSquare IsoRoom::getRandomSquare() {
    // TODO: Implement getRandomSquare
    return nullptr;
}

IsoGridSquare IsoRoom::getRandomFreeSquare() {
    // TODO: Implement getRandomFreeSquare
    return nullptr;
}

bool IsoRoom::hasLightSwitches() {
    // TODO: Implement hasLightSwitches
    return false;
}

void IsoRoom::createLights(bool var1) {
    // TODO: Implement createLights
}

RoomDef IsoRoom::getRoomDef() {
    // TODO: Implement getRoomDef
    return nullptr;
}

} // namespace areas
} // namespace iso
} // namespace zombie
