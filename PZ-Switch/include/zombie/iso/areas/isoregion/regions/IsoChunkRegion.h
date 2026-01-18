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
private
 boolean[] enclosed = new boolean[4];
 bool enclosedCache = true;
private
 ArrayList<IsoChunkRegion> connectedNeighbors =
 std::make_unique<ArrayList<>>();
private
 ArrayList<IsoChunkRegion> allNeighbors =
 std::make_unique<ArrayList<>>();
 bool isDirtyEnclosed = false;
 IsoWorldRegion isoWorldRegion;

 int getID() { return this->ID; }

 int getSquareSize() { return this->squareSize; }

 Color getColor() { return this->color; }

 int getzLayer() { return this->zLayer; }

 IsoWorldRegion getIsoWorldRegion() { return this->isoWorldRegion; }

 void setIsoWorldRegion(IsoWorldRegion mr) { this->isoWorldRegion = mr; }

 bool isInPool() { return this->isInPool; }

protected
 IsoChunkRegion(IsoRegionManager regionManager) {
 this->manager = regionManager;
 }

 void init(int int0, int int1) {
 this->isInPool = false;
 this->ID = int0;
 this->zLayer = (byte)int1;
 this->resetChunkBorderSquaresCnt();
 if (this->color.empty()) {
 this->color = this->manager.getColor();
 }

 this->squareSize = 0;
 this->roofCnt = 0;
 this->resetEnclosed();
 }

 IsoChunkRegion reset() {
 this->isInPool = true;
 this->unlinkNeighbors();
 IsoWorldRegion worldRegion = this->unlinkFromIsoWorldRegion();
 if (worldRegion != nullptr && worldRegion.size() <= 0) {
 if (Core.bDebug) {
 throw RuntimeException("ChunkRegion.reset IsoChunkRegion has "
 "IsoWorldRegion with 0 members.");
 }

 this->manager.releaseIsoWorldRegion(worldRegion);
 IsoRegions.warn("ChunkRegion.reset IsoChunkRegion has IsoWorldRegion "
 "with 0 members.");
 }

 this->resetChunkBorderSquaresCnt();
 this->ID = -1;
 this->squareSize = 0;
 this->roofCnt = 0;
 this->resetEnclosed();
 return this;
 }

 IsoWorldRegion unlinkFromIsoWorldRegion() {
 if (this->isoWorldRegion != nullptr) {
 IsoWorldRegion worldRegion = this->isoWorldRegion;
 this->isoWorldRegion.removeIsoChunkRegion(this);
 this->isoWorldRegion = nullptr;
 return worldRegion;
 } else {
 return nullptr;
 }
 }

 int getRoofCnt() { return this->roofCnt; }

 void addRoof() {
 this->roofCnt++;
 if (this->roofCnt > this->squareSize) {
 IsoRegions.warn("ChunkRegion.addRoof roofCount exceed squareSize.");
 this->roofCnt = this->squareSize;
 } else {
 if (this->isoWorldRegion != nullptr) {
 this->isoWorldRegion.addRoof();
 }
 }
 }

 void resetRoofCnt() {
 if (this->isoWorldRegion != nullptr) {
 this->isoWorldRegion.removeRoofs(this->roofCnt);
 }

 this->roofCnt = 0;
 }

 void addSquareCount() { this->squareSize++; }

 int getChunkBorderSquaresCnt() { return this->chunkBorderSquaresCnt; }

 void addChunkBorderSquaresCnt() { this->chunkBorderSquaresCnt++; }

 void removeChunkBorderSquaresCnt() {
 this->chunkBorderSquaresCnt--;
 if (this->chunkBorderSquaresCnt < 0) {
 this->chunkBorderSquaresCnt = 0;
 }
 }

 void resetChunkBorderSquaresCnt() { this->chunkBorderSquaresCnt = 0; }

 void resetEnclosed() {
 for (byte byte0 = 0; byte0 < 4; byte0++) {
 this->enclosed[byte0] = true;
 }

 this->isDirtyEnclosed = false;
 this->enclosedCache = true;
 }

 void setEnclosed(uint8_t dir, bool b) {
 this->isDirtyEnclosed = true;
 this->enclosed[dir] = b;
 }

 void setDirtyEnclosed() {
 this->isDirtyEnclosed = true;
 if (this->isoWorldRegion != nullptr) {
 this->isoWorldRegion.setDirtyEnclosed();
 }
 }

 bool getIsEnclosed() {
 if (!this->isDirtyEnclosed) {
 return this->enclosedCache;
 } else {
 this->isDirtyEnclosed = false;
 this->enclosedCache = true;

 for (byte byte0 = 0; byte0 < 4; byte0++) {
 if (!this->enclosed[byte0]) {
 this->enclosedCache = false;
 }
 }

 if (this->isoWorldRegion != nullptr) {
 this->isoWorldRegion.setDirtyEnclosed();
 }

 return this->enclosedCache;
 }
 }

public
 ArrayList<IsoChunkRegion> getConnectedNeighbors() {
 return this->connectedNeighbors;
 }

 void addConnectedNeighbor(IsoChunkRegion neighbor) {
 if (neighbor != nullptr) {
 if (!this->connectedNeighbors.contains(neighbor) {
 this->connectedNeighbors.add(neighbor);
 }
 }
 }

 void removeConnectedNeighbor(IsoChunkRegion chunkRegion0) {
 this->connectedNeighbors.remove(chunkRegion0);
 }

 int getNeighborCount() { return this->allNeighbors.size(); }

protected
 ArrayList<IsoChunkRegion> getAllNeighbors() { return this->allNeighbors; }

 void addNeighbor(IsoChunkRegion neighbor) {
 if (neighbor != nullptr) {
 if (!this->allNeighbors.contains(neighbor) {
 this->allNeighbors.add(neighbor);
 }
 }
 }

 void removeNeighbor(IsoChunkRegion chunkRegion0) {
 this->allNeighbors.remove(chunkRegion0);
 }

 void unlinkNeighbors() {
 for (int int0 = 0; int0 < this->connectedNeighbors.size(); int0++) {
 IsoChunkRegion chunkRegion1 = this->connectedNeighbors.get(int0);
 chunkRegion1.removeConnectedNeighbor(this);
 }

 this->connectedNeighbors.clear();

 for (int int1 = 0; int1 < this->allNeighbors.size(); int1++) {
 IsoChunkRegion chunkRegion2 = this->allNeighbors.get(int1);
 chunkRegion2.removeNeighbor(this);
 }

 this->allNeighbors.clear();
 }

public
 ArrayList<IsoChunkRegion> getDebugConnectedNeighborCopy() {
 std::vector arrayList = new ArrayList();
 if (this->connectedNeighbors.size() == 0) {
 return arrayList;
 } else {
 arrayList.addAll(this->connectedNeighbors);
 return arrayList;
 }
 }

 bool containsConnectedNeighbor(IsoChunkRegion n) {
 return this->connectedNeighbors.contains(n);
 }

 bool containsConnectedNeighborID(int id) {
 if (this->connectedNeighbors.size() == 0) {
 return false;
 } else {
 for (int int0 = 0; int0 < this->connectedNeighbors.size(); int0++) {
 IsoChunkRegion chunkRegion = this->connectedNeighbors.get(int0);
 if (chunkRegion.getID() == id) {
 return true;
 }
 }

 return false;
 }
 }

 IsoChunkRegion getConnectedNeighborWithLargestIsoWorldRegion() {
 if (this->connectedNeighbors.size() == 0) {
 return nullptr;
 } else {
 IsoWorldRegion worldRegion0 = nullptr;
 IsoChunkRegion chunkRegion1 = nullptr;

 for (int int0 = 0; int0 < this->connectedNeighbors.size(); int0++) {
 IsoChunkRegion chunkRegion2 = this->connectedNeighbors.get(int0);
 IsoWorldRegion worldRegion1 = chunkRegion2.getIsoWorldRegion();
 if (worldRegion1 != nullptr &&
 (worldRegion0.empty() ||
 worldRegion1.getSquareSize() > worldRegion0.getSquareSize())) {
 worldRegion0 = worldRegion1;
 chunkRegion1 = chunkRegion2;
 }
 }

 return chunkRegion1;
 }
 }

 IsoChunkRegion getFirstNeighborWithIsoWorldRegion() {
 if (this->connectedNeighbors.size() == 0) {
 return nullptr;
 } else {
 for (int int0 = 0; int0 < this->connectedNeighbors.size(); int0++) {
 IsoChunkRegion chunkRegion1 = this->connectedNeighbors.get(int0);
 IsoWorldRegion worldRegion = chunkRegion1.getIsoWorldRegion();
 if (worldRegion != nullptr) {
 return chunkRegion1;
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
