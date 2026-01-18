#pragma once
#include "zombie/GameTime.h"
#include "zombie/MapCollisionData.h"
#include "zombie/ReanimatedPlayers.h"
#include "zombie/VirtualZombieManager.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Rand.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/stash/StashSystem.h"
#include "zombie/core/utils/OnceEvery.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/globalObjects/SGlobalObjects.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/Vector3.h"
#include "zombie/popman/NetworkZombiePacker.h"
#include "zombie/popman/ZombiePopulationManager.h"
#include "zombie/radio/ZomboidRadio.h"
#include "zombie/savefile/ServerPlayerDB.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/VehiclesDB2.h"
#include "zombie/world/moddata/GlobalModData.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ServerMap {
public:
 bool bUpdateLOSThisFrame = false;
 static OnceEvery LOSTick = new OnceEvery(1.0F);
 static OnceEvery TimeTick = new OnceEvery(600.0F);
 static const int CellSize = 50;
 static const int ChunksPerCellWidth = 5;
 long LastSaved = 0L;
 static bool MapLoading;
public
 IsoObjectID<IsoZombie> ZombieMap = new IsoObjectID<>(IsoZombie.class);
 bool bQueuedSaveAll = false;
 bool bQueuedQuit = false;
 static ServerMap instance = new ServerMap();
public
 ServerMap.ServerCell[] cellMap;
public
 ArrayList<ServerMap.ServerCell> LoadedCells = std::make_unique<ArrayList<>>();
public
 ArrayList<ServerMap.ServerCell> ReleventNow = std::make_unique<ArrayList<>>();
 int width;
 int height;
 IsoMetaGrid grid;
 ArrayList<ServerMap.ServerCell> ToLoad = std::make_unique<ArrayList<>>();
 static ServerMap.DistToCellComparator distToCellComparator =
 new ServerMap.DistToCellComparator();
private
 ArrayList<ServerMap.ServerCell> tempCells =
 std::make_unique<ArrayList<>>();
 long lastTick = 0L;
 Vector2 start;

 short getUniqueZombieId() { return this->ZombieMap.allocateID(); }

 Vector3 getStartLocation(ServerWorldDatabase.LogonResult var1) {
 short short0 = 9412;
 short short1 = 10745;
 uint8_t byte0 = 0;
 return new Vector3(short1, short0, byte0);
 }

 void SaveAll() {
 long long0 = System.nanoTime();

 for (int int0 = 0; int0 < this->LoadedCells.size(); int0++) {
 this->LoadedCells.get(int0).Save();
 }

 this->grid.save();
 DebugLog.log("SaveAll took " + (System.nanoTime() - long0) / 1000000.0 +
 " ms");
 }

 void QueueSaveAll() { this->bQueuedSaveAll = true; }

 void QueueQuit() {
 DebugLog.Multiplayer.printStackTrace();
 this->bQueuedSaveAll = true;
 this->bQueuedQuit = true;
 }

 int toServerCellX(int int0) {
 int0 *= 300;
 return int0 / 50;
 }

 int toServerCellY(int int0) {
 int0 *= 300;
 return int0 / 50;
 }

 int toWorldCellX(int int0) {
 int0 *= 50;
 return int0 / 300;
 }

 int toWorldCellY(int int0) {
 int0 *= 50;
 return int0 / 300;
 }

 int getMaxX() {
 int int0 = this->toServerCellX(this->grid.maxX + 1);
 if ((this->grid.maxX + 1) * 300 % 50 == 0) {
 int0--;
 }

 return int0;
 }

 int getMaxY() {
 int int0 = this->toServerCellY(this->grid.maxY + 1);
 if ((this->grid.maxY + 1) * 300 % 50 == 0) {
 int0--;
 }

 return int0;
 }

 int getMinX() { return this->toServerCellX(this->grid.minX); }

 int getMinY() { return this->toServerCellY(this->grid.minY); }

 void init(IsoMetaGrid metaGrid) {
 this->grid = metaGrid;
 this->width = this->getMaxX() - this->getMinX() + 1;
 this->height = this->getMaxY() - this->getMinY() + 1;

 assert this->width * 50 >= metaGrid.getWidth() * 300;

 assert this->height * 50 >= metaGrid.getHeight() * 300;

 assert this->getMaxX() * 50 < (metaGrid.getMaxX() + 1) * 300;

 assert this->getMaxY() * 50 < (metaGrid.getMaxY() + 1) * 300;

 int int0 = this->width * this->height;
 this->cellMap = new ServerMap.ServerCell[int0];
 StashSystem.init();
 }

public
 ServerMap.ServerCell getCell(int int0, int int1) {
 return !this->isValidCell(int0, int1)
 ? nullptr
 : this->cellMap[int1 * this->width + int0];
 }

 bool isValidCell(int int1, int int0) {
 return int1 >= 0 && int0 >= 0 && int1 < this->width && int0 < this->height;
 }

 void loadOrKeepRelevent(int int0, int int1) {
 if (this->isValidCell(int0, int1) {
 ServerMap.ServerCell serverCell = this->getCell(int0, int1);
 if (serverCell.empty()) {
 serverCell = new ServerMap.ServerCell();
 serverCell.WX = int0 + this->getMinX();
 serverCell.WY = int1 + this->getMinY();
 if (MapLoading) {
 DebugLog.log(DebugType.MapLoading,
 "Loading cell: " + serverCell.WX + ", " + serverCell.WY +
 " (" + this->toWorldCellX(serverCell.WX) + ", " +
 this->toWorldCellX(serverCell.WY) + ")");
 }

 this->cellMap[int1 * this->width + int0] = serverCell;
 this->ToLoad.add(serverCell);
 MPStatistic.getInstance().ServerMapToLoad.Added();
 this->LoadedCells.add(serverCell);
 MPStatistic.getInstance().ServerMapLoadedCells.Added();
 this->ReleventNow.add(serverCell);
 } else if (!this->ReleventNow.contains(serverCell) {
 this->ReleventNow.add(serverCell);
 }
 }
 }

 void characterIn(IsoPlayer player) {
 while (this->grid.empty()) {
 try {
 Thread.sleep(1000L);
 } catch (InterruptedException interruptedException) {
 interruptedException.printStackTrace();
 }
 }

 int int0 = player.OnlineChunkGridWidth / 2 * 10;
 int int1 =
 (int)(Math.floor((player.getX() - int0) / 50.0F) - this->getMinX());
 int int2 =
 (int)(Math.floor((player.getX() + int0) / 50.0F) - this->getMinX());
 int int3 =
 (int)(Math.floor((player.getY() - int0) / 50.0F) - this->getMinY());
 int int4 =
 (int)(Math.floor((player.getY() + int0) / 50.0F) - this->getMinY());

 for (int int5 = int3; int5 <= int4; int5++) {
 for (int int6 = int1; int6 <= int2; int6++) {
 this->loadOrKeepRelevent(int6, int5);
 }
 }
 }

 void characterIn(int int1, int int3, int int7) {
 while (this->grid.empty()) {
 try {
 Thread.sleep(1000L);
 } catch (InterruptedException interruptedException) {
 interruptedException.printStackTrace();
 }
 }

 int int0 = int1 * 10;
 int int2 = int3 * 10;
 int0 = (int)(int0 / 50.0F);
 int2 = (int)(int2 / 50.0F);
 int0 -= this->getMinX();
 int2 -= this->getMinY();
 int int4 = int1 * 10 % 50;
 int int5 = int3 * 10 % 50;
 int int6 = int7 / 2 * 10;
 int int8 = int0;
 int int9 = int2;
 int int10 = int0;
 int int11 = int2;
 if (int4 < int6) {
 int8 = int0 - 1;
 }

 if (int4 > 50 - int6) {
 int10 = int0 + 1;
 }

 if (int5 < int6) {
 int9 = int2 - 1;
 }

 if (int5 > 50 - int6) {
 int11 = int2 + 1;
 }

 for (int int12 = int9; int12 <= int11; int12++) {
 for (int int13 = int8; int13 <= int10; int13++) {
 this->loadOrKeepRelevent(int13, int12);
 }
 }
 }

 void loadMapChunk(int int1, int int3) {
 while (this->grid.empty()) {
 try {
 Thread.sleep(1000L);
 } catch (InterruptedException interruptedException) {
 interruptedException.printStackTrace();
 }
 }

 int int0 = (int)(int1 / 50.0F);
 int int2 = (int)(int3 / 50.0F);
 int0 -= this->getMinX();
 int2 -= this->getMinY();
 this->loadOrKeepRelevent(int0, int2);
 }

 void preupdate() {
 long long0 = System.nanoTime();
 long long1 = long0 - this->lastTick;
 double double0 = long1 * 1.0E-6;
 this->lastTick = long0;
 MapLoading = DebugType.Do(DebugType.MapLoading);

 for (int int0 = 0; int0 < this->ToLoad.size(); int0++) {
 ServerMap.ServerCell serverCell0 = this->ToLoad.get(int0);
 if (serverCell0.bLoadingWasCancelled) {
 if (MapLoading) {
 DebugLog.log(DebugType.MapLoading,
 "MainThread: forgetting cancelled " + serverCell0.WX +
 "," + serverCell0.WY);
 }

 int int1 = serverCell0.WX - this->getMinX();
 int int2 = serverCell0.WY - this->getMinY();

 assert this->cellMap[int1 + int2 * this->width] == serverCell0;

 this->cellMap[int1 + int2 * this->width] = nullptr;
 this->LoadedCells.remove(serverCell0);
 this->ReleventNow.remove(serverCell0);
 ServerMap.ServerCell.loaded2.remove(serverCell0);
 this->ToLoad.remove(int0--);
 MPStatistic.getInstance().ServerMapToLoad.Canceled();
 }
 }

 for (int int3 = 0; int3 < this->LoadedCells.size(); int3++) {
 ServerMap.ServerCell serverCell1 = this->LoadedCells.get(int3);
 if (serverCell1.bCancelLoading) {
 if (MapLoading) {
 DebugLog.log(DebugType.MapLoading,
 "MainThread: forgetting cancelled " + serverCell1.WX +
 "," + serverCell1.WY);
 }

 int int4 = serverCell1.WX - this->getMinX();
 int int5 = serverCell1.WY - this->getMinY();

 assert this->cellMap[int4 + int5 * this->width] == serverCell1;

 this->cellMap[int4 + int5 * this->width] = nullptr;
 this->LoadedCells.remove(int3--);
 this->ReleventNow.remove(serverCell1);
 ServerMap.ServerCell.loaded2.remove(serverCell1);
 this->ToLoad.remove(serverCell1);
 MPStatistic.getInstance().ServerMapLoadedCells.Canceled();
 }
 }

 for (int int6 = 0; int6 < ServerMap.ServerCell.loaded2.size(); int6++) {
 ServerMap.ServerCell serverCell2 = ServerMap.ServerCell.loaded2.get(int6);
 if (serverCell2.bCancelLoading) {
 if (MapLoading) {
 DebugLog.log(DebugType.MapLoading,
 "MainThread: forgetting cancelled " + serverCell2.WX +
 "," + serverCell2.WY);
 }

 int int7 = serverCell2.WX - this->getMinX();
 int int8 = serverCell2.WY - this->getMinY();

 assert this->cellMap[int7 + int8 * this->width] == serverCell2;

 this->cellMap[int7 + int8 * this->width] = nullptr;
 this->LoadedCells.remove(serverCell2);
 this->ReleventNow.remove(serverCell2);
 ServerMap.ServerCell.loaded2.remove(serverCell2);
 this->ToLoad.remove(serverCell2);
 MPStatistic.getInstance().ServerMapLoaded2.Canceled();
 }
 }

 if (!this->ToLoad.empty()) {
 this->tempCells.clear();

 for (int int9 = 0; int9 < this->ToLoad.size(); int9++) {
 ServerMap.ServerCell serverCell3 = this->ToLoad.get(int9);
 if (!serverCell3.bCancelLoading && !serverCell3.startedLoading) {
 this->tempCells.add(serverCell3);
 }
 }

 if (!this->tempCells.empty()) {
 distToCellComparator.init();
 Collections.sort(this->tempCells, distToCellComparator);

 for (int int10 = 0; int10 < this->tempCells.size(); int10++) {
 ServerMap.ServerCell serverCell4 = this->tempCells.get(int10);
 ServerMap.ServerCell.chunkLoader.addJob(serverCell4);
 serverCell4.startedLoading = true;
 }
 }

 ServerMap.ServerCell.chunkLoader.getLoaded(ServerMap.ServerCell.loaded);

 for (int int11 = 0; int11 < ServerMap.ServerCell.loaded.size(); int11++) {
 ServerMap.ServerCell serverCell5 =
 ServerMap.ServerCell.loaded.get(int11);
 if (!serverCell5.doingRecalc) {
 ServerMap.ServerCell.chunkLoader.addRecalcJob(serverCell5);
 serverCell5.doingRecalc = true;
 }
 }

 ServerMap.ServerCell.loaded.clear();
 ServerMap.ServerCell.chunkLoader.getRecalc(ServerMap.ServerCell.loaded2);
 if (!ServerMap.ServerCell.loaded2.empty()) {
 try {
 ServerLOS.instance.suspend();

 for (int int12 = 0; int12 < ServerMap.ServerCell.loaded2.size();
 int12++) {
 ServerMap.ServerCell serverCell6 =
 ServerMap.ServerCell.loaded2.get(int12);
 long long2 = System.nanoTime();
 if (serverCell6.Load2()) {
 long2 = System.nanoTime();
 int12--;
 this->ToLoad.remove(serverCell6);
 }
 }
 } finally {
 ServerLOS.instance.resume();
 }
 }
 }

 int int13 = ServerOptions.instance.SaveWorldEveryMinutes.getValue();
 if (int13 > 0) {
 long long3 = System.currentTimeMillis();
 if (long3 > this->LastSaved + int13 * 60 * 1000) {
 this->bQueuedSaveAll = true;
 this->LastSaved = long3;
 }
 }

 if (this->bQueuedSaveAll) {
 this->bQueuedSaveAll = false;
 long long4 = System.nanoTime();
 this->SaveAll();
 ServerMap.ServerCell.chunkLoader.saveLater(GameTime.instance);
 ReanimatedPlayers.instance.saveReanimatedPlayers();
 MapCollisionData.instance.save();
 SGlobalObjects.save();

 try {
 ZomboidRadio.getInstance().Save();
 } catch (Exception exception0) {
 exception0.printStackTrace();
 }

 try {
 GlobalModData.instance.save();
 } catch (Exception exception1) {
 exception1.printStackTrace();
 }

 GameServer.UnPauseAllClients();
 System.out.println("Saving finish");
 DebugLog.log("Saving took " + (System.nanoTime() - long4) / 1000000.0 +
 " ms");
 }

 if (this->bQueuedQuit) {
 ByteBufferWriter byteBufferWriter = GameServer.udpEngine.startPacket();
 PacketTypes.PacketType.ServerQuit.doPacket(byteBufferWriter);
 GameServer.udpEngine.endPacketBroadcast(
 PacketTypes.PacketType.ServerQuit);

 try {
 Thread.sleep(5000L);
 } catch (InterruptedException interruptedException) {
 interruptedException.printStackTrace();
 }

 MapCollisionData.instance.stop();
 ZombiePopulationManager.instance.stop();
 RCONServer.shutdown();
 ServerMap.ServerCell.chunkLoader.quit();
 ServerWorldDatabase.instance.close();
 ServerPlayersVehicles.instance.stop();
 ServerPlayerDB.getInstance().close();
 VehiclesDB2.instance.Reset();
 GameServer.udpEngine.Shutdown();
 ServerGUI.shutdown();
 SteamUtils.shutdown();
 System.exit(0);
 }

 this->ReleventNow.clear();
 this->bUpdateLOSThisFrame = LOSTick.Check();
 if (TimeTick.Check()) {
 ServerMap.ServerCell.chunkLoader.saveLater(GameTime.instance);
 }
 }

 IsoGridSquare getRandomSquareFromCell(int int0, int int1) {
 this->loadOrKeepRelevent(int0, int1);
 int int2 = int0;
 int int3 = int1;
 ServerMap.ServerCell serverCell = this->getCell(int0, int1);
 if (serverCell.empty()) {
 throw RuntimeException("Cannot find a random square.");
 } else {
 int0 = (int0 + this->getMinX()) * 50;
 int1 = (int1 + this->getMinY()) * 50;
 IsoGridSquare square = nullptr;
 int int4 = 100;

 do {
 square = this->getGridSquare(Rand.Next(int0, int0 + 50),
 Rand.Next(int1, int1 + 50), 0);
 int4--;
 if (square.empty()) {
 this->loadOrKeepRelevent(int2, int3);
 }
 } while (square.empty() && int4 > 0);

 return square;
 }
 }

 void postupdate() {
 int int0 = this->LoadedCells.size();
 bool boolean0 = false;

 try {
 for (int int1 = 0; int1 < this->LoadedCells.size(); int1++) {
 ServerMap.ServerCell serverCell = this->LoadedCells.get(int1);
 bool boolean1 = this->ReleventNow.contains(serverCell) ||
 !this->outsidePlayerInfluence(serverCell);
 if (!serverCell.bLoaded) {
 if (!boolean1 && !serverCell.bCancelLoading) {
 if (MapLoading) {
 DebugLog.log(DebugType.MapLoading,
 "MainThread: cancelling " + serverCell.WX + "," +
 serverCell.WY + " cell.startedLoading=" +
 serverCell.startedLoading);
 }

 if (!serverCell.startedLoading) {
 serverCell.bLoadingWasCancelled = true;
 }

 serverCell.bCancelLoading = true;
 }
 } else if (!boolean1) {
 int int2 = serverCell.WX - this->getMinX();
 int int3 = serverCell.WY - this->getMinY();
 if (!boolean0) {
 ServerLOS.instance.suspend();
 boolean0 = true;
 }

 this->cellMap[int3 * this->width + int2].Unload();
 this->cellMap[int3 * this->width + int2] = nullptr;
 this->LoadedCells.remove(serverCell);
 int1--;
 } else {
 serverCell.update();
 }
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 } finally {
 if (boolean0) {
 ServerLOS.instance.resume();
 }
 }

 NetworkZombiePacker.getInstance().postupdate();
 ServerMap.ServerCell.chunkLoader.updateSaved();
 }

 void physicsCheck(int int1, int int3) {
 int int0 = int1 / 50;
 int int2 = int3 / 50;
 int0 -= this->getMinX();
 int2 -= this->getMinY();
 ServerMap.ServerCell serverCell = this->getCell(int0, int2);
 if (serverCell != nullptr && serverCell.bLoaded) {
 serverCell.bPhysicsCheck = true;
 }
 }

 bool outsidePlayerInfluence(ServerMap.ServerCell serverCell) {
 int int0 = serverCell.WX * 50;
 int int1 = serverCell.WY * 50;
 int int2 = (serverCell.WX + 1) * 50;
 int int3 = (serverCell.WY + 1) * 50;

 for (int int4 = 0; int4 < GameServer.udpEngine.connections.size(); int4++) {
 UdpConnection udpConnection = GameServer.udpEngine.connections.get(int4);
 if (udpConnection.RelevantTo(int0, int1) {
 return false;
 }

 if (udpConnection.RelevantTo(int2, int1) {
 return false;
 }

 if (udpConnection.RelevantTo(int2, int3) {
 return false;
 }

 if (udpConnection.RelevantTo(int0, int3) {
 return false;
 }
 }

 return true;
 }

 void saveZoneInsidePlayerInfluence(short short0) {
 for (int int0 = 0; int0 < GameServer.udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = GameServer.udpEngine.connections.get(int0);

 for (int int1 = 0; int1 < udpConnection.players.length; int1++) {
 if (udpConnection.players[int1] != nullptr &&
 udpConnection.players[int1].OnlineID == short0) {
 IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare(
 (double)udpConnection.players[int1].x,
 (double)udpConnection.players[int1].y,
 (double)udpConnection.players[int1].z);
 if (square != nullptr) {
 ServerMap.ServerCell.chunkLoader.addSaveLoadedJob(square.chunk);
 return;
 }
 }
 }
 }

 ServerMap.ServerCell.chunkLoader.updateSaved();
 }

 bool InsideThePlayerInfluence(ServerMap.ServerCell serverCell, short short0) {
 int int0 = serverCell.WX * 50;
 int int1 = serverCell.WY * 50;
 int int2 = (serverCell.WX + 1) * 50;
 int int3 = (serverCell.WY + 1) * 50;

 for (int int4 = 0; int4 < GameServer.udpEngine.connections.size(); int4++) {
 UdpConnection udpConnection = GameServer.udpEngine.connections.get(int4);

 for (int int5 = 0; int5 < udpConnection.players.length; int5++) {
 if (udpConnection.players[int5] != nullptr &&
 udpConnection.players[int5].OnlineID == short0) {
 if (udpConnection.RelevantToPlayerIndex(int5, int0, int1) {
 return true;
 }

 if (udpConnection.RelevantToPlayerIndex(int5, int2, int1) {
 return true;
 }

 if (udpConnection.RelevantToPlayerIndex(int5, int2, int3) {
 return true;
 }

 if (udpConnection.RelevantToPlayerIndex(int5, int0, int3) {
 return true;
 }

 return false;
 }
 }
 }

 return false;
 }

 IsoGridSquare getGridSquare(int int0, int int1, int int2) {
 if (!IsoWorld.instance.isValidSquare(int0, int1, int2) {
 return nullptr;
 } else {
 int int3 = int0 / 50;
 int int4 = int1 / 50;
 int3 -= this->getMinX();
 int4 -= this->getMinY();
 int int5 = int0 / 10;
 int int6 = int1 / 10;
 int int7 = int5 % 5;
 int int8 = int6 % 5;
 int int9 = int0 % 10;
 int int10 = int1 % 10;
 ServerMap.ServerCell serverCell = this->getCell(int3, int4);
 if (serverCell != nullptr && serverCell.bLoaded) {
 IsoChunk chunk = serverCell.chunks[int7][int8];
 return chunk = = nullptr ? nullptr : chunk.getGridSquare(int9, int10, int2);
 } else {
 return nullptr;
 }
 }
 }

 void setGridSquare(int int1, int int3, int int10, IsoGridSquare square) {
 int int0 = int1 / 50;
 int int2 = int3 / 50;
 int0 -= this->getMinX();
 int2 -= this->getMinY();
 int int4 = int1 / 10;
 int int5 = int3 / 10;
 int int6 = int4 % 5;
 int int7 = int5 % 5;
 int int8 = int1 % 10;
 int int9 = int3 % 10;
 ServerMap.ServerCell serverCell = this->getCell(int0, int2);
 if (serverCell != nullptr) {
 IsoChunk chunk = serverCell.chunks[int6][int7];
 if (chunk != nullptr) {
 chunk.setSquare(int8, int9, int10, square);
 }
 }
 }

 bool isInLoaded(float float0, float float1) {
 int int0 = (int)float0;
 int int1 = (int)float1;
 int0 /= 50;
 int1 /= 50;
 int0 -= this->getMinX();
 int1 -= this->getMinY();
 return this->ToLoad.contains(this->getCell(int0, int1)
 ? false
 : this->getCell(int0, int1) != nullptr;
 }

 IsoChunk getChunk(int int1, int int0) {
 if (int1 >= 0 && int0 >= 0) {
 int int2 = int1 / 5;
 int int3 = int0 / 5;
 int2 -= this->getMinX();
 int3 -= this->getMinY();
 int int4 = int1 % 5;
 int int5 = int0 % 5;
 ServerMap.ServerCell serverCell = this->getCell(int2, int3);
 return serverCell != nullptr && serverCell.bLoaded
 ? serverCell.chunks[int4][int5]
 : nullptr;
 } else {
 return nullptr;
 }
 }

 void setSoftResetChunk(IsoChunk chunk) {
 int int0 = chunk.wx / 5;
 int int1 = chunk.wy / 5;
 int0 -= this->getMinX();
 int1 -= this->getMinY();
 if (this->isValidCell(int0, int1) {
 ServerMap.ServerCell serverCell = this->getCell(int0, int1);
 if (serverCell.empty()) {
 serverCell = new ServerMap.ServerCell();
 serverCell.bLoaded = true;
 this->cellMap[int1 * this->width + int0] = serverCell;
 }

 int int2 = chunk.wx % 5;
 int int3 = chunk.wy % 5;
 serverCell.chunks[int2][int3] = chunk;
 }
 }

 void clearSoftResetChunk(IsoChunk chunk) {
 int int0 = chunk.wx / 5;
 int int1 = chunk.wy / 5;
 int0 -= this->getMinX();
 int1 -= this->getMinY();
 ServerMap.ServerCell serverCell = this->getCell(int0, int1);
 if (serverCell != nullptr) {
 int int2 = chunk.wx % 5;
 int int3 = chunk.wy % 5;
 serverCell.chunks[int2][int3] = nullptr;
 }
 }

private
 static class DistToCellComparator implements
 Comparator<ServerMap.ServerCell> {
 private
 Vector2[] pos = new Vector2[1024];
 int posCount;

 public
 DistToCellComparator() {
 for (int int0 = 0; int0 < this->pos.length; int0++) {
 this->pos[int0] = std::make_unique<Vector2>();
 }
 }

 void init() {
 this->posCount = 0;

 for (int int0 = 0; int0 < GameServer.udpEngine.connections.size();
 int0++) {
 UdpConnection udpConnection =
 GameServer.udpEngine.connections.get(int0);
 if (udpConnection.isFullyConnected()) {
 for (int int1 = 0; int1 < 4; int1++) {
 if (udpConnection.players[int1] != nullptr) {
 this->pos[this->posCount].set(udpConnection.players[int1].x,
 udpConnection.players[int1].y);
 this->posCount++;
 }
 }
 }
 }
 }

 int compare(ServerMap.ServerCell serverCell0,
 ServerMap.ServerCell serverCell1) {
 float float0 = Float.MAX_VALUE;
 float float1 = Float.MAX_VALUE;

 for (int int0 = 0; int0 < this->posCount; int0++) {
 float float2 = this->pos[int0].x;
 float float3 = this->pos[int0].y;
 float0 = Math.min(float0, this->distToCell(float2, float3, serverCell0);
 float1 = Math.min(float1, this->distToCell(float2, float3, serverCell1);
 }

 if (float0 < float1) {
 return -1;
 } else {
 return float0 > float1 ? 1 : 0;
 }
 }

 float distToCell(float float1, float float3,
 ServerMap.ServerCell serverCell) {
 int int0 = serverCell.WX * 50;
 int int1 = serverCell.WY * 50;
 int int2 = int0 + 50;
 int int3 = int1 + 50;
 float float0 = float1;
 float float2 = float3;
 if (float1 < int0) {
 float0 = int0;
 } else if (float1 > int2) {
 float0 = int2;
 }

 if (float3 < int1) {
 float2 = int1;
 } else if (float3 > int3) {
 float2 = int3;
 }

 return IsoUtils.DistanceToSquared(float1, float3, float0, float2);
 }
 }

 public static class ServerCell {
 int WX;
 int WY;
 bool bLoaded = false;
 bool bPhysicsCheck = false;
 public
 IsoChunk[][] chunks = new IsoChunk[5][5];
 private
 HashSet<RoomDef> UnexploredRooms = std::make_unique<HashSet<>>();
 static const ServerChunkLoader chunkLoader = new ServerChunkLoader();
 private
 static ArrayList<ServerMap.ServerCell> loaded =
 std::make_unique<ArrayList<>>();
 bool startedLoading = false;
 bool bCancelLoading = false;
 bool bLoadingWasCancelled = false;
 private
 static ArrayList<ServerMap.ServerCell> loaded2 =
 std::make_unique<ArrayList<>>();
 bool doingRecalc = false;

 bool Load2() {
 chunkLoader.getRecalc(loaded2);

 for (int int0 = 0; int0 < loaded2.size(); int0++) {
 if (loaded2.get(int0) == this) {
 long long0 = System.nanoTime();
 this->RecalcAll2();
 loaded2.remove(int0);
 if (ServerMap.MapLoading) {
 DebugLog.log(DebugType.MapLoading, "loaded2=" + loaded2);
 }

 float float0 = (float)(System.nanoTime() - long0) / 1000000.0F;
 if (ServerMap.MapLoading) {
 DebugLog.log(DebugType.MapLoading, "finish loading cell " +
 this->WX + "," + this->WY +
 " ms=" + float0);
 }

 this->loadVehicles();
 return true;
 }
 }

 return false;
 }

 void loadVehicles() {
 for (int int0 = 0; int0 < 5; int0++) {
 for (int int1 = 0; int1 < 5; int1++) {
 IsoChunk chunk = this->chunks[int0][int1];
 if (chunk != nullptr && !chunk.isNewChunk()) {
 VehiclesDB2.instance.loadChunkMain(chunk);
 }
 }
 }
 }

 void RecalcAll2() {
 int int0 = this->WX * 5 * 10;
 int int1 = this->WY * 5 * 10;
 int int2 = int0 + 50;
 int int3 = int1 + 50;

 for (RoomDef roomDef0 : this->UnexploredRooms) {
 roomDef0.IndoorZombies--;
 }

 this->UnexploredRooms.clear();
 this->bLoaded = true;

 for (int int4 = 1; int4 < 8; int4++) {
 for (int int5 = -1; int5 < 51; int5++) {
 IsoGridSquare square0 =
 ServerMap.instance.getGridSquare(int0 + int5, int1 - 1, int4);
 if (square0 != nullptr && !square0.getObjects().empty()) {
 IsoWorld.instance.CurrentCell.EnsureSurroundNotNull(
 square0.x, square0.y, int4);
 } else if (int5 >= 0 && int5 < 50) {
 square0 = ServerMap.instance.getGridSquare(int0 + int5, int1, int4);
 if (square0 != nullptr && !square0.getObjects().empty()) {
 IsoWorld.instance.CurrentCell.EnsureSurroundNotNull(
 square0.x, square0.y, int4);
 }
 }

 square0 =
 ServerMap.instance.getGridSquare(int0 + int5, int1 + 50, int4);
 if (square0 != nullptr && !square0.getObjects().empty()) {
 IsoWorld.instance.CurrentCell.EnsureSurroundNotNull(
 square0.x, square0.y, int4);
 } else if (int5 >= 0 && int5 < 50) {
 ServerMap.instance.getGridSquare(int0 + int5, int1 + 50 - 1, int4);
 if (square0 != nullptr && !square0.getObjects().empty()) {
 IsoWorld.instance.CurrentCell.EnsureSurroundNotNull(
 square0.x, square0.y, int4);
 }
 }
 }

 for (int int6 = 0; int6 < 50; int6++) {
 IsoGridSquare square1 =
 ServerMap.instance.getGridSquare(int0 - 1, int1 + int6, int4);
 if (square1 != nullptr && !square1.getObjects().empty()) {
 IsoWorld.instance.CurrentCell.EnsureSurroundNotNull(
 square1.x, square1.y, int4);
 } else {
 square1 = ServerMap.instance.getGridSquare(int0, int1 + int6, int4);
 if (square1 != nullptr && !square1.getObjects().empty()) {
 IsoWorld.instance.CurrentCell.EnsureSurroundNotNull(
 square1.x, square1.y, int4);
 }
 }

 square1 =
 ServerMap.instance.getGridSquare(int0 + 50, int1 + int6, int4);
 if (square1 != nullptr && !square1.getObjects().empty()) {
 IsoWorld.instance.CurrentCell.EnsureSurroundNotNull(
 square1.x, square1.y, int4);
 } else {
 square1 = ServerMap.instance.getGridSquare(int0 + 50 - 1,
 int1 + int6, int4);
 if (square1 != nullptr && !square1.getObjects().empty()) {
 IsoWorld.instance.CurrentCell.EnsureSurroundNotNull(
 square1.x, square1.y, int4);
 }
 }
 }
 }

 for (int int7 = 0; int7 < 8; int7++) {
 for (int int8 = 0; int8 < 50; int8++) {
 IsoGridSquare square2 =
 ServerMap.instance.getGridSquare(int0 + int8, int1 + 0, int7);
 if (square2 != nullptr) {
 square2.RecalcAllWithNeighbours(true);
 }

 square2 =
 ServerMap.instance.getGridSquare(int0 + int8, int3 - 1, int7);
 if (square2 != nullptr) {
 square2.RecalcAllWithNeighbours(true);
 }
 }

 for (int int9 = 0; int9 < 50; int9++) {
 IsoGridSquare square3 =
 ServerMap.instance.getGridSquare(int0 + 0, int1 + int9, int7);
 if (square3 != nullptr) {
 square3.RecalcAllWithNeighbours(true);
 }

 square3 =
 ServerMap.instance.getGridSquare(int2 - 1, int1 + int9, int7);
 if (square3 != nullptr) {
 square3.RecalcAllWithNeighbours(true);
 }
 }
 }

 uint8_t byte0 = 100;

 for (int int10 = 0; int10 < 5; int10++) {
 for (int int11 = 0; int11 < 5; int11++) {
 IsoChunk chunk = this->chunks[int10][int11];
 if (chunk != nullptr) {
 chunk.bLoaded = true;

 for (int int12 = 0; int12 < byte0; int12++) {
 for (int int13 = 0; int13 <= chunk.maxLevel; int13++) {
 IsoGridSquare square4 = chunk.squares[int13][int12];
 if (square4 != nullptr) {
 if (square4.getRoom() != nullptr &&
 !square4.getRoom().def.bExplored) {
 this->UnexploredRooms.add(square4.getRoom().def);
 }

 square4.propertiesDirty = true;
 }
 }
 }
 }
 }
 }

 for (int int14 = 0; int14 < 5; int14++) {
 for (int int15 = 0; int15 < 5; int15++) {
 if (this->chunks[int14][int15] != nullptr) {
 this->chunks[int14][int15].doLoadGridsquare();
 }
 }
 }

 for (RoomDef roomDef1 : this->UnexploredRooms) {
 roomDef1.IndoorZombies++;
 if (roomDef1.IndoorZombies == 1) {
 try {
 VirtualZombieManager.instance.tryAddIndoorZombies(roomDef1, false);
 } catch (Exception exception) {
 exception.printStackTrace();
 }
 }
 }

 this->bLoaded = true;
 }

 void Unload() {
 if (this->bLoaded) {
 if (ServerMap.MapLoading) {
 DebugLog.log(DebugType.MapLoading,
 "Unloading cell: " + this->WX + ", " + this->WY + " (" +
 ServerMap.instance.toWorldCellX(this->WX) + ", " +
 ServerMap.instance.toWorldCellX(this->WY) + ")");
 }

 for (int int0 = 0; int0 < 5; int0++) {
 for (int int1 = 0; int1 < 5; int1++) {
 IsoChunk chunk = this->chunks[int0][int1];
 if (chunk != nullptr) {
 chunk.removeFromWorld();
 chunk.m_loadVehiclesObject = nullptr;

 for (int int2 = 0; int2 < chunk.vehicles.size(); int2++) {
 BaseVehicle vehicle = chunk.vehicles.get(int2);
 VehiclesDB2.instance.updateVehicle(vehicle);
 }

 chunkLoader.addSaveUnloadedJob(chunk);
 this->chunks[int0][int1] = nullptr;
 }
 }
 }

 for (RoomDef roomDef : this->UnexploredRooms) {
 if (roomDef.IndoorZombies == 1) {
 }

 roomDef.IndoorZombies--;
 }
 }
 }

 void Save() {
 if (this->bLoaded) {
 for (int int0 = 0; int0 < 5; int0++) {
 for (int int1 = 0; int1 < 5; int1++) {
 IsoChunk chunk = this->chunks[int0][int1];
 if (chunk != nullptr) {
 try {
 chunkLoader.addSaveLoadedJob(chunk);

 for (int int2 = 0; int2 < chunk.vehicles.size(); int2++) {
 BaseVehicle vehicle = chunk.vehicles.get(int2);
 VehiclesDB2.instance.updateVehicle(vehicle);
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 LoggerManager.getLogger("map").write(exception);
 }
 }
 }
 }

 chunkLoader.updateSaved();
 }
 }

 void update() {
 for (int int0 = 0; int0 < 5; int0++) {
 for (int int1 = 0; int1 < 5; int1++) {
 IsoChunk chunk = this->chunks[int0][int1];
 if (chunk != nullptr) {
 chunk.update();
 }
 }
 }

 this->bPhysicsCheck = false;
 }

 IsoChunk getChunk(int int1, int int0) {
 if (int1 >= 0 && int1 < 5 && int0 >= 0 && int0 < 5) {
 IsoChunk chunk = this->chunks[int1][int0];
 if (chunk != nullptr) {
 return chunk;
 }
 }

 return nullptr;
 }

 int getWX() { return this->WX; }

 int getWY() { return this->WY; }
 }
}
} // namespace network
} // namespace zombie
