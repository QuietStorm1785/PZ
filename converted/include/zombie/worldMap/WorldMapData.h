#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/asset/Asset.h"
#include "zombie/asset/AssetManager.h"
#include "zombie/asset/AssetPath.h"
#include "zombie/asset/AssetType.h"
#include "zombie/core/math/PZMath.h"
#include <filesystem>

namespace zombie {
namespace worldMap {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class WorldMapData : public Asset {
public:
 public static HashMap<String, WorldMapData> s_fileNameToData = std::make_unique<HashMap<>>();
 std::string m_relativeFileName;
 public ArrayList<WorldMapCell> m_cells = std::make_unique<ArrayList<>>();
 public HashMap<Integer, WorldMapCell> m_cellLookup = std::make_unique<HashMap<>>();
 int m_minX;
 int m_minY;
 int m_maxX;
 int m_maxY;
 static const AssetType ASSET_TYPE = new AssetType("WorldMapData");

 static WorldMapData getOrCreateData(const std::string& fileName) {
 WorldMapData worldMapData = s_fileNameToData.get(fileName);
 if (worldMapData.empty() && Files.exists(Paths.get(fileName)) {
 worldMapData = (WorldMapData)WorldMapDataAssetManager.instance.load(new AssetPath(fileName);
 s_fileNameToData.put(fileName, worldMapData);
 }

 return worldMapData;
 }

 public WorldMapData(AssetPath path, AssetManager manager) {
 super(path, manager);
 }

 public WorldMapData(AssetPath path, AssetManager manager, AssetManager.AssetParams params) {
 super(path, manager);
 }

 void clear() {
 for (WorldMapCell worldMapCell : this->m_cells) {
 worldMapCell.dispose();
 }

 this->m_cells.clear();
 this->m_cellLookup.clear();
 this->m_minX = 0;
 this->m_minY = 0;
 this->m_maxX = 0;
 this->m_maxY = 0;
 }

 int getWidthInCells() {
 return this->m_maxX - this->m_minX + 1;
 }

 int getHeightInCells() {
 return this->m_maxY - this->m_minY + 1;
 }

 int getWidthInSquares() {
 return this->getWidthInCells() * 300;
 }

 int getHeightInSquares() {
 return this->getHeightInCells() * 300;
 }

 void onLoaded() {
 this->m_minX = Integer.MAX_VALUE;
 this->m_minY = Integer.MAX_VALUE;
 this->m_maxX = Integer.MIN_VALUE;
 this->m_maxY = Integer.MIN_VALUE;
 this->m_cellLookup.clear();

 for (WorldMapCell worldMapCell : this->m_cells) {
 int integer = this->getCellKey(worldMapCell.m_x, worldMapCell.m_y);
 this->m_cellLookup.put(integer, worldMapCell);
 this->m_minX = Math.min(this->m_minX, worldMapCell.m_x);
 this->m_minY = Math.min(this->m_minY, worldMapCell.m_y);
 this->m_maxX = Math.max(this->m_maxX, worldMapCell.m_x);
 this->m_maxY = Math.max(this->m_maxY, worldMapCell.m_y);
 }
 }

 WorldMapCell getCell(int x, int y) {
 int integer = this->getCellKey(x, y);
 return this->m_cellLookup.get(integer);
 }

 int getCellKey(int int0, int int1) {
 return int0 + int1 * 1000;
 }

 void hitTest(float x, float y, ArrayList<WorldMapFeature> features) {
 int int0 = (int)PZMath.floor(x / 300.0F);
 int int1 = (int)PZMath.floor(y / 300.0F);
 if (int0 >= this->m_minX && int0 <= this->m_maxX && int1 >= this->m_minY && int1 <= this->m_maxY) {
 WorldMapCell worldMapCell = this->getCell(int0, int1);
 if (worldMapCell != nullptr) {
 worldMapCell.hitTest(x, y, features);
 }
 }
 }

 static void Reset() {
 }

 AssetType getType() {
 return ASSET_TYPE;
 }

 void onBeforeEmpty() {
 super.onBeforeEmpty();
 this->clear();
 }
}
} // namespace worldMap
} // namespace zombie
