#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/asset/Asset.h"
#include "zombie/asset/AssetManager.h"
#include "zombie/asset/AssetManager/AssetParams.h"
#include "zombie/asset/AssetPath.h"
#include "zombie/asset/AssetType.h"
#include "zombie/core/math/PZMath.h"
#include <filesystem>

namespace zombie {
namespace worldMap {


class WorldMapData :  Asset {
:
    static HashMap<String, WorldMapData> s_fileNameToData = std::make_unique<HashMap<>>();
    std::string m_relativeFileName;
    ArrayList<WorldMapCell> m_cells = std::make_unique<ArrayList<>>();
    HashMap<Integer, WorldMapCell> m_cellLookup = std::make_unique<HashMap<>>();
    int m_minX;
    int m_minY;
    int m_maxX;
    int m_maxY;
    static const AssetType ASSET_TYPE = new AssetType("WorldMapData");

    static WorldMapData getOrCreateData(const std::string& var0) {
    WorldMapData var1 = s_fileNameToData.get(var0);
      if (var1 == nullptr && Files.exists(Paths.get(var0))) {
         var1 = (WorldMapData)WorldMapDataAssetManager.instance.load(new AssetPath(var0));
         s_fileNameToData.put(var0, var1);
      }

    return var1;
   }

     WorldMapData(AssetPath var1, AssetManager var2) {
      super(var1, var2);
   }

     WorldMapData(AssetPath var1, AssetManager var2, AssetParams var3) {
      super(var1, var2);
   }

    void clear() {
      for (WorldMapCell var2 : this.m_cells) {
         var2.dispose();
      }

      this.m_cells.clear();
      this.m_cellLookup.clear();
      this.m_minX = 0;
      this.m_minY = 0;
      this.m_maxX = 0;
      this.m_maxY = 0;
   }

    int getWidthInCells() const {
      return this.m_maxX - this.m_minX + 1;
   }

    int getHeightInCells() const {
      return this.m_maxY - this.m_minY + 1;
   }

    int getWidthInSquares() const {
      return this.getWidthInCells() * 300;
   }

    int getHeightInSquares() const {
      return this.getHeightInCells() * 300;
   }

    void onLoaded() {
      this.m_minX = Integer.MAX_VALUE;
      this.m_minY = Integer.MAX_VALUE;
      this.m_maxX = Integer.MIN_VALUE;
      this.m_maxY = Integer.MIN_VALUE;
      this.m_cellLookup.clear();

      for (WorldMapCell var2 : this.m_cells) {
    int var3 = this.getCellKey(var2.m_x, var2.m_y);
         this.m_cellLookup.put(var3, var2);
         this.m_minX = Math.min(this.m_minX, var2.m_x);
         this.m_minY = Math.min(this.m_minY, var2.m_y);
         this.m_maxX = Math.max(this.m_maxX, var2.m_x);
         this.m_maxY = Math.max(this.m_maxY, var2.m_y);
      }
   }

    WorldMapCell getCell(int var1, int var2) {
    int var3 = this.getCellKey(var1, var2);
      return this.m_cellLookup.get(var3);
   }

    int getCellKey(int var1, int var2) {
      return var1 + var2 * 1000;
   }

    void hitTest(float var1, float var2, ArrayList<WorldMapFeature> var3) {
    int var4 = (int)PZMath.floor(var1 / 300.0F);
    int var5 = (int)PZMath.floor(var2 / 300.0F);
      if (var4 >= this.m_minX && var4 <= this.m_maxX && var5 >= this.m_minY && var5 <= this.m_maxY) {
    WorldMapCell var6 = this.getCell(var4, var5);
         if (var6 != nullptr) {
            var6.hitTest(var1, var2, var3);
         }
      }
   }

    static void Reset() {
   }

    AssetType getType() const {
    return ASSET_TYPE;
   }

    void onBeforeEmpty() {
      super.onBeforeEmpty();
      this.clear();
   }
}
} // namespace worldMap
} // namespace zombie
