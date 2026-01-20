#pragma once
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/MapCollisionData.h"
#include "zombie/ReanimatedPlayers.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Rand.h"
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
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/Vector3.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/network/ServerMap/DistToCellComparator.h"
#include "zombie/network/ServerMap/ServerCell.h"
#include "zombie/network/ServerWorldDatabase/LogonResult.h"
#include "zombie/popman/NetworkZombiePacker.h"
#include "zombie/popman/ZombiePopulationManager.h"
#include "zombie/radio/ZomboidRadio.h"
#include "zombie/savefile/ServerPlayerDB.h"
#include "zombie/vehicles/VehiclesDB2.h"
#include "zombie/world/moddata/GlobalModData.h"

namespace zombie {
namespace network {


class ServerMap {
public:
    bool bUpdateLOSThisFrame = false;
    static OnceEvery LOSTick = std::make_shared<OnceEvery>(1.0F);
    static OnceEvery TimeTick = std::make_shared<OnceEvery>(600.0F);
    static const int CellSize = 50;
    static const int ChunksPerCellWidth = 5;
    long LastSaved = 0L;
    static bool MapLoading;
   public const IsoObjectID<IsoZombie> ZombieMap = std::make_shared<IsoObjectID>(IsoZombie.class);
    bool bQueuedSaveAll = false;
    bool bQueuedQuit = false;
    static ServerMap instance = std::make_shared<ServerMap>();
   public ServerCell[] cellMap;
   public std::vector<ServerCell> LoadedCells = std::make_unique<std::vector<>>();
   public std::vector<ServerCell> ReleventNow = std::make_unique<std::vector<>>();
    int width;
    int height;
    IsoMetaGrid grid;
   std::vector<ServerCell> ToLoad = std::make_unique<std::vector<>>();
    static const DistToCellComparator distToCellComparator = std::make_shared<DistToCellComparator>();
   private const std::vector<ServerCell> tempCells = std::make_unique<std::vector<>>();
    long lastTick = 0L;
    Vector2 start;

    short getUniqueZombieId() {
      return this.ZombieMap.allocateID();
   }

    Vector3 getStartLocation(LogonResult var1) {
    short var2 = 9412;
    short var3 = 10745;
    uint8_t var4 = 0;
      return std::make_shared<Vector3>(var3, var2, var4);
   }

    void SaveAll() {
    long var1 = System.nanoTime();

      for (int var3 = 0; var3 < this.LoadedCells.size(); var3++) {
         this.LoadedCells.get(var3).Save();
      }

      this.grid.save();
      DebugLog.log("SaveAll took " + (System.nanoTime() - var1) / 1000000.0 + " ms");
   }

    void QueueSaveAll() {
      this.bQueuedSaveAll = true;
   }

    void QueueQuit() {
      DebugLog.Multiplayer.printStackTrace();
      this.bQueuedSaveAll = true;
      this.bQueuedQuit = true;
   }

    int toServerCellX(int var1) {
      var1 *= 300;
      return var1 / 50;
   }

    int toServerCellY(int var1) {
      var1 *= 300;
      return var1 / 50;
   }

    int toWorldCellX(int var1) {
      var1 *= 50;
      return var1 / 300;
   }

    int toWorldCellY(int var1) {
      var1 *= 50;
      return var1 / 300;
   }

    int getMaxX() {
    int var1 = this.toServerCellX(this.grid.maxX + 1);
      if ((this.grid.maxX + 1) * 300 % 50 == 0) {
         var1--;
      }

    return var1;
   }

    int getMaxY() {
    int var1 = this.toServerCellY(this.grid.maxY + 1);
      if ((this.grid.maxY + 1) * 300 % 50 == 0) {
         var1--;
      }

    return var1;
   }

    int getMinX() {
      return this.toServerCellX(this.grid.minX);
   }

    int getMinY() {
      return this.toServerCellY(this.grid.minY);
   }

    void init(IsoMetaGrid var1) {
      this.grid = var1;
      this.width = this.getMaxX() - this.getMinX() + 1;
      this.height = this.getMaxY() - this.getMinY() + 1;

      assert this.width * 50 >= var1.getWidth() * 300;

      assert this.height * 50 >= var1.getHeight() * 300;

      assert this.getMaxX() * 50 < (var1.getMaxX() + 1) * 300;

      assert this.getMaxY() * 50 < (var1.getMaxY() + 1) * 300;

    int var2 = this.width * this.height;
      this.cellMap = new ServerCell[var2];
      StashSystem.init();
   }

    ServerCell getCell(int var1, int var2) {
      return !this.isValidCell(var1, var2) ? nullptr : this.cellMap[var2 * this.width + var1];
   }

    bool isValidCell(int var1, int var2) {
      return var1 >= 0 && var2 >= 0 && var1 < this.width && var2 < this.height;
   }

    void loadOrKeepRelevent(int var1, int var2) {
      if (this.isValidCell(var1, var2)) {
    ServerCell var3 = this.getCell(var1, var2);
         if (var3 == nullptr) {
            var3 = std::make_unique<ServerCell>();
            var3.WX = var1 + this.getMinX();
            var3.WY = var2 + this.getMinY();
            if (MapLoading) {
               DebugLog.log(
                  DebugType.MapLoading,
                  "Loading cell: " + var3.WX + ", " + var3.WY + " (" + this.toWorldCellX(var3.WX) + ", " + this.toWorldCellX(var3.WY) + ")"
               );
            }

            this.cellMap[var2 * this.width + var1] = var3;
            this.ToLoad.push_back(var3);
            MPStatistic.getInstance().ServerMapToLoad.Added();
            this.LoadedCells.push_back(var3);
            MPStatistic.getInstance().ServerMapLoadedCells.Added();
            this.ReleventNow.push_back(var3);
         } else if (!this.ReleventNow.contains(var3)) {
            this.ReleventNow.push_back(var3);
         }
      }
   }

    void characterIn(IsoPlayer var1) {
      while (this.grid == nullptr) {
         try {
            Thread.sleep(1000L);
         } catch (InterruptedException var9) {
            var9.printStackTrace();
         }
      }

    int var2 = var1.OnlineChunkGridWidth / 2 * 10;
    int var3 = (int)(Math.floor((var1.getX() - var2) / 50.0F) - this.getMinX());
    int var4 = (int)(Math.floor((var1.getX() + var2) / 50.0F) - this.getMinX());
    int var5 = (int)(Math.floor((var1.getY() - var2) / 50.0F) - this.getMinY());
    int var6 = (int)(Math.floor((var1.getY() + var2) / 50.0F) - this.getMinY());

      for (int var7 = var5; var7 <= var6; var7++) {
         for (int var8 = var3; var8 <= var4; var8++) {
            this.loadOrKeepRelevent(var8, var7);
         }
      }
   }

    void characterIn(int var1, int var2, int var3) {
      while (this.grid == nullptr) {
         try {
            Thread.sleep(1000L);
         } catch (InterruptedException var17) {
            var17.printStackTrace();
         }
      }

    int var4 = var1 * 10;
    int var5 = var2 * 10;
      var4 = (int)(var4 / 50.0F);
      var5 = (int)(var5 / 50.0F);
      var4 -= this.getMinX();
      var5 -= this.getMinY();
    int var8 = var1 * 10 % 50;
    int var9 = var2 * 10 % 50;
    int var10 = var3 / 2 * 10;
    int var11 = var4;
    int var12 = var5;
    int var13 = var4;
    int var14 = var5;
      if (var8 < var10) {
         var11 = var4 - 1;
      }

      if (var8 > 50 - var10) {
         var13 = var4 + 1;
      }

      if (var9 < var10) {
         var12 = var5 - 1;
      }

      if (var9 > 50 - var10) {
         var14 = var5 + 1;
      }

      for (int var15 = var12; var15 <= var14; var15++) {
         for (int var16 = var11; var16 <= var13; var16++) {
            this.loadOrKeepRelevent(var16, var15);
         }
      }
   }

    void loadMapChunk(int var1, int var2) {
      while (this.grid == nullptr) {
         try {
            Thread.sleep(1000L);
         } catch (InterruptedException var5) {
            var5.printStackTrace();
         }
      }

    int var3 = (int)(var1 / 50.0F);
    int var4 = (int)(var2 / 50.0F);
      var3 -= this.getMinX();
      var4 -= this.getMinY();
      this.loadOrKeepRelevent(var3, var4);
   }

    void preupdate() {
    long var1 = System.nanoTime();
    long var3 = var1 - this.lastTick;
    double var5 = var3 * 1.0E-6;
      this.lastTick = var1;
      MapLoading = DebugType.Do(DebugType.MapLoading);

      for (int var7 = 0; var7 < this.ToLoad.size(); var7++) {
    ServerCell var8 = this.ToLoad.get(var7);
         if (var8.bLoadingWasCancelled) {
            if (MapLoading) {
               DebugLog.log(DebugType.MapLoading, "MainThread: forgetting cancelled " + var8.WX + "," + var8.WY);
            }

    int var9 = var8.WX - this.getMinX();
    int var10 = var8.WY - this.getMinY();

            assert this.cellMap[var9 + var10 * this.width] == var8;

            this.cellMap[var9 + var10 * this.width] = nullptr;
            this.LoadedCells.remove(var8);
            this.ReleventNow.remove(var8);
            ServerCell.loaded2.remove(var8);
            this.ToLoad.remove(var7--);
            MPStatistic.getInstance().ServerMapToLoad.Canceled();
         }
      }

      for (int var20 = 0; var20 < this.LoadedCells.size(); var20++) {
    ServerCell var27 = this.LoadedCells.get(var20);
         if (var27.bCancelLoading) {
            if (MapLoading) {
               DebugLog.log(DebugType.MapLoading, "MainThread: forgetting cancelled " + var27.WX + "," + var27.WY);
            }

    int var36 = var27.WX - this.getMinX();
    int var40 = var27.WY - this.getMinY();

            assert this.cellMap[var36 + var40 * this.width] == var27;

            this.cellMap[var36 + var40 * this.width] = nullptr;
            this.LoadedCells.remove(var20--);
            this.ReleventNow.remove(var27);
            ServerCell.loaded2.remove(var27);
            this.ToLoad.remove(var27);
            MPStatistic.getInstance().ServerMapLoadedCells.Canceled();
         }
      }

      for (int var21 = 0; var21 < ServerCell.loaded2.size(); var21++) {
    ServerCell var28 = (ServerCell)ServerCell.loaded2.get(var21);
         if (var28.bCancelLoading) {
            if (MapLoading) {
               DebugLog.log(DebugType.MapLoading, "MainThread: forgetting cancelled " + var28.WX + "," + var28.WY);
            }

    int var37 = var28.WX - this.getMinX();
    int var41 = var28.WY - this.getMinY();

            assert this.cellMap[var37 + var41 * this.width] == var28;

            this.cellMap[var37 + var41 * this.width] = nullptr;
            this.LoadedCells.remove(var28);
            this.ReleventNow.remove(var28);
            ServerCell.loaded2.remove(var28);
            this.ToLoad.remove(var28);
            MPStatistic.getInstance().ServerMapLoaded2.Canceled();
         }
      }

      if (!this.ToLoad.empty()) {
         this.tempCells.clear();

         for (int var22 = 0; var22 < this.ToLoad.size(); var22++) {
    ServerCell var29 = this.ToLoad.get(var22);
            if (!var29.bCancelLoading && !var29.startedLoading) {
               this.tempCells.push_back(var29);
            }
         }

         if (!this.tempCells.empty()) {
            distToCellComparator.init();
            Collections.sort(this.tempCells, distToCellComparator);

            for (int var23 = 0; var23 < this.tempCells.size(); var23++) {
    ServerCell var30 = this.tempCells.get(var23);
               ServerCell.chunkLoader.addJob(var30);
               var30.startedLoading = true;
            }
         }

         ServerCell.chunkLoader.getLoaded(ServerCell.loaded);

         for (int var24 = 0; var24 < ServerCell.loaded.size(); var24++) {
    ServerCell var31 = (ServerCell)ServerCell.loaded.get(var24);
            if (!var31.doingRecalc) {
               ServerCell.chunkLoader.addRecalcJob(var31);
               var31.doingRecalc = true;
            }
         }

         ServerCell.loaded.clear();
         ServerCell.chunkLoader.getRecalc(ServerCell.loaded2);
         if (!ServerCell.loaded2.empty()) {
            try {
               ServerLOS.instance.suspend();

               for (int var25 = 0; var25 < ServerCell.loaded2.size(); var25++) {
    ServerCell var32 = (ServerCell)ServerCell.loaded2.get(var25);
    long var38 = System.nanoTime();
                  if (var32.Load2()) {
                     var38 = System.nanoTime();
                     var25--;
                     this.ToLoad.remove(var32);
                  }
               }
            } finally {
               ServerLOS.instance.resume();
            }
         }
      }

    int var26 = ServerOptions.instance.SaveWorldEveryMinutes.getValue();
      if (var26 > 0) {
    long var33 = System.currentTimeMillis();
         if (var33 > this.LastSaved + var26 * 60 * 1000) {
            this.bQueuedSaveAll = true;
            this.LastSaved = var33;
         }
      }

      if (this.bQueuedSaveAll) {
         this.bQueuedSaveAll = false;
    long var34 = System.nanoTime();
         this.SaveAll();
         ServerCell.chunkLoader.saveLater(GameTime.instance);
         ReanimatedPlayers.instance.saveReanimatedPlayers();
         MapCollisionData.instance.save();
         SGlobalObjects.save();

         try {
            ZomboidRadio.getInstance().Save();
         } catch (Exception var18) {
            var18.printStackTrace();
         }

         try {
            GlobalModData.instance.save();
         } catch (Exception var17) {
            var17.printStackTrace();
         }

         GameServer.UnPauseAllClients();
         System.out.println("Saving finish");
         DebugLog.log("Saving took " + (System.nanoTime() - var34) / 1000000.0 + " ms");
      }

      if (this.bQueuedQuit) {
    ByteBufferWriter var35 = GameServer.udpEngine.startPacket();
         PacketType.ServerQuit.doPacket(var35);
         GameServer.udpEngine.endPacketBroadcast(PacketType.ServerQuit);

         try {
            Thread.sleep(5000L);
         } catch (InterruptedException var16) {
            var16.printStackTrace();
         }

         MapCollisionData.instance.stop();
         ZombiePopulationManager.instance.stop();
         RCONServer.shutdown();
         ServerCell.chunkLoader.quit();
         ServerWorldDatabase.instance.close();
         ServerPlayersVehicles.instance.stop();
         ServerPlayerDB.getInstance().close();
         VehiclesDB2.instance.Reset();
         GameServer.udpEngine.Shutdown();
         ServerGUI.shutdown();
         SteamUtils.shutdown();
         System.exit(0);
      }

      this.ReleventNow.clear();
      this.bUpdateLOSThisFrame = LOSTick.Check();
      if (TimeTick.Check()) {
         ServerCell.chunkLoader.saveLater(GameTime.instance);
      }
   }

    IsoGridSquare getRandomSquareFromCell(int var1, int var2) {
      this.loadOrKeepRelevent(var1, var2);
    int var3 = var1;
    int var4 = var2;
    ServerCell var5 = this.getCell(var1, var2);
      if (var5 == nullptr) {
         throw RuntimeException("Cannot find a random square.");
      } else {
         var1 = (var1 + this.getMinX()) * 50;
         var2 = (var2 + this.getMinY()) * 50;
    IsoGridSquare var6 = nullptr;
    int var7 = 100;

         do {
            var6 = this.getGridSquare(Rand.Next(var1, var1 + 50), Rand.Next(var2, var2 + 50), 0);
            var7--;
            if (var6 == nullptr) {
               this.loadOrKeepRelevent(var3, var4);
            }
         } while (var6 == nullptr && var7 > 0);

    return var6;
      }
   }

    void postupdate() {
    int var1 = this.LoadedCells.size();
    bool var2 = false;

      try {
         for (int var3 = 0; var3 < this.LoadedCells.size(); var3++) {
    ServerCell var4 = this.LoadedCells.get(var3);
    bool var5 = this.ReleventNow.contains(var4) || !this.outsidePlayerInfluence(var4);
            if (!var4.bLoaded) {
               if (!var5 && !var4.bCancelLoading) {
                  if (MapLoading) {
                     DebugLog.log(DebugType.MapLoading, "MainThread: cancelling " + var4.WX + "," + var4.WY + " cell.startedLoading=" + var4.startedLoading);
                  }

                  if (!var4.startedLoading) {
                     var4.bLoadingWasCancelled = true;
                  }

                  var4.bCancelLoading = true;
               }
            } else if (!var5) {
    int var6 = var4.WX - this.getMinX();
    int var7 = var4.WY - this.getMinY();
               if (!var2) {
                  ServerLOS.instance.suspend();
                  var2 = true;
               }

               this.cellMap[var7 * this.width + var6].Unload();
               this.cellMap[var7 * this.width + var6] = nullptr;
               this.LoadedCells.remove(var4);
               var3--;
            } else {
               var4.update();
            }
         }
      } catch (Exception var11) {
         var11.printStackTrace();
      } finally {
         if (var2) {
            ServerLOS.instance.resume();
         }
      }

      NetworkZombiePacker.getInstance().postupdate();
      ServerCell.chunkLoader.updateSaved();
   }

    void physicsCheck(int var1, int var2) {
    int var3 = var1 / 50;
    int var4 = var2 / 50;
      var3 -= this.getMinX();
      var4 -= this.getMinY();
    ServerCell var5 = this.getCell(var3, var4);
      if (var5 != nullptr && var5.bLoaded) {
         var5.bPhysicsCheck = true;
      }
   }

    bool outsidePlayerInfluence(ServerCell var1) {
    int var2 = var1.WX * 50;
    int var3 = var1.WY * 50;
    int var4 = (var1.WX + 1) * 50;
    int var5 = (var1.WY + 1) * 50;

      for (int var6 = 0; var6 < GameServer.udpEngine.connections.size(); var6++) {
    UdpConnection var7 = (UdpConnection)GameServer.udpEngine.connections.get(var6);
         if (var7.RelevantTo(var2, var3)) {
    return false;
         }

         if (var7.RelevantTo(var4, var3)) {
    return false;
         }

         if (var7.RelevantTo(var4, var5)) {
    return false;
         }

         if (var7.RelevantTo(var2, var5)) {
    return false;
         }
      }

    return true;
   }

    void saveZoneInsidePlayerInfluence(short var1) {
      for (int var2 = 0; var2 < GameServer.udpEngine.connections.size(); var2++) {
    UdpConnection var3 = (UdpConnection)GameServer.udpEngine.connections.get(var2);

         for (int var4 = 0; var4 < var3.players.length; var4++) {
            if (var3.players[var4] != nullptr && var3.players[var4].OnlineID == var1) {
    IsoGridSquare var5 = IsoWorld.instance.CurrentCell.getGridSquare(var3.players[var4].x, var3.players[var4].y, var3.players[var4].z);
               if (var5 != nullptr) {
                  ServerCell.chunkLoader.addSaveLoadedJob(var5.chunk);
                  return;
               }
            }
         }
      }

      ServerCell.chunkLoader.updateSaved();
   }

    bool InsideThePlayerInfluence(ServerCell var1, short var2) {
    int var3 = var1.WX * 50;
    int var4 = var1.WY * 50;
    int var5 = (var1.WX + 1) * 50;
    int var6 = (var1.WY + 1) * 50;

      for (int var7 = 0; var7 < GameServer.udpEngine.connections.size(); var7++) {
    UdpConnection var8 = (UdpConnection)GameServer.udpEngine.connections.get(var7);

         for (int var9 = 0; var9 < var8.players.length; var9++) {
            if (var8.players[var9] != nullptr && var8.players[var9].OnlineID == var2) {
               if (var8.RelevantToPlayerIndex(var9, var3, var4)) {
    return true;
               }

               if (var8.RelevantToPlayerIndex(var9, var5, var4)) {
    return true;
               }

               if (var8.RelevantToPlayerIndex(var9, var5, var6)) {
    return true;
               }

               if (var8.RelevantToPlayerIndex(var9, var3, var6)) {
    return true;
               }

    return false;
            }
         }
      }

    return false;
   }

    IsoGridSquare getGridSquare(int var1, int var2, int var3) {
      if (!IsoWorld.instance.isValidSquare(var1, var2, var3)) {
    return nullptr;
      } else {
    int var4 = var1 / 50;
    int var5 = var2 / 50;
         var4 -= this.getMinX();
         var5 -= this.getMinY();
    int var6 = var1 / 10;
    int var7 = var2 / 10;
    int var8 = var6 % 5;
    int var9 = var7 % 5;
    int var10 = var1 % 10;
    int var11 = var2 % 10;
    ServerCell var12 = this.getCell(var4, var5);
         if (var12 != nullptr && var12.bLoaded) {
    IsoChunk var13 = var12.chunks[var8][var9];
    return var13 = = nullptr ? nullptr : var13.getGridSquare(var10, var11, var3);
         } else {
    return nullptr;
         }
      }
   }

    void setGridSquare(int var1, int var2, int var3, IsoGridSquare var4) {
    int var5 = var1 / 50;
    int var6 = var2 / 50;
      var5 -= this.getMinX();
      var6 -= this.getMinY();
    int var7 = var1 / 10;
    int var8 = var2 / 10;
    int var9 = var7 % 5;
    int var10 = var8 % 5;
    int var11 = var1 % 10;
    int var12 = var2 % 10;
    ServerCell var13 = this.getCell(var5, var6);
      if (var13 != nullptr) {
    IsoChunk var14 = var13.chunks[var9][var10];
         if (var14 != nullptr) {
            var14.setSquare(var11, var12, var3, var4);
         }
      }
   }

    bool isInLoaded(float var1, float var2) {
    int var3 = (int)var1;
    int var4 = (int)var2;
      var3 /= 50;
      var4 /= 50;
      var3 -= this.getMinX();
      var4 -= this.getMinY();
      return this.ToLoad.contains(this.getCell(var3, var4)) ? false : this.getCell(var3, var4) != nullptr;
   }

    IsoChunk getChunk(int var1, int var2) {
      if (var1 >= 0 && var2 >= 0) {
    int var3 = var1 / 5;
    int var4 = var2 / 5;
         var3 -= this.getMinX();
         var4 -= this.getMinY();
    int var5 = var1 % 5;
    int var6 = var2 % 5;
    ServerCell var7 = this.getCell(var3, var4);
         return var7 != nullptr && var7.bLoaded ? var7.chunks[var5][var6] : nullptr;
      } else {
    return nullptr;
      }
   }

    void setSoftResetChunk(IsoChunk var1) {
    int var2 = var1.wx / 5;
    int var3 = var1.wy / 5;
      var2 -= this.getMinX();
      var3 -= this.getMinY();
      if (this.isValidCell(var2, var3)) {
    ServerCell var4 = this.getCell(var2, var3);
         if (var4 == nullptr) {
            var4 = std::make_unique<ServerCell>();
            var4.bLoaded = true;
            this.cellMap[var3 * this.width + var2] = var4;
         }

    int var5 = var1.wx % 5;
    int var6 = var1.wy % 5;
         var4.chunks[var5][var6] = var1;
      }
   }

    void clearSoftResetChunk(IsoChunk var1) {
    int var2 = var1.wx / 5;
    int var3 = var1.wy / 5;
      var2 -= this.getMinX();
      var3 -= this.getMinY();
    ServerCell var4 = this.getCell(var2, var3);
      if (var4 != nullptr) {
    int var5 = var1.wx % 5;
    int var6 = var1.wy % 5;
         var4.chunks[var5][var6] = nullptr;
      }
   }
}
} // namespace network
} // namespace zombie
