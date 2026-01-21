#include <string>
#include <vector>
#include "zombie/worldMap/WorldMapData.h"

namespace zombie {
namespace worldMap {

WorldMapData WorldMapData::getOrCreateData(const std::string& var0) {
    // TODO: Implement getOrCreateData
    return nullptr;
}

public WorldMapData::WorldMapData(AssetPath var1, AssetManager var2) {
    // TODO: Implement WorldMapData
    return nullptr;
}

public WorldMapData::WorldMapData(AssetPath var1, AssetManager var2, AssetParams var3) {
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

WorldMapCell WorldMapData::getCell(int var1, int var2) {
    // TODO: Implement getCell
    return nullptr;
}

int WorldMapData::getCellKey(int var1, int var2) {
    // TODO: Implement getCellKey
    return 0;
}

void WorldMapData::hitTest(float var1, float var2, std::vector<WorldMapFeature> var3) {
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
