#pragma once
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/areas/isoregion/IsoRegions.h"
#include "zombie/iso/areas/isoregion/regions/IsoChunkRegion.h"
#include "zombie/iso/areas/isoregion/regions/IsoWorldRegion.h"
#include <algorithm>
#include <filesystem>

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {
namespace data {


class DataChunk {
public:
    const DataCell cell;
    const int hashId;
    const int chunkX;
    const int chunkY;
    int highestZ = 0;
    long lastUpdateStamp = 0L;
   private const boolean[] activeZLayers = new boolean[8];
   private const boolean[] dirtyZLayers = new boolean[8];
   private byte[] squareFlags;
   private byte[] regionIDs;
   private const std::vector<std::vector<IsoChunkRegion>> chunkRegions = new std::vector<>(8);
    static uint8_t selectedFlags;
   private static const ArrayDeque<DataSquarePos> tmpSquares = std::make_unique<ArrayDeque<>>();
   private static const std::unordered_set<int> tmpLinkedChunks = std::make_unique<std::unordered_set<>>();
   private static const boolean[] exploredPositions = new boolean[100];
    static IsoChunkRegion lastCurRegion;
    static IsoChunkRegion lastOtherRegionFullConnect;
   private static std::vector<IsoChunkRegion> oldList = std::make_unique<std::vector<>>();
   private static const ArrayDeque<IsoChunkRegion> chunkQueue = std::make_unique<ArrayDeque<>>();

    protected DataChunk(int var1, int var2, DataCell var3, int var4) {
      this.cell = var3;
      this.hashId = var4 < 0 ? IsoRegions.hash(var1, var2) : var4;
      this.chunkX = var1;
      this.chunkY = var2;

      for (int var5 = 0; var5 < 8; var5++) {
         this.chunkRegions.push_back(std::make_unique<std::vector<>>());
      }
   }

    int getHashId() {
      return this.hashId;
   }

    int getChunkX() {
      return this.chunkX;
   }

    int getChunkY() {
      return this.chunkY;
   }

   protected std::vector<IsoChunkRegion> getChunkRegions(int var1) {
      return this.chunkRegions.get(var1);
   }

    long getLastUpdateStamp() {
      return this.lastUpdateStamp;
   }

    void setLastUpdateStamp(long var1) {
      this.lastUpdateStamp = var1;
   }

    bool isDirty(int var1) {
      return this.activeZLayers[var1] ? this.dirtyZLayers[var1] : false;
   }

    void setDirty(int var1) {
      if (this.activeZLayers[var1]) {
         this.dirtyZLayers[var1] = true;
         this.cell.dataRoot.EnqueueDirtyDataChunk(this);
      }
   }

    void setDirtyAllActive() {
    bool var1 = false;

      for (int var2 = 0; var2 < 8; var2++) {
         if (this.activeZLayers[var2]) {
            this.dirtyZLayers[var2] = true;
            if (!var1) {
               this.cell.dataRoot.EnqueueDirtyDataChunk(this);
               var1 = true;
            }
         }
      }
   }

    void unsetDirtyAll() {
      for (int var1 = 0; var1 < 8; var1++) {
         this.dirtyZLayers[var1] = false;
      }
   }

    bool validCoords(int var1, int var2, int var3) {
      return var1 >= 0 && var1 < 10 && var2 >= 0 && var2 < 10 && var3 >= 0 && var3 < this.highestZ + 1;
   }

    int getCoord1D(int var1, int var2, int var3) {
      return var3 * 10 * 10 + var2 * 10 + var1;
   }

    uint8_t getSquare(int var1, int var2, int var3) {
      return this.getSquare(var1, var2, var3, false);
   }

    uint8_t getSquare(int var1, int var2, int var3, bool var4) {
      if (this.squareFlags != nullptr && (var4 || this.validCoords(var1, var2, var3))) {
         return this.activeZLayers[var3] ? this.squareFlags[this.getCoord1D(var1, var2, var3)] : -1;
      } else {
         return -1;
      }
   }

    uint8_t setOrAddSquare(int var1, int var2, int var3, uint8_t var4) {
      return this.setOrAddSquare(var1, var2, var3, var4, false);
   }

    uint8_t setOrAddSquare(int var1, int var2, int var3, uint8_t var4, bool var5) {
      if (!var5 && !this.validCoords(var1, var2, var3)) {
         return -1;
      } else {
         this.ensureSquares(var3);
    int var6 = this.getCoord1D(var1, var2, var3);
         if (this.squareFlags[var6] != var4) {
            this.setDirty(var3);
         }

         this.squareFlags[var6] = var4;
    return var4;
      }
   }

    void ensureSquares(int var1) {
      if (var1 >= 0 && var1 < 8) {
         if (!this.activeZLayers[var1]) {
            this.ensureSquareArray(var1);
            this.activeZLayers[var1] = true;
            if (var1 > this.highestZ) {
               this.highestZ = var1;
            }

            for (int var3 = 0; var3 < 10; var3++) {
               for (int var4 = 0; var4 < 10; var4++) {
    int var2 = this.getCoord1D(var4, var3, var1);
                  this.squareFlags[var2] = (byte)(var1 == 0 ? 16 : 0);
               }
            }
         }
      }
   }

    void ensureSquareArray(int var1) {
    int var2 = (var1 + 1) * 10 * 10;
      if (this.squareFlags == nullptr || this.squareFlags.length < var2) {
         byte[] var3 = this.squareFlags;
         byte[] var4 = this.regionIDs;
         this.squareFlags = new byte[var2];
         this.regionIDs = new byte[var2];
         if (var3 != nullptr) {
            for (int var5 = 0; var5 < var3.length; var5++) {
               this.squareFlags[var5] = var3[var5];
               this.regionIDs[var5] = var4[var5];
            }
         }
      }
   }

    void save(ByteBuffer var1) {
      try {
    int var2 = var1.position();
         var1.putInt(0);
         var1.putInt(this.highestZ);
    int var3 = (this.highestZ + 1) * 100;
         var1.putInt(var3);

         for (int var4 = 0; var4 < var3; var4++) {
            var1.put(this.squareFlags[var4]);
         }

    int var6 = var1.position();
         var1.position(var2);
         var1.putInt(var6 - var2);
         var1.position(var6);
      } catch (Exception var5) {
         DebugLog.log(var5.getMessage());
         var5.printStackTrace();
      }
   }

    void load(ByteBuffer var1, int var2, bool var3) {
      try {
         if (var3) {
            var1.getInt();
         }

         this.highestZ = var1.getInt();

         for (int var4 = this.highestZ; var4 >= 0; var4--) {
            this.ensureSquares(var4);
         }

    int var7 = var1.getInt();

         for (int var5 = 0; var5 < var7; var5++) {
            this.squareFlags[var5] = var1.get();
         }
      } catch (Exception var6) {
         DebugLog.log(var6.getMessage());
         var6.printStackTrace();
      }
   }

    void setSelectedFlags(int var1, int var2, int var3) {
      if (var3 >= 0 && var3 <= this.highestZ) {
         selectedFlags = this.squareFlags[this.getCoord1D(var1, var2, var3)];
      } else {
         selectedFlags = -1;
      }
   }

    bool selectedHasFlags(uint8_t var1) {
      return (selectedFlags & var1) == var1;
   }

    bool squareHasFlags(int var1, int var2, int var3, uint8_t var4) {
      return this.squareHasFlags(this.getCoord1D(var1, var2, var3), var4);
   }

    bool squareHasFlags(int var1, uint8_t var2) {
    uint8_t var3 = this.squareFlags[var1];
      return (var3 & var2) == var2;
   }

    uint8_t squareGetFlags(int var1, int var2, int var3) {
      return this.squareGetFlags(this.getCoord1D(var1, var2, var3));
   }

    uint8_t squareGetFlags(int var1) {
      return this.squareFlags[var1];
   }

    void squareAddFlags(int var1, int var2, int var3, uint8_t var4) {
      this.squareAddFlags(this.getCoord1D(var1, var2, var3), var4);
   }

    void squareAddFlags(int var1, uint8_t var2) {
      this.squareFlags[var1] = (byte)(this.squareFlags[var1] | var2);
   }

    void squareRemoveFlags(int var1, int var2, int var3, uint8_t var4) {
      this.squareRemoveFlags(this.getCoord1D(var1, var2, var3), var4);
   }

    void squareRemoveFlags(int var1, uint8_t var2) {
      this.squareFlags[var1] = (byte)(this.squareFlags[var1] ^ var2);
   }

    bool squareCanConnect(int var1, int var2, int var3, uint8_t var4) {
      return this.squareCanConnect(this.getCoord1D(var1, var2, var3), var3, var4);
   }

    bool squareCanConnect(int var1, int var2, uint8_t var3) {
      if (var2 >= 0 && var2 < this.highestZ + 1) {
         if (var3 == 0) {
            return !this.squareHasFlags(var1, (byte)1);
         }

         if (var3 == 1) {
            return !this.squareHasFlags(var1, (byte)2);
         }

         if (var3 == 2) {
    return true;
         }

         if (var3 == 3) {
    return true;
         }

         if (var3 == 4) {
            return !this.squareHasFlags(var1, (byte)64);
         }

         if (var3 == 5) {
            return !this.squareHasFlags(var1, (byte)16);
         }
      }

    return false;
   }

    IsoChunkRegion getIsoChunkRegion(int var1, int var2, int var3) {
      return this.getIsoChunkRegion(this.getCoord1D(var1, var2, var3), var3);
   }

    IsoChunkRegion getIsoChunkRegion(int var1, int var2) {
      if (var2 >= 0 && var2 < this.highestZ + 1) {
    uint8_t var3 = this.regionIDs[var1];
         if (var3 >= 0 && var3 < this.chunkRegions.get(var2).size()) {
            return this.chunkRegions.get(var2).get(var3);
         }
      }

    return nullptr;
   }

    void setRegion(int var1, int var2, int var3, uint8_t var4) {
      this.regionIDs[this.getCoord1D(var1, var2, var3)] = var4;
   }

    void recalculate() {
      for (int var1 = 0; var1 <= this.highestZ; var1++) {
         if (this.dirtyZLayers[var1] && this.activeZLayers[var1]) {
            this.recalculate(var1);
         }
      }
   }

    void recalculate(int var1) {
    std::vector var2 = this.chunkRegions.get(var1);

      for (int var3 = var2.size() - 1; var3 >= 0; var3--) {
    IsoChunkRegion var4 = (IsoChunkRegion)var2.get(var3);
    IsoWorldRegion var5 = var4.unlinkFromIsoWorldRegion();
         if (var5 != nullptr && var5.size() <= 0) {
            this.cell.dataRoot.regionManager.releaseIsoWorldRegion(var5);
         }

         this.cell.dataRoot.regionManager.releaseIsoChunkRegion(var4);
         var2.remove(var3);
      }

      var2.clear();
    uint8_t var7 = 100;
      Arrays.fill(this.regionIDs, var1 * var7, var1 * var7 + var7, (byte)-1);

      for (int var8 = 0; var8 < 10; var8++) {
         for (int var9 = 0; var9 < 10; var9++) {
            if (this.regionIDs[this.getCoord1D(var9, var8, var1)] == -1) {
    IsoChunkRegion var6 = this.floodFill(var9, var8, var1);
            }
         }
      }
   }

    IsoChunkRegion floodFill(int var1, int var2, int var3) {
    IsoChunkRegion var4 = this.cell.dataRoot.regionManager.allocIsoChunkRegion(var3);
    uint8_t var5 = (byte)this.chunkRegions.get(var3).size();
      this.chunkRegions.get(var3).push_back(var4);
      this.clearExploredPositions();
      tmpSquares.clear();
      tmpLinkedChunks.clear();
      tmpSquares.push_back(DataSquarePos.alloc(var1, var2, var3));

    DataSquarePos var6;
      while ((var6 = tmpSquares.poll()) != nullptr) {
    int var8 = this.getCoord1D(var6.x, var6.y, var6.z);
         this.setExploredPosition(var8, var6.z);
         if (this.regionIDs[var8] == -1) {
            this.regionIDs[var8] = var5;
            var4.addSquareCount();

            for (byte var10 = 0; var10 < 4; var10++) {
    DataSquarePos var7 = this.getNeighbor(var6, var10);
               if (var7 != nullptr) {
    int var9 = this.getCoord1D(var7.x, var7.y, var7.z);
                  if (this.isExploredPosition(var9, var7.z)) {
                     DataSquarePos.release(var7);
                  } else {
                     if (this.squareCanConnect(var8, var6.z, var10) && this.squareCanConnect(var9, var7.z, IsoRegions.GetOppositeDir(var10))) {
                        if (this.regionIDs[var9] == -1) {
                           tmpSquares.push_back(var7);
                           this.setExploredPosition(var9, var7.z);
                           continue;
                        }
                     } else {
    IsoChunkRegion var11 = this.getIsoChunkRegion(var9, var7.z);
                        if (var11 != nullptr && var11 != var4) {
                           if (!tmpLinkedChunks.contains(var11.getID())) {
                              var4.addNeighbor(var11);
                              var11.addNeighbor(var4);
                              tmpLinkedChunks.push_back(var11.getID());
                           }

                           this.setExploredPosition(var9, var7.z);
                           DataSquarePos.release(var7);
                           continue;
                        }
                     }

                     DataSquarePos.release(var7);
                  }
               } else if (this.squareCanConnect(var8, var6.z, var10)) {
                  var4.addChunkBorderSquaresCnt();
               }
            }
         }
      }

    return var4;
   }

    bool isExploredPosition(int var1, int var2) {
    int var3 = var1 - var2 * 10 * 10;
      return exploredPositions[var3];
   }

    void setExploredPosition(int var1, int var2) {
    int var3 = var1 - var2 * 10 * 10;
      exploredPositions[var3] = true;
   }

    void clearExploredPositions() {
      Arrays.fill(exploredPositions, false);
   }

    DataSquarePos getNeighbor(DataSquarePos var1, uint8_t var2) {
    int var3 = var1.x;
    int var4 = var1.y;
      if (var2 == 1) {
         var3 = var1.x - 1;
      } else if (var2 == 3) {
         var3 = var1.x + 1;
      }

      if (var2 == 0) {
         var4 = var1.y - 1;
      } else if (var2 == 2) {
         var4 = var1.y + 1;
      }

      return var3 >= 0 && var3 < 10 && var4 >= 0 && var4 < 10 ? DataSquarePos.alloc(var3, var4, var1.z) : nullptr;
   }

    void link(DataChunk var1, DataChunk var2, DataChunk var3, DataChunk var4) {
      for (int var5 = 0; var5 <= this.highestZ; var5++) {
         if (this.dirtyZLayers[var5] && this.activeZLayers[var5]) {
            this.linkRegionsOnSide(var5, var1, (byte)0);
            this.linkRegionsOnSide(var5, var2, (byte)1);
            this.linkRegionsOnSide(var5, var3, (byte)2);
            this.linkRegionsOnSide(var5, var4, (byte)3);
         }
      }
   }

    void linkRegionsOnSide(int var1, DataChunk var2, uint8_t var3) {
    int var4;
    int var5;
    int var6;
    int var7;
      if (var3 != 0 && var3 != 2) {
         var4 = var3 == 1 ? 0 : 9;
         var5 = var4 + 1;
         var6 = 0;
         var7 = 10;
      } else {
         var4 = 0;
         var5 = 10;
         var6 = var3 == 0 ? 0 : 9;
         var7 = var6 + 1;
      }

      if (var2 != nullptr && var2.isDirty(var1)) {
         var2.resetEnclosedSide(var1, IsoRegions.GetOppositeDir(var3));
      }

      lastCurRegion = nullptr;
      lastOtherRegionFullConnect = nullptr;

      for (int var14 = var6; var14 < var7; var14++) {
         for (int var15 = var4; var15 < var5; var15++) {
    int var8;
    int var9;
            if (var3 != 0 && var3 != 2) {
               var8 = var3 == 1 ? 9 : 0;
               var9 = var14;
            } else {
               var8 = var15;
               var9 = var3 == 0 ? 9 : 0;
            }

    int var10 = this.getCoord1D(var15, var14, var1);
    int var11 = this.getCoord1D(var8, var9, var1);
    IsoChunkRegion var12 = this.getIsoChunkRegion(var10, var1);
    IsoChunkRegion var13 = var2 != nullptr ? var2.getIsoChunkRegion(var11, var1) : nullptr;
            if (var12 == nullptr) {
               IsoRegions.warn("ds.getRegion()==nullptr, shouldnt happen at this point.");
            } else {
               if (lastCurRegion != nullptr && lastCurRegion != var12) {
                  lastOtherRegionFullConnect = nullptr;
               }

               if (lastCurRegion == nullptr || lastCurRegion != var12 || var13 == nullptr || lastOtherRegionFullConnect != var13) {
                  if (var2 != nullptr && var13 != nullptr) {
                     if (this.squareCanConnect(var10, var1, var3) && var2.squareCanConnect(var11, var1, IsoRegions.GetOppositeDir(var3))) {
                        var12.addConnectedNeighbor(var13);
                        var13.addConnectedNeighbor(var12);
                        var12.addNeighbor(var13);
                        var13.addNeighbor(var12);
                        if (!var13.getIsEnclosed()) {
                           var13.setEnclosed(IsoRegions.GetOppositeDir(var3), true);
                        }

                        lastOtherRegionFullConnect = var13;
                     } else {
                        var12.addNeighbor(var13);
                        var13.addNeighbor(var12);
                        if (!var13.getIsEnclosed()) {
                           var13.setEnclosed(IsoRegions.GetOppositeDir(var3), true);
                        }

                        lastOtherRegionFullConnect = nullptr;
                     }
                  } else if (this.squareCanConnect(var10, var1, var3)) {
                     var12.setEnclosed(var3, false);
                  }

                  lastCurRegion = var12;
               }
            }
         }
      }
   }

    void resetEnclosedSide(int var1, uint8_t var2) {
    std::vector var3 = this.chunkRegions.get(var1);

      for (int var4 = 0; var4 < var3.size(); var4++) {
    IsoChunkRegion var5 = (IsoChunkRegion)var3.get(var4);
         if (var5.getzLayer() == var1) {
            var5.setEnclosed(var2, true);
         }
      }
   }

    void interConnect() {
      for (int var4 = 0; var4 <= this.highestZ; var4++) {
         if (this.dirtyZLayers[var4] && this.activeZLayers[var4]) {
    std::vector var3 = this.chunkRegions.get(var4);

            for (int var5 = 0; var5 < var3.size(); var5++) {
    IsoChunkRegion var1 = (IsoChunkRegion)var3.get(var5);
               if (var1.getzLayer() == var4 && var1.getIsoWorldRegion() == nullptr) {
                  if (var1.getConnectedNeighbors().size() == 0) {
    IsoWorldRegion var12 = this.cell.dataRoot.regionManager.allocIsoWorldRegion();
                     this.cell.dataRoot.EnqueueDirtyIsoWorldRegion(var12);
                     var12.addIsoChunkRegion(var1);
                  } else {
    IsoChunkRegion var6 = var1.getConnectedNeighborWithLargestIsoWorldRegion();
                     if (var6 == nullptr) {
    IsoWorldRegion var13 = this.cell.dataRoot.regionManager.allocIsoWorldRegion();
                        this.cell.dataRoot.EnqueueDirtyIsoWorldRegion(var13);
                        this.floodFillExpandWorldRegion(var1, var13);
                        DataRoot.floodFills++;
                     } else {
    IsoWorldRegion var7 = var6.getIsoWorldRegion();
                        oldList.clear();
                        oldList = var7.swapIsoChunkRegions(oldList);

                        for (int var8 = 0; var8 < oldList.size(); var8++) {
    IsoChunkRegion var2 = oldList.get(var8);
                           var2.setIsoWorldRegion(nullptr);
                        }

                        this.cell.dataRoot.regionManager.releaseIsoWorldRegion(var7);
    IsoWorldRegion var14 = this.cell.dataRoot.regionManager.allocIsoWorldRegion();
                        this.cell.dataRoot.EnqueueDirtyIsoWorldRegion(var14);
                        this.floodFillExpandWorldRegion(var1, var14);

                        for (int var10 = 0; var10 < oldList.size(); var10++) {
    IsoChunkRegion var11 = oldList.get(var10);
                           if (var11.getIsoWorldRegion() == nullptr) {
    IsoWorldRegion var9 = this.cell.dataRoot.regionManager.allocIsoWorldRegion();
                              this.cell.dataRoot.EnqueueDirtyIsoWorldRegion(var9);
                              this.floodFillExpandWorldRegion(var11, var9);
                           }
                        }

                        DataRoot.floodFills++;
                     }
                  }
               }
            }
         }
      }
   }

    void floodFillExpandWorldRegion(IsoChunkRegion var1, IsoWorldRegion var2) {
      chunkQueue.push_back(var1);

    IsoChunkRegion var3;
      while ((var3 = chunkQueue.poll()) != nullptr) {
         var2.addIsoChunkRegion(var3);
         if (var3.getConnectedNeighbors().size() != 0) {
            for (int var5 = 0; var5 < var3.getConnectedNeighbors().size(); var5++) {
    IsoChunkRegion var4 = (IsoChunkRegion)var3.getConnectedNeighbors().get(var5);
               if (!chunkQueue.contains(var4)) {
                  if (var4.getIsoWorldRegion() == nullptr) {
                     chunkQueue.push_back(var4);
                  } else if (var4.getIsoWorldRegion() != var2) {
                     var2.merge(var4.getIsoWorldRegion());
                  }
               }
            }
         }
      }
   }

    void recalcRoofs() {
      if (this.highestZ >= 1) {
         for (int var1 = 0; var1 < this.chunkRegions.size(); var1++) {
            for (int var2 = 0; var2 < this.chunkRegions.get(var1).size(); var2++) {
    IsoChunkRegion var3 = this.chunkRegions.get(var1).get(var2);
               var3.resetRoofCnt();
            }
         }

    int var8 = this.highestZ;

         for (int var5 = 0; var5 < 10; var5++) {
            for (int var6 = 0; var6 < 10; var6++) {
    uint8_t var9 = this.getSquare(var6, var5, var8);
    bool var11 = false;
               if (var9 > 0) {
                  var11 = this.squareHasFlags(var6, var5, var8, (byte)16);
               }

               if (var8 >= 1) {
                  for (int var7 = var8 - 1; var7 >= 0; var7--) {
                     var9 = this.getSquare(var6, var5, var7);
                     if (var9 > 0) {
                        var11 = var11 || this.squareHasFlags(var6, var5, var7, (byte)32);
                        if (var11) {
    IsoChunkRegion var4 = this.getIsoChunkRegion(var6, var5, var7);
                           if (var4 != nullptr) {
                              var4.addRoof();
                              if (var4.getIsoWorldRegion() != nullptr && !var4.getIsoWorldRegion().isEnclosed()) {
                                 var11 = false;
                              }
                           } else {
                              var11 = false;
                           }
                        }

                        if (!var11) {
                           var11 = this.squareHasFlags(var6, var5, var7, (byte)16);
                        }
                     } else {
                        var11 = false;
                     }
                  }
               }
            }
         }
      }
   }
}
} // namespace data
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie
