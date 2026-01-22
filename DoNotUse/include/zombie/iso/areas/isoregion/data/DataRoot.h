#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Colors.h"
#include "zombie/iso/areas/isoregion/IsoRegions.h"
#include "zombie/iso/areas/isoregion/data/DataRoot/SelectInfo.h"
#include "zombie/iso/areas/isoregion/regions/IsoChunkRegion.h"
#include "zombie/iso/areas/isoregion/regions/IsoRegionManager.h"
#include "zombie/iso/areas/isoregion/regions/IsoWorldRegion.h"
#include <algorithm>

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {
namespace data {


class DataRoot {
public:
   private const Map<int, DataCell> cellMap = std::make_unique<std::unordered_map<>>();
    const SelectInfo select = std::make_shared<SelectInfo>(this);
    const SelectInfo selectInternal = std::make_shared<SelectInfo>(this);
    const IsoRegionManager regionManager;
   private const std::vector<IsoWorldRegion> dirtyIsoWorldRegions = std::make_unique<std::vector<>>();
   private const std::vector<DataChunk> dirtyChunks = std::make_unique<std::vector<>>();
    static int recalcs;
    static int floodFills;
    static int merges;
   private static const long[] t_start = new long[5];
   private static const long[] t_end = new long[5];
   private static const long[] t_time = new long[5];

    public DataRoot() {
      this.regionManager = std::make_shared<IsoRegionManager>(this);
   }

    void getAllChunks(List<DataChunk> var1) {
      for (Entry var3 : this.cellMap.entrySet()) {
         ((DataCell)var3.getValue()).getAllChunks(var1);
      }
   }

    DataCell getCell(int var1) {
      return this.cellMap.get(var1);
   }

    DataCell addCell(int var1, int var2, int var3) {
    DataCell var4 = std::make_shared<DataCell>(this, var1, var2, var3);
      this.cellMap.put(var3, var4);
    return var4;
   }

    DataChunk getDataChunk(int var1, int var2) {
    int var3 = IsoRegions.hash(var1 / 30, var2 / 30);
    DataCell var4 = this.cellMap.get(var3);
      if (var4 != nullptr) {
    int var5 = IsoRegions.hash(var1, var2);
         return var4.getChunk(var5);
      } else {
    return nullptr;
      }
   }

    void setDataChunk(DataChunk var1) {
    int var2 = IsoRegions.hash(var1.getChunkX() / 30, var1.getChunkY() / 30);
    DataCell var3 = this.cellMap.get(var2);
      if (var3 == nullptr) {
         var3 = this.addCell(var1.getChunkX() / 30, var1.getChunkY() / 30, var2);
      }

      var3.setChunk(var1);
   }

    IsoWorldRegion getIsoWorldRegion(int var1, int var2, int var3) {
      this.selectInternal.reset(var1, var2, var3, false);
      if (this.selectInternal.chunk != nullptr) {
    IsoChunkRegion var4 = this.selectInternal.chunk.getIsoChunkRegion(this.selectInternal.chunkSquareX, this.selectInternal.chunkSquareY, var3);
         if (var4 != nullptr) {
            return var4.getIsoWorldRegion();
         }
      }

    return nullptr;
   }

    uint8_t getSquareFlags(int var1, int var2, int var3) {
      this.selectInternal.reset(var1, var2, var3, false);
      return this.selectInternal.square;
   }

    IsoChunkRegion getIsoChunkRegion(int var1, int var2, int var3) {
      this.selectInternal.reset(var1, var2, var3, false);
      return this.selectInternal.chunk != nullptr
         ? this.selectInternal.chunk.getIsoChunkRegion(this.selectInternal.chunkSquareX, this.selectInternal.chunkSquareY, var3)
         : nullptr;
   }

    void resetAllData() {
    std::vector var1 = new std::vector();

      for (Entry var3 : this.cellMap.entrySet()) {
    DataCell var4 = (DataCell)var3.getValue();

         for (Entry var6 : var4.dataChunks.entrySet()) {
    DataChunk var7 = (DataChunk)var6.getValue();

            for (int var8 = 0; var8 < 8; var8++) {
               for (IsoChunkRegion var10 : var7.getChunkRegions(var8)) {
                  if (var10.getIsoWorldRegion() != nullptr && !var1.contains(var10.getIsoWorldRegion())) {
                     var1.push_back(var10.getIsoWorldRegion());
                  }

                  var10.setIsoWorldRegion(nullptr);
                  this.regionManager.releaseIsoChunkRegion(var10);
               }
            }
         }

         var4.dataChunks.clear();
      }

      this.cellMap.clear();

    for (auto& var12 : var1)         this.regionManager.releaseIsoWorldRegion(var12);
      }
   }

    void EnqueueDirtyDataChunk(DataChunk var1) {
      if (!this.dirtyChunks.contains(var1)) {
         this.dirtyChunks.push_back(var1);
      }
   }

    void EnqueueDirtyIsoWorldRegion(IsoWorldRegion var1) {
      if (!this.dirtyIsoWorldRegions.contains(var1)) {
         this.dirtyIsoWorldRegions.push_back(var1);
      }
   }

    void DequeueDirtyIsoWorldRegion(IsoWorldRegion var1) {
      this.dirtyIsoWorldRegions.remove(var1);
   }

    void updateExistingSquare(int var1, int var2, int var3, uint8_t var4) {
      this.select.reset(var1, var2, var3, false);
      if (this.select.chunk != nullptr) {
    uint8_t var5 = -1;
         if (this.select.square != -1) {
            var5 = this.select.square;
         }

         if (var4 == var5) {
            return;
         }

         this.select.chunk.setOrAddSquare(this.select.chunkSquareX, this.select.chunkSquareY, this.select.z, var4, true);
      } else {
         IsoRegions.warn("DataRoot.updateExistingSquare -> trying to change a square on a unknown chunk");
      }
   }

    void processDirtyChunks() {
      if (this.dirtyChunks.size() > 0) {
    long var1 = System.nanoTime();
         recalcs = 0;
         floodFills = 0;
         merges = 0;
         t_start[0] = System.nanoTime();

         for (int var4 = 0; var4 < this.dirtyChunks.size(); var4++) {
    DataChunk var3 = this.dirtyChunks.get(var4);
            var3.recalculate();
            recalcs++;
         }

         t_end[0] = System.nanoTime();
         t_start[1] = System.nanoTime();

         for (int var12 = 0; var12 < this.dirtyChunks.size(); var12++) {
    DataChunk var9 = this.dirtyChunks.get(var12);
    DataChunk var5 = this.getDataChunk(var9.getChunkX(), var9.getChunkY() - 1);
    DataChunk var6 = this.getDataChunk(var9.getChunkX() - 1, var9.getChunkY());
    DataChunk var7 = this.getDataChunk(var9.getChunkX(), var9.getChunkY() + 1);
    DataChunk var8 = this.getDataChunk(var9.getChunkX() + 1, var9.getChunkY());
            var9.link(var5, var6, var7, var8);
         }

         t_end[1] = System.nanoTime();
         t_start[2] = System.nanoTime();

         for (int var13 = 0; var13 < this.dirtyChunks.size(); var13++) {
    DataChunk var10 = this.dirtyChunks.get(var13);
            var10.interConnect();
         }

         t_end[2] = System.nanoTime();
         t_start[3] = System.nanoTime();

         for (int var14 = 0; var14 < this.dirtyChunks.size(); var14++) {
    DataChunk var11 = this.dirtyChunks.get(var14);
            var11.recalcRoofs();
            var11.unsetDirtyAll();
         }

         t_end[3] = System.nanoTime();
         t_start[4] = System.nanoTime();
         if (this.dirtyIsoWorldRegions.size() > 0) {
            for (int var18 = 0; var18 < this.dirtyIsoWorldRegions.size(); var18++) {
    IsoWorldRegion var15 = this.dirtyIsoWorldRegions.get(var18);
               var15.unlinkNeighbors();
            }

            for (int var19 = 0; var19 < this.dirtyIsoWorldRegions.size(); var19++) {
    IsoWorldRegion var16 = this.dirtyIsoWorldRegions.get(var19);
               var16.linkNeighbors();
            }

            this.dirtyIsoWorldRegions.clear();
         }

         t_end[4] = System.nanoTime();
         this.dirtyChunks.clear();
    long var17 = System.nanoTime();
    long var20 = var17 - var1;
         if (IsoRegions.PRINT_D) {
            t_time[0] = t_end[0] - t_start[0];
            t_time[1] = t_end[1] - t_start[1];
            t_time[2] = t_end[2] - t_start[2];
            t_time[3] = t_end[3] - t_start[3];
            t_time[4] = t_end[4] - t_start[4];
            IsoRegions.log(
               "--- IsoRegion update: "
                  + std::string.format("%.6f", var20 / 1000000.0)
                  + " ms, recalc: "
                  + std::string.format("%.6f", t_time[0] / 1000000.0)
                  + " ms, link: "
                  + std::string.format("%.6f", t_time[1] / 1000000.0)
                  + " ms, interconnect: "
                  + std::string.format("%.6f", t_time[2] / 1000000.0)
                  + " ms, roofs: "
                  + std::string.format("%.6f", t_time[3] / 1000000.0)
                  + " ms, worldRegion: "
                  + std::string.format("%.6f", t_time[4] / 1000000.0)
                  + " ms, recalcs = "
                  + recalcs
                  + ", merges = "
                  + merges
                  + ", floodfills = "
                  + floodFills,
               Colors.CornFlowerBlue
            );
         }
      }
   }
}
} // namespace data
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie
