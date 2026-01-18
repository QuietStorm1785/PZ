#include "zombie/iso/IsoMetaChunk.h"

namespace zombie {
namespace iso {

float IsoMetaChunk::getZombieIntensity(bool bRandom) {
  // TODO: Implement getZombieIntensity
  return 0;
}

float IsoMetaChunk::getZombieIntensity() {
  // TODO: Implement getZombieIntensity
  return 0;
}

void IsoMetaChunk::setZombieIntensity(int zombieIntensity) {
  // TODO: Implement setZombieIntensity
}

float IsoMetaChunk::getLootZombieIntensity() {
  // TODO: Implement getLootZombieIntensity
  return 0;
}

int IsoMetaChunk::getUnadjustedZombieIntensity() {
  // TODO: Implement getUnadjustedZombieIntensity
  return 0;
}

void IsoMetaChunk::addZone(IsoMetaGrid.Zone zone) {
  // TODO: Implement addZone
}

void IsoMetaChunk::removeZone(IsoMetaGrid.Zone zone) {
  // TODO: Implement removeZone
}

void IsoMetaChunk::getZonesUnique(Set<IsoMetaGrid.Zone> result) {
  // TODO: Implement getZonesUnique
}

void IsoMetaChunk::getZonesIntersecting(int x, int y, int z, int w, int h,
                                        ArrayList<IsoMetaGrid.Zone> result) {
  // TODO: Implement getZonesIntersecting
}

void IsoMetaChunk::clearZones() {
  // TODO: Implement clearZones
}

void IsoMetaChunk::clearRooms() {
  // TODO: Implement clearRooms
}

int IsoMetaChunk::numZones() {
  // TODO: Implement numZones
  return 0;
}

void IsoMetaChunk::addRoom(RoomDef room) {
  // TODO: Implement addRoom
}

RoomDef IsoMetaChunk::getRoomAt(int x, int y, int z) {
  // TODO: Implement getRoomAt
  return nullptr;
}

RoomDef IsoMetaChunk::getEmptyOutsideAt(int x, int y, int z) {
  // TODO: Implement getEmptyOutsideAt
  return nullptr;
}

int IsoMetaChunk::getNumRooms() {
  // TODO: Implement getNumRooms
  return 0;
}

void IsoMetaChunk::getRoomsIntersecting(int x, int y, int w, int h,
                                        ArrayList<RoomDef> result) {
  // TODO: Implement getRoomsIntersecting
}

void IsoMetaChunk::Dispose() {
  // TODO: Implement Dispose
}

} // namespace iso
} // namespace zombie
