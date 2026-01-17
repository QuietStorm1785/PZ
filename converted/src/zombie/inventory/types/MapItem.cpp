#include "zombie/inventory/types/MapItem.h"

namespace zombie {
namespace inventory {
namespace types {

MapItem MapItem::getSingleton() {
  // TODO: Implement getSingleton
  return nullptr;
}

void MapItem::SaveWorldMap() {
  // TODO: Implement SaveWorldMap
}

void MapItem::LoadWorldMap() {
  // TODO: Implement LoadWorldMap
}

void MapItem::Reset() {
  // TODO: Implement Reset
}

public
MapItem::MapItem(const std::string &module, const std::string &name,
                 const std::string &type, const std::string &tex) {
  // TODO: Implement MapItem
  return nullptr;
}

public
MapItem::MapItem(const std::string &module, const std::string &name,
                 const std::string &type, Item item) {
  // TODO: Implement MapItem
  return nullptr;
}

int MapItem::getSaveType() {
  // TODO: Implement getSaveType
  return 0;
}

bool MapItem::IsMap() {
  // TODO: Implement IsMap
  return false;
}

void MapItem::setMapID(const std::string &mapID) {
  // TODO: Implement setMapID
}

std::string MapItem::getMapID() {
  // TODO: Implement getMapID
  return "";
}

WorldMapSymbols MapItem::getSymbols() {
  // TODO: Implement getSymbols
  return nullptr;
}

void MapItem::save(ByteBuffer output, bool net) {
  // TODO: Implement save
}

void MapItem::load(ByteBuffer input, int WorldVersion) {
  // TODO: Implement load
}

} // namespace types
} // namespace inventory
} // namespace zombie
