#pragma once
#include "zombie/GameTime.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoChunkMap.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/WorldReuserThread.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ServerChunkLoader {
public:
  long debugSlowMapLoadingDelay = 0L;
  bool MapLoading = false;
private
  ServerChunkLoader.LoaderThread threadLoad;
private
  ServerChunkLoader.SaveChunkThread threadSave;
  const CRC32 crcSave = new CRC32();
private
  ServerChunkLoader.RecalcAllThread threadRecalc;

public
  ServerChunkLoader() {
    this.threadLoad = new ServerChunkLoader.LoaderThread();
    this.threadLoad.setName("LoadChunk");
    this.threadLoad.setDaemon(true);
    this.threadLoad.start();
    this.threadRecalc = new ServerChunkLoader.RecalcAllThread();
    this.threadRecalc.setName("RecalcAll");
    this.threadRecalc.setDaemon(true);
    this.threadRecalc.setPriority(10);
    this.threadRecalc.start();
    this.threadSave = new ServerChunkLoader.SaveChunkThread();
    this.threadSave.setName("SaveChunk");
    this.threadSave.setDaemon(true);
    this.threadSave.start();
  }

  void addJob(ServerMap.ServerCell serverCell) {
    this.MapLoading = DebugType.Do(DebugType.MapLoading);
    this.threadLoad.toThread.add(serverCell);
    MPStatistic.getInstance().LoaderThreadTasks.Added();
  }

  void getLoaded(ArrayList<ServerMap.ServerCell> arrayList) {
    this.threadLoad.fromThread.drainTo(arrayList);
  }

  void quit() {
    this.threadLoad.quit();

    while (this.threadLoad.isAlive()) {
      try {
        Thread.sleep(500L);
      } catch (InterruptedException interruptedException0) {
      }
    }

    this.threadSave.quit();

    while (this.threadSave.isAlive()) {
      try {
        Thread.sleep(500L);
      } catch (InterruptedException interruptedException1) {
      }
    }
  }

  void addSaveUnloadedJob(IsoChunk chunk) {
    this.threadSave.addUnloadedJob(chunk);
  }

  void addSaveLoadedJob(IsoChunk chunk) { this.threadSave.addLoadedJob(chunk); }

  void saveLater(GameTime gameTime) { this.threadSave.saveLater(gameTime); }

  void updateSaved() { this.threadSave.update(); }

  void addRecalcJob(ServerMap.ServerCell serverCell) {
    this.threadRecalc.toThread.add(serverCell);
    MPStatistic.getInstance().RecalcThreadTasks.Added();
  }

  void getRecalc(ArrayList<ServerMap.ServerCell> arrayList) {
    MPStatistic.getInstance().ServerMapLoaded2.Added(
        this.threadRecalc.fromThread.size());
    this.threadRecalc.fromThread.drainTo(arrayList);
    MPStatistic.getInstance().RecalcThreadTasks.Processed();
  }

private
  class GetSquare implements IsoGridSquare.GetSquare {
    ServerMap.ServerCell cell;

    IsoGridSquare getGridSquare(int int0, int int1, int int2) {
      int0 -= this.cell.WX * 50;
      int1 -= this.cell.WY * 50;
      if (int0 < 0 || int0 >= 50) {
        return null;
      } else if (int1 >= 0 && int1 < 50) {
        IsoChunk chunk = this.cell.chunks[int0 / 10][int1 / 10];
        return chunk = = null ? null
                              : chunk.getGridSquare(int0 % 10, int1 % 10, int2);
      } else {
        return null;
      }
    }

    bool contains(int int1, int int0, int var3) {
      return int1 < 0 || int1 >= 50 ? false : int0 >= 0 && int0 < 50;
    }

    IsoChunk getChunkForSquare(int int0, int int1) {
      int0 -= this.cell.WX * 50;
      int1 -= this.cell.WY * 50;
      if (int0 < 0 || int0 >= 50) {
        return null;
      } else {
        return int1 >= 0 && int1 < 50 ? this.cell.chunks[int0 / 10][int1 / 10]
                                      : nullptr;
      }
    }

    void EnsureSurroundNotNull(int int6, int int5, int int4) {
      int int0 = this.cell.WX * 50;
      int int1 = this.cell.WY * 50;

      for (int int2 = -1; int2 <= 1; int2++) {
        for (int int3 = -1; int3 <= 1; int3++) {
          if ((int2 != 0 || int3 != 0) &&
              this.contains(int6 + int2, int5 + int3, int4)) {
            IsoGridSquare square = this.getGridSquare(int0 + int6 + int2,
                                                      int1 + int5 + int3, int4);
            if (square == nullptr) {
              square = IsoGridSquare.getNew(IsoWorld.instance.CurrentCell,
                                            nullptr, int0 + int6 + int2,
                                            int1 + int5 + int3, int4);
              int int7 = (int6 + int2) / 10;
              int int8 = (int5 + int3) / 10;
              int int9 = (int6 + int2) % 10;
              int int10 = (int5 + int3) % 10;
              if (this.cell.chunks[int7][int8] != nullptr) {
                this.cell.chunks[int7][int8].setSquare(int9, int10, int4,
                                                       square);
              }
            }
          }
        }
      }
    }
  }

private
  class LoaderThread extends Thread {
  private
    final LinkedBlockingQueue<ServerMap.ServerCell> toThread =
        std::make_unique<LinkedBlockingQueue<>>();
  private
    final LinkedBlockingQueue<ServerMap.ServerCell> fromThread =
        std::make_unique<LinkedBlockingQueue<>>();
    ArrayDeque<IsoGridSquare> isoGridSquareCache =
        std::make_unique<ArrayDeque<>>();

    void run() {
      while (true) {
        try {
          MPStatistic.getInstance().LoaderThread.End();
          ServerMap.ServerCell serverCell = this.toThread.take();
          MPStatistic.getInstance().LoaderThread.Start();
          if (this.isoGridSquareCache.size() < 10000) {
            IsoGridSquare.getSquaresForThread(this.isoGridSquareCache, 10000);
            IsoGridSquare.loadGridSquareCache = this.isoGridSquareCache;
          }

          if (serverCell.WX == -1 && serverCell.WY == -1) {
            return;
          }

          if (serverCell.bCancelLoading) {
            if (ServerChunkLoader.this.MapLoading) {
              DebugLog.log(DebugType.MapLoading, "LoaderThread: cancelled " +
                                                     serverCell.WX + "," +
                                                     serverCell.WY);
            }

            serverCell.bLoadingWasCancelled = true;
          } else {
            long long0 = System.nanoTime();

            for (int int0 = 0; int0 < 5; int0++) {
              for (int int1 = 0; int1 < 5; int1++) {
                int int2 = serverCell.WX * 5 + int0;
                int int3 = serverCell.WY * 5 + int1;
                if (IsoWorld.instance.MetaGrid.isValidChunk(int2, int3)) {
                  IsoChunk chunk = IsoChunkMap.chunkStore.poll();
                  if (chunk == nullptr) {
                    chunk = new IsoChunk(nullptr);
                  } else {
                    MPStatistics.decreaseStoredChunk();
                  }

                  ServerChunkLoader.this.threadSave.saveNow(int2, int3);

                  try {
                    if (chunk.LoadOrCreate(int2, int3, nullptr)) {
                      chunk.bLoaded = true;
                    } else {
                      ChunkChecksum.setChecksum(int2, int3, 0L);
                      chunk.Blam(int2, int3);
                      if (chunk.LoadBrandNew(int2, int3)) {
                        chunk.bLoaded = true;
                      }
                    }
                  } catch (Exception exception0) {
                    exception0.printStackTrace();
                    LoggerManager.getLogger("map").write(exception0);
                  }

                  if (chunk.bLoaded) {
                    serverCell.chunks[int0][int1] = chunk;
                  }
                }
              }
            }

            if (GameServer.bDebug &&
                ServerChunkLoader.this.debugSlowMapLoadingDelay > 0L) {
              Thread.sleep(ServerChunkLoader.this.debugSlowMapLoadingDelay);
            }

            float float0 = (float)(System.nanoTime() - long0) / 1000000.0F;
            MPStatistic.getInstance().IncrementLoadCellFromDisk();
            this.fromThread.add(serverCell);
            MPStatistic.getInstance().LoaderThreadTasks.Processed();
          }
        } catch (Exception exception1) {
          exception1.printStackTrace();
          LoggerManager.getLogger("map").write(exception1);
        }
      }
    }

    void quit() {
      ServerMap.ServerCell serverCell = new ServerMap.ServerCell();
      serverCell.WX = -1;
      serverCell.WY = -1;
      this.toThread.add(serverCell);
      MPStatistic.getInstance().LoaderThreadTasks.Added();
    }
  }

  private class QuitThreadTask implements ServerChunkLoader.SaveTask {
    void save() { ServerChunkLoader.this.threadSave.quit = true; }

    void release() {}

    int wx() { return 0; }

    int wy() { return 0; }
  }

private
  class RecalcAllThread extends Thread {
  private
    final LinkedBlockingQueue<ServerMap.ServerCell> toThread =
        std::make_unique<LinkedBlockingQueue<>>();
  private
    final LinkedBlockingQueue<ServerMap.ServerCell> fromThread =
        std::make_unique<LinkedBlockingQueue<>>();
  private
    final ServerChunkLoader.GetSquare serverCellGetSquare =
        ServerChunkLoader.this.std::make_unique<GetSquare>();

    void run() {
      while (true) {
        try {
          this.runInner();
        } catch (Exception exception) {
          exception.printStackTrace();
        }
      }
    }

    void runInner() {
      MPStatistic.getInstance().RecalcAllThread.End();
      ServerMap.ServerCell serverCell = this.toThread.take();
      MPStatistic.getInstance().RecalcAllThread.Start();
      if (serverCell.bCancelLoading && !this.hasAnyBrandNewChunks(serverCell)) {
        for (int int0 = 0; int0 < 5; int0++) {
          for (int int1 = 0; int1 < 5; int1++) {
            IsoChunk chunk0 = serverCell.chunks[int1][int0];
            if (chunk0 != nullptr) {
              serverCell.chunks[int1][int0] = nullptr;
              WorldReuserThread.instance.addReuseChunk(chunk0);
            }
          }
        }

        if (ServerChunkLoader.this.MapLoading) {
          DebugLog.log(DebugType.MapLoading, "RecalcAllThread: cancelled " +
                                                 serverCell.WX + "," +
                                                 serverCell.WY);
        }

        serverCell.bLoadingWasCancelled = true;
      } else {
        long long0 = System.nanoTime();
        this.serverCellGetSquare.cell = serverCell;
        int int2 = serverCell.WX * 50;
        int int3 = serverCell.WY * 50;
        int int4 = int2 + 50;
        int int5 = int3 + 50;
        int int6 = 0;
        uint8_t byte0 = 100;

        for (int int7 = 0; int7 < 5; int7++) {
          for (int int8 = 0; int8 < 5; int8++) {
            IsoChunk chunk1 = serverCell.chunks[int7][int8];
            if (chunk1 != nullptr) {
              chunk1.bLoaded = false;

              for (int int9 = 0; int9 < byte0; int9++) {
                for (int int10 = 0; int10 <= chunk1.maxLevel; int10++) {
                  IsoGridSquare square0 = chunk1.squares[int10][int9];
                  if (int10 == 0) {
                    if (square0 == nullptr) {
                      int int11 = chunk1.wx * 10 + int9 % 10;
                      int int12 = chunk1.wy * 10 + int9 / 10;
                      square0 =
                          IsoGridSquare.getNew(IsoWorld.instance.CurrentCell,
                                               nullptr, int11, int12, int10);
                      chunk1.setSquare(int11 % 10, int12 % 10, int10, square0);
                    }

                    if (square0.getFloor() == nullptr) {
                      DebugLog.log("ERROR: added floor at " + square0.x + "," +
                                   square0.y + "," + square0.z +
                                   " because there wasn't one");
                      IsoObject object = IsoObject.getNew();
                      object.sprite = IsoSprite.getSprite(
                          IsoSpriteManager.instance, "carpentry_02_58", 0);
                      object.square = square0;
                      square0.getObjects().add(0, object);
                    }
                  }

                  if (square0 != nullptr) {
                    square0.RecalcProperties();
                  }
                }
              }

              if (chunk1.maxLevel > int6) {
                int6 = chunk1.maxLevel;
              }
            }
          }
        }

        for (int int13 = 0; int13 < 5; int13++) {
          for (int int14 = 0; int14 < 5; int14++) {
            IsoChunk chunk2 = serverCell.chunks[int13][int14];
            if (chunk2 != nullptr) {
              for (int int15 = 0; int15 < byte0; int15++) {
                for (int int16 = 0; int16 <= chunk2.maxLevel; int16++) {
                  IsoGridSquare square1 = chunk2.squares[int16][int15];
                  if (square1 != nullptr) {
                    if (int16 > 0 && !square1.getObjects().isEmpty()) {
                      this.serverCellGetSquare.EnsureSurroundNotNull(
                          square1.x - int2, square1.y - int3, int16);
                    }

                    square1.RecalcAllWithNeighbours(true,
                                                    this.serverCellGetSquare);
                  }
                }
              }
            }
          }
        }

        for (int int17 = 0; int17 < 5; int17++) {
          for (int int18 = 0; int18 < 5; int18++) {
            IsoChunk chunk3 = serverCell.chunks[int17][int18];
            if (chunk3 != nullptr) {
              for (int int19 = 0; int19 < byte0; int19++) {
                for (int int20 = chunk3.maxLevel; int20 > 0; int20--) {
                  IsoGridSquare square2 = chunk3.squares[int20][int19];
                  if (square2 != nullptr &&
                      square2.Is(IsoFlagType.solidfloor)) {
                    int20--;

                    for (; int20 >= 0; int20--) {
                      square2 = chunk3.squares[int20][int19];
                      if (square2 != nullptr) {
                        square2.haveRoof = true;
                        square2.getProperties().UnSet(IsoFlagType.exterior);
                      }
                    }
                    break;
                  }
                }
              }
            }
          }
        }

        if (GameServer.bDebug &&
            ServerChunkLoader.this.debugSlowMapLoadingDelay > 0L) {
          Thread.sleep(ServerChunkLoader.this.debugSlowMapLoadingDelay);
        }

        float float0 = (float)(System.nanoTime() - long0) / 1000000.0F;
        if (ServerChunkLoader.this.MapLoading) {
          DebugLog.log(DebugType.MapLoading,
                       "RecalcAll for cell " + serverCell.WX + "," +
                           serverCell.WY + " ms=" + float0);
        }

        this.fromThread.add(serverCell);
      }
    }

    bool hasAnyBrandNewChunks(ServerMap.ServerCell serverCell) {
      for (int int0 = 0; int0 < 5; int0++) {
        for (int int1 = 0; int1 < 5; int1++) {
          IsoChunk chunk = serverCell.chunks[int1][int0];
          if (chunk != nullptr && !chunk.getErosionData().init) {
            return true;
          }
        }
      }

      return false;
    }
  }

  private class SaveChunkThread extends Thread {
  private
    final LinkedBlockingQueue<ServerChunkLoader.SaveTask> toThread =
        std::make_unique<LinkedBlockingQueue<>>();
  private
    final LinkedBlockingQueue<ServerChunkLoader.SaveTask> fromThread =
        std::make_unique<LinkedBlockingQueue<>>();
    bool quit = false;
    const CRC32 crc32 = new CRC32();
    const ClientChunkRequest ccr = new ClientChunkRequest();
  private
    final ArrayList<ServerChunkLoader.SaveTask> toSaveChunk =
        std::make_unique<ArrayList<>>();
  private
    final ArrayList<ServerChunkLoader.SaveTask> savedChunks =
        std::make_unique<ArrayList<>>();

    void run() {
      do {
        ServerChunkLoader.SaveTask saveTask = nullptr;

        try {
          MPStatistic.getInstance().SaveThread.End();
          saveTask = this.toThread.take();
          MPStatistic.getInstance().SaveThread.Start();
          MPStatistic.getInstance().IncrementSaveCellToDisk();
          saveTask.save();
          this.fromThread.add(saveTask);
          MPStatistic.getInstance().SaveTasks.Processed();
        } catch (InterruptedException interruptedException) {
        } catch (Exception exception) {
          exception.printStackTrace();
          if (saveTask != nullptr) {
            LoggerManager.getLogger("map").write(
                "Error saving chunk " + saveTask.wx() + "," + saveTask.wy());
          }

          LoggerManager.getLogger("map").write(exception);
        }
      } while (!this.quit || !this.toThread.isEmpty());
    }

    void addUnloadedJob(IsoChunk chunk) {
      this.toThread.add(ServerChunkLoader.this.new SaveUnloadedTask(chunk));
      MPStatistic.getInstance().SaveTasks.SaveUnloadedTasksAdded();
    }

    void addLoadedJob(IsoChunk chunk1) {
      ClientChunkRequest.Chunk chunk0 = this.ccr.getChunk();
      chunk0.wx = chunk1.wx;
      chunk0.wy = chunk1.wy;
      this.ccr.getByteBuffer(chunk0);

      try {
        chunk1.SaveLoadedChunk(chunk0, this.crc32);
      } catch (Exception exception) {
        exception.printStackTrace();
        LoggerManager.getLogger("map").write(exception);
        this.ccr.releaseChunk(chunk0);
        return;
      }

      this.toThread.add(
          ServerChunkLoader.this.new SaveLoadedTask(this.ccr, chunk0));
      MPStatistic.getInstance().SaveTasks.SaveLoadedTasksAdded();
    }

    void saveLater(GameTime gameTime) {
      this.toThread.add(ServerChunkLoader.this.new SaveGameTimeTask(gameTime));
      MPStatistic.getInstance().SaveTasks.SaveGameTimeTasksAdded();
    }

    void saveNow(int int2, int int1) {
      this.toSaveChunk.clear();
      this.toThread.drainTo(this.toSaveChunk);

      for (int int0 = 0; int0 < this.toSaveChunk.size(); int0++) {
        ServerChunkLoader.SaveTask saveTask = this.toSaveChunk.get(int0);
        if (saveTask.wx() == int2 && saveTask.wy() == int1) {
          try {
            this.toSaveChunk.remove(int0--);
            saveTask.save();
            MPStatistic.getInstance().IncrementServerChunkThreadSaveNow();
          } catch (Exception exception) {
            exception.printStackTrace();
            LoggerManager.getLogger("map").write("Error saving chunk " + int2 +
                                                 "," + int1);
            LoggerManager.getLogger("map").write(exception);
          }

          MPStatistic.getInstance().SaveTasks.Processed();
          this.fromThread.add(saveTask);
        }
      }

      this.toThread.addAll(this.toSaveChunk);
    }

    void quit() {
      this.toThread.add(
          ServerChunkLoader.this.std::make_unique<QuitThreadTask>());
      MPStatistic.getInstance().SaveTasks.QuitThreadTasksAdded();
    }

    void update() {
      this.savedChunks.clear();
      this.fromThread.drainTo(this.savedChunks);

      for (int int0 = 0; int0 < this.savedChunks.size(); int0++) {
        this.savedChunks.get(int0).release();
      }

      this.savedChunks.clear();
    }
  }

  private class SaveGameTimeTask implements ServerChunkLoader.SaveTask {
  private
    byte[] bytes;

  public
    SaveGameTimeTask(GameTime gameTime) {
      try {
        try(ByteArrayOutputStream byteArrayOutputStream =
                new ByteArrayOutputStream(32768);
            DataOutputStream dataOutputStream =
                new DataOutputStream(byteArrayOutputStream);) {
          gameTime.save(dataOutputStream);
          dataOutputStream.close();
          this.bytes = byteArrayOutputStream.toByteArray();
        }
      } catch (Exception exception) {
        exception.printStackTrace();
      }
    }

    void save() {
      if (this.bytes != nullptr) {
        File file =
            ZomboidFileSystem.instance.getFileInCurrentSave("map_t.bin");

        try(FileOutputStream fileOutputStream = new FileOutputStream(file)) {
          fileOutputStream.write(this.bytes);
        }
        catch (Exception exception) {
          exception.printStackTrace();
          return;
        }
      }
    }

    void release() {}

    int wx() { return 0; }

    int wy() { return 0; }
  }

private
  class SaveLoadedTask implements ServerChunkLoader.SaveTask {
    const ClientChunkRequest ccr;
  private
    final ClientChunkRequest.Chunk chunk;

  public
    SaveLoadedTask(ClientChunkRequest clientChunkRequest,
                   ClientChunkRequest.Chunk chunkx) {
      this.ccr = clientChunkRequest;
      this.chunk = chunkx;
    }

    void save() {
      long long0 =
          ChunkChecksum.getChecksumIfExists(this.chunk.wx, this.chunk.wy);
      ServerChunkLoader.this.crcSave.reset();
      ServerChunkLoader.this.crcSave.update(this.chunk.bb.array(), 0,
                                            this.chunk.bb.position());
      if (long0 != ServerChunkLoader.this.crcSave.getValue()) {
        ChunkChecksum.setChecksum(this.chunk.wx, this.chunk.wy,
                                  ServerChunkLoader.this.crcSave.getValue());
        IsoChunk.SafeWrite("map_", this.chunk.wx, this.chunk.wy, this.chunk.bb);
      }
    }

    void release() { this.ccr.releaseChunk(this.chunk); }

    int wx() { return this.chunk.wx; }

    int wy() { return this.chunk.wy; }
  }

private
  interface SaveTask {
    void save();

    void release();

    int wx();

    int wy();
  }

private
  class SaveUnloadedTask implements ServerChunkLoader.SaveTask {
    const IsoChunk chunk;

  public
    SaveUnloadedTask(IsoChunk chunkx) { this.chunk = chunkx; }

    void save() { this.chunk.Save(false); }

    void release() { WorldReuserThread.instance.addReuseChunk(this.chunk); }

    int wx() { return this.chunk.wx; }

    int wy() { return this.chunk.wy; }
  }
}
} // namespace network
} // namespace zombie
