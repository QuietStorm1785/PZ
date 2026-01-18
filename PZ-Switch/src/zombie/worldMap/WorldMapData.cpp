#include "zombie/worldMap/WorldMapData.h"

namespace zombie {
namespace worldMap {

WorldMapData WorldMapData::getOrCreateData(const std::string &fileName) {
 // TODO: Implement getOrCreateData
 return nullptr;
}

public
WorldMapData::WorldMapData(AssetPath path, AssetManager manager) {
 // TODO: Implement WorldMapData
 return nullptr;
}

public
WorldMapData::WorldMapData(AssetPath path, AssetManager manager,
 AssetManager.AssetParams params) {
 // TODO: Implement WorldMapData
 return nullptr;
}

void WorldMapData::clear() {
 // TODO: Implement clear
}

int WorldMapData::getWidthInCells() {
 // TODO: Implement getWidthInCells
 return 0;
}

int WorldMapData::getHeightInCells() {
 // TODO: Implement getHeightInCells
 return 0;
}

int WorldMapData::getWidthInSquares() {
 // TODO: Implement getWidthInSquares
 return 0;
}

int WorldMapData::getHeightInSquares() {
 // TODO: Implement getHeightInSquares
 return 0;
}

void WorldMapData::onLoaded() {
 // TODO: Implement onLoaded
}

WorldMapCell WorldMapData::getCell(int x, int y) {
 // TODO: Implement getCell
 return nullptr;
}

int WorldMapData::getCellKey(int int0, int int1) {
 // TODO: Implement getCellKey
 return 0;
}

void WorldMapData::hitTest(float x, float y,
 ArrayList<WorldMapFeature> features) {
 // TODO: Implement hitTest
}

void WorldMapData::Reset() {
 // TODO: Implement Reset
}

AssetType WorldMapData::getType() {
 // TODO: Implement getType
 return {};
}

void WorldMapData::onBeforeEmpty() {
 // TODO: Implement onBeforeEmpty
}

} // namespace worldMap
} // namespace zombie
