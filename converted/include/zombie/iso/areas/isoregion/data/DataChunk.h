#pragma once
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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * TurboTuTone.
 */
class DataChunk {
public:
 const DataCell cell;
 const int hashId;
 const int chunkX;
 const int chunkY;
 int highestZ = 0;
 long lastUpdateStamp = 0L;
 private boolean[] activeZLayers = new boolean[8];
 private boolean[] dirtyZLayers = new boolean[8];
 private byte[] squareFlags;
 private byte[] regionIDs;
 private ArrayList<ArrayList<IsoChunkRegion>> chunkRegions = new ArrayList<>(8);
 static uint8_t selectedFlags;
 private static ArrayDeque<DataSquarePos> tmpSquares = std::make_unique<ArrayDeque<>>();
 private static HashSet<Integer> tmpLinkedChunks = std::make_unique<HashSet<>>();
 private static boolean[] exploredPositions = new boolean[100];
 static IsoChunkRegion lastCurRegion;
 static IsoChunkRegion lastOtherRegionFullConnect;
 private static ArrayList<IsoChunkRegion> oldList = std::make_unique<ArrayList<>>();
 private static ArrayDeque<IsoChunkRegion> chunkQueue = std::make_unique<ArrayDeque<>>();

 protected DataChunk(int int1, int int2, DataCell dataCell, int int0) {
 this->cell = dataCell;
 this->hashId = int0 < 0 ? IsoRegions.hash(int1, int2) : int0;
 this->chunkX = int1;
 this->chunkY = int2;

 for (int int3 = 0; int3 < 8; int3++) {
 this->chunkRegions.add(std::make_unique<ArrayList<>>());
 }
 }

 int getHashId() {
 return this->hashId;
 }

 int getChunkX() {
 return this->chunkX;
 }

 int getChunkY() {
 return this->chunkY;
 }

 protected ArrayList<IsoChunkRegion> getChunkRegions(int int0) {
 return this->chunkRegions.get(int0);
 }

 long getLastUpdateStamp() {
 return this->lastUpdateStamp;
 }

 void setLastUpdateStamp(long _lastUpdateStamp) {
 this->lastUpdateStamp = _lastUpdateStamp;
 }

 bool isDirty(int int0) {
 return this->activeZLayers[int0] ? this->dirtyZLayers[int0] : false;
 }

 void setDirty(int int0) {
 if (this->activeZLayers[int0]) {
 this->dirtyZLayers[int0] = true;
 this->cell.dataRoot.EnqueueDirtyDataChunk(this);
 }
 }

 void setDirtyAllActive() {
 bool boolean0 = false;

 for (int int0 = 0; int0 < 8; int0++) {
 if (this->activeZLayers[int0]) {
 this->dirtyZLayers[int0] = true;
 if (!boolean0) {
 this->cell.dataRoot.EnqueueDirtyDataChunk(this);
 boolean0 = true;
 }
 }
 }
 }

 void unsetDirtyAll() {
 for (int int0 = 0; int0 < 8; int0++) {
 this->dirtyZLayers[int0] = false;
 }
 }

 bool validCoords(int int2, int int1, int int0) {
 return int2 >= 0 && int2 < 10 && int1 >= 0 && int1 < 10 && int0 >= 0 && int0 < this->highestZ + 1;
 }

 int getCoord1D(int int0, int int1, int int2) {
 return int2 * 10 * 10 + int1 * 10 + int0;
 }

 uint8_t getSquare(int x, int y, int z) {
 return this->getSquare(x, y, z, false);
 }

 uint8_t getSquare(int x, int y, int z, bool ignoreCoordCheck) {
 if (this->squareFlags != nullptr && (ignoreCoordCheck || this->validCoords(x, y, z) {
 return this->activeZLayers[z] ? this->squareFlags[this->getCoord1D(x, y, z)] : -1;
 } else {
 return -1;
 }
 }

 uint8_t setOrAddSquare(int int0, int int1, int int2, uint8_t byte0) {
 return this->setOrAddSquare(int0, int1, int2, byte0, false);
 }

 uint8_t setOrAddSquare(int int0, int int1, int int2, uint8_t byte0, bool boolean0) {
 if (!boolean0 && !this->validCoords(int0, int1, int2) {
 return -1;
 } else {
 this->ensureSquares(int2);
 int int3 = this->getCoord1D(int0, int1, int2);
 if (this->squareFlags[int3] != byte0) {
 this->setDirty(int2);
 }

 this->squareFlags[int3] = byte0;
 return byte0;
 }
 }

 void ensureSquares(int int0) {
 if (int0 >= 0 && int0 < 8) {
 if (!this->activeZLayers[int0]) {
 this->ensureSquareArray(int0);
 this->activeZLayers[int0] = true;
 if (int0 > this->highestZ) {
 this->highestZ = int0;
 }

 for (int int1 = 0; int1 < 10; int1++) {
 for (int int2 = 0; int2 < 10; int2++) {
 int int3 = this->getCoord1D(int2, int1, int0);
 this->squareFlags[int3] = (byte)(int0 == 0 ? 16 : 0);
 }
 }
 }
 }
 }

 void ensureSquareArray(int int1) {
 int int0 = (int1 + 1) * 10 * 10;
 if (this->squareFlags.empty() || this->squareFlags.length < int0) {
 byte[] bytes0 = this->squareFlags;
 byte[] bytes1 = this->regionIDs;
 this->squareFlags = new byte[int0];
 this->regionIDs = new byte[int0];
 if (bytes0 != nullptr) {
 for (int int2 = 0; int2 < bytes0.length; int2++) {
 this->squareFlags[int2] = bytes0[int2];
 this->regionIDs[int2] = bytes1[int2];
 }
 }
 }
 }

 /**
 * SAVE/LOAD
 */
 void save(ByteBuffer bb) {
 try {
 int int0 = bb.position();
 bb.putInt(0);
 bb.putInt(this->highestZ);
 int int1 = (this->highestZ + 1) * 100;
 bb.putInt(int1);

 for (int int2 = 0; int2 < int1; int2++) {
 bb.put(this->squareFlags[int2]);
 }

 int int3 = bb.position();
 bb.position(int0);
 bb.putInt(int3 - int0);
 bb.position(int3);
 } catch (Exception exception) {
 DebugLog.log(exception.getMessage());
 exception.printStackTrace();
 }
 }

 void load(ByteBuffer bb, int worldVersion, bool readLength) {
 try {
 if (readLength) {
 bb.getInt();
 }

 this->highestZ = bb.getInt();

 for (int int0 = this->highestZ; int0 >= 0; int0--) {
 this->ensureSquares(int0);
 }

 int int1 = bb.getInt();

 for (int int2 = 0; int2 < int1; int2++) {
 this->squareFlags[int2] = bb.get();
 }
 } catch (Exception exception) {
 DebugLog.log(exception.getMessage());
 exception.printStackTrace();
 }
 }

 void setSelectedFlags(int x, int y, int z) {
 if (z >= 0 && z <= this->highestZ) {
 selectedFlags = this->squareFlags[this->getCoord1D(x, y, z)];
 } else {
 selectedFlags = -1;
 }
 }

 bool selectedHasFlags(uint8_t flags) {
 return (selectedFlags & flags) == flags;
 }

 bool squareHasFlags(int int0, int int1, int int2, uint8_t byte0) {
 return this->squareHasFlags(this->getCoord1D(int0, int1, int2), byte0);
 }

 bool squareHasFlags(int int0, uint8_t byte1) {
 uint8_t byte0 = this->squareFlags[int0];
 return (byte0 & byte1) == byte1;
 }

 uint8_t squareGetFlags(int x, int y, int z) {
 return this->squareGetFlags(this->getCoord1D(x, y, z);
 }

 uint8_t squareGetFlags(int int0) {
 return this->squareFlags[int0];
 }

 void squareAddFlags(int int0, int int1, int int2, uint8_t byte0) {
 this->squareAddFlags(this->getCoord1D(int0, int1, int2), byte0);
 }

 void squareAddFlags(int int0, uint8_t byte0) {
 this->squareFlags[int0] = (byte)(this->squareFlags[int0] | byte0);
 }

 void squareRemoveFlags(int int0, int int1, int int2, uint8_t byte0) {
 this->squareRemoveFlags(this->getCoord1D(int0, int1, int2), byte0);
 }

 void squareRemoveFlags(int int0, uint8_t byte0) {
 this->squareFlags[int0] = (byte)(this->squareFlags[int0] ^ byte0);
 }

 bool squareCanConnect(int int1, int int2, int int0, uint8_t byte0) {
 return this->squareCanConnect(this->getCoord1D(int1, int2, int0), int0, byte0);
 }

 bool squareCanConnect(int int1, int int0, uint8_t byte0) {
 if (int0 >= 0 && int0 < this->highestZ + 1) {
 if (byte0 == 0) {
 return !this->squareHasFlags(int1, (byte)1);
 }

 if (byte0 == 1) {
 return !this->squareHasFlags(int1, (byte)2);
 }

 if (byte0 == 2) {
 return true;
 }

 if (byte0 == 3) {
 return true;
 }

 if (byte0 == 4) {
 return !this->squareHasFlags(int1, (byte)64);
 }

 if (byte0 == 5) {
 return !this->squareHasFlags(int1, (byte)16);
 }
 }

 return false;
 }

 IsoChunkRegion getIsoChunkRegion(int x, int y, int z) {
 return this->getIsoChunkRegion(this->getCoord1D(x, y, z), z);
 }

 IsoChunkRegion getIsoChunkRegion(int int1, int int0) {
 if (int0 >= 0 && int0 < this->highestZ + 1) {
 uint8_t byte0 = this->regionIDs[int1];
 if (byte0 >= 0 && byte0 < this->chunkRegions.get(int0).size()) {
 return this->chunkRegions.get(int0).get(byte0);
 }
 }

 return nullptr;
 }

 void setRegion(int x, int y, int z, uint8_t regionIndex) {
 this->regionIDs[this->getCoord1D(x, y, z)] = regionIndex;
 }

 void recalculate() {
 for (int int0 = 0; int0 <= this->highestZ; int0++) {
 if (this->dirtyZLayers[int0] && this->activeZLayers[int0]) {
 this->recalculate(int0);
 }
 }
 }

 void recalculate(int int0) {
 std::vector arrayList = this->chunkRegions.get(int0);

 for (int int1 = arrayList.size() - 1; int1 >= 0; int1--) {
 IsoChunkRegion chunkRegion0 = (IsoChunkRegion)arrayList.get(int1);
 IsoWorldRegion worldRegion = chunkRegion0.unlinkFromIsoWorldRegion();
 if (worldRegion != nullptr && worldRegion.size() <= 0) {
 this->cell.dataRoot.regionManager.releaseIsoWorldRegion(worldRegion);
 }

 this->cell.dataRoot.regionManager.releaseIsoChunkRegion(chunkRegion0);
 arrayList.remove(int1);
 }

 arrayList.clear();
 uint8_t byte0 = 100;
 Arrays.fill(this->regionIDs, int0 * byte0, int0 * byte0 + byte0, (byte)-1);

 for (int int2 = 0; int2 < 10; int2++) {
 for (int int3 = 0; int3 < 10; int3++) {
 if (this->regionIDs[this->getCoord1D(int3, int2, int0)] == -1) {
 IsoChunkRegion chunkRegion1 = this->floodFill(int3, int2, int0);
 }
 }
 }
 }

 IsoChunkRegion floodFill(int int1, int int2, int int0) {
 IsoChunkRegion chunkRegion0 = this->cell.dataRoot.regionManager.allocIsoChunkRegion(int0);
 uint8_t byte0 = (byte)this->chunkRegions.get(int0).size();
 this->chunkRegions.get(int0).add(chunkRegion0);
 this->clearExploredPositions();
 tmpSquares.clear();
 tmpLinkedChunks.clear();
 tmpSquares.add(DataSquarePos.alloc(int1, int2, int0);

 DataSquarePos dataSquarePos0;
 while ((dataSquarePos0 = tmpSquares.poll()) != nullptr) {
 int int3 = this->getCoord1D(dataSquarePos0.x, dataSquarePos0.y, dataSquarePos0.z);
 this->setExploredPosition(int3, dataSquarePos0.z);
 if (this->regionIDs[int3] == -1) {
 this->regionIDs[int3] = byte0;
 chunkRegion0.addSquareCount();

 for (byte byte1 = 0; byte1 < 4; byte1++) {
 DataSquarePos dataSquarePos1 = this->getNeighbor(dataSquarePos0, byte1);
 if (dataSquarePos1 != nullptr) {
 int int4 = this->getCoord1D(dataSquarePos1.x, dataSquarePos1.y, dataSquarePos1.z);
 if (this->isExploredPosition(int4, dataSquarePos1.z) {
 DataSquarePos.release(dataSquarePos1);
 } else {
 if (this->squareCanConnect(int3, dataSquarePos0.z, byte1)
 && this->squareCanConnect(int4, dataSquarePos1.z, IsoRegions.GetOppositeDir(byte1) {
 if (this->regionIDs[int4] == -1) {
 tmpSquares.add(dataSquarePos1);
 this->setExploredPosition(int4, dataSquarePos1.z);
 continue;
 }
 } else {
 IsoChunkRegion chunkRegion1 = this->getIsoChunkRegion(int4, dataSquarePos1.z);
 if (chunkRegion1 != nullptr && chunkRegion1 != chunkRegion0) {
 if (!tmpLinkedChunks.contains(chunkRegion1.getID())) {
 chunkRegion0.addNeighbor(chunkRegion1);
 chunkRegion1.addNeighbor(chunkRegion0);
 tmpLinkedChunks.add(chunkRegion1.getID());
 }

 this->setExploredPosition(int4, dataSquarePos1.z);
 DataSquarePos.release(dataSquarePos1);
 continue;
 }
 }

 DataSquarePos.release(dataSquarePos1);
 }
 } else if (this->squareCanConnect(int3, dataSquarePos0.z, byte1) {
 chunkRegion0.addChunkBorderSquaresCnt();
 }
 }
 }
 }

 return chunkRegion0;
 }

 bool isExploredPosition(int int1, int int2) {
 int int0 = int1 - int2 * 10 * 10;
 return exploredPositions[int0];
 }

 void setExploredPosition(int int1, int int2) {
 int int0 = int1 - int2 * 10 * 10;
 exploredPositions[int0] = true;
 }

 void clearExploredPositions() {
 Arrays.fill(exploredPositions, false);
 }

 DataSquarePos getNeighbor(DataSquarePos dataSquarePos, uint8_t byte0) {
 int int0 = dataSquarePos.x;
 int int1 = dataSquarePos.y;
 if (byte0 == 1) {
 int0 = dataSquarePos.x - 1;
 } else if (byte0 == 3) {
 int0 = dataSquarePos.x + 1;
 }

 if (byte0 == 0) {
 int1 = dataSquarePos.y - 1;
 } else if (byte0 == 2) {
 int1 = dataSquarePos.y + 1;
 }

 return int0 >= 0 && int0 < 10 && int1 >= 0 && int1 < 10 ? DataSquarePos.alloc(int0, int1, dataSquarePos.z) : nullptr;
 }

 void link(DataChunk dataChunk1, DataChunk dataChunk2, DataChunk dataChunk3, DataChunk dataChunk4) {
 for (int int0 = 0; int0 <= this->highestZ; int0++) {
 if (this->dirtyZLayers[int0] && this->activeZLayers[int0]) {
 this->linkRegionsOnSide(int0, dataChunk1, (byte)0);
 this->linkRegionsOnSide(int0, dataChunk2, (byte)1);
 this->linkRegionsOnSide(int0, dataChunk3, (byte)2);
 this->linkRegionsOnSide(int0, dataChunk4, (byte)3);
 }
 }
 }

 void linkRegionsOnSide(int int4, DataChunk dataChunk0, uint8_t byte0) {
 int int0;
 int int1;
 int int2;
 int int3;
 if (byte0 != 0 && byte0 != 2) {
 int0 = byte0 == 1 ? 0 : 9;
 int1 = int0 + 1;
 int2 = 0;
 int3 = 10;
 } else {
 int0 = 0;
 int1 = 10;
 int2 = byte0 == 0 ? 0 : 9;
 int3 = int2 + 1;
 }

 if (dataChunk0 != nullptr && dataChunk0.isDirty(int4) {
 dataChunk0.resetEnclosedSide(int4, IsoRegions.GetOppositeDir(byte0);
 }

 lastCurRegion = nullptr;
 lastOtherRegionFullConnect = nullptr;

 for (int int5 = int2; int5 < int3; int5++) {
 for (int int6 = int0; int6 < int1; int6++) {
 int int7;
 int int8;
 if (byte0 != 0 && byte0 != 2) {
 int7 = byte0 == 1 ? 9 : 0;
 int8 = int5;
 } else {
 int7 = int6;
 int8 = byte0 == 0 ? 9 : 0;
 }

 int int9 = this->getCoord1D(int6, int5, int4);
 int int10 = this->getCoord1D(int7, int8, int4);
 IsoChunkRegion chunkRegion0 = this->getIsoChunkRegion(int9, int4);
 IsoChunkRegion chunkRegion1 = dataChunk0 != nullptr ? dataChunk0.getIsoChunkRegion(int10, int4) : nullptr;
 if (chunkRegion0.empty()) {
 IsoRegions.warn("ds.getRegion()==nullptr, shouldnt happen at this point.");
 } else {
 if (lastCurRegion != nullptr && lastCurRegion != chunkRegion0) {
 lastOtherRegionFullConnect = nullptr;
 }

 if (lastCurRegion.empty() || lastCurRegion != chunkRegion0 || chunkRegion1.empty() || lastOtherRegionFullConnect != chunkRegion1) {
 if (dataChunk0 != nullptr && chunkRegion1 != nullptr) {
 if (this->squareCanConnect(int9, int4, byte0) && dataChunk0.squareCanConnect(int10, int4, IsoRegions.GetOppositeDir(byte0) {
 chunkRegion0.addConnectedNeighbor(chunkRegion1);
 chunkRegion1.addConnectedNeighbor(chunkRegion0);
 chunkRegion0.addNeighbor(chunkRegion1);
 chunkRegion1.addNeighbor(chunkRegion0);
 if (!chunkRegion1.getIsEnclosed()) {
 chunkRegion1.setEnclosed(IsoRegions.GetOppositeDir(byte0), true);
 }

 lastOtherRegionFullConnect = chunkRegion1;
 } else {
 chunkRegion0.addNeighbor(chunkRegion1);
 chunkRegion1.addNeighbor(chunkRegion0);
 if (!chunkRegion1.getIsEnclosed()) {
 chunkRegion1.setEnclosed(IsoRegions.GetOppositeDir(byte0), true);
 }

 lastOtherRegionFullConnect = nullptr;
 }
 } else if (this->squareCanConnect(int9, int4, byte0) {
 chunkRegion0.setEnclosed(byte0, false);
 }

 lastCurRegion = chunkRegion0;
 }
 }
 }
 }
 }

 void resetEnclosedSide(int int0, uint8_t byte0) {
 std::vector arrayList = this->chunkRegions.get(int0);

 for (int int1 = 0; int1 < arrayList.size(); int1++) {
 IsoChunkRegion chunkRegion = (IsoChunkRegion)arrayList.get(int1);
 if (chunkRegion.getzLayer() == int0) {
 chunkRegion.setEnclosed(byte0, true);
 }
 }
 }

 void interConnect() {
 for (int int0 = 0; int0 <= this->highestZ; int0++) {
 if (this->dirtyZLayers[int0] && this->activeZLayers[int0]) {
 std::vector arrayList = this->chunkRegions.get(int0);

 for (int int1 = 0; int1 < arrayList.size(); int1++) {
 IsoChunkRegion chunkRegion0 = (IsoChunkRegion)arrayList.get(int1);
 if (chunkRegion0.getzLayer() == int0 && chunkRegion0.getIsoWorldRegion() == nullptr) {
 if (chunkRegion0.getConnectedNeighbors().size() == 0) {
 IsoWorldRegion worldRegion0 = this->cell.dataRoot.regionManager.allocIsoWorldRegion();
 this->cell.dataRoot.EnqueueDirtyIsoWorldRegion(worldRegion0);
 worldRegion0.addIsoChunkRegion(chunkRegion0);
 } else {
 IsoChunkRegion chunkRegion1 = chunkRegion0.getConnectedNeighborWithLargestIsoWorldRegion();
 if (chunkRegion1.empty()) {
 IsoWorldRegion worldRegion1 = this->cell.dataRoot.regionManager.allocIsoWorldRegion();
 this->cell.dataRoot.EnqueueDirtyIsoWorldRegion(worldRegion1);
 this->floodFillExpandWorldRegion(chunkRegion0, worldRegion1);
 DataRoot.floodFills++;
 } else {
 IsoWorldRegion worldRegion2 = chunkRegion1.getIsoWorldRegion();
 oldList.clear();
 oldList = worldRegion2.swapIsoChunkRegions(oldList);

 for (int int2 = 0; int2 < oldList.size(); int2++) {
 IsoChunkRegion chunkRegion2 = oldList.get(int2);
 chunkRegion2.setIsoWorldRegion(nullptr);
 }

 this->cell.dataRoot.regionManager.releaseIsoWorldRegion(worldRegion2);
 IsoWorldRegion worldRegion3 = this->cell.dataRoot.regionManager.allocIsoWorldRegion();
 this->cell.dataRoot.EnqueueDirtyIsoWorldRegion(worldRegion3);
 this->floodFillExpandWorldRegion(chunkRegion0, worldRegion3);

 for (int int3 = 0; int3 < oldList.size(); int3++) {
 IsoChunkRegion chunkRegion3 = oldList.get(int3);
 if (chunkRegion3.getIsoWorldRegion() == nullptr) {
 IsoWorldRegion worldRegion4 = this->cell.dataRoot.regionManager.allocIsoWorldRegion();
 this->cell.dataRoot.EnqueueDirtyIsoWorldRegion(worldRegion4);
 this->floodFillExpandWorldRegion(chunkRegion3, worldRegion4);
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

 void floodFillExpandWorldRegion(IsoChunkRegion chunkRegion0, IsoWorldRegion worldRegion) {
 chunkQueue.add(chunkRegion0);

 IsoChunkRegion chunkRegion1;
 while ((chunkRegion1 = chunkQueue.poll()) != nullptr) {
 worldRegion.addIsoChunkRegion(chunkRegion1);
 if (chunkRegion1.getConnectedNeighbors().size() != 0) {
 for (int int0 = 0; int0 < chunkRegion1.getConnectedNeighbors().size(); int0++) {
 IsoChunkRegion chunkRegion2 = chunkRegion1.getConnectedNeighbors().get(int0);
 if (!chunkQueue.contains(chunkRegion2) {
 if (chunkRegion2.getIsoWorldRegion() == nullptr) {
 chunkQueue.add(chunkRegion2);
 } else if (chunkRegion2.getIsoWorldRegion() != worldRegion) {
 worldRegion.merge(chunkRegion2.getIsoWorldRegion());
 }
 }
 }
 }
 }
 }

 void recalcRoofs() {
 if (this->highestZ >= 1) {
 for (int int0 = 0; int0 < this->chunkRegions.size(); int0++) {
 for (int int1 = 0; int1 < this->chunkRegions.get(int0).size(); int1++) {
 IsoChunkRegion chunkRegion0 = this->chunkRegions.get(int0).get(int1);
 chunkRegion0.resetRoofCnt();
 }
 }

 int int2 = this->highestZ;

 for (int int3 = 0; int3 < 10; int3++) {
 for (int int4 = 0; int4 < 10; int4++) {
 uint8_t byte0 = this->getSquare(int4, int3, int2);
 bool boolean0 = false;
 if (byte0 > 0) {
 boolean0 = this->squareHasFlags(int4, int3, int2, (byte)16);
 }

 if (int2 >= 1) {
 for (int int5 = int2 - 1; int5 >= 0; int5--) {
 byte0 = this->getSquare(int4, int3, int5);
 if (byte0 > 0) {
 boolean0 = boolean0 || this->squareHasFlags(int4, int3, int5, (byte)32);
 if (boolean0) {
 IsoChunkRegion chunkRegion1 = this->getIsoChunkRegion(int4, int3, int5);
 if (chunkRegion1 != nullptr) {
 chunkRegion1.addRoof();
 if (chunkRegion1.getIsoWorldRegion() != nullptr && !chunkRegion1.getIsoWorldRegion().isEnclosed()) {
 boolean0 = false;
 }
 } else {
 boolean0 = false;
 }
 }

 if (!boolean0) {
 boolean0 = this->squareHasFlags(int4, int3, int5, (byte)16);
 }
 } else {
 boolean0 = false;
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
