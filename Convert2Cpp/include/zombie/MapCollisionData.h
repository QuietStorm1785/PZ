#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/MapCollisionData/MCDThread.h"
#include "zombie/MapCollisionData/PathTask.h"
#include "zombie/MapCollisionData/Sync.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/gameStates/IngameState.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoLot.h"
#include "zombie/iso/IsoMetaCell.h"
#include "zombie/iso/IsoMetaChunk.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/popman/ZombiePopulationManager.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {


class MapCollisionData {
public:
    static const MapCollisionData instance = new MapCollisionData();
    static const uint8_t BIT_SOLID = 1;
    static const uint8_t BIT_WALLN = 2;
    static const uint8_t BIT_WALLW = 4;
    static const uint8_t BIT_WATER = 8;
    static const uint8_t BIT_ROOM = 16;
    static const int SQUARES_PER_CHUNK = 10;
    static const int CHUNKS_PER_CELL = 30;
    static const int SQUARES_PER_CELL = 300;
   private static int[] curXY = new int[2];
    const void* renderLock = new Object();
   private final Stack<PathTask> freePathTasks = std::make_unique<Stack<>>();
   private final ConcurrentLinkedQueue<PathTask> pathTaskQueue = std::make_unique<ConcurrentLinkedQueue<>>();
   private final ConcurrentLinkedQueue<PathTask> pathResultQueue = std::make_unique<ConcurrentLinkedQueue<>>();
    const Sync sync = new Sync();
   private final byte[] squares = new byte[100];
    const int SQUARE_UPDATE_SIZE = 9;
    const ByteBuffer squareUpdateBuffer = ByteBuffer.allocateDirect(1024);
    bool bClient;
    bool bPaused;
    bool bNoSave;
    MCDThread thread;
    long lastUpdate;

   private static native void n_init(int var0, int var1, int var2, int var3);

   private static native void n_chunkUpdateTask(int var0, int var1, byte[] var2);

   private static native void n_squareUpdateTask(int var0, ByteBuffer var1);

   private static native int n_pathTask(int var0, int var1, int var2, int var3, int[] var4);

   private static native boolean n_hasDataForThread();

   private static native boolean n_shouldWait();

   private static native void n_update();

   private static native void n_save();

   private static native void n_stop();

   private static native void n_setGameState(String var0, boolean var1);

   private static native void n_setGameState(String var0, double var1);

   private static native void n_setGameState(String var0, float var1);

   private static native void n_setGameState(String var0, int var1);

   private static native void n_setGameState(String var0, String var1);

   private static native void n_initMetaGrid(int var0, int var1, int var2, int var3);

   private static native void n_initMetaCell(int var0, int var1, String var2);

   private static native void n_initMetaChunk(int var0, int var1, int var2, int var3, int var4);

    static void writeToStdErr(const std::string& var0) {
      System.err.println(var0);
   }

    void init(IsoMetaGrid var1) {
      this.bClient = GameClient.bClient;
      if (!this.bClient) {
    int var2 = var1.getMinX();
    int var3 = var1.getMinY();
    int var4 = var1.getWidth();
    int var5 = var1.getHeight();
         n_setGameState("Core.GameMode", Core.getInstance().getGameMode());
         n_setGameState("Core.GameSaveWorld", Core.GameSaveWorld);
         n_setGameState("Core.bLastStand", Core.bLastStand);
         n_setGameState("Core.noSave", this.bNoSave = Core.getInstance().isNoSave());
         n_setGameState("GameWindow.CacheDir", ZomboidFileSystem.instance.getCacheDir());
         n_setGameState("GameWindow.GameModeCacheDir", ZomboidFileSystem.instance.getGameModeCacheDir() + File.separator);
         n_setGameState("GameWindow.SaveDir", ZomboidFileSystem.instance.getSaveDir());
         n_setGameState("SandboxOptions.Distribution", SandboxOptions.instance.Distribution.getValue());
         n_setGameState("SandboxOptions.Zombies", SandboxOptions.instance.Zombies.getValue());
         n_setGameState("World.ZombiesDisabled", IsoWorld.getZombiesDisabled());
         n_setGameState("PAUSED", this.bPaused = true);
         n_initMetaGrid(var2, var3, var4, var5);

         for (int var6 = var3; var6 < var3 + var5; var6++) {
            for (int var7 = var2; var7 < var2 + var4; var7++) {
    IsoMetaCell var8 = var1.getCellData(var7, var6);
               n_initMetaCell(var7, var6, (String)IsoLot.InfoFileNames.get("chunkdata_" + var7 + "_" + var6 + ".bin"));
               if (var8 != nullptr) {
                  for (int var9 = 0; var9 < 30; var9++) {
                     for (int var10 = 0; var10 < 30; var10++) {
    IsoMetaChunk var11 = var8.getChunk(var10, var9);
                        if (var11 != nullptr) {
                           n_initMetaChunk(var7, var6, var10, var9, var11.getUnadjustedZombieIntensity());
                        }
                     }
                  }
               }
            }
         }

         n_init(var2, var3, var4, var5);
      }
   }

    void start() {
      if (!this.bClient) {
         if (this.thread == nullptr) {
            this.thread = new MCDThread(this);
            this.thread.setDaemon(true);
            this.thread.setName("MapCollisionDataJNI");
            if (GameServer.bServer) {
               this.thread.start();
            }
         }
      }
   }

    void startGame() {
      if (!GameClient.bClient) {
         this.updateMain();
         ZombiePopulationManager.instance.updateMain();
         n_update();
         ZombiePopulationManager.instance.updateThread();
         this.updateMain();
         ZombiePopulationManager.instance.updateMain();
         this.thread.start();
      }
   }

    void updateMain() {
      if (!this.bClient) {
         for (PathTask var1 = this.pathResultQueue.poll(); var1 != nullptr; var1 = this.pathResultQueue.poll()) {
            var1.result.finished(var1.status, var1.curX, var1.curY);
            var1.release();
         }

    long var3 = System.currentTimeMillis();
         if (var3 - this.lastUpdate > 10000L) {
            this.lastUpdate = var3;
            this.notifyThread();
         }
      }
   }

    bool hasDataForThread() {
      if (this.squareUpdateBuffer.position() > 0) {
         try {
            n_squareUpdateTask(this.squareUpdateBuffer.position() / 9, this.squareUpdateBuffer);
         } finally {
            this.squareUpdateBuffer.clear();
         }
      }

    return n_hasDataForThread();
   }

    void updateGameState() {
    bool var1 = Core.getInstance().isNoSave();
      if (this.bNoSave != var1) {
         this.bNoSave = var1;
         n_setGameState("Core.noSave", this.bNoSave);
      }

    bool var2 = GameTime.isGamePaused();
      if (GameWindow.states.current != IngameState.instance) {
         var2 = true;
      }

      if (GameServer.bServer) {
         var2 = IngameState.instance.Paused;
      }

      if (var2 != this.bPaused) {
         this.bPaused = var2;
         n_setGameState("PAUSED", this.bPaused);
      }
   }

    void notifyThread() {
      synchronized (this.thread.notifier) {
         this.thread.notifier.notify();
      }
   }

    void addChunkToWorld(IsoChunk var1) {
      if (!this.bClient) {
         for (int var2 = 0; var2 < 10; var2++) {
            for (int var3 = 0; var3 < 10; var3++) {
    IsoGridSquare var4 = var1.getGridSquare(var3, var2, 0);
               if (var4 == nullptr) {
                  this.squares[var3 + var2 * 10] = 1;
               } else {
    uint8_t var5 = 0;
                  if (this.isSolid(var4)) {
                     var5 = (byte)(var5 | 1);
                  }

                  if (this.isBlockedN(var4)) {
                     var5 = (byte)(var5 | 2);
                  }

                  if (this.isBlockedW(var4)) {
                     var5 = (byte)(var5 | 4);
                  }

                  if (this.isWater(var4)) {
                     var5 = (byte)(var5 | 8);
                  }

                  if (this.isRoom(var4)) {
                     var5 = (byte)(var5 | 16);
                  }

                  this.squares[var3 + var2 * 10] = var5;
               }
            }
         }

         n_chunkUpdateTask(var1.wx, var1.wy, this.squares);
      }
   }

    void removeChunkFromWorld(IsoChunk var1) {
      if (!this.bClient) {
         ;
      }
   }

    void squareChanged(IsoGridSquare var1) {
      if (!this.bClient) {
         try {
    uint8_t var2 = 0;
            if (this.isSolid(var1)) {
               var2 = (byte)(var2 | 1);
            }

            if (this.isBlockedN(var1)) {
               var2 = (byte)(var2 | 2);
            }

            if (this.isBlockedW(var1)) {
               var2 = (byte)(var2 | 4);
            }

            if (this.isWater(var1)) {
               var2 = (byte)(var2 | 8);
            }

            if (this.isRoom(var1)) {
               var2 = (byte)(var2 | 16);
            }

            this.squareUpdateBuffer.putInt(var1.x);
            this.squareUpdateBuffer.putInt(var1.y);
            this.squareUpdateBuffer.put(var2);
            if (this.squareUpdateBuffer.remaining() < 9) {
               n_squareUpdateTask(this.squareUpdateBuffer.position() / 9, this.squareUpdateBuffer);
               this.squareUpdateBuffer.clear();
            }
         } catch (Exception var3) {
            ExceptionLogger.logException(var3);
         }
      }
   }

    void save() {
      if (!this.bClient) {
         ZombiePopulationManager.instance.beginSaveRealZombies();
         if (!this.thread.isAlive()) {
            n_save();
            ZombiePopulationManager.instance.save();
         } else {
            this.thread.bSave = true;
            synchronized (this.thread.notifier) {
               this.thread.notifier.notify();
            }

            while (this.thread.bSave) {
               try {
                  Thread.sleep(5L);
               } catch (InterruptedException var3) {
               }
            }

            ZombiePopulationManager.instance.endSaveRealZombies();
         }
      }
   }

    void stop() {
      if (!this.bClient) {
         this.thread.bStop = true;
         synchronized (this.thread.notifier) {
            this.thread.notifier.notify();
         }

         while (this.thread.isAlive()) {
            try {
               Thread.sleep(5L);
            } catch (InterruptedException var3) {
            }
         }

         n_stop();
         this.thread = nullptr;
         this.pathTaskQueue.clear();
         this.pathResultQueue.clear();
         this.squareUpdateBuffer.clear();
      }
   }

    bool isSolid(IsoGridSquare var1) {
    bool var2 = var1.isSolid() || var1.isSolidTrans();
      if (var1.HasStairs()) {
         var2 = true;
      }

      if (var1.Is(IsoFlagType.water)) {
         var2 = false;
      }

      if (var1.Has(IsoObjectType.tree)) {
         var2 = false;
      }

    return var2;
   }

    bool isBlockedN(IsoGridSquare var1) {
      if (var1.Is(IsoFlagType.HoppableN)) {
    return false;
      } else {
    bool var2 = var1.Is(IsoFlagType.collideN);
         if (var1.Has(IsoObjectType.doorFrN)) {
            var2 = true;
         }

         if (var1.getProperties().Is(IsoFlagType.DoorWallN)) {
            var2 = true;
         }

         if (var1.Has(IsoObjectType.windowFN)) {
            var2 = true;
         }

         if (var1.Is(IsoFlagType.windowN)) {
            var2 = true;
         }

         if (var1.getProperties().Is(IsoFlagType.WindowN)) {
            var2 = true;
         }

    return var2;
      }
   }

    bool isBlockedW(IsoGridSquare var1) {
      if (var1.Is(IsoFlagType.HoppableW)) {
    return false;
      } else {
    bool var2 = var1.Is(IsoFlagType.collideW);
         if (var1.Has(IsoObjectType.doorFrW)) {
            var2 = true;
         }

         if (var1.getProperties().Is(IsoFlagType.DoorWallW)) {
            var2 = true;
         }

         if (var1.Has(IsoObjectType.windowFW)) {
            var2 = true;
         }

         if (var1.Is(IsoFlagType.windowW)) {
            var2 = true;
         }

         if (var1.getProperties().Is(IsoFlagType.WindowW)) {
            var2 = true;
         }

    return var2;
      }
   }

    bool isWater(IsoGridSquare var1) {
      return var1.Is(IsoFlagType.water);
   }

    bool isRoom(IsoGridSquare var1) {
      return var1.getRoom() != nullptr;
   }
}
} // namespace zombie
