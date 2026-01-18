#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/physics/WorldSimulation.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/utils/UpdateLimit.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/iso/areas/IsoRoom.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/MPStatistics.h"
#include "zombie/network/PacketTypes.h"
#include "zombie/ui/TextManager.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/VehicleCache.h"
#include "zombie/vehicles/VehicleManager.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class IsoChunkMap {
public:
 static const int LEVELS = 8;
 static const int ChunksPerWidth = 10;
 public static HashMap<Integer, IsoChunk> SharedChunks = std::make_unique<HashMap<>>();
 static int MPWorldXA = 0;
 static int MPWorldYA = 0;
 static int MPWorldZA = 0;
 static int WorldXA = 11702;
 static int WorldYA = 6896;
 static int WorldZA = 0;
 public static int[] SWorldX = new int[4];
 public static int[] SWorldY = new int[4];
 public static ConcurrentLinkedQueue<IsoChunk> chunkStore = std::make_unique<ConcurrentLinkedQueue<>>();
 static const ReentrantLock bSettingChunk = new ReentrantLock(true);
 static int StartChunkGridWidth = 13;
 static int ChunkGridWidth = StartChunkGridWidth;
 static int ChunkWidthInTiles = 10 * ChunkGridWidth;
 static const ColorInfo inf = new ColorInfo();
 private static ArrayList<IsoChunk> saveList = std::make_unique<ArrayList<>>();
 private static ArrayList<ArrayList<IsoFloorBloodSplat>> splatByType = std::make_unique<ArrayList<>>();
 int PlayerID = 0;
 bool ignore = false;
 int WorldX = tileToChunk(WorldXA);
 int WorldY = tileToChunk(WorldYA);
 public ArrayList<String> filenameServerRequests = std::make_unique<ArrayList<>>();
 protected IsoChunk[] chunksSwapB;
 protected IsoChunk[] chunksSwapA;
 bool bReadBufferA = true;
 int XMinTiles = -1;
 int YMinTiles = -1;
 int XMaxTiles = -1;
 int YMaxTiles = -1;
 IsoCell cell;
 const UpdateLimit checkVehiclesFrequency = new UpdateLimit(3000L);

 public IsoChunkMap(IsoCell _cell) {
 this->cell = _cell;
 WorldReuserThread.instance.finished = false;
 this->chunksSwapB = new IsoChunk[ChunkGridWidth * ChunkGridWidth];
 this->chunksSwapA = new IsoChunk[ChunkGridWidth * ChunkGridWidth];
 }

 static void CalcChunkWidth() {
 if (DebugOptions.instance.WorldChunkMap5x5.getValue()) {
 ChunkGridWidth = 5;
 ChunkWidthInTiles = ChunkGridWidth * 10;
 } else {
 float float0 = Core.getInstance().getScreenWidth();
 float float1 = float0 / 1920.0F;
 if (float1 > 1.0F) {
 float1 = 1.0F;
 }

 ChunkGridWidth = (int)(StartChunkGridWidth * float1 * 1.5);
 if (ChunkGridWidth / 2 * 2 == ChunkGridWidth) {
 ChunkGridWidth++;
 }

 ChunkWidthInTiles = ChunkGridWidth * 10;
 }
 }

 static void setWorldStartPos(int x, int y) {
 SWorldX[IsoPlayer.getPlayerIndex()] = tileToChunk(x);
 SWorldY[IsoPlayer.getPlayerIndex()] = tileToChunk(y);
 }

 void Dispose() {
 WorldReuserThread.instance.finished = true;
 IsoChunk.loadGridSquare.clear();
 this->chunksSwapA = nullptr;
 this->chunksSwapB = nullptr;
 }

 void setInitialPos(int wx, int wy) {
 this->WorldX = wx;
 this->WorldY = wy;
 this->XMinTiles = -1;
 this->XMaxTiles = -1;
 this->YMinTiles = -1;
 this->YMaxTiles = -1;
 }

 void processAllLoadGridSquare() {
 for (IsoChunk chunk = IsoChunk.loadGridSquare.poll(); chunk != nullptr; chunk = IsoChunk.loadGridSquare.poll()) {
 bSettingChunk.lock();

 try {
 bool boolean0 = false;

 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 IsoChunkMap chunkMap = IsoWorld.instance.CurrentCell.ChunkMap[int0];
 if (!chunkMap.ignore && chunkMap.setChunkDirect(chunk, false) {
 boolean0 = true;
 }
 }

 if (!boolean0) {
 WorldReuserThread.instance.addReuseChunk(chunk);
 } else {
 chunk.doLoadGridsquare();
 }
 } finally {
 bSettingChunk.unlock();
 }
 }
 }

 void update() {
 int int0 = IsoChunk.loadGridSquare.size();
 if (int0 != 0) {
 int0 = 1 + int0 * 3 / ChunkGridWidth;
 }

 while (int0 > 0) {
 IsoChunk chunk0 = IsoChunk.loadGridSquare.poll();
 if (chunk0 != nullptr) {
 bool boolean0 = false;

 for (int int1 = 0; int1 < IsoPlayer.numPlayers; int1++) {
 IsoChunkMap chunkMap0 = IsoWorld.instance.CurrentCell.ChunkMap[int1];
 if (!chunkMap0.ignore && chunkMap0.setChunkDirect(chunk0, false) {
 boolean0 = true;
 }
 }

 if (!boolean0) {
 WorldReuserThread.instance.addReuseChunk(chunk0);
 int0--;
 continue;
 }

 chunk0.bLoaded = true;
 bSettingChunk.lock();

 try {
 chunk0.doLoadGridsquare();
 if (GameClient.bClient) {
 std::vector list = VehicleCache.vehicleGet(chunk0.wx, chunk0.wy);
 VehicleManager.instance.sendRequestGetFull(list);
 }
 } finally {
 bSettingChunk.unlock();
 }

 for (int int2 = 0; int2 < IsoPlayer.numPlayers; int2++) {
 IsoPlayer player = IsoPlayer.players[int2];
 if (player != nullptr) {
 player.dirtyRecalcGridStackTime = 20.0F;
 }
 }
 }

 int0--;
 }

 for (int int3 = 0; int3 < ChunkGridWidth; int3++) {
 for (int int4 = 0; int4 < ChunkGridWidth; int4++) {
 IsoChunk chunk1 = this->getChunk(int4, int3);
 if (chunk1 != nullptr) {
 chunk1.update();
 }
 }
 }

 if (this->checkVehiclesFrequency.Check() && GameClient.bClient) {
 this->checkVehicles();
 }
 }

 void checkVehicles() {
 for (int int0 = 0; int0 < ChunkGridWidth; int0++) {
 for (int int1 = 0; int1 < ChunkGridWidth; int1++) {
 IsoChunk chunk = this->getChunk(int1, int0);
 if (chunk != nullptr && chunk.bLoaded) {
 std::vector list = VehicleCache.vehicleGet(chunk.wx, chunk.wy);
 if (list != nullptr && chunk.vehicles.size() != list.size()) {
 for (int int2 = 0; int2 < list.size(); int2++) {
 short short0 = ((VehicleCache)list.get(int2).id;
 bool boolean0 = false;

 for (int int3 = 0; int3 < chunk.vehicles.size(); int3++) {
 if (chunk.vehicles.get(int3).getId() == short0) {
 boolean0 = true;
 break;
 }
 }

 if (!boolean0 && VehicleManager.instance.getVehicleByID(short0) == nullptr) {
 VehicleManager.instance.sendRequestGetFull(short0, PacketTypes.PacketType.Vehicles);
 }
 }
 }
 }
 }
 }
 }

 void checkIntegrity() {
 IsoWorld.instance.CurrentCell.ChunkMap[0].XMinTiles = -1;

 for (int int0 = IsoWorld.instance.CurrentCell.ChunkMap[0].getWorldXMinTiles();
 int0 < IsoWorld.instance.CurrentCell.ChunkMap[0].getWorldXMaxTiles();
 int0++
 ) {
 for (int int1 = IsoWorld.instance.CurrentCell.ChunkMap[0].getWorldYMinTiles();
 int1 < IsoWorld.instance.CurrentCell.ChunkMap[0].getWorldYMaxTiles();
 int1++
 ) {
 IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare(int0, int1, 0);
 if (square != nullptr && (square.getX() != int0 || square.getY() != int1) {
 int int2 = int0 / 10;
 int int3 = int1 / 10;
 int2 -= IsoWorld.instance.CurrentCell.ChunkMap[0].getWorldXMin();
 int3 -= IsoWorld.instance.CurrentCell.ChunkMap[0].getWorldYMin();
 void* object = nullptr;
 object = new IsoChunk(IsoWorld.instance.CurrentCell);
 ((IsoChunk)object).refs.add(IsoWorld.instance.CurrentCell.ChunkMap[0]);
 WorldStreamer.instance.addJob((IsoChunk)object, int0 / 10, int1 / 10, false);

 while (!((IsoChunk)object).bLoaded) {
 try {
 Thread.sleep(13L);
 } catch (InterruptedException interruptedException) {
 interruptedException.printStackTrace();
 }
 }
 }
 }
 }
 }

 void checkIntegrityThread() {
 IsoWorld.instance.CurrentCell.ChunkMap[0].XMinTiles = -1;

 for (int int0 = IsoWorld.instance.CurrentCell.ChunkMap[0].getWorldXMinTiles();
 int0 < IsoWorld.instance.CurrentCell.ChunkMap[0].getWorldXMaxTiles();
 int0++
 ) {
 for (int int1 = IsoWorld.instance.CurrentCell.ChunkMap[0].getWorldYMinTiles();
 int1 < IsoWorld.instance.CurrentCell.ChunkMap[0].getWorldYMaxTiles();
 int1++
 ) {
 IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare(int0, int1, 0);
 if (square != nullptr && (square.getX() != int0 || square.getY() != int1) {
 int int2 = int0 / 10;
 int int3 = int1 / 10;
 int2 -= IsoWorld.instance.CurrentCell.ChunkMap[0].getWorldXMin();
 int3 -= IsoWorld.instance.CurrentCell.ChunkMap[0].getWorldYMin();
 IsoChunk chunk = new IsoChunk(IsoWorld.instance.CurrentCell);
 chunk.refs.add(IsoWorld.instance.CurrentCell.ChunkMap[0]);
 WorldStreamer.instance.addJobInstant(chunk, int0, int1, int0 / 10, int1 / 10);
 }

 if (square != nullptr) {
 }
 }
 }
 }

 void LoadChunk(int wx, int wy, int x, int y) {
 IsoChunk chunk = nullptr;
 if (SharedChunks.containsKey((wx << 16) + wy) {
 chunk = SharedChunks.get((wx << 16) + wy);
 chunk.setCache();
 this->setChunk(x, y, chunk);
 chunk.refs.add(this);
 } else {
 chunk = chunkStore.poll();
 if (chunk == nullptr) {
 chunk = new IsoChunk(this->cell);
 } else {
 MPStatistics.decreaseStoredChunk();
 }

 SharedChunks.put((wx << 16) + wy, chunk);
 chunk.refs.add(this);
 WorldStreamer.instance.addJob(chunk, wx, wy, false);
 }
 }

 IsoChunk LoadChunkForLater(int wx, int wy, int x, int y) {
 if (!IsoWorld.instance.getMetaGrid().isValidChunk(wx, wy) {
 return nullptr;
 } else {
 IsoChunk chunk;
 if (SharedChunks.containsKey((wx << 16) + wy) {
 chunk = SharedChunks.get((wx << 16) + wy);
 if (!chunk.refs.contains(this) {
 chunk.refs.add(this);
 chunk.lightCheck[this->PlayerID] = true;
 }

 if (!chunk.bLoaded) {
 return chunk;
 }

 this->setChunk(x, y, chunk);
 } else {
 chunk = chunkStore.poll();
 if (chunk == nullptr) {
 chunk = new IsoChunk(this->cell);
 } else {
 MPStatistics.decreaseStoredChunk();
 }

 SharedChunks.put((wx << 16) + wy, chunk);
 chunk.refs.add(this);
 WorldStreamer.instance.addJob(chunk, wx, wy, true);
 }

 return chunk;
 }
 }

 IsoChunk getChunkForGridSquare(int x, int y) {
 x = this->gridSquareToTileX(x);
 y = this->gridSquareToTileY(y);
 return !this->isTileOutOfrange(x) && !this->isTileOutOfrange(y) ? this->getChunk(tileToChunk(x), tileToChunk(y) : nullptr;
 }

 IsoChunk getChunkCurrent(int x, int y) {
 if (x < 0 || x >= ChunkGridWidth || y < 0 || y >= ChunkGridWidth) {
 return nullptr;
 } else {
 return !this->bReadBufferA ? this->chunksSwapA[ChunkGridWidth * y + x] : this->chunksSwapB[ChunkGridWidth * y + x];
 }
 }

 void setGridSquare(IsoGridSquare square, int x, int y, int z) {
 assert square = = nullptr || square.x == x && square.y == y && square.z == z;

 int int0 = this->gridSquareToTileX(x);
 int int1 = this->gridSquareToTileY(y);
 if (!this->isTileOutOfrange(int0) && !this->isTileOutOfrange(int1) && !this->isGridSquareOutOfRangeZ(z) {
 IsoChunk chunk = this->getChunk(tileToChunk(int0), tileToChunk(int1);
 if (chunk != nullptr) {
 if (z > chunk.maxLevel) {
 chunk.maxLevel = z;
 }

 chunk.setSquare(this->tileToGridSquare(int0), this->tileToGridSquare(int1), z, square);
 }
 }
 }

 IsoGridSquare getGridSquare(int x, int y, int z) {
 x = this->gridSquareToTileX(x);
 y = this->gridSquareToTileY(y);
 return this->getGridSquareDirect(x, y, z);
 }

 IsoGridSquare getGridSquareDirect(int tileX, int tileY, int tileZ) {
 if (!this->isTileOutOfrange(tileX) && !this->isTileOutOfrange(tileY) && !this->isGridSquareOutOfRangeZ(tileZ) {
 IsoChunk chunk = this->getChunk(tileToChunk(tileX), tileToChunk(tileY);
 return chunk = = nullptr ? nullptr : chunk.getGridSquare(this->tileToGridSquare(tileX), this->tileToGridSquare(tileY), tileZ);
 } else {
 return nullptr;
 }
 }

 int tileToGridSquare(int int0) {
 return int0 % 10;
 }

 static int tileToChunk(int int0) {
 return int0 / 10;
 }

 bool isTileOutOfrange(int int0) {
 return int0 < 0 || int0 >= this->getWidthInTiles();
 }

 bool isGridSquareOutOfRangeZ(int int0) {
 return int0 < 0 || int0 >= 8;
 }

 int gridSquareToTileX(int int0) {
 return int0 - (this->WorldX - ChunkGridWidth / 2) * 10;
 }

 int gridSquareToTileY(int int0) {
 return int0 - (this->WorldY - ChunkGridWidth / 2) * 10;
 }

 IsoChunk getChunk(int x, int y) {
 if (x < 0 || x >= ChunkGridWidth || y < 0 || y >= ChunkGridWidth) {
 return nullptr;
 } else {
 return this->bReadBufferA ? this->chunksSwapA[ChunkGridWidth * y + x] : this->chunksSwapB[ChunkGridWidth * y + x];
 }
 }

 void setChunk(int int0, int int1, IsoChunk chunk) {
 if (!this->bReadBufferA) {
 this->chunksSwapA[ChunkGridWidth * int1 + int0] = chunk;
 } else {
 this->chunksSwapB[ChunkGridWidth * int1 + int0] = chunk;
 }
 }

 bool setChunkDirect(IsoChunk c, bool bRequireLock) {
 long long0 = System.nanoTime();
 if (bRequireLock) {
 bSettingChunk.lock();
 }

 long long1 = System.nanoTime();
 int int0 = c.wx - this->WorldX;
 int int1 = c.wy - this->WorldY;
 int0 += ChunkGridWidth / 2;
 int1 += ChunkGridWidth / 2;
 if (c.jobType == IsoChunk.JobType.Convert) {
 int0 = 0;
 int1 = 0;
 }

 if (!c.refs.empty() && int0 >= 0 && int1 >= 0 && int0 < ChunkGridWidth && int1 < ChunkGridWidth) {
 try {
 if (this->bReadBufferA) {
 this->chunksSwapA[ChunkGridWidth * int1 + int0] = c;
 } else {
 this->chunksSwapB[ChunkGridWidth * int1 + int0] = c;
 }

 c.bLoaded = true;
 if (c.jobType == IsoChunk.JobType.None) {
 c.setCache();
 c.updateBuildings();
 }

 double double0 = (System.nanoTime() - long1) / 1000000.0;
 double double1 = (System.nanoTime() - long0) / 1000000.0;
 if (LightingThread.DebugLockTime && double1 > 10.0) {
 DebugLog.log("setChunkDirect time " + double0 + "/" + double1 + " ms");
 }
 } finally {
 if (bRequireLock) {
 bSettingChunk.unlock();
 }
 }

 return true;
 } else {
 if (c.refs.contains(this) {
 c.refs.remove(this);
 if (c.refs.empty()) {
 SharedChunks.remove((c.wx << 16) + c.wy);
 }
 }

 if (bRequireLock) {
 bSettingChunk.unlock();
 }

 return false;
 }
 }

 void drawDebugChunkMap() {
 short short0 = 64;
 uint8_t byte0 = 0;

 for (int int0 = 0; int0 < ChunkGridWidth; int0++) {
 byte0 = 0;

 for (int int1 = 0; int1 < ChunkGridWidth; int1++) {
 byte0 += 64;
 IsoChunk chunk = this->getChunk(int0, int1);
 if (chunk != nullptr) {
 IsoGridSquare square = chunk.getGridSquare(0, 0, 0);
 if (square == nullptr) {
 TextManager.instance.DrawString(short0, byte0, "wx:" + chunk.wx + " wy:" + chunk.wy);
 }
 }
 }

 short0 += 128;
 }
 }

 void LoadLeft() {
 this->XMinTiles = -1;
 this->YMinTiles = -1;
 this->XMaxTiles = -1;
 this->YMaxTiles = -1;
 this->Left();
 WorldSimulation.instance.scrollGroundLeft(this->PlayerID);
 this->XMinTiles = -1;
 this->YMinTiles = -1;
 this->XMaxTiles = -1;
 this->YMaxTiles = -1;

 for (int int0 = -(ChunkGridWidth / 2); int0 <= ChunkGridWidth / 2; int0++) {
 this->LoadChunkForLater(this->WorldX - ChunkGridWidth / 2, this->WorldY + int0, 0, int0 + ChunkGridWidth / 2);
 }

 this->SwapChunkBuffers();
 this->XMinTiles = -1;
 this->YMinTiles = -1;
 this->XMaxTiles = -1;
 this->YMaxTiles = -1;
 this->UpdateCellCache();
 LightingThread.instance.scrollLeft(this->PlayerID);
 }

 void SwapChunkBuffers() {
 for (int int0 = 0; int0 < ChunkGridWidth * ChunkGridWidth; int0++) {
 if (this->bReadBufferA) {
 this->chunksSwapA[int0] = nullptr;
 } else {
 this->chunksSwapB[int0] = nullptr;
 }
 }

 this->XMinTiles = this->XMaxTiles = -1;
 this->YMinTiles = this->YMaxTiles = -1;
 this->bReadBufferA = !this->bReadBufferA;
 }

 void setChunk(int int0, IsoChunk chunk) {
 if (!this->bReadBufferA) {
 this->chunksSwapA[int0] = chunk;
 } else {
 this->chunksSwapB[int0] = chunk;
 }
 }

 IsoChunk getChunk(int int0) {
 return this->bReadBufferA ? this->chunksSwapA[int0] : this->chunksSwapB[int0];
 }

 void LoadRight() {
 this->XMinTiles = -1;
 this->YMinTiles = -1;
 this->XMaxTiles = -1;
 this->YMaxTiles = -1;
 this->Right();
 WorldSimulation.instance.scrollGroundRight(this->PlayerID);
 this->XMinTiles = -1;
 this->YMinTiles = -1;
 this->XMaxTiles = -1;
 this->YMaxTiles = -1;

 for (int int0 = -(ChunkGridWidth / 2); int0 <= ChunkGridWidth / 2; int0++) {
 this->LoadChunkForLater(this->WorldX + ChunkGridWidth / 2, this->WorldY + int0, ChunkGridWidth - 1, int0 + ChunkGridWidth / 2);
 }

 this->SwapChunkBuffers();
 this->XMinTiles = -1;
 this->YMinTiles = -1;
 this->XMaxTiles = -1;
 this->YMaxTiles = -1;
 this->UpdateCellCache();
 LightingThread.instance.scrollRight(this->PlayerID);
 }

 void LoadUp() {
 this->XMinTiles = -1;
 this->YMinTiles = -1;
 this->XMaxTiles = -1;
 this->YMaxTiles = -1;
 this->Up();
 WorldSimulation.instance.scrollGroundUp(this->PlayerID);
 this->XMinTiles = -1;
 this->YMinTiles = -1;
 this->XMaxTiles = -1;
 this->YMaxTiles = -1;

 for (int int0 = -(ChunkGridWidth / 2); int0 <= ChunkGridWidth / 2; int0++) {
 this->LoadChunkForLater(this->WorldX + int0, this->WorldY - ChunkGridWidth / 2, int0 + ChunkGridWidth / 2, 0);
 }

 this->SwapChunkBuffers();
 this->XMinTiles = -1;
 this->YMinTiles = -1;
 this->XMaxTiles = -1;
 this->YMaxTiles = -1;
 this->UpdateCellCache();
 LightingThread.instance.scrollUp(this->PlayerID);
 }

 void LoadDown() {
 this->XMinTiles = -1;
 this->YMinTiles = -1;
 this->XMaxTiles = -1;
 this->YMaxTiles = -1;
 this->Down();
 WorldSimulation.instance.scrollGroundDown(this->PlayerID);
 this->XMinTiles = -1;
 this->YMinTiles = -1;
 this->XMaxTiles = -1;
 this->YMaxTiles = -1;

 for (int int0 = -(ChunkGridWidth / 2); int0 <= ChunkGridWidth / 2; int0++) {
 this->LoadChunkForLater(this->WorldX + int0, this->WorldY + ChunkGridWidth / 2, int0 + ChunkGridWidth / 2, ChunkGridWidth - 1);
 }

 this->SwapChunkBuffers();
 this->XMinTiles = -1;
 this->YMinTiles = -1;
 this->XMaxTiles = -1;
 this->YMaxTiles = -1;
 this->UpdateCellCache();
 LightingThread.instance.scrollDown(this->PlayerID);
 }

 void UpdateCellCache() {
 int int0 = this->getWidthInTiles();

 for (int int1 = 0; int1 < int0; int1++) {
 for (int int2 = 0; int2 < int0; int2++) {
 for (int int3 = 0; int3 < 8; int3++) {
 IsoGridSquare square = this->getGridSquare(int1 + this->getWorldXMinTiles(), int2 + this->getWorldYMinTiles(), int3);
 IsoWorld.instance.CurrentCell.setCacheGridSquareLocal(int1, int2, int3, square, this->PlayerID);
 }
 }
 }
 }

 void Up() {
 for (int int0 = 0; int0 < ChunkGridWidth; int0++) {
 for (int int1 = ChunkGridWidth - 1; int1 > 0; int1--) {
 IsoChunk chunk = this->getChunk(int0, int1);
 if (chunk == nullptr && int1 == ChunkGridWidth - 1) {
 int int2 = this->WorldX - ChunkGridWidth / 2 + int0;
 int int3 = this->WorldY - ChunkGridWidth / 2 + int1;
 chunk = SharedChunks.get((int2 << 16) + int3);
 if (chunk != nullptr) {
 if (chunk.refs.contains(this) {
 chunk.refs.remove(this);
 if (chunk.refs.empty()) {
 SharedChunks.remove((chunk.wx << 16) + chunk.wy);
 }
 }

 chunk = nullptr;
 }
 }

 if (chunk != nullptr && int1 == ChunkGridWidth - 1) {
 chunk.refs.remove(this);
 if (chunk.refs.empty()) {
 SharedChunks.remove((chunk.wx << 16) + chunk.wy);
 chunk.removeFromWorld();
 ChunkSaveWorker.instance.Add(chunk);
 }
 }

 this->setChunk(int0, int1, this->getChunk(int0, int1 - 1);
 }

 this->setChunk(int0, 0, nullptr);
 }

 this->WorldY--;
 }

 void Down() {
 for (int int0 = 0; int0 < ChunkGridWidth; int0++) {
 for (int int1 = 0; int1 < ChunkGridWidth - 1; int1++) {
 IsoChunk chunk = this->getChunk(int0, int1);
 if (chunk == nullptr && int1 == 0) {
 int int2 = this->WorldX - ChunkGridWidth / 2 + int0;
 int int3 = this->WorldY - ChunkGridWidth / 2 + int1;
 chunk = SharedChunks.get((int2 << 16) + int3);
 if (chunk != nullptr) {
 if (chunk.refs.contains(this) {
 chunk.refs.remove(this);
 if (chunk.refs.empty()) {
 SharedChunks.remove((chunk.wx << 16) + chunk.wy);
 }
 }

 chunk = nullptr;
 }
 }

 if (chunk != nullptr && int1 == 0) {
 chunk.refs.remove(this);
 if (chunk.refs.empty()) {
 SharedChunks.remove((chunk.wx << 16) + chunk.wy);
 chunk.removeFromWorld();
 ChunkSaveWorker.instance.Add(chunk);
 }
 }

 this->setChunk(int0, int1, this->getChunk(int0, int1 + 1);
 }

 this->setChunk(int0, ChunkGridWidth - 1, nullptr);
 }

 this->WorldY++;
 }

 void Left() {
 for (int int0 = 0; int0 < ChunkGridWidth; int0++) {
 for (int int1 = ChunkGridWidth - 1; int1 > 0; int1--) {
 IsoChunk chunk = this->getChunk(int1, int0);
 if (chunk == nullptr && int1 == ChunkGridWidth - 1) {
 int int2 = this->WorldX - ChunkGridWidth / 2 + int1;
 int int3 = this->WorldY - ChunkGridWidth / 2 + int0;
 chunk = SharedChunks.get((int2 << 16) + int3);
 if (chunk != nullptr) {
 if (chunk.refs.contains(this) {
 chunk.refs.remove(this);
 if (chunk.refs.empty()) {
 SharedChunks.remove((chunk.wx << 16) + chunk.wy);
 }
 }

 chunk = nullptr;
 }
 }

 if (chunk != nullptr && int1 == ChunkGridWidth - 1) {
 chunk.refs.remove(this);
 if (chunk.refs.empty()) {
 SharedChunks.remove((chunk.wx << 16) + chunk.wy);
 chunk.removeFromWorld();
 ChunkSaveWorker.instance.Add(chunk);
 }
 }

 this->setChunk(int1, int0, this->getChunk(int1 - 1, int0);
 }

 this->setChunk(0, int0, nullptr);
 }

 this->WorldX--;
 }

 void Right() {
 for (int int0 = 0; int0 < ChunkGridWidth; int0++) {
 for (int int1 = 0; int1 < ChunkGridWidth - 1; int1++) {
 IsoChunk chunk = this->getChunk(int1, int0);
 if (chunk == nullptr && int1 == 0) {
 int int2 = this->WorldX - ChunkGridWidth / 2 + int1;
 int int3 = this->WorldY - ChunkGridWidth / 2 + int0;
 chunk = SharedChunks.get((int2 << 16) + int3);
 if (chunk != nullptr) {
 if (chunk.refs.contains(this) {
 chunk.refs.remove(this);
 if (chunk.refs.empty()) {
 SharedChunks.remove((chunk.wx << 16) + chunk.wy);
 }
 }

 chunk = nullptr;
 }
 }

 if (chunk != nullptr && int1 == 0) {
 chunk.refs.remove(this);
 if (chunk.refs.empty()) {
 SharedChunks.remove((chunk.wx << 16) + chunk.wy);
 chunk.removeFromWorld();
 ChunkSaveWorker.instance.Add(chunk);
 }
 }

 this->setChunk(int1, int0, this->getChunk(int1 + 1, int0);
 }

 this->setChunk(ChunkGridWidth - 1, int0, nullptr);
 }

 this->WorldX++;
 }

 int getWorldXMin() {
 return this->WorldX - ChunkGridWidth / 2;
 }

 int getWorldYMin() {
 return this->WorldY - ChunkGridWidth / 2;
 }

 void ProcessChunkPos(IsoGameCharacter chr) {
 int int0 = (int)chr.getX();
 int int1 = (int)chr.getY();
 int int2 = (int)chr.getZ();
 if (IsoPlayer.getInstance() != nullptr && IsoPlayer.getInstance().getVehicle() != nullptr) {
 IsoPlayer player0 = IsoPlayer.getInstance();
 BaseVehicle vehicle = player0.getVehicle();
 float float0 = vehicle.getCurrentSpeedKmHour() / 5.0F;
 if (!player0.isDriving()) {
 float0 = Math.min(float0 * 2.0F, 20.0F);
 }

 int0 += Math.round(player0.getForwardDirection().x * float0);
 int1 += Math.round(player0.getForwardDirection().y * float0);
 }

 int0 /= 10;
 int1 /= 10;
 if (int0 != this->WorldX || int1 != this->WorldY) {
 long long0 = System.nanoTime();
 double double0 = 0.0;
 bSettingChunk.lock();
 long long1 = System.nanoTime();

 try {
 if (Math.abs(int0 - this->WorldX) < ChunkGridWidth && Math.abs(int1 - this->WorldY) < ChunkGridWidth) {
 if (int0 != this->WorldX) {
 if (int0 < this->WorldX) {
 this->LoadLeft();
 } else {
 this->LoadRight();
 }
 } else if (int1 != this->WorldY) {
 if (int1 < this->WorldY) {
 this->LoadUp();
 } else {
 this->LoadDown();
 }
 }
 } else {
 if (LightingJNI.init) {
 LightingJNI.teleport(this->PlayerID, int0 - ChunkGridWidth / 2, int1 - ChunkGridWidth / 2);
 }

 this->Unload();
 IsoPlayer player1 = IsoPlayer.players[this->PlayerID];
 player1.removeFromSquare();
 player1.square = nullptr;
 this->WorldX = int0;
 this->WorldY = int1;
 if (!GameServer.bServer) {
 WorldSimulation.instance.activateChunkMap(this->PlayerID);
 }

 int int3 = this->WorldX - ChunkGridWidth / 2;
 int int4 = this->WorldY - ChunkGridWidth / 2;
 int int5 = this->WorldX + ChunkGridWidth / 2;
 int int6 = this->WorldY + ChunkGridWidth / 2;

 for (int int7 = int3; int7 <= int5; int7++) {
 for (int int8 = int4; int8 <= int6; int8++) {
 this->LoadChunkForLater(int7, int8, int7 - int3, int8 - int4);
 }
 }

 this->SwapChunkBuffers();
 this->UpdateCellCache();
 if (!IsoWorld.instance.getCell().getObjectList().contains(player1) {
 IsoWorld.instance.getCell().getAddList().add(player1);
 }
 }
 } finally {
 bSettingChunk.unlock();
 }

 double0 = (System.nanoTime() - long1) / 1000000.0;
 double double1 = (System.nanoTime() - long0) / 1000000.0;
 if (LightingThread.DebugLockTime && double1 > 10.0) {
 DebugLog.log("ProcessChunkPos time " + double0 + "/" + double1 + " ms");
 }
 }
 }

 IsoRoom getRoom(int iD) {
 return nullptr;
 }

 int getWidthInTiles() {
 return ChunkWidthInTiles;
 }

 int getWorldXMinTiles() {
 if (this->XMinTiles != -1) {
 return this->XMinTiles;
 } else {
 this->XMinTiles = this->getWorldXMin() * 10;
 return this->XMinTiles;
 }
 }

 int getWorldYMinTiles() {
 if (this->YMinTiles != -1) {
 return this->YMinTiles;
 } else {
 this->YMinTiles = this->getWorldYMin() * 10;
 return this->YMinTiles;
 }
 }

 int getWorldXMaxTiles() {
 if (this->XMaxTiles != -1) {
 return this->XMaxTiles;
 } else {
 this->XMaxTiles = this->getWorldXMin() * 10 + this->getWidthInTiles();
 return this->XMaxTiles;
 }
 }

 int getWorldYMaxTiles() {
 if (this->YMaxTiles != -1) {
 return this->YMaxTiles;
 } else {
 this->YMaxTiles = this->getWorldYMin() * 10 + this->getWidthInTiles();
 return this->YMaxTiles;
 }
 }

 void Save() {
 if (!GameServer.bServer) {
 for (int int0 = 0; int0 < ChunkGridWidth; int0++) {
 for (int int1 = 0; int1 < ChunkGridWidth; int1++) {
 IsoChunk chunk = this->getChunk(int0, int1);
 if (chunk != nullptr && !saveList.contains(chunk) {
 try {
 chunk.Save(true);
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }
 }
 }
 }
 }
 }

 void renderBloodForChunks(int zza) {
 if (DebugOptions.instance.Terrain.RenderTiles.BloodDecals.getValue()) {
 if (!(zza > IsoCamera.CamCharacter.z) {
 if (Core.OptionBloodDecals != 0) {
 float float0 = (float)GameTime.getInstance().getWorldAgeHours();
 int int0 = IsoCamera.frameState.playerIndex;

 for (int int1 = 0; int1 < IsoFloorBloodSplat.FloorBloodTypes.length; int1++) {
 splatByType.get(int1).clear();
 }

 for (int int2 = 0; int2 < ChunkGridWidth; int2++) {
 for (int int3 = 0; int3 < ChunkGridWidth; int3++) {
 IsoChunk chunk = this->getChunk(int2, int3);
 if (chunk != nullptr) {
 for (int int4 = 0; int4 < chunk.FloorBloodSplatsFade.size(); int4++) {
 IsoFloorBloodSplat floorBloodSplat0 = chunk.FloorBloodSplatsFade.get(int4);
 if ((
 floorBloodSplat0.index < 1
 || floorBloodSplat0.index > 10
 || IsoChunk.renderByIndex[Core.OptionBloodDecals - 1][floorBloodSplat0.index - 1] != 0
 )
 && (int)floorBloodSplat0.z == zza
 && floorBloodSplat0.Type >= 0
 && floorBloodSplat0.Type < IsoFloorBloodSplat.FloorBloodTypes.length) {
 floorBloodSplat0.chunk = chunk;
 splatByType.get(floorBloodSplat0.Type).add(floorBloodSplat0);
 }
 }

 if (!chunk.FloorBloodSplats.empty()) {
 for (int int5 = 0; int5 < chunk.FloorBloodSplats.size(); int5++) {
 IsoFloorBloodSplat floorBloodSplat1 = chunk.FloorBloodSplats.get(int5);
 if ((
 floorBloodSplat1.index < 1
 || floorBloodSplat1.index > 10
 || IsoChunk.renderByIndex[Core.OptionBloodDecals - 1][floorBloodSplat1.index - 1] != 0
 )
 && (int)floorBloodSplat1.z == zza
 && floorBloodSplat1.Type >= 0
 && floorBloodSplat1.Type < IsoFloorBloodSplat.FloorBloodTypes.length) {
 floorBloodSplat1.chunk = chunk;
 splatByType.get(floorBloodSplat1.Type).add(floorBloodSplat1);
 }
 }
 }
 }
 }
 }

 for (int int6 = 0; int6 < splatByType.size(); int6++) {
 std::vector arrayList = splatByType.get(int6);
 if (!arrayList.empty()) {
 std::string string = IsoFloorBloodSplat.FloorBloodTypes[int6];
 IsoSprite sprite0 = nullptr;
 if (!IsoFloorBloodSplat.SpriteMap.containsKey(string) {
 IsoSprite sprite1 = IsoSprite.CreateSprite(IsoSpriteManager.instance);
 sprite1.LoadFramesPageSimple(string, string, string, string);
 IsoFloorBloodSplat.SpriteMap.put(string, sprite1);
 sprite0 = sprite1;
 } else {
 sprite0 = IsoFloorBloodSplat.SpriteMap.get(string);
 }

 for (int int7 = 0; int7 < arrayList.size(); int7++) {
 IsoFloorBloodSplat floorBloodSplat2 = (IsoFloorBloodSplat)arrayList.get(int7);
 inf.r = 1.0F;
 inf.g = 1.0F;
 inf.b = 1.0F;
 inf.a = 0.27F;
 float float1 = (floorBloodSplat2.x + floorBloodSplat2.y / floorBloodSplat2.x) * (floorBloodSplat2.Type + 1);
 float float2 = float1 * floorBloodSplat2.x / floorBloodSplat2.y * (floorBloodSplat2.Type + 1) / (float1 + floorBloodSplat2.y);
 float float3 = float2 * float1 * float2 * floorBloodSplat2.x / (floorBloodSplat2.y + 2.0F);
 float1 *= 42367.543F;
 float2 *= 6367.123F;
 float3 *= 23367.133F;
 float1 %= 1000.0F;
 float2 %= 1000.0F;
 float3 %= 1000.0F;
 float1 /= 1000.0F;
 float2 /= 1000.0F;
 float3 /= 1000.0F;
 if (float1 > 0.25F) {
 float1 = 0.25F;
 }

 inf.r -= float1 * 2.0F;
 inf.g -= float1 * 2.0F;
 inf.b -= float1 * 2.0F;
 inf.r += float2 / 3.0F;
 inf.g -= float3 / 3.0F;
 inf.b -= float3 / 3.0F;
 float float4 = float0 - floorBloodSplat2.worldAge;
 if (float4 >= 0.0F && float4 < 72.0F) {
 float float5 = 1.0F - float4 / 72.0F;
 inf.r *= 0.2F + float5 * 0.8F;
 inf.g *= 0.2F + float5 * 0.8F;
 inf.b *= 0.2F + float5 * 0.8F;
 inf.a *= 0.25F + float5 * 0.75F;
 } else {
 inf.r *= 0.2F;
 inf.g *= 0.2F;
 inf.b *= 0.2F;
 inf.a *= 0.25F;
 }

 if (floorBloodSplat2.fade > 0) {
 inf.a = inf.a * (floorBloodSplat2.fade / (PerformanceSettings.getLockFPS() * 5.0F);
 if (--floorBloodSplat2.fade == 0) {
 floorBloodSplat2.chunk.FloorBloodSplatsFade.remove(floorBloodSplat2);
 }
 }

 IsoGridSquare square = floorBloodSplat2.chunk
 .getGridSquare((int)floorBloodSplat2.x, (int)floorBloodSplat2.y, (int)floorBloodSplat2.z);
 if (square != nullptr) {
 int int8 = square.getVertLight(0, int0);
 int int9 = square.getVertLight(1, int0);
 int int10 = square.getVertLight(2, int0);
 int int11 = square.getVertLight(3, int0);
 float float6 = Color.getRedChannelFromABGR(int8);
 float float7 = Color.getGreenChannelFromABGR(int8);
 float float8 = Color.getBlueChannelFromABGR(int8);
 float float9 = Color.getRedChannelFromABGR(int9);
 float float10 = Color.getGreenChannelFromABGR(int9);
 float float11 = Color.getBlueChannelFromABGR(int9);
 float float12 = Color.getRedChannelFromABGR(int10);
 float float13 = Color.getGreenChannelFromABGR(int10);
 float float14 = Color.getBlueChannelFromABGR(int10);
 float float15 = Color.getRedChannelFromABGR(int11);
 float float16 = Color.getGreenChannelFromABGR(int11);
 float float17 = Color.getBlueChannelFromABGR(int11);
 inf.r *= (float6 + float9 + float12 + float15) / 4.0F;
 inf.g *= (float7 + float10 + float13 + float16) / 4.0F;
 inf.b *= (float8 + float11 + float14 + float17) / 4.0F;
 }

 sprite0.renderBloodSplat(
 floorBloodSplat2.chunk.wx * 10 + floorBloodSplat2.x,
 floorBloodSplat2.chunk.wy * 10 + floorBloodSplat2.y,
 floorBloodSplat2.z,
 inf
 );
 }
 }
 }
 }
 }
 }
 }

 void copy(IsoChunkMap from) {
 IsoChunkMap chunkMap = this;
 this->WorldX = from.WorldX;
 this->WorldY = from.WorldY;
 this->XMinTiles = -1;
 this->YMinTiles = -1;
 this->XMaxTiles = -1;
 this->YMaxTiles = -1;

 for (int int0 = 0; int0 < ChunkGridWidth * ChunkGridWidth; int0++) {
 chunkMap.bReadBufferA = from.bReadBufferA;
 if (chunkMap.bReadBufferA) {
 if (from.chunksSwapA[int0] != nullptr) {
 from.chunksSwapA[int0].refs.add(chunkMap);
 chunkMap.chunksSwapA[int0] = from.chunksSwapA[int0];
 }
 } else if (from.chunksSwapB[int0] != nullptr) {
 from.chunksSwapB[int0].refs.add(chunkMap);
 chunkMap.chunksSwapB[int0] = from.chunksSwapB[int0];
 }
 }
 }

 void Unload() {
 for (int int0 = 0; int0 < ChunkGridWidth; int0++) {
 for (int int1 = 0; int1 < ChunkGridWidth; int1++) {
 IsoChunk chunk = this->getChunk(int1, int0);
 if (chunk != nullptr) {
 if (chunk.refs.contains(this) {
 chunk.refs.remove(this);
 if (chunk.refs.empty()) {
 SharedChunks.remove((chunk.wx << 16) + chunk.wy);
 chunk.removeFromWorld();
 ChunkSaveWorker.instance.Add(chunk);
 }
 }

 this->chunksSwapA[int0 * ChunkGridWidth + int1] = nullptr;
 this->chunksSwapB[int0 * ChunkGridWidth + int1] = nullptr;
 }
 }
 }

 WorldSimulation.instance.deactivateChunkMap(this->PlayerID);
 this->XMinTiles = -1;
 this->XMaxTiles = -1;
 this->YMinTiles = -1;
 this->YMaxTiles = -1;
 if (IsoWorld.instance != nullptr && IsoWorld.instance.CurrentCell != nullptr) {
 IsoWorld.instance.CurrentCell.clearCacheGridSquare(this->PlayerID);
 }
 }

 static {
 for (int int0 = 0; int0 < IsoFloorBloodSplat.FloorBloodTypes.length; int0++) {
 splatByType.add(std::make_unique<ArrayList<>>());
 }
 }
}
} // namespace iso
} // namespace zombie
