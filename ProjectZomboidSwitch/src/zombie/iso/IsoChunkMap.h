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
#include "zombie/iso/IsoChunk/JobType.h"
#include "zombie/iso/areas/IsoRoom.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/MPStatistics.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/ui/TextManager.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/VehicleCache.h"
#include "zombie/vehicles/VehicleManager.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {


class IsoChunkMap {
public:
    static const int LEVELS = 8;
    static const int ChunksPerWidth = 10;
   public static const std::unordered_map<int, IsoChunk> SharedChunks = std::make_unique<std::unordered_map<>>();
    static int MPWorldXA = 0;
    static int MPWorldYA = 0;
    static int MPWorldZA = 0;
    static int WorldXA = 11702;
    static int WorldYA = 6896;
    static int WorldZA = 0;
   public static const int[] SWorldX = new int[4];
   public static const int[] SWorldY = new int[4];
   public static const ConcurrentLinkedQueue<IsoChunk> chunkStore = std::make_unique<ConcurrentLinkedQueue<>>();
    static const ReentrantLock bSettingChunk = std::make_shared<ReentrantLock>(true);
    static int StartChunkGridWidth = 13;
    static int ChunkGridWidth = StartChunkGridWidth;
    static int ChunkWidthInTiles = 10 * ChunkGridWidth;
    static const ColorInfo inf = std::make_shared<ColorInfo>();
   private static const std::vector<IsoChunk> saveList = std::make_unique<std::vector<>>();
   private static const std::vector<std::vector<IsoFloorBloodSplat>> splatByType = std::make_unique<std::vector<>>();
    int PlayerID = 0;
    bool ignore = false;
    int WorldX = tileToChunk(WorldXA);
    int WorldY = tileToChunk(WorldYA);
   public const std::vector<std::string> filenameServerRequests = std::make_unique<std::vector<>>();
   protected IsoChunk[] chunksSwapB;
   protected IsoChunk[] chunksSwapA;
    bool bReadBufferA = true;
    int XMinTiles = -1;
    int YMinTiles = -1;
    int XMaxTiles = -1;
    int YMaxTiles = -1;
    IsoCell cell;
    const UpdateLimit checkVehiclesFrequency = std::make_shared<UpdateLimit>(3000L);

    public IsoChunkMap(IsoCell var1) {
      this.cell = var1;
      WorldReuserThread.instance.finished = false;
      this.chunksSwapB = new IsoChunk[ChunkGridWidth * ChunkGridWidth];
      this.chunksSwapA = new IsoChunk[ChunkGridWidth * ChunkGridWidth];
   }

    static void CalcChunkWidth() {
      if (DebugOptions.instance.WorldChunkMap5x5.getValue()) {
         ChunkGridWidth = 5;
         ChunkWidthInTiles = ChunkGridWidth * 10;
      } else {
    float var0 = Core.getInstance().getScreenWidth();
    float var1 = var0 / 1920.0F;
         if (var1 > 1.0F) {
            var1 = 1.0F;
         }

         ChunkGridWidth = (int)(StartChunkGridWidth * var1 * 1.5);
         if (ChunkGridWidth / 2 * 2 == ChunkGridWidth) {
            ChunkGridWidth++;
         }

         ChunkWidthInTiles = ChunkGridWidth * 10;
      }
   }

    static void setWorldStartPos(int var0, int var1) {
      SWorldX[IsoPlayer.getPlayerIndex()] = tileToChunk(var0);
      SWorldY[IsoPlayer.getPlayerIndex()] = tileToChunk(var1);
   }

    void Dispose() {
      WorldReuserThread.instance.finished = true;
      IsoChunk.loadGridSquare.clear();
      this.chunksSwapA = nullptr;
      this.chunksSwapB = nullptr;
   }

    void setInitialPos(int var1, int var2) {
      this.WorldX = var1;
      this.WorldY = var2;
      this.XMinTiles = -1;
      this.XMaxTiles = -1;
      this.YMinTiles = -1;
      this.YMaxTiles = -1;
   }

    void processAllLoadGridSquare() {
      for (IsoChunk var1 = (IsoChunk)IsoChunk.loadGridSquare.poll(); var1 != nullptr; var1 = (IsoChunk)IsoChunk.loadGridSquare.poll()) {
         bSettingChunk.lock();

         try {
    bool var2 = false;

            for (int var3 = 0; var3 < IsoPlayer.numPlayers; var3++) {
    IsoChunkMap var4 = IsoWorld.instance.CurrentCell.ChunkMap[var3];
               if (!var4.ignore && var4.setChunkDirect(var1, false)) {
                  var2 = true;
               }
            }

            if (!var2) {
               WorldReuserThread.instance.addReuseChunk(var1);
            } else {
               var1.doLoadGridsquare();
            }
         } finally {
            bSettingChunk.unlock();
         }
      }
   }

    void update() {
    int var2 = IsoChunk.loadGridSquare.size();
      if (var2 != 0) {
         var2 = 1 + var2 * 3 / ChunkGridWidth;
      }

      while (var2 > 0) {
    IsoChunk var1 = (IsoChunk)IsoChunk.loadGridSquare.poll();
         if (var1 != nullptr) {
    bool var3 = false;

            for (int var4 = 0; var4 < IsoPlayer.numPlayers; var4++) {
    IsoChunkMap var5 = IsoWorld.instance.CurrentCell.ChunkMap[var4];
               if (!var5.ignore && var5.setChunkDirect(var1, false)) {
                  var3 = true;
               }
            }

            if (!var3) {
               WorldReuserThread.instance.addReuseChunk(var1);
               var2--;
               continue;
            }

            var1.bLoaded = true;
            bSettingChunk.lock();

            try {
               var1.doLoadGridsquare();
               if (GameClient.bClient) {
    std::vector var11 = VehicleCache.vehicleGet(var1.wx, var1.wy);
                  VehicleManager.instance.sendRequestGetFull(var11);
               }
            } finally {
               bSettingChunk.unlock();
            }

            for (int var12 = 0; var12 < IsoPlayer.numPlayers; var12++) {
    IsoPlayer var14 = IsoPlayer.players[var12];
               if (var14 != nullptr) {
                  var14.dirtyRecalcGridStackTime = 20.0F;
               }
            }
         }

         var2--;
      }

      for (int var10 = 0; var10 < ChunkGridWidth; var10++) {
         for (int var13 = 0; var13 < ChunkGridWidth; var13++) {
    IsoChunk var9 = this.getChunk(var13, var10);
            if (var9 != nullptr) {
               var9.update();
            }
         }
      }

      if (this.checkVehiclesFrequency.Check() && GameClient.bClient) {
         this.checkVehicles();
      }
   }

    void checkVehicles() {
      for (int var1 = 0; var1 < ChunkGridWidth; var1++) {
         for (int var2 = 0; var2 < ChunkGridWidth; var2++) {
    IsoChunk var3 = this.getChunk(var2, var1);
            if (var3 != nullptr && var3.bLoaded) {
    std::vector var4 = VehicleCache.vehicleGet(var3.wx, var3.wy);
               if (var4 != nullptr && var3.vehicles.size() != var4.size()) {
                  for (int var5 = 0; var5 < var4.size(); var5++) {
    short var6 = ((VehicleCache)var4.get(var5)).id;
    bool var7 = false;

                     for (int var8 = 0; var8 < var3.vehicles.size(); var8++) {
                        if (((BaseVehicle)var3.vehicles.get(var8)).getId() == var6) {
                           var7 = true;
                           break;
                        }
                     }

                     if (!var7 && VehicleManager.instance.getVehicleByID(var6) == nullptr) {
                        VehicleManager.instance.sendRequestGetFull(var6, PacketType.Vehicles);
                     }
                  }
               }
            }
         }
      }
   }

    void checkIntegrity() {
      IsoWorld.instance.CurrentCell.ChunkMap[0].XMinTiles = -1;

      for (int var1 = IsoWorld.instance.CurrentCell.ChunkMap[0].getWorldXMinTiles();
         var1 < IsoWorld.instance.CurrentCell.ChunkMap[0].getWorldXMaxTiles();
         var1++
      ) {
         for (int var2 = IsoWorld.instance.CurrentCell.ChunkMap[0].getWorldYMinTiles();
            var2 < IsoWorld.instance.CurrentCell.ChunkMap[0].getWorldYMaxTiles();
            var2++
         ) {
    IsoGridSquare var3 = IsoWorld.instance.CurrentCell.getGridSquare(var1, var2, 0);
            if (var3 != nullptr && (var3.getX() != var1 || var3.getY() != var2)) {
    int var4 = var1 / 10;
    int var5 = var2 / 10;
               var4 -= IsoWorld.instance.CurrentCell.ChunkMap[0].getWorldXMin();
               var5 -= IsoWorld.instance.CurrentCell.ChunkMap[0].getWorldYMin();
    void* var6 = nullptr;
               var6 = std::make_shared<IsoChunk>(IsoWorld.instance.CurrentCell);
               ((IsoChunk)var6).refs.push_back(IsoWorld.instance.CurrentCell.ChunkMap[0]);
               WorldStreamer.instance.addJob((IsoChunk)var6, var1 / 10, var2 / 10, false);

               while (!((IsoChunk)var6).bLoaded) {
                  try {
                     Thread.sleep(13L);
                  } catch (InterruptedException var8) {
                     var8.printStackTrace();
                  }
               }
            }
         }
      }
   }

    void checkIntegrityThread() {
      IsoWorld.instance.CurrentCell.ChunkMap[0].XMinTiles = -1;

      for (int var1 = IsoWorld.instance.CurrentCell.ChunkMap[0].getWorldXMinTiles();
         var1 < IsoWorld.instance.CurrentCell.ChunkMap[0].getWorldXMaxTiles();
         var1++
      ) {
         for (int var2 = IsoWorld.instance.CurrentCell.ChunkMap[0].getWorldYMinTiles();
            var2 < IsoWorld.instance.CurrentCell.ChunkMap[0].getWorldYMaxTiles();
            var2++
         ) {
    IsoGridSquare var3 = IsoWorld.instance.CurrentCell.getGridSquare(var1, var2, 0);
            if (var3 != nullptr && (var3.getX() != var1 || var3.getY() != var2)) {
    int var4 = var1 / 10;
    int var5 = var2 / 10;
               var4 -= IsoWorld.instance.CurrentCell.ChunkMap[0].getWorldXMin();
               var5 -= IsoWorld.instance.CurrentCell.ChunkMap[0].getWorldYMin();
    IsoChunk var6 = std::make_shared<IsoChunk>(IsoWorld.instance.CurrentCell);
               var6.refs.push_back(IsoWorld.instance.CurrentCell.ChunkMap[0]);
               WorldStreamer.instance.addJobInstant(var6, var1, var2, var1 / 10, var2 / 10);
            }

            if (var3 != nullptr) {
            }
         }
      }
   }

    void LoadChunk(int var1, int var2, int var3, int var4) {
    IsoChunk var5 = nullptr;
      if (SharedChunks.containsKey((var1 << 16) + var2)) {
         var5 = SharedChunks.get((var1 << 16) + var2);
         var5.setCache();
         this.setChunk(var3, var4, var5);
         var5.refs.push_back(this);
      } else {
         var5 = chunkStore.poll();
         if (var5 == nullptr) {
            var5 = std::make_shared<IsoChunk>(this.cell);
         } else {
            MPStatistics.decreaseStoredChunk();
         }

         SharedChunks.put((var1 << 16) + var2, var5);
         var5.refs.push_back(this);
         WorldStreamer.instance.addJob(var5, var1, var2, false);
      }
   }

    IsoChunk LoadChunkForLater(int var1, int var2, int var3, int var4) {
      if (!IsoWorld.instance.getMetaGrid().isValidChunk(var1, var2)) {
    return nullptr;
      } else {
    IsoChunk var5;
         if (SharedChunks.containsKey((var1 << 16) + var2)) {
            var5 = SharedChunks.get((var1 << 16) + var2);
            if (!var5.refs.contains(this)) {
               var5.refs.push_back(this);
               var5.lightCheck[this.PlayerID] = true;
            }

            if (!var5.bLoaded) {
    return var5;
            }

            this.setChunk(var3, var4, var5);
         } else {
            var5 = chunkStore.poll();
            if (var5 == nullptr) {
               var5 = std::make_shared<IsoChunk>(this.cell);
            } else {
               MPStatistics.decreaseStoredChunk();
            }

            SharedChunks.put((var1 << 16) + var2, var5);
            var5.refs.push_back(this);
            WorldStreamer.instance.addJob(var5, var1, var2, true);
         }

    return var5;
      }
   }

    IsoChunk getChunkForGridSquare(int var1, int var2) {
      var1 = this.gridSquareToTileX(var1);
      var2 = this.gridSquareToTileY(var2);
      return !this.isTileOutOfrange(var1) && !this.isTileOutOfrange(var2) ? this.getChunk(tileToChunk(var1), tileToChunk(var2)) : nullptr;
   }

    IsoChunk getChunkCurrent(int var1, int var2) {
      if (var1 < 0 || var1 >= ChunkGridWidth || var2 < 0 || var2 >= ChunkGridWidth) {
    return nullptr;
      } else {
         return !this.bReadBufferA ? this.chunksSwapA[ChunkGridWidth * var2 + var1] : this.chunksSwapB[ChunkGridWidth * var2 + var1];
      }
   }

    void setGridSquare(IsoGridSquare var1, int var2, int var3, int var4) {
    assert var1 = = nullptr || var1.x == var2 && var1.y == var3 && var1.z == var4;

    int var5 = this.gridSquareToTileX(var2);
    int var6 = this.gridSquareToTileY(var3);
      if (!this.isTileOutOfrange(var5) && !this.isTileOutOfrange(var6) && !this.isGridSquareOutOfRangeZ(var4)) {
    IsoChunk var7 = this.getChunk(tileToChunk(var5), tileToChunk(var6));
         if (var7 != nullptr) {
            if (var4 > var7.maxLevel) {
               var7.maxLevel = var4;
            }

            var7.setSquare(this.tileToGridSquare(var5), this.tileToGridSquare(var6), var4, var1);
         }
      }
   }

    IsoGridSquare getGridSquare(int var1, int var2, int var3) {
      var1 = this.gridSquareToTileX(var1);
      var2 = this.gridSquareToTileY(var2);
      return this.getGridSquareDirect(var1, var2, var3);
   }

    IsoGridSquare getGridSquareDirect(int var1, int var2, int var3) {
      if (!this.isTileOutOfrange(var1) && !this.isTileOutOfrange(var2) && !this.isGridSquareOutOfRangeZ(var3)) {
    IsoChunk var4 = this.getChunk(tileToChunk(var1), tileToChunk(var2));
    return var4 = = nullptr ? nullptr : var4.getGridSquare(this.tileToGridSquare(var1), this.tileToGridSquare(var2), var3);
      } else {
    return nullptr;
      }
   }

    int tileToGridSquare(int var1) {
      return var1 % 10;
   }

    static int tileToChunk(int var0) {
      return var0 / 10;
   }

    bool isTileOutOfrange(int var1) {
      return var1 < 0 || var1 >= this.getWidthInTiles();
   }

    bool isGridSquareOutOfRangeZ(int var1) {
      return var1 < 0 || var1 >= 8;
   }

    int gridSquareToTileX(int var1) {
      return var1 - (this.WorldX - ChunkGridWidth / 2) * 10;
   }

    int gridSquareToTileY(int var1) {
      return var1 - (this.WorldY - ChunkGridWidth / 2) * 10;
   }

    IsoChunk getChunk(int var1, int var2) {
      if (var1 < 0 || var1 >= ChunkGridWidth || var2 < 0 || var2 >= ChunkGridWidth) {
    return nullptr;
      } else {
         return this.bReadBufferA ? this.chunksSwapA[ChunkGridWidth * var2 + var1] : this.chunksSwapB[ChunkGridWidth * var2 + var1];
      }
   }

    void setChunk(int var1, int var2, IsoChunk var3) {
      if (!this.bReadBufferA) {
         this.chunksSwapA[ChunkGridWidth * var2 + var1] = var3;
      } else {
         this.chunksSwapB[ChunkGridWidth * var2 + var1] = var3;
      }
   }

    bool setChunkDirect(IsoChunk var1, bool var2) {
    long var3 = System.nanoTime();
      if (var2) {
         bSettingChunk.lock();
      }

    long var5 = System.nanoTime();
    int var7 = var1.wx - this.WorldX;
    int var8 = var1.wy - this.WorldY;
      var7 += ChunkGridWidth / 2;
      var8 += ChunkGridWidth / 2;
      if (var1.jobType == JobType.Convert) {
         var7 = 0;
         var8 = 0;
      }

      if (!var1.refs.empty() && var7 >= 0 && var8 >= 0 && var7 < ChunkGridWidth && var8 < ChunkGridWidth) {
         try {
            if (this.bReadBufferA) {
               this.chunksSwapA[ChunkGridWidth * var8 + var7] = var1;
            } else {
               this.chunksSwapB[ChunkGridWidth * var8 + var7] = var1;
            }

            var1.bLoaded = true;
            if (var1.jobType == JobType.None) {
               var1.setCache();
               var1.updateBuildings();
            }

    double var9 = (System.nanoTime() - var5) / 1000000.0;
    double var11 = (System.nanoTime() - var3) / 1000000.0;
            if (LightingThread.DebugLockTime && var11 > 10.0) {
               DebugLog.log("setChunkDirect time " + var9 + "/" + var11 + " ms");
            }
         } finally {
            if (var2) {
               bSettingChunk.unlock();
            }
         }

    return true;
      } else {
         if (var1.refs.contains(this)) {
            var1.refs.remove(this);
            if (var1.refs.empty()) {
               SharedChunks.remove((var1.wx << 16) + var1.wy);
            }
         }

         if (var2) {
            bSettingChunk.unlock();
         }

    return false;
      }
   }

    void drawDebugChunkMap() {
    short var1 = 64;
    uint8_t var2 = 0;

      for (int var3 = 0; var3 < ChunkGridWidth; var3++) {
         var2 = 0;

         for (int var4 = 0; var4 < ChunkGridWidth; var4++) {
            var2 += 64;
    IsoChunk var5 = this.getChunk(var3, var4);
            if (var5 != nullptr) {
    IsoGridSquare var6 = var5.getGridSquare(0, 0, 0);
               if (var6 == nullptr) {
                  TextManager.instance.DrawString(var1, var2, "wx:" + var5.wx + " wy:" + var5.wy);
               }
            }
         }

         var1 += 128;
      }
   }

    void LoadLeft() {
      this.XMinTiles = -1;
      this.YMinTiles = -1;
      this.XMaxTiles = -1;
      this.YMaxTiles = -1;
      this.Left();
      WorldSimulation.instance.scrollGroundLeft(this.PlayerID);
      this.XMinTiles = -1;
      this.YMinTiles = -1;
      this.XMaxTiles = -1;
      this.YMaxTiles = -1;

      for (int var1 = -(ChunkGridWidth / 2); var1 <= ChunkGridWidth / 2; var1++) {
         this.LoadChunkForLater(this.WorldX - ChunkGridWidth / 2, this.WorldY + var1, 0, var1 + ChunkGridWidth / 2);
      }

      this.SwapChunkBuffers();
      this.XMinTiles = -1;
      this.YMinTiles = -1;
      this.XMaxTiles = -1;
      this.YMaxTiles = -1;
      this.UpdateCellCache();
      LightingThread.instance.scrollLeft(this.PlayerID);
   }

    void SwapChunkBuffers() {
      for (int var1 = 0; var1 < ChunkGridWidth * ChunkGridWidth; var1++) {
         if (this.bReadBufferA) {
            this.chunksSwapA[var1] = nullptr;
         } else {
            this.chunksSwapB[var1] = nullptr;
         }
      }

      this.XMinTiles = this.XMaxTiles = -1;
      this.YMinTiles = this.YMaxTiles = -1;
      this.bReadBufferA = !this.bReadBufferA;
   }

    void setChunk(int var1, IsoChunk var2) {
      if (!this.bReadBufferA) {
         this.chunksSwapA[var1] = var2;
      } else {
         this.chunksSwapB[var1] = var2;
      }
   }

    IsoChunk getChunk(int var1) {
      return this.bReadBufferA ? this.chunksSwapA[var1] : this.chunksSwapB[var1];
   }

    void LoadRight() {
      this.XMinTiles = -1;
      this.YMinTiles = -1;
      this.XMaxTiles = -1;
      this.YMaxTiles = -1;
      this.Right();
      WorldSimulation.instance.scrollGroundRight(this.PlayerID);
      this.XMinTiles = -1;
      this.YMinTiles = -1;
      this.XMaxTiles = -1;
      this.YMaxTiles = -1;

      for (int var1 = -(ChunkGridWidth / 2); var1 <= ChunkGridWidth / 2; var1++) {
         this.LoadChunkForLater(this.WorldX + ChunkGridWidth / 2, this.WorldY + var1, ChunkGridWidth - 1, var1 + ChunkGridWidth / 2);
      }

      this.SwapChunkBuffers();
      this.XMinTiles = -1;
      this.YMinTiles = -1;
      this.XMaxTiles = -1;
      this.YMaxTiles = -1;
      this.UpdateCellCache();
      LightingThread.instance.scrollRight(this.PlayerID);
   }

    void LoadUp() {
      this.XMinTiles = -1;
      this.YMinTiles = -1;
      this.XMaxTiles = -1;
      this.YMaxTiles = -1;
      this.Up();
      WorldSimulation.instance.scrollGroundUp(this.PlayerID);
      this.XMinTiles = -1;
      this.YMinTiles = -1;
      this.XMaxTiles = -1;
      this.YMaxTiles = -1;

      for (int var1 = -(ChunkGridWidth / 2); var1 <= ChunkGridWidth / 2; var1++) {
         this.LoadChunkForLater(this.WorldX + var1, this.WorldY - ChunkGridWidth / 2, var1 + ChunkGridWidth / 2, 0);
      }

      this.SwapChunkBuffers();
      this.XMinTiles = -1;
      this.YMinTiles = -1;
      this.XMaxTiles = -1;
      this.YMaxTiles = -1;
      this.UpdateCellCache();
      LightingThread.instance.scrollUp(this.PlayerID);
   }

    void LoadDown() {
      this.XMinTiles = -1;
      this.YMinTiles = -1;
      this.XMaxTiles = -1;
      this.YMaxTiles = -1;
      this.Down();
      WorldSimulation.instance.scrollGroundDown(this.PlayerID);
      this.XMinTiles = -1;
      this.YMinTiles = -1;
      this.XMaxTiles = -1;
      this.YMaxTiles = -1;

      for (int var1 = -(ChunkGridWidth / 2); var1 <= ChunkGridWidth / 2; var1++) {
         this.LoadChunkForLater(this.WorldX + var1, this.WorldY + ChunkGridWidth / 2, var1 + ChunkGridWidth / 2, ChunkGridWidth - 1);
      }

      this.SwapChunkBuffers();
      this.XMinTiles = -1;
      this.YMinTiles = -1;
      this.XMaxTiles = -1;
      this.YMaxTiles = -1;
      this.UpdateCellCache();
      LightingThread.instance.scrollDown(this.PlayerID);
   }

    void UpdateCellCache() {
    int var1 = this.getWidthInTiles();

      for (int var2 = 0; var2 < var1; var2++) {
         for (int var3 = 0; var3 < var1; var3++) {
            for (int var4 = 0; var4 < 8; var4++) {
    IsoGridSquare var5 = this.getGridSquare(var2 + this.getWorldXMinTiles(), var3 + this.getWorldYMinTiles(), var4);
               IsoWorld.instance.CurrentCell.setCacheGridSquareLocal(var2, var3, var4, var5, this.PlayerID);
            }
         }
      }
   }

    void Up() {
      for (int var1 = 0; var1 < ChunkGridWidth; var1++) {
         for (int var2 = ChunkGridWidth - 1; var2 > 0; var2--) {
    IsoChunk var3 = this.getChunk(var1, var2);
            if (var3 == nullptr && var2 == ChunkGridWidth - 1) {
    int var4 = this.WorldX - ChunkGridWidth / 2 + var1;
    int var5 = this.WorldY - ChunkGridWidth / 2 + var2;
               var3 = SharedChunks.get((var4 << 16) + var5);
               if (var3 != nullptr) {
                  if (var3.refs.contains(this)) {
                     var3.refs.remove(this);
                     if (var3.refs.empty()) {
                        SharedChunks.remove((var3.wx << 16) + var3.wy);
                     }
                  }

                  var3 = nullptr;
               }
            }

            if (var3 != nullptr && var2 == ChunkGridWidth - 1) {
               var3.refs.remove(this);
               if (var3.refs.empty()) {
                  SharedChunks.remove((var3.wx << 16) + var3.wy);
                  var3.removeFromWorld();
                  ChunkSaveWorker.instance.Add(var3);
               }
            }

            this.setChunk(var1, var2, this.getChunk(var1, var2 - 1));
         }

         this.setChunk(var1, 0, nullptr);
      }

      this.WorldY--;
   }

    void Down() {
      for (int var1 = 0; var1 < ChunkGridWidth; var1++) {
         for (int var2 = 0; var2 < ChunkGridWidth - 1; var2++) {
    IsoChunk var3 = this.getChunk(var1, var2);
            if (var3 == nullptr && var2 == 0) {
    int var4 = this.WorldX - ChunkGridWidth / 2 + var1;
    int var5 = this.WorldY - ChunkGridWidth / 2 + var2;
               var3 = SharedChunks.get((var4 << 16) + var5);
               if (var3 != nullptr) {
                  if (var3.refs.contains(this)) {
                     var3.refs.remove(this);
                     if (var3.refs.empty()) {
                        SharedChunks.remove((var3.wx << 16) + var3.wy);
                     }
                  }

                  var3 = nullptr;
               }
            }

            if (var3 != nullptr && var2 == 0) {
               var3.refs.remove(this);
               if (var3.refs.empty()) {
                  SharedChunks.remove((var3.wx << 16) + var3.wy);
                  var3.removeFromWorld();
                  ChunkSaveWorker.instance.Add(var3);
               }
            }

            this.setChunk(var1, var2, this.getChunk(var1, var2 + 1));
         }

         this.setChunk(var1, ChunkGridWidth - 1, nullptr);
      }

      this.WorldY++;
   }

    void Left() {
      for (int var1 = 0; var1 < ChunkGridWidth; var1++) {
         for (int var2 = ChunkGridWidth - 1; var2 > 0; var2--) {
    IsoChunk var3 = this.getChunk(var2, var1);
            if (var3 == nullptr && var2 == ChunkGridWidth - 1) {
    int var4 = this.WorldX - ChunkGridWidth / 2 + var2;
    int var5 = this.WorldY - ChunkGridWidth / 2 + var1;
               var3 = SharedChunks.get((var4 << 16) + var5);
               if (var3 != nullptr) {
                  if (var3.refs.contains(this)) {
                     var3.refs.remove(this);
                     if (var3.refs.empty()) {
                        SharedChunks.remove((var3.wx << 16) + var3.wy);
                     }
                  }

                  var3 = nullptr;
               }
            }

            if (var3 != nullptr && var2 == ChunkGridWidth - 1) {
               var3.refs.remove(this);
               if (var3.refs.empty()) {
                  SharedChunks.remove((var3.wx << 16) + var3.wy);
                  var3.removeFromWorld();
                  ChunkSaveWorker.instance.Add(var3);
               }
            }

            this.setChunk(var2, var1, this.getChunk(var2 - 1, var1));
         }

         this.setChunk(0, var1, nullptr);
      }

      this.WorldX--;
   }

    void Right() {
      for (int var1 = 0; var1 < ChunkGridWidth; var1++) {
         for (int var2 = 0; var2 < ChunkGridWidth - 1; var2++) {
    IsoChunk var3 = this.getChunk(var2, var1);
            if (var3 == nullptr && var2 == 0) {
    int var4 = this.WorldX - ChunkGridWidth / 2 + var2;
    int var5 = this.WorldY - ChunkGridWidth / 2 + var1;
               var3 = SharedChunks.get((var4 << 16) + var5);
               if (var3 != nullptr) {
                  if (var3.refs.contains(this)) {
                     var3.refs.remove(this);
                     if (var3.refs.empty()) {
                        SharedChunks.remove((var3.wx << 16) + var3.wy);
                     }
                  }

                  var3 = nullptr;
               }
            }

            if (var3 != nullptr && var2 == 0) {
               var3.refs.remove(this);
               if (var3.refs.empty()) {
                  SharedChunks.remove((var3.wx << 16) + var3.wy);
                  var3.removeFromWorld();
                  ChunkSaveWorker.instance.Add(var3);
               }
            }

            this.setChunk(var2, var1, this.getChunk(var2 + 1, var1));
         }

         this.setChunk(ChunkGridWidth - 1, var1, nullptr);
      }

      this.WorldX++;
   }

    int getWorldXMin() {
      return this.WorldX - ChunkGridWidth / 2;
   }

    int getWorldYMin() {
      return this.WorldY - ChunkGridWidth / 2;
   }

    void ProcessChunkPos(IsoGameCharacter var1) {
    int var2 = (int)var1.getX();
    int var3 = (int)var1.getY();
    int var4 = (int)var1.getZ();
      if (IsoPlayer.getInstance() != nullptr && IsoPlayer.getInstance().getVehicle() != nullptr) {
    IsoPlayer var5 = IsoPlayer.getInstance();
    BaseVehicle var6 = var5.getVehicle();
    float var7 = var6.getCurrentSpeedKmHour() / 5.0F;
         if (!var5.isDriving()) {
            var7 = Math.min(var7 * 2.0F, 20.0F);
         }

         var2 += Math.round(var5.getForwardDirection().x * var7);
         var3 += Math.round(var5.getForwardDirection().y * var7);
      }

      var2 /= 10;
      var3 /= 10;
      if (var2 != this.WorldX || var3 != this.WorldY) {
    long var23 = System.nanoTime();
    double var24 = 0.0;
         bSettingChunk.lock();
    long var9 = System.nanoTime();

         try {
            if (Math.abs(var2 - this.WorldX) < ChunkGridWidth && Math.abs(var3 - this.WorldY) < ChunkGridWidth) {
               if (var2 != this.WorldX) {
                  if (var2 < this.WorldX) {
                     this.LoadLeft();
                  } else {
                     this.LoadRight();
                  }
               } else if (var3 != this.WorldY) {
                  if (var3 < this.WorldY) {
                     this.LoadUp();
                  } else {
                     this.LoadDown();
                  }
               }
            } else {
               if (LightingJNI.init) {
                  LightingJNI.teleport(this.PlayerID, var2 - ChunkGridWidth / 2, var3 - ChunkGridWidth / 2);
               }

               this.Unload();
    IsoPlayer var11 = IsoPlayer.players[this.PlayerID];
               var11.removeFromSquare();
               var11.square = nullptr;
               this.WorldX = var2;
               this.WorldY = var3;
               if (!GameServer.bServer) {
                  WorldSimulation.instance.activateChunkMap(this.PlayerID);
               }

    int var12 = this.WorldX - ChunkGridWidth / 2;
    int var13 = this.WorldY - ChunkGridWidth / 2;
    int var14 = this.WorldX + ChunkGridWidth / 2;
    int var15 = this.WorldY + ChunkGridWidth / 2;

               for (int var16 = var12; var16 <= var14; var16++) {
                  for (int var17 = var13; var17 <= var15; var17++) {
                     this.LoadChunkForLater(var16, var17, var16 - var12, var17 - var13);
                  }
               }

               this.SwapChunkBuffers();
               this.UpdateCellCache();
               if (!IsoWorld.instance.getCell().getObjectList().contains(var11)) {
                  IsoWorld.instance.getCell().getAddList().push_back(var11);
               }
            }
         } finally {
            bSettingChunk.unlock();
         }

         var24 = (System.nanoTime() - var9) / 1000000.0;
    double var26 = (System.nanoTime() - var23) / 1000000.0;
         if (LightingThread.DebugLockTime && var26 > 10.0) {
            DebugLog.log("ProcessChunkPos time " + var24 + "/" + var26 + " ms");
         }
      }
   }

    IsoRoom getRoom(int var1) {
    return nullptr;
   }

    int getWidthInTiles() {
    return ChunkWidthInTiles;
   }

    int getWorldXMinTiles() {
      if (this.XMinTiles != -1) {
         return this.XMinTiles;
      } else {
         this.XMinTiles = this.getWorldXMin() * 10;
         return this.XMinTiles;
      }
   }

    int getWorldYMinTiles() {
      if (this.YMinTiles != -1) {
         return this.YMinTiles;
      } else {
         this.YMinTiles = this.getWorldYMin() * 10;
         return this.YMinTiles;
      }
   }

    int getWorldXMaxTiles() {
      if (this.XMaxTiles != -1) {
         return this.XMaxTiles;
      } else {
         this.XMaxTiles = this.getWorldXMin() * 10 + this.getWidthInTiles();
         return this.XMaxTiles;
      }
   }

    int getWorldYMaxTiles() {
      if (this.YMaxTiles != -1) {
         return this.YMaxTiles;
      } else {
         this.YMaxTiles = this.getWorldYMin() * 10 + this.getWidthInTiles();
         return this.YMaxTiles;
      }
   }

    void Save() {
      if (!GameServer.bServer) {
         for (int var1 = 0; var1 < ChunkGridWidth; var1++) {
            for (int var2 = 0; var2 < ChunkGridWidth; var2++) {
    IsoChunk var3 = this.getChunk(var1, var2);
               if (var3 != nullptr && !saveList.contains(var3)) {
                  try {
                     var3.Save(true);
                  } catch (IOException var5) {
                     var5.printStackTrace();
                  }
               }
            }
         }
      }
   }

    void renderBloodForChunks(int var1) {
      if (DebugOptions.instance.Terrain.RenderTiles.BloodDecals.getValue()) {
         if (!(var1 > IsoCamera.CamCharacter.z)) {
            if (Core.OptionBloodDecals != 0) {
    float var2 = (float)GameTime.getInstance().getWorldAgeHours();
    int var3 = IsoCamera.frameState.playerIndex;

               for (int var4 = 0; var4 < IsoFloorBloodSplat.FloorBloodTypes.length; var4++) {
                  splatByType.get(var4).clear();
               }

               for (int var31 = 0; var31 < ChunkGridWidth; var31++) {
                  for (int var5 = 0; var5 < ChunkGridWidth; var5++) {
    IsoChunk var6 = this.getChunk(var31, var5);
                     if (var6 != nullptr) {
                        for (int var7 = 0; var7 < var6.FloorBloodSplatsFade.size(); var7++) {
    IsoFloorBloodSplat var8 = (IsoFloorBloodSplat)var6.FloorBloodSplatsFade.get(var7);
                           if ((var8.index < 1 || var8.index > 10 || IsoChunk.renderByIndex[Core.OptionBloodDecals - 1][var8.index - 1] != 0)
                              && (int)var8.z == var1
                              && var8.Type >= 0
                              && var8.Type < IsoFloorBloodSplat.FloorBloodTypes.length) {
                              var8.chunk = var6;
                              splatByType.get(var8.Type).push_back(var8);
                           }
                        }

                        if (!var6.FloorBloodSplats.empty()) {
                           for (int var35 = 0; var35 < var6.FloorBloodSplats.size(); var35++) {
    IsoFloorBloodSplat var38 = (IsoFloorBloodSplat)var6.FloorBloodSplats.get(var35);
                              if ((var38.index < 1 || var38.index > 10 || IsoChunk.renderByIndex[Core.OptionBloodDecals - 1][var38.index - 1] != 0)
                                 && (int)var38.z == var1
                                 && var38.Type >= 0
                                 && var38.Type < IsoFloorBloodSplat.FloorBloodTypes.length) {
                                 var38.chunk = var6;
                                 splatByType.get(var38.Type).push_back(var38);
                              }
                           }
                        }
                     }
                  }
               }

               for (int var32 = 0; var32 < splatByType.size(); var32++) {
    std::vector var33 = splatByType.get(var32);
                  if (!var33.empty()) {
    std::string var34 = IsoFloorBloodSplat.FloorBloodTypes[var32];
    IsoSprite var36 = nullptr;
                     if (!IsoFloorBloodSplat.SpriteMap.containsKey(var34)) {
    IsoSprite var39 = IsoSprite.CreateSprite(IsoSpriteManager.instance);
                        var39.LoadFramesPageSimple(var34, var34, var34, var34);
                        IsoFloorBloodSplat.SpriteMap.put(var34, var39);
                        var36 = var39;
                     } else {
                        var36 = (IsoSprite)IsoFloorBloodSplat.SpriteMap.get(var34);
                     }

                     for (int var40 = 0; var40 < var33.size(); var40++) {
    IsoFloorBloodSplat var9 = (IsoFloorBloodSplat)var33.get(var40);
                        inf.r = 1.0F;
                        inf.g = 1.0F;
                        inf.b = 1.0F;
                        inf.a = 0.27F;
    float var10 = (var9.x + var9.y / var9.x) * (var9.Type + 1);
    float var11 = var10 * var9.x / var9.y * (var9.Type + 1) / (var10 + var9.y);
    float var12 = var11 * var10 * var11 * var9.x / (var9.y + 2.0F);
                        var10 *= 42367.543F;
                        var11 *= 6367.123F;
                        var12 *= 23367.133F;
                        var10 %= 1000.0F;
                        var11 %= 1000.0F;
                        var12 %= 1000.0F;
                        var10 /= 1000.0F;
                        var11 /= 1000.0F;
                        var12 /= 1000.0F;
                        if (var10 > 0.25F) {
                           var10 = 0.25F;
                        }

                        inf.r -= var10 * 2.0F;
                        inf.g -= var10 * 2.0F;
                        inf.b -= var10 * 2.0F;
                        inf.r += var11 / 3.0F;
                        inf.g -= var12 / 3.0F;
                        inf.b -= var12 / 3.0F;
    float var13 = var2 - var9.worldAge;
                        if (var13 >= 0.0F && var13 < 72.0F) {
    float var14 = 1.0F - var13 / 72.0F;
                           inf.r *= 0.2F + var14 * 0.8F;
                           inf.g *= 0.2F + var14 * 0.8F;
                           inf.b *= 0.2F + var14 * 0.8F;
                           inf.a *= 0.25F + var14 * 0.75F;
                        } else {
                           inf.r *= 0.2F;
                           inf.g *= 0.2F;
                           inf.b *= 0.2F;
                           inf.a *= 0.25F;
                        }

                        if (var9.fade > 0) {
                           inf.a = inf.a * (var9.fade / (PerformanceSettings.getLockFPS() * 5.0F));
                           if (--var9.fade == 0) {
                              var9.chunk.FloorBloodSplatsFade.remove(var9);
                           }
                        }

    IsoGridSquare var50 = var9.chunk.getGridSquare((int)var9.x, (int)var9.y, (int)var9.z);
                        if (var50 != nullptr) {
    int var15 = var50.getVertLight(0, var3);
    int var16 = var50.getVertLight(1, var3);
    int var17 = var50.getVertLight(2, var3);
    int var18 = var50.getVertLight(3, var3);
    float var19 = Color.getRedChannelFromABGR(var15);
    float var20 = Color.getGreenChannelFromABGR(var15);
    float var21 = Color.getBlueChannelFromABGR(var15);
    float var22 = Color.getRedChannelFromABGR(var16);
    float var23 = Color.getGreenChannelFromABGR(var16);
    float var24 = Color.getBlueChannelFromABGR(var16);
    float var25 = Color.getRedChannelFromABGR(var17);
    float var26 = Color.getGreenChannelFromABGR(var17);
    float var27 = Color.getBlueChannelFromABGR(var17);
    float var28 = Color.getRedChannelFromABGR(var18);
    float var29 = Color.getGreenChannelFromABGR(var18);
    float var30 = Color.getBlueChannelFromABGR(var18);
                           inf.r *= (var19 + var22 + var25 + var28) / 4.0F;
                           inf.g *= (var20 + var23 + var26 + var29) / 4.0F;
                           inf.b *= (var21 + var24 + var27 + var30) / 4.0F;
                        }

                        var36.renderBloodSplat(var9.chunk.wx * 10 + var9.x, var9.chunk.wy * 10 + var9.y, var9.z, inf);
                     }
                  }
               }
            }
         }
      }
   }

    void copy(IsoChunkMap var1) {
    IsoChunkMap var2 = this;
      this.WorldX = var1.WorldX;
      this.WorldY = var1.WorldY;
      this.XMinTiles = -1;
      this.YMinTiles = -1;
      this.XMaxTiles = -1;
      this.YMaxTiles = -1;

      for (int var3 = 0; var3 < ChunkGridWidth * ChunkGridWidth; var3++) {
         var2.bReadBufferA = var1.bReadBufferA;
         if (var2.bReadBufferA) {
            if (var1.chunksSwapA[var3] != nullptr) {
               var1.chunksSwapA[var3].refs.push_back(var2);
               var2.chunksSwapA[var3] = var1.chunksSwapA[var3];
            }
         } else if (var1.chunksSwapB[var3] != nullptr) {
            var1.chunksSwapB[var3].refs.push_back(var2);
            var2.chunksSwapB[var3] = var1.chunksSwapB[var3];
         }
      }
   }

    void Unload() {
      for (int var1 = 0; var1 < ChunkGridWidth; var1++) {
         for (int var2 = 0; var2 < ChunkGridWidth; var2++) {
    IsoChunk var3 = this.getChunk(var2, var1);
            if (var3 != nullptr) {
               if (var3.refs.contains(this)) {
                  var3.refs.remove(this);
                  if (var3.refs.empty()) {
                     SharedChunks.remove((var3.wx << 16) + var3.wy);
                     var3.removeFromWorld();
                     ChunkSaveWorker.instance.Add(var3);
                  }
               }

               this.chunksSwapA[var1 * ChunkGridWidth + var2] = nullptr;
               this.chunksSwapB[var1 * ChunkGridWidth + var2] = nullptr;
            }
         }
      }

      WorldSimulation.instance.deactivateChunkMap(this.PlayerID);
      this.XMinTiles = -1;
      this.XMaxTiles = -1;
      this.YMinTiles = -1;
      this.YMaxTiles = -1;
      if (IsoWorld.instance != nullptr && IsoWorld.instance.CurrentCell != nullptr) {
         IsoWorld.instance.CurrentCell.clearCacheGridSquare(this.PlayerID);
      }
   }

   static {
      for (int var0 = 0; var0 < IsoFloorBloodSplat.FloorBloodTypes.length; var0++) {
         splatByType.push_back(std::make_unique<std::vector<>>());
      }
   }
}
} // namespace iso
} // namespace zombie
