#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ZomboidFileSystem.h"
#include "zombie/asset/Asset.h"
#include "zombie/asset/Asset/State.h"
#include "zombie/asset/AssetStateObserver.h"
#include "zombie/inventory/types/MapItem.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/util/StringUtils.h"
#include "zombie/worldMap/symbols/MapSymbolDefinitions.h"

namespace zombie {
namespace worldMap {


class WorldMap {
:
    ArrayList<WorldMapData> m_data = std::make_unique<ArrayList<>>();
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
    ArrayList<WorldMapData> m_lastDataInDirectory = std::make_unique<ArrayList<>>();

    void setBoundsInCells(int var1, int var2, int var3, int var4) {
      this.setBoundsInSquares(var1 * 300, var2 * 300, var3 * 300 + 299, var4 * 300 + 299);
   }

    void setBoundsInSquares(int var1, int var2, int var3, int var4) {
      this.m_minX = var1;
      this.m_minY = var2;
      this.m_maxX = var3;
      this.m_maxY = var4;
   }

    void setBoundsFromData() {
      this.m_boundsFromData = true;
      this.setBoundsInCells(this.m_minDataX, this.m_minDataY, this.m_maxDataX, this.m_maxDataY);
   }

    void setBoundsFromWorld() {
    IsoMetaGrid var1 = IsoWorld.instance.getMetaGrid();
      this.setBoundsInCells(var1.getMinX(), var1.getMinY(), var1.getMaxX(), var1.getMaxY());
   }

    void addData(std::string_view var1) {
      if (!StringUtils.isNullOrWhitespace(var1)) {
    std::string var2 = ZomboidFileSystem.instance.getString(var1);
    WorldMapData var3 = WorldMapData.getOrCreateData(var2);
         if (var3 != nullptr && !this.m_data.contains(var3)) {
            var3.m_relativeFileName = var1;
            this.m_data.add(var3);
            var3.getObserverCb().add(this);
            if (var3.isReady()) {
               this.updateDataBounds();
            }
         }
      }
   }

    int getDataCount() const noexcept {
      return this.m_data.size();
   }

    WorldMapData getDataByIndex(int var1) {
      return this.m_data.get(var1);
   }

    void clearData() {
      for (WorldMapData var2 : this.m_data) {
         var2.getObserverCb().remove(this);
      }

      this.m_data.clear();
      this.m_lastDataInDirectory.clear();
      this.updateDataBounds();
   }

    void endDirectoryData() {
      if (this.hasData()) {
    WorldMapData var1 = this.getDataByIndex(this.getDataCount() - 1);
         if (!this.m_lastDataInDirectory.contains(var1)) {
            this.m_lastDataInDirectory.add(var1);
         }
      }
   }

    bool isLastDataInDirectory(WorldMapData var1) {
      return this.m_lastDataInDirectory.contains(var1);
   }

    void updateDataBounds() {
      this.m_minDataX = Integer.MAX_VALUE;
      this.m_minDataY = Integer.MAX_VALUE;
      this.m_maxDataX = Integer.MIN_VALUE;
      this.m_maxDataY = Integer.MIN_VALUE;

      for (int var1 = 0; var1 < this.m_data.size(); var1++) {
    WorldMapData var2 = this.m_data.get(var1);
         if (var2.isReady()) {
            this.m_minDataX = Math.min(this.m_minDataX, var2.m_minX);
            this.m_minDataY = Math.min(this.m_minDataY, var2.m_minY);
            this.m_maxDataX = Math.max(this.m_maxDataX, var2.m_maxX);
            this.m_maxDataY = Math.max(this.m_maxDataY, var2.m_maxY);
         }
      }

      if (this.m_minDataX > this.m_maxDataX) {
         this.m_minDataX = this.m_maxDataX = this.m_minDataY = this.m_maxDataY = 0;
      }
   }

    bool hasData() {
      return !this.m_data.isEmpty();
   }

    void addImages(std::string_view var1) {
      if (!StringUtils.isNullOrWhitespace(var1)) {
    WorldMapImages var2 = WorldMapImages.getOrCreate(var1);
         if (var2 != nullptr && !this.m_images.contains(var2)) {
            this.m_images.add(var2);
         }
      }
   }

    bool hasImages() {
      return !this.m_images.isEmpty();
   }

    int getImagesCount() const noexcept {
      return this.m_images.size();
   }

    WorldMapImages getImagesByIndex(int var1) {
      return this.m_images.get(var1);
   }

    int getMinXInCells() const {
      return this.m_minX / 300;
   }

    int getMinYInCells() const {
      return this.m_minY / 300;
   }

    int getMaxXInCells() const {
      return this.m_maxX / 300;
   }

    int getMaxYInCells() const {
      return this.m_maxY / 300;
   }

    int getWidthInCells() const {
      return this.getMaxXInCells() - this.getMinXInCells() + 1;
   }

    int getHeightInCells() const {
      return this.getMaxYInCells() - this.getMinYInCells() + 1;
   }

    int getMinXInSquares() const {
      return this.m_minX;
   }

    int getMinYInSquares() const {
      return this.m_minY;
   }

    int getMaxXInSquares() const {
      return this.m_maxX;
   }

    int getMaxYInSquares() const {
      return this.m_maxY;
   }

    int getWidthInSquares() const {
      return this.m_maxX - this.m_minX + 1;
   }

    int getHeightInSquares() const {
      return this.m_maxY - this.m_minY + 1;
   }

    WorldMapCell getCell(int var1, int var2) {
      for (int var3 = 0; var3 < this.m_data.size(); var3++) {
    WorldMapData var4 = this.m_data.get(var3);
         if (var4.isReady()) {
    WorldMapCell var5 = var4.getCell(var1, var2);
            if (var5 != nullptr) {
    return var5;
            }
         }
      }

    return nullptr;
   }

    int getDataWidthInCells() const {
      return this.m_maxDataX - this.m_minDataX + 1;
   }

    int getDataHeightInCells() const {
      return this.m_maxDataY - this.m_minDataY + 1;
   }

    int getDataWidthInSquares() const {
      return this.getDataWidthInCells() * 300;
   }

    int getDataHeightInSquares() const {
      return this.getDataHeightInCells() * 300;
   }

    static void Reset() {
      WorldMapSettings.Reset();
      WorldMapVisited.Reset();
      WorldMapData.Reset();
      WorldMapImages.Reset();
      MapSymbolDefinitions.Reset();
      MapItem.Reset();
   }

    void onStateChanged(State var1, State var2, Asset var3) {
      this.updateDataBounds();
      if (this.m_boundsFromData) {
         this.setBoundsInCells(this.m_minDataX, this.m_minDataY, this.m_maxDataX, this.m_maxDataY);
      }
   }
}
} // namespace worldMap
} // namespace zombie
