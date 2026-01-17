#include "zombie/VirtualZombieManager.h"

namespace zombie {

bool VirtualZombieManager::removeZombieFromWorld(IsoZombie z) {
  // TODO: Implement removeZombieFromWorld
  return false;
}

void VirtualZombieManager::reuseZombie(IsoZombie zombie0) {
  // TODO: Implement reuseZombie
}

void VirtualZombieManager::addToReusable(IsoZombie z) {
  // TODO: Implement addToReusable
}

bool VirtualZombieManager::isReused(IsoZombie z) {
  // TODO: Implement isReused
  return false;
}

void VirtualZombieManager::init() {
  // TODO: Implement init
}

void VirtualZombieManager::Reset() {
  // TODO: Implement Reset
}

void VirtualZombieManager::update() {
  // TODO: Implement update
}

IsoZombie VirtualZombieManager::createRealZombieAlways(int ZombieDir,
                                                       bool bDead) {
  // TODO: Implement createRealZombieAlways
  return nullptr;
}

IsoZombie VirtualZombieManager::createRealZombieAlways(int descriptorID,
                                                       int ZombieDir,
                                                       bool bDead) {
  // TODO: Implement createRealZombieAlways
  return nullptr;
}

IsoZombie VirtualZombieManager::createRealZombieAlways(int ZombieDir,
                                                       bool bDead,
                                                       int outfitID) {
  // TODO: Implement createRealZombieAlways
  return nullptr;
}

new VirtualZombieManager::IsoDeadBody() {
  // TODO: Implement IsoDeadBody
  return nullptr;
}

IsoGridSquare VirtualZombieManager::pickEatingZombieSquare(
    float float2, float float3, float float1, float float0, int int0) {
  // TODO: Implement pickEatingZombieSquare
  return nullptr;
}

void VirtualZombieManager::createEatingZombies(IsoDeadBody target, int nb) {
  // TODO: Implement createEatingZombies
}

IsoZombie VirtualZombieManager::createRealZombie(int int0, bool boolean0) {
  // TODO: Implement createRealZombie
  return nullptr;
}

void VirtualZombieManager::AddBloodToMap(int nSize, IsoChunk chk) {
  // TODO: Implement AddBloodToMap
}

void VirtualZombieManager::tryAddIndoorZombies(RoomDef room, bool bAllowDead) {
  // TODO: Implement tryAddIndoorZombies
}

void VirtualZombieManager::addIndoorZombies(int int4, RoomDef roomDef,
                                            bool boolean0) {
  // TODO: Implement addIndoorZombies
}

void VirtualZombieManager::addIndoorZombiesToChunk(
    IsoChunk chunk, IsoRoom room, int zombieCountForRoom,
    ArrayList<IsoZombie> zombies) {
  // TODO: Implement addIndoorZombiesToChunk
}

void VirtualZombieManager::addIndoorZombiesToChunk(IsoChunk chunk,
                                                   IsoRoom room) {
  // TODO: Implement addIndoorZombiesToChunk
}

void VirtualZombieManager::addDeadZombiesToMap(int nSize, RoomDef room) {
  // TODO: Implement addDeadZombiesToMap
}

void VirtualZombieManager::RemoveZombie(IsoZombie obj) {
  // TODO: Implement RemoveZombie
}

void VirtualZombieManager::createHordeFromTo(float spawnX, float spawnY,
                                             float targetX, float targetY,
                                             int count) {
  // TODO: Implement createHordeFromTo
}

IsoZombie VirtualZombieManager::createRealZombie(float x, float y, float z) {
  // TODO: Implement createRealZombie
  return nullptr;
}

IsoZombie VirtualZombieManager::createRealZombieNow(float x, float y, float z) {
  // TODO: Implement createRealZombieNow
  return nullptr;
}

int VirtualZombieManager::getZombieCountForRoom(IsoRoom room) {
  // TODO: Implement getZombieCountForRoom
  return 0;
}

void VirtualZombieManager::roomSpotted(IsoRoom room) {
  // TODO: Implement roomSpotted
}

int VirtualZombieManager::getBlockedBits(IsoGridSquare square) {
  // TODO: Implement getBlockedBits
  return 0;
}

bool VirtualZombieManager::isBlockedInAllDirections(int int0, int int1,
                                                    int int2) {
  // TODO: Implement isBlockedInAllDirections
  return false;
}

bool VirtualZombieManager::canPathOnlyN(IsoGridSquare square) {
  // TODO: Implement canPathOnlyN
  return false;
}

bool VirtualZombieManager::canPathOnlyS(IsoGridSquare square) {
  // TODO: Implement canPathOnlyS
  return false;
}

bool VirtualZombieManager::canPathOnlyW(IsoGridSquare square) {
  // TODO: Implement canPathOnlyW
  return false;
}

bool VirtualZombieManager::canPathOnlyE(IsoGridSquare square) {
  // TODO: Implement canPathOnlyE
  return false;
}

bool VirtualZombieManager::canSpawnAt(int x, int y, int z) {
  // TODO: Implement canSpawnAt
  return false;
}

int VirtualZombieManager::reusableZombiesSize() {
  // TODO: Implement reusableZombiesSize
  return 0;
}

} // namespace zombie
