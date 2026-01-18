#include "zombie/worldMap/WorldMapBinary.h"

namespace zombie {
namespace worldMap {

bool WorldMapBinary::read(const std::string& string, WorldMapData worldMapData) {
 // TODO: Implement read
 return false;
}

int WorldMapBinary::readByte(InputStream inputStream) {
 // TODO: Implement readByte
 return 0;
}

int WorldMapBinary::readInt(InputStream inputStream) {
 // TODO: Implement readInt
 return 0;
}

int WorldMapBinary::readShort(InputStream inputStream) {
 // TODO: Implement readShort
 return 0;
}

void WorldMapBinary::readStringTable(InputStream inputStream) {
 // TODO: Implement readStringTable
}

std::string WorldMapBinary::readStringIndexed(InputStream inputStream) {
 // TODO: Implement readStringIndexed
 return "";
}

WorldMapCell WorldMapBinary::parseCell(InputStream inputStream) {
 // TODO: Implement parseCell
 return nullptr;
}

WorldMapFeature WorldMapBinary::parseFeature(WorldMapCell worldMapCell, InputStream inputStream) {
 // TODO: Implement parseFeature
 return nullptr;
}

void WorldMapBinary::parseFeatureProperties(InputStream inputStream, WorldMapFeature worldMapFeature) {
 // TODO: Implement parseFeatureProperties
}

WorldMapProperties WorldMapBinary::getOrCreateProperties(WorldMapProperties worldMapProperties0) {
 // TODO: Implement getOrCreateProperties
 return nullptr;
}

WorldMapGeometry WorldMapBinary::parseGeometry(InputStream inputStream) {
 // TODO: Implement parseGeometry
 return nullptr;
}

void WorldMapBinary::parseGeometryCoordinates(InputStream inputStream, WorldMapPoints worldMapPoints) {
 // TODO: Implement parseGeometryCoordinates
}

} // namespace worldMap
} // namespace zombie
