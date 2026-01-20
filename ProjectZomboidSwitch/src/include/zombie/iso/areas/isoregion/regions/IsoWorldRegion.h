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


class IsoWorldRegion {
public:
    const IsoRegionManager manager;
    bool isInPool = false;
    int ID;
    Color color;
    bool enclosed = true;
   private std::vector<IsoChunkRegion> isoChunkRegions = std::make_unique<std::vector<>>();
    int squareSize = 0;
    int roofCnt = 0;
    bool isDirtyEnclosed = false;
    bool isDirtyRoofed = false;
   private std::vector<IsoWorldRegion> neighbors = std::make_unique<std::vector<>>();

    int getID() {
      return this.ID;
   }

    Color getColor() {
      return this.color;
   }

    int size() {
      return this.isoChunkRegions.size();
   }

    int getSquareSize() {
      return this.squareSize;
   }

    bool isInPool() {
      return this.isInPool;
   }

    protected IsoWorldRegion(IsoRegionManager var1) {
      this.manager = var1;
   }

    void init(int var1) {
      this.isInPool = false;
      this.ID = var1;
      if (this.color == nullptr) {
         this.color = this.manager.getColor();
      }

      this.squareSize = 0;
      this.roofCnt = 0;
      this.enclosed = true;
      this.isDirtyEnclosed = false;
      this.isDirtyRoofed = false;
   }

    IsoWorldRegion reset() {
      this.isInPool = true;
      this.ID = -1;
      this.squareSize = 0;
      this.roofCnt = 0;
      this.enclosed = true;
      this.isDirtyRoofed = false;
      this.isDirtyEnclosed = false;
      this.unlinkNeighbors();
      if (this.isoChunkRegions.size() > 0) {
         if (Core.bDebug) {
            throw RuntimeException("MasterRegion.reset Resetting master region which still has chunk regions");
         }

         IsoRegions.warn("MasterRegion.reset Resetting master region which still has chunk regions");

         for (int var2 = 0; var2 < this.isoChunkRegions.size(); var2++) {
    IsoChunkRegion var1 = this.isoChunkRegions.get(var2);
            var1.setIsoWorldRegion(nullptr);
         }

         this.isoChunkRegions.clear();
      }

    return this;
   }

    void unlinkNeighbors() {
      for (int var2 = 0; var2 < this.neighbors.size(); var2++) {
    IsoWorldRegion var1 = this.neighbors.get(var2);
         var1.removeNeighbor(this);
      }

      this.neighbors.clear();
   }

    void linkNeighbors() {
      for (int var3 = 0; var3 < this.isoChunkRegions.size(); var3++) {
    IsoChunkRegion var1 = this.isoChunkRegions.get(var3);

         for (int var4 = 0; var4 < var1.getAllNeighbors().size(); var4++) {
    IsoChunkRegion var2 = (IsoChunkRegion)var1.getAllNeighbors().get(var4);
            if (var2.getIsoWorldRegion() != nullptr && var2.getIsoWorldRegion() != this) {
               this.addNeighbor(var2.getIsoWorldRegion());
               var2.getIsoWorldRegion().addNeighbor(this);
            }
         }
      }
   }

    void addNeighbor(IsoWorldRegion var1) {
      if (!this.neighbors.contains(var1)) {
         this.neighbors.push_back(var1);
      }
   }

    void removeNeighbor(IsoWorldRegion var1) {
      this.neighbors.remove(var1);
   }

   public std::vector<IsoWorldRegion> getNeighbors() {
      return this.neighbors;
   }

   public std::vector<IsoWorldRegion> getDebugConnectedNeighborCopy() {
    std::vector var1 = new std::vector();
      if (this.neighbors.size() == 0) {
    return var1;
      } else {
         var1.addAll(this.neighbors);
    return var1;
      }
   }

    bool isFogMask() {
      return this.isEnclosed() && this.isFullyRoofed();
   }

    bool isPlayerRoom() {
      return this.isFogMask();
   }

    bool isFullyRoofed() {
      return this.roofCnt == this.squareSize;
   }

    float getRoofedPercentage() {
      return this.squareSize == 0 ? 0.0F : (float)this.roofCnt / this.squareSize;
   }

    int getRoofCnt() {
      return this.roofCnt;
   }

    void addRoof() {
      this.roofCnt++;
      if (this.roofCnt > this.squareSize) {
         IsoRegions.warn("WorldRegion.addRoof roofCount exceed squareSize.");
         this.roofCnt = this.squareSize;
      }
   }

    void removeRoofs(int var1) {
      if (var1 > 0) {
         this.roofCnt -= var1;
         if (this.roofCnt < 0) {
            IsoRegions.warn("MasterRegion.removeRoofs Roofcount managed to get below zero.");
            this.roofCnt = 0;
         }
      }
   }

    void addIsoChunkRegion(IsoChunkRegion var1) {
      if (!this.isoChunkRegions.contains(var1)) {
         this.squareSize = this.squareSize + var1.getSquareSize();
         this.roofCnt = this.roofCnt + var1.getRoofCnt();
         this.isDirtyEnclosed = true;
         this.isoChunkRegions.push_back(var1);
         var1.setIsoWorldRegion(this);
      }
   }

    void removeIsoChunkRegion(IsoChunkRegion var1) {
      if (this.isoChunkRegions.remove(var1)) {
         this.squareSize = this.squareSize - var1.getSquareSize();
         this.roofCnt = this.roofCnt - var1.getRoofCnt();
         this.isDirtyEnclosed = true;
         var1.setIsoWorldRegion(nullptr);
      }
   }

    bool containsIsoChunkRegion(IsoChunkRegion var1) {
      return this.isoChunkRegions.contains(var1);
   }

   public std::vector<IsoChunkRegion> swapIsoChunkRegions(std::vector<IsoChunkRegion> var1) {
    std::vector var2 = this.isoChunkRegions;
      this.isoChunkRegions = var1;
    return var2;
   }

    void resetSquareSize() {
      this.squareSize = 0;
   }

    void setDirtyEnclosed() {
      this.isDirtyEnclosed = true;
   }

    bool isEnclosed() {
      if (this.isDirtyEnclosed) {
         this.recalcEnclosed();
      }

      return this.enclosed;
   }

    void recalcEnclosed() {
      this.isDirtyEnclosed = false;
      this.enclosed = true;

      for (int var2 = 0; var2 < this.isoChunkRegions.size(); var2++) {
    IsoChunkRegion var1 = this.isoChunkRegions.get(var2);
         if (!var1.getIsEnclosed()) {
            this.enclosed = false;
         }
      }
   }

    void merge(IsoWorldRegion var1) {
      if (var1.isoChunkRegions.size() > 0) {
         for (int var2 = var1.isoChunkRegions.size() - 1; var2 >= 0; var2--) {
    IsoChunkRegion var3 = var1.isoChunkRegions.get(var2);
            var1.removeIsoChunkRegion(var3);
            this.addIsoChunkRegion(var3);
         }

         this.isDirtyEnclosed = true;
         var1.isoChunkRegions.clear();
      }

      if (var1.neighbors.size() > 0) {
         for (int var4 = 0; var4 < var1.neighbors.size(); var4++) {
    IsoWorldRegion var5 = var1.neighbors.get(var4);
            var5.removeNeighbor(var1);
            this.addNeighbor(var5);
         }

         var1.neighbors.clear();
      }

      this.manager.releaseIsoWorldRegion(var1);
   }

   public std::vector<IsoChunkRegion> getDebugIsoChunkRegionCopy() {
    std::vector var1 = new std::vector();
      var1.addAll(this.isoChunkRegions);
    return var1;
   }
}
} // namespace regions
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie
