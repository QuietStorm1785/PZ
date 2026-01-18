#pragma once
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"
#include "zombie/iso/areas/isoregion/IsoRegions.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {
namespace regions {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * TurboTuTone.
 */
class IsoWorldRegion {
public:
 const IsoRegionManager manager;
 bool isInPool = false;
 int ID;
 Color color;
 bool enclosed = true;
private
 ArrayList<IsoChunkRegion> isoChunkRegions = std::make_unique<ArrayList<>>();
 int squareSize = 0;
 int roofCnt = 0;
 bool isDirtyEnclosed = false;
 bool isDirtyRoofed = false;
private
 ArrayList<IsoWorldRegion> neighbors = std::make_unique<ArrayList<>>();

 int getID() { return this->ID; }

 Color getColor() { return this->color; }

 int size() { return this->isoChunkRegions.size(); }

 int getSquareSize() { return this->squareSize; }

 bool isInPool() { return this->isInPool; }

protected
 IsoWorldRegion(IsoRegionManager regionManager) {
 this->manager = regionManager;
 }

 void init(int int0) {
 this->isInPool = false;
 this->ID = int0;
 if (this->color.empty()) {
 this->color = this->manager.getColor();
 }

 this->squareSize = 0;
 this->roofCnt = 0;
 this->enclosed = true;
 this->isDirtyEnclosed = false;
 this->isDirtyRoofed = false;
 }

 IsoWorldRegion reset() {
 this->isInPool = true;
 this->ID = -1;
 this->squareSize = 0;
 this->roofCnt = 0;
 this->enclosed = true;
 this->isDirtyRoofed = false;
 this->isDirtyEnclosed = false;
 this->unlinkNeighbors();
 if (this->isoChunkRegions.size() > 0) {
 if (Core.bDebug) {
 throw RuntimeException("MasterRegion.reset Resetting master region "
 "which still has chunk regions");
 }

 IsoRegions.warn("MasterRegion.reset Resetting master region which still "
 "has chunk regions");

 for (int int0 = 0; int0 < this->isoChunkRegions.size(); int0++) {
 IsoChunkRegion chunkRegion = this->isoChunkRegions.get(int0);
 chunkRegion.setIsoWorldRegion(nullptr);
 }

 this->isoChunkRegions.clear();
 }

 return this;
 }

 void unlinkNeighbors() {
 for (int int0 = 0; int0 < this->neighbors.size(); int0++) {
 IsoWorldRegion worldRegion1 = this->neighbors.get(int0);
 worldRegion1.removeNeighbor(this);
 }

 this->neighbors.clear();
 }

 void linkNeighbors() {
 for (int int0 = 0; int0 < this->isoChunkRegions.size(); int0++) {
 IsoChunkRegion chunkRegion0 = this->isoChunkRegions.get(int0);

 for (int int1 = 0; int1 < chunkRegion0.getAllNeighbors().size(); int1++) {
 IsoChunkRegion chunkRegion1 = chunkRegion0.getAllNeighbors().get(int1);
 if (chunkRegion1.getIsoWorldRegion() != nullptr &&
 chunkRegion1.getIsoWorldRegion() != this) {
 this->addNeighbor(chunkRegion1.getIsoWorldRegion());
 chunkRegion1.getIsoWorldRegion().addNeighbor(this);
 }
 }
 }
 }

 void addNeighbor(IsoWorldRegion worldRegion0) {
 if (!this->neighbors.contains(worldRegion0) {
 this->neighbors.add(worldRegion0);
 }
 }

 void removeNeighbor(IsoWorldRegion worldRegion0) {
 this->neighbors.remove(worldRegion0);
 }

public
 ArrayList<IsoWorldRegion> getNeighbors() { return this->neighbors; }

public
 ArrayList<IsoWorldRegion> getDebugConnectedNeighborCopy() {
 std::vector arrayList = new ArrayList();
 if (this->neighbors.size() == 0) {
 return arrayList;
 } else {
 arrayList.addAll(this->neighbors);
 return arrayList;
 }
 }

 bool isFogMask() { return this->isEnclosed() && this->isFullyRoofed(); }

 bool isPlayerRoom() { return this->isFogMask(); }

 bool isFullyRoofed() { return this->roofCnt == this->squareSize; }

 float getRoofedPercentage() {
 return this->squareSize == 0 ? 0.0F : (float)this->roofCnt / this->squareSize;
 }

 int getRoofCnt() { return this->roofCnt; }

 void addRoof() {
 this->roofCnt++;
 if (this->roofCnt > this->squareSize) {
 IsoRegions.warn("WorldRegion.addRoof roofCount exceed squareSize.");
 this->roofCnt = this->squareSize;
 }
 }

 void removeRoofs(int int0) {
 if (int0 > 0) {
 this->roofCnt -= int0;
 if (this->roofCnt < 0) {
 IsoRegions.warn(
 "MasterRegion.removeRoofs Roofcount managed to get below zero.");
 this->roofCnt = 0;
 }
 }
 }

 void addIsoChunkRegion(IsoChunkRegion region) {
 if (!this->isoChunkRegions.contains(region) {
 this->squareSize = this->squareSize + region.getSquareSize();
 this->roofCnt = this->roofCnt + region.getRoofCnt();
 this->isDirtyEnclosed = true;
 this->isoChunkRegions.add(region);
 region.setIsoWorldRegion(this);
 }
 }

 void removeIsoChunkRegion(IsoChunkRegion chunkRegion) {
 if (this->isoChunkRegions.remove(chunkRegion) {
 this->squareSize = this->squareSize - chunkRegion.getSquareSize();
 this->roofCnt = this->roofCnt - chunkRegion.getRoofCnt();
 this->isDirtyEnclosed = true;
 chunkRegion.setIsoWorldRegion(nullptr);
 }
 }

 bool containsIsoChunkRegion(IsoChunkRegion region) {
 return this->isoChunkRegions.contains(region);
 }

public
 ArrayList<IsoChunkRegion>
 swapIsoChunkRegions(ArrayList<IsoChunkRegion> newlist) {
 std::vector arrayList = this->isoChunkRegions;
 this->isoChunkRegions = newlist;
 return arrayList;
 }

 void resetSquareSize() { this->squareSize = 0; }

 void setDirtyEnclosed() { this->isDirtyEnclosed = true; }

 bool isEnclosed() {
 if (this->isDirtyEnclosed) {
 this->recalcEnclosed();
 }

 return this->enclosed;
 }

 void recalcEnclosed() {
 this->isDirtyEnclosed = false;
 this->enclosed = true;

 for (int int0 = 0; int0 < this->isoChunkRegions.size(); int0++) {
 IsoChunkRegion chunkRegion = this->isoChunkRegions.get(int0);
 if (!chunkRegion.getIsEnclosed()) {
 this->enclosed = false;
 }
 }
 }

 void merge(IsoWorldRegion other) {
 if (other.isoChunkRegions.size() > 0) {
 for (int int0 = other.isoChunkRegions.size() - 1; int0 >= 0; int0--) {
 IsoChunkRegion chunkRegion = other.isoChunkRegions.get(int0);
 other.removeIsoChunkRegion(chunkRegion);
 this->addIsoChunkRegion(chunkRegion);
 }

 this->isDirtyEnclosed = true;
 other.isoChunkRegions.clear();
 }

 if (other.neighbors.size() > 0) {
 for (int int1 = 0; int1 < other.neighbors.size(); int1++) {
 IsoWorldRegion worldRegion = other.neighbors.get(int1);
 worldRegion.removeNeighbor(other);
 this->addNeighbor(worldRegion);
 }

 other.neighbors.clear();
 }

 this->manager.releaseIsoWorldRegion(other);
 }

public
 ArrayList<IsoChunkRegion> getDebugIsoChunkRegionCopy() {
 std::vector arrayList = new ArrayList();
 arrayList.addAll(this->isoChunkRegions);
 return arrayList;
 }
}
} // namespace regions
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie
