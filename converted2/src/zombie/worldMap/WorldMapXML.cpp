#include "zombie/worldMap/WorldMapXML.h"

namespace zombie {
namespace worldMap {

bool WorldMapXML::read(const std::string &string, WorldMapData worldMapData) {
  // TODO: Implement read
  return false;
}

void WorldMapXML::parseWorld(Element element, WorldMapData worldMapData) {
  // TODO: Implement parseWorld
}

WorldMapCell WorldMapXML::parseCell(Element element) {
  // TODO: Implement parseCell
  return nullptr;
}

WorldMapFeature WorldMapXML::parseFeature(WorldMapCell worldMapCell,
                                          Element element) {
  // TODO: Implement parseFeature
  return nullptr;
}

void WorldMapXML::parseFeatureProperties(Element element,
                                         WorldMapFeature worldMapFeature) {
  // TODO: Implement parseFeatureProperties
}

WorldMapProperties
WorldMapXML::getOrCreateProperties(WorldMapProperties worldMapProperties0) {
  // TODO: Implement getOrCreateProperties
  return nullptr;
}

WorldMapGeometry WorldMapXML::parseGeometry(Element element) {
  // TODO: Implement parseGeometry
  return nullptr;
}

void WorldMapXML::parseGeometryCoordinates(Element element,
                                           WorldMapPoints worldMapPoints) {
  // TODO: Implement parseGeometryCoordinates
}

WorldMapPoint WorldMapXML::parsePoint(Element element,
                                      WorldMapPoint worldMapPoint) {
  // TODO: Implement parsePoint
  return nullptr;
}

} // namespace worldMap
} // namespace zombie
