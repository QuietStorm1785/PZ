#include "zombie/iso/areas/IsoRoom.h"

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

IsoBuilding IsoRoom::CreateBuilding(IsoCell cell) {
  // TODO: Implement CreateBuilding
  return nullptr;
}

bool IsoRoom::isInside(int x, int y, int z) {
  // TODO: Implement isInside
  return false;
}

IsoGridSquare IsoRoom::getFreeTile() {
  // TODO: Implement getFreeTile
  return nullptr;
}

void IsoRoom::AddToBuilding(IsoBuilding buildingx) {
  // TODO: Implement AddToBuilding
}

void IsoRoom::setWaterSources(ArrayList<IsoObject> _WaterSources) {
  // TODO: Implement setWaterSources
}

bool IsoRoom::hasWater() {
  // TODO: Implement hasWater
  return false;
}

void IsoRoom::useWater() {
  // TODO: Implement useWater
}

void IsoRoom::addSquare(IsoGridSquare sq) {
  // TODO: Implement addSquare
}

void IsoRoom::refreshSquares() {
  // TODO: Implement refreshSquares
}

void IsoRoom::addExitTo(IsoGridSquare square0, IsoGridSquare square1) {
  // TODO: Implement addExitTo
}

IsoRoomExit IsoRoom::getExitAt(int int3, int int2, int int1) {
  // TODO: Implement getExitAt
  return nullptr;
}

void IsoRoom::removeSquare(IsoGridSquare sq) {
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

void IsoRoom::createLights(bool active) {
  // TODO: Implement createLights
}

RoomDef IsoRoom::getRoomDef() {
  // TODO: Implement getRoomDef
  return nullptr;
}

} // namespace areas
} // namespace iso
} // namespace zombie
