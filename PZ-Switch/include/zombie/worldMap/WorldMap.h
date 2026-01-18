#pragma once
#include "zombie/ZomboidFileSystem.h"
#include "zombie/asset/Asset.h"
#include "zombie/asset/AssetStateObserver.h"
#include "zombie/inventory/types/MapItem.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/util/StringUtils.h"
#include "zombie/worldMap/symbols/MapSymbolDefinitions.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace worldMap {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class WorldMap {
public:
public
 ArrayList<WorldMapData> m_data = std::make_unique<ArrayList<>>();
public
 ArrayList<WorldMapImages> m_images = std::make_unique<ArrayList<>>();
 int m_minDataX;
 int m_minDataY;
 int m_maxDataX;
 int m_maxDataY;
 int m_minX;
 int m_minY;
 int m_maxX;
 int m_maxY;
 bool m_boundsFromData = false;
public
 ArrayList<WorldMapData> m_lastDataInDirectory =
 std::make_unique<ArrayList<>>();

 void setBoundsInCells(int minX, int minY, int maxX, int maxY) {
 this->setBoundsInSquares(minX * 300, minY * 300, maxX * 300 + 299,
 maxY * 300 + 299);
 }

 void setBoundsInSquares(int minX, int minY, int maxX, int maxY) {
 this->m_minX = minX;
 this->m_minY = minY;
 this->m_maxX = maxX;
 this->m_maxY = maxY;
 }

 void setBoundsFromData() {
 this->m_boundsFromData = true;
 this->setBoundsInCells(this->m_minDataX, this->m_minDataY, this->m_maxDataX,
 this->m_maxDataY);
 }

 void setBoundsFromWorld() {
 IsoMetaGrid metaGrid = IsoWorld.instance.getMetaGrid();
 this->setBoundsInCells(metaGrid.getMinX(), metaGrid.getMinY(),
 metaGrid.getMaxX(), metaGrid.getMaxY());
 }

 void addData(const std::string &fileName) {
 if (!StringUtils.isNullOrWhitespace(fileName) {
 std::string string = ZomboidFileSystem.instance.getString(fileName);
 WorldMapData worldMapData = WorldMapData.getOrCreateData(string);
 if (worldMapData != nullptr && !this->m_data.contains(worldMapData) {
 worldMapData.m_relativeFileName = fileName;
 this->m_data.add(worldMapData);
 worldMapData.getObserverCb().add(this);
 if (worldMapData.isReady()) {
 this->updateDataBounds();
 }
 }
 }
 }

 int getDataCount() { return this->m_data.size(); }

 WorldMapData getDataByIndex(int index) { return this->m_data.get(index); }

 void clearData() {
 for (WorldMapData worldMapData : this->m_data) {
 worldMapData.getObserverCb().remove(this);
 }

 this->m_data.clear();
 this->m_lastDataInDirectory.clear();
 this->updateDataBounds();
 }

 void endDirectoryData() {
 if (this->hasData()) {
 WorldMapData worldMapData = this->getDataByIndex(this->getDataCount() - 1);
 if (!this->m_lastDataInDirectory.contains(worldMapData) {
 this->m_lastDataInDirectory.add(worldMapData);
 }
 }
 }

 bool isLastDataInDirectory(WorldMapData data) {
 return this->m_lastDataInDirectory.contains(data);
 }

 void updateDataBounds() {
 this->m_minDataX = Integer.MAX_VALUE;
 this->m_minDataY = Integer.MAX_VALUE;
 this->m_maxDataX = Integer.MIN_VALUE;
 this->m_maxDataY = Integer.MIN_VALUE;

 for (int int0 = 0; int0 < this->m_data.size(); int0++) {
 WorldMapData worldMapData = this->m_data.get(int0);
 if (worldMapData.isReady()) {
 this->m_minDataX = Math.min(this->m_minDataX, worldMapData.m_minX);
 this->m_minDataY = Math.min(this->m_minDataY, worldMapData.m_minY);
 this->m_maxDataX = Math.max(this->m_maxDataX, worldMapData.m_maxX);
 this->m_maxDataY = Math.max(this->m_maxDataY, worldMapData.m_maxY);
 }
 }

 if (this->m_minDataX > this->m_maxDataX) {
 this->m_minDataX = this->m_maxDataX = this->m_minDataY = this->m_maxDataY = 0;
 }
 }

 bool hasData() { return !this->m_data.empty(); }

 void addImages(const std::string &directory) {
 if (!StringUtils.isNullOrWhitespace(directory) {
 WorldMapImages worldMapImages = WorldMapImages.getOrCreate(directory);
 if (worldMapImages != nullptr &&
 !this->m_images.contains(worldMapImages) {
 this->m_images.add(worldMapImages);
 }
 }
 }

 bool hasImages() { return !this->m_images.empty(); }

 int getImagesCount() { return this->m_images.size(); }

 WorldMapImages getImagesByIndex(int index) {
 return this->m_images.get(index);
 }

 int getMinXInCells() { return this->m_minX / 300; }

 int getMinYInCells() { return this->m_minY / 300; }

 int getMaxXInCells() { return this->m_maxX / 300; }

 int getMaxYInCells() { return this->m_maxY / 300; }

 int getWidthInCells() {
 return this->getMaxXInCells() - this->getMinXInCells() + 1;
 }

 int getHeightInCells() {
 return this->getMaxYInCells() - this->getMinYInCells() + 1;
 }

 int getMinXInSquares() { return this->m_minX; }

 int getMinYInSquares() { return this->m_minY; }

 int getMaxXInSquares() { return this->m_maxX; }

 int getMaxYInSquares() { return this->m_maxY; }

 int getWidthInSquares() { return this->m_maxX - this->m_minX + 1; }

 int getHeightInSquares() { return this->m_maxY - this->m_minY + 1; }

 WorldMapCell getCell(int x, int y) {
 for (int int0 = 0; int0 < this->m_data.size(); int0++) {
 WorldMapData worldMapData = this->m_data.get(int0);
 if (worldMapData.isReady()) {
 WorldMapCell worldMapCell = worldMapData.getCell(x, y);
 if (worldMapCell != nullptr) {
 return worldMapCell;
 }
 }
 }

 return nullptr;
 }

 int getDataWidthInCells() { return this->m_maxDataX - this->m_minDataX + 1; }

 int getDataHeightInCells() { return this->m_maxDataY - this->m_minDataY + 1; }

 int getDataWidthInSquares() { return this->getDataWidthInCells() * 300; }

 int getDataHeightInSquares() { return this->getDataHeightInCells() * 300; }

 static void Reset() {
 WorldMapSettings.Reset();
 WorldMapVisited.Reset();
 WorldMapData.Reset();
 WorldMapImages.Reset();
 MapSymbolDefinitions.Reset();
 MapItem.Reset();
 }

 void onStateChanged(Asset.State oldState, Asset.State newState, Asset asset) {
 this->updateDataBounds();
 if (this->m_boundsFromData) {
 this->setBoundsInCells(this->m_minDataX, this->m_minDataY, this->m_maxDataX,
 this->m_maxDataY);
 }
 }
}
} // namespace worldMap
} // namespace zombie
