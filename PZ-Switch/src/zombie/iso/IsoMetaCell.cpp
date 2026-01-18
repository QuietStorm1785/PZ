#include "zombie/iso/IsoMetaCell.h"

namespace zombie {
namespace iso {

public
IsoMetaCell::IsoMetaCell(int _wx, int _wy) {
 // TODO: Implement IsoMetaCell
 return nullptr;
}

void IsoMetaCell::addTrigger(BuildingDef def, int triggerRange,
 int zombieExclusionRange,
 const std::string &type) {
 // TODO: Implement addTrigger
}

void IsoMetaCell::checkTriggers() {
 // TODO: Implement checkTriggers
}

IsoMetaChunk IsoMetaCell::getChunk(int x, int y) {
 // TODO: Implement getChunk
 return nullptr;
}

void IsoMetaCell::addZone(IsoMetaGrid.Zone zone, int cellX, int cellY) {
 // TODO: Implement addZone
}

void IsoMetaCell::removeZone(IsoMetaGrid.Zone zone) {
 // TODO: Implement removeZone
}

void IsoMetaCell::addRoom(RoomDef room, int cellX, int cellY) {
 // TODO: Implement addRoom
}

void IsoMetaCell::getZonesUnique(Set<IsoMetaGrid.Zone> result) {
 // TODO: Implement getZonesUnique
}

void IsoMetaCell::getZonesIntersecting(int x, int y, int z, int w, int h,
 ArrayList<IsoMetaGrid.Zone> result) {
 // TODO: Implement getZonesIntersecting
}

void IsoMetaCell::getRoomsIntersecting(int x, int y, int w, int h,
 ArrayList<RoomDef> result) {
 // TODO: Implement getRoomsIntersecting
}

void IsoMetaCell::Dispose() {
 // TODO: Implement Dispose
}

} // namespace iso
} // namespace zombie
