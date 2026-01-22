#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"
#include "zombie/iso/areas/isoregion/IsoRegions.h"

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {
namespace regions {


class IsoChunkRegion {
public:
    const IsoRegionManager manager;
    bool isInPool = false;
    Color color;
    int ID;
    uint8_t zLayer;
    uint8_t squareSize = 0;
    uint8_t roofCnt = 0;
    uint8_t chunkBorderSquaresCnt = 0;
   private const boolean[] enclosed = new boolean[4];
    bool enclosedCache = true;
   private const std::vector<IsoChunkRegion> connectedNeighbors = std::make_unique<std::vector<>>();
   private const std::vector<IsoChunkRegion> allNeighbors = std::make_unique<std::vector<>>();
    bool isDirtyEnclosed = false;
    IsoWorldRegion isoWorldRegion;

    int getID() {
      return this.ID;
   }

    int getSquareSize() {
      return this.squareSize;
   }

    Color getColor() {
      return this.color;
   }

    int getzLayer() {
      return this.zLayer;
   }

    IsoWorldRegion getIsoWorldRegion() {
      return this.isoWorldRegion;
   }

    void setIsoWorldRegion(IsoWorldRegion var1) {
      this.isoWorldRegion = var1;
   }

    bool isInPool() {
      return this.isInPool;
   }

    protected IsoChunkRegion(IsoRegionManager var1) {
      this.manager = var1;
   }

    void init(int var1, int var2) {
      this.isInPool = false;
      this.ID = var1;
      this.zLayer = (byte)var2;
      this.resetChunkBorderSquaresCnt();
      if (this.color == nullptr) {
         this.color = this.manager.getColor();
      }

      this.squareSize = 0;
      this.roofCnt = 0;
      this.resetEnclosed();
   }

    IsoChunkRegion reset() {
      this.isInPool = true;
      this.unlinkNeighbors();
    IsoWorldRegion var1 = this.unlinkFromIsoWorldRegion();
      if (var1 != nullptr && var1.size() <= 0) {
         if (Core.bDebug) {
            throw RuntimeException("ChunkRegion.reset IsoChunkRegion has IsoWorldRegion with 0 members.");
         }

         this.manager.releaseIsoWorldRegion(var1);
         IsoRegions.warn("ChunkRegion.reset IsoChunkRegion has IsoWorldRegion with 0 members.");
      }

      this.resetChunkBorderSquaresCnt();
      this.ID = -1;
      this.squareSize = 0;
      this.roofCnt = 0;
      this.resetEnclosed();
    return this;
   }

    IsoWorldRegion unlinkFromIsoWorldRegion() {
      if (this.isoWorldRegion != nullptr) {
    IsoWorldRegion var1 = this.isoWorldRegion;
         this.isoWorldRegion.removeIsoChunkRegion(this);
         this.isoWorldRegion = nullptr;
    return var1;
      } else {
    return nullptr;
      }
   }

    int getRoofCnt() {
      return this.roofCnt;
   }

    void addRoof() {
      this.roofCnt++;
      if (this.roofCnt > this.squareSize) {
         IsoRegions.warn("ChunkRegion.addRoof roofCount exceed squareSize.");
         this.roofCnt = this.squareSize;
      } else {
         if (this.isoWorldRegion != nullptr) {
            this.isoWorldRegion.addRoof();
         }
      }
   }

    void resetRoofCnt() {
      if (this.isoWorldRegion != nullptr) {
         this.isoWorldRegion.removeRoofs(this.roofCnt);
      }

      this.roofCnt = 0;
   }

    void addSquareCount() {
      this.squareSize++;
   }

    int getChunkBorderSquaresCnt() {
      return this.chunkBorderSquaresCnt;
   }

    void addChunkBorderSquaresCnt() {
      this.chunkBorderSquaresCnt++;
   }

    void removeChunkBorderSquaresCnt() {
      this.chunkBorderSquaresCnt--;
      if (this.chunkBorderSquaresCnt < 0) {
         this.chunkBorderSquaresCnt = 0;
      }
   }

    void resetChunkBorderSquaresCnt() {
      this.chunkBorderSquaresCnt = 0;
   }

    void resetEnclosed() {
      for (byte var1 = 0; var1 < 4; var1++) {
         this.enclosed[var1] = true;
      }

      this.isDirtyEnclosed = false;
      this.enclosedCache = true;
   }

    void setEnclosed(uint8_t var1, bool var2) {
      this.isDirtyEnclosed = true;
      this.enclosed[var1] = var2;
   }

    void setDirtyEnclosed() {
      this.isDirtyEnclosed = true;
      if (this.isoWorldRegion != nullptr) {
         this.isoWorldRegion.setDirtyEnclosed();
      }
   }

    bool getIsEnclosed() {
      if (!this.isDirtyEnclosed) {
         return this.enclosedCache;
      } else {
         this.isDirtyEnclosed = false;
         this.enclosedCache = true;

         for (byte var1 = 0; var1 < 4; var1++) {
            if (!this.enclosed[var1]) {
               this.enclosedCache = false;
            }
         }

         if (this.isoWorldRegion != nullptr) {
            this.isoWorldRegion.setDirtyEnclosed();
         }

         return this.enclosedCache;
      }
   }

   public std::vector<IsoChunkRegion> getConnectedNeighbors() {
      return this.connectedNeighbors;
   }

    void addConnectedNeighbor(IsoChunkRegion var1) {
      if (var1 != nullptr) {
         if (!this.connectedNeighbors.contains(var1)) {
            this.connectedNeighbors.push_back(var1);
         }
      }
   }

    void removeConnectedNeighbor(IsoChunkRegion var1) {
      this.connectedNeighbors.remove(var1);
   }

    int getNeighborCount() {
      return this.allNeighbors.size();
   }

   protected std::vector<IsoChunkRegion> getAllNeighbors() {
      return this.allNeighbors;
   }

    void addNeighbor(IsoChunkRegion var1) {
      if (var1 != nullptr) {
         if (!this.allNeighbors.contains(var1)) {
            this.allNeighbors.push_back(var1);
         }
      }
   }

    void removeNeighbor(IsoChunkRegion var1) {
      this.allNeighbors.remove(var1);
   }

    void unlinkNeighbors() {
      for (int var2 = 0; var2 < this.connectedNeighbors.size(); var2++) {
    IsoChunkRegion var1 = this.connectedNeighbors.get(var2);
         var1.removeConnectedNeighbor(this);
      }

      this.connectedNeighbors.clear();

      for (int var4 = 0; var4 < this.allNeighbors.size(); var4++) {
    IsoChunkRegion var3 = this.allNeighbors.get(var4);
         var3.removeNeighbor(this);
      }

      this.allNeighbors.clear();
   }

   public std::vector<IsoChunkRegion> getDebugConnectedNeighborCopy() {
    std::vector var1 = new std::vector();
      if (this.connectedNeighbors.size() == 0) {
    return var1;
      } else {
         var1.addAll(this.connectedNeighbors);
    return var1;
      }
   }

    bool containsConnectedNeighbor(IsoChunkRegion var1) {
      return this.connectedNeighbors.contains(var1);
   }

    bool containsConnectedNeighborID(int var1) {
      if (this.connectedNeighbors.size() == 0) {
    return false;
      } else {
         for (int var3 = 0; var3 < this.connectedNeighbors.size(); var3++) {
    IsoChunkRegion var2 = this.connectedNeighbors.get(var3);
            if (var2.getID() == var1) {
    return true;
            }
         }

    return false;
      }
   }

    IsoChunkRegion getConnectedNeighborWithLargestIsoWorldRegion() {
      if (this.connectedNeighbors.size() == 0) {
    return nullptr;
      } else {
    IsoWorldRegion var1 = nullptr;
    IsoChunkRegion var2 = nullptr;

         for (int var4 = 0; var4 < this.connectedNeighbors.size(); var4++) {
    IsoChunkRegion var3 = this.connectedNeighbors.get(var4);
    IsoWorldRegion var5 = var3.getIsoWorldRegion();
            if (var5 != nullptr && (var1 == nullptr || var5.getSquareSize() > var1.getSquareSize())) {
               var1 = var5;
               var2 = var3;
            }
         }

    return var2;
      }
   }

    IsoChunkRegion getFirstNeighborWithIsoWorldRegion() {
      if (this.connectedNeighbors.size() == 0) {
    return nullptr;
      } else {
         for (int var2 = 0; var2 < this.connectedNeighbors.size(); var2++) {
    IsoChunkRegion var1 = this.connectedNeighbors.get(var2);
    IsoWorldRegion var3 = var1.getIsoWorldRegion();
            if (var3 != nullptr) {
    return var1;
            }
         }

    return nullptr;
      }
   }
}
} // namespace regions
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie
