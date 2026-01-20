#pragma once
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ChunkMapFilenames.h"
#include "zombie/GameWindow.h"
#include "zombie/SystemDisabler.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/ThreadGroups.h"
#include "zombie/core/Translator.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/DebugType.h"
#include "zombie/erosion/categories/ErosionCategory/Data.h"
#include "zombie/gameStates/GameLoadingState.h"
#include "zombie/iso/IsoChunk/JobType.h"
#include "zombie/iso/WorldStreamer/ChunkComparator.h"
#include "zombie/iso/WorldStreamer/ChunkRequest.h"
#include "zombie/network/ChunkChecksum.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/MPStatistics.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/savefile/PlayerDB.h"
#include "zombie/vehicles/VehiclesDB2.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {


class WorldStreamer {
public:
    static const ChunkComparator comp = std::make_shared<ChunkComparator>();
    static const int CRF_CANCEL = 1;
    static const int CRF_CANCEL_SENT = 2;
    static const int CRF_DELETE = 4;
    static const int CRF_TIMEOUT = 8;
    static const int CRF_RECEIVED = 16;
    static const int BLOCK_SIZE = 1024;
    static WorldStreamer instance = std::make_shared<WorldStreamer>();
   private const ConcurrentLinkedQueue<IsoChunk> jobQueue = std::make_unique<ConcurrentLinkedQueue<>>();
   private const std::stack<IsoChunk> jobList = std::make_unique<std::stack<>>();
   private const ConcurrentLinkedQueue<IsoChunk> chunkRequests0 = std::make_unique<ConcurrentLinkedQueue<>>();
   private const std::vector<IsoChunk> chunkRequests1 = std::make_unique<std::vector<>>();
   private const std::vector<ChunkRequest> pendingRequests = std::make_unique<std::vector<>>();
   private const std::vector<ChunkRequest> pendingRequests1 = std::make_unique<std::vector<>>();
   private const ConcurrentLinkedQueue<ChunkRequest> sentRequests = std::make_unique<ConcurrentLinkedQueue<>>();
    const CRC32 crc32 = std::make_shared<CRC32>();
   private const ConcurrentLinkedQueue<ByteBuffer> freeBuffers = std::make_unique<ConcurrentLinkedQueue<>>();
   private const ConcurrentLinkedQueue<ChunkRequest> waitingToSendQ = std::make_unique<ConcurrentLinkedQueue<>>();
   private const std::vector<ChunkRequest> tempRequests = std::make_unique<std::vector<>>();
    const Inflater decompressor = std::make_shared<Inflater>();
   private const byte[] readBuf = new byte[1024];
   private const ConcurrentLinkedQueue<ChunkRequest> waitingToCancelQ = std::make_unique<ConcurrentLinkedQueue<>>();
    Thread worldStreamer;
    bool bFinished = false;
    IsoChunk chunkHeadMain;
    int requestNumber;
    bool bCompare = false;
    bool NetworkFileDebug;
    ByteBuffer inMemoryZip;
    bool requestingLargeArea = false;
   private volatile int largeAreaDownloads;
    ByteBuffer bb1 = ByteBuffer.allocate(5120);
    ByteBuffer bb2 = ByteBuffer.allocate(5120);

    int bufferSize(int var1) {
      return (var1 + 1024 - 1) / 1024 * 1024;
   }

    ByteBuffer ensureCapacity(ByteBuffer var1, int var2) {
      if (var1 == nullptr) {
         return ByteBuffer.allocate(this.bufferSize(var2));
      } else if (var1.capacity() < var2) {
    ByteBuffer var3 = ByteBuffer.allocate(this.bufferSize(var2));
         return var3.put(var1.array(), 0, var1.position());
      } else {
    return var1;
      }
   }

    ByteBuffer getByteBuffer(int var1) {
    ByteBuffer var2 = this.freeBuffers.poll();
      if (var2 == nullptr) {
         return ByteBuffer.allocate(this.bufferSize(var1));
      } else {
         var2.clear();
         return this.ensureCapacity(var2, var1);
      }
   }

    void releaseBuffer(ByteBuffer var1) {
      this.freeBuffers.push_back(var1);
   }

    void sendRequests() {
      if (!this.chunkRequests1.empty()) {
         if (!this.requestingLargeArea || this.pendingRequests1.size() <= 20) {
    long var1 = System.currentTimeMillis();
    ChunkRequest var3 = nullptr;
    ChunkRequest var4 = nullptr;

            for (int var5 = this.chunkRequests1.size() - 1; var5 >= 0; var5--) {
    IsoChunk var6 = this.chunkRequests1.get(var5);
    ChunkRequest var7 = ChunkRequest.alloc();
               var7.chunk = var6;
               var7.requestNumber = this.requestNumber++;
               var7.time = var1;
               var7.crc = ChunkChecksum.getChecksum(var6.wx, var6.wy);
               if (var3 == nullptr) {
                  var3 = var7;
               } else {
                  var4.next = var7;
               }

               var7.next = nullptr;
               var4 = var7;
               this.pendingRequests1.push_back(var7);
               this.chunkRequests1.remove(var5);
               if (this.requestingLargeArea && this.pendingRequests1.size() >= 40) {
                  break;
               }
            }

            this.waitingToSendQ.push_back(var3);
         }
      }
   }

    void updateMain() {
    UdpConnection var1 = GameClient.connection;
      if (this.chunkHeadMain != nullptr) {
         this.chunkRequests0.push_back(this.chunkHeadMain);
         this.chunkHeadMain = nullptr;
      }

      this.tempRequests.clear();

      for (ChunkRequest var2 = this.waitingToSendQ.poll(); var2 != nullptr; var2 = this.waitingToSendQ.poll()) {
         while (var2 != nullptr) {
    ChunkRequest var3 = var2.next;
            if ((var2.flagsWS & 1) != 0) {
               var2.flagsUDP |= 16;
            } else {
               this.tempRequests.push_back(var2);
            }

            var2 = var3;
         }
      }

      if (!this.tempRequests.empty()) {
    ByteBufferWriter var6 = var1.startPacket();
         PacketType.RequestZipList.doPacket(var6);
         var6.putInt(this.tempRequests.size());

         for (int var9 = 0; var9 < this.tempRequests.size(); var9++) {
    ChunkRequest var4 = this.tempRequests.get(var9);
            var6.putInt(var4.requestNumber);
            var6.putInt(var4.chunk.wx);
            var6.putInt(var4.chunk.wy);
            var6.putLong(var4.crc);
            if (this.NetworkFileDebug) {
               DebugLog.log(DebugType.NetworkFileDebug, "requested " + var4.chunk.wx + "," + var4.chunk.wy + " crc=" + var4.crc);
            }
         }

         PacketType.RequestZipList.send(var1);

         for (int var10 = 0; var10 < this.tempRequests.size(); var10++) {
    ChunkRequest var12 = this.tempRequests.get(var10);
            this.sentRequests.push_back(var12);
         }
      }

      this.tempRequests.clear();

      for (ChunkRequest var7 = this.waitingToCancelQ.poll(); var7 != nullptr; var7 = this.waitingToCancelQ.poll()) {
         this.tempRequests.push_back(var7);
      }

      if (!this.tempRequests.empty()) {
    ByteBufferWriter var8 = var1.startPacket();
         PacketType.NotRequiredInZip.doPacket(var8);

         try {
            var8.putInt(this.tempRequests.size());

            for (int var11 = 0; var11 < this.tempRequests.size(); var11++) {
    ChunkRequest var13 = this.tempRequests.get(var11);
               if (this.NetworkFileDebug) {
                  DebugLog.log(DebugType.NetworkFileDebug, "cancelled " + var13.chunk.wx + "," + var13.chunk.wy);
               }

               var8.putInt(var13.requestNumber);
               var13.flagsMain |= 2;
            }

            PacketType.NotRequiredInZip.send(var1);
         } catch (Exception var5) {
            var5.printStackTrace();
            var1.cancelPacket();
         }
      }
   }

    void getStatistics() {
      MPStatistics.countChunkRequests(
         this.sentRequests.size(), this.chunkRequests0.size(), this.chunkRequests1.size(), this.pendingRequests.size(), this.pendingRequests1.size()
      );
   }

    void loadReceivedChunks() {
    bool var1 = false;
    int var2 = 0;
    int var3 = 0;

      for (int var4 = 0; var4 < this.pendingRequests1.size(); var4++) {
    ChunkRequest var5 = this.pendingRequests1.get(var4);
         if ((var5.flagsUDP & 16) != 0) {
            if (var1) {
               var2++;
               if ((var5.flagsWS & 1) != 0) {
                  var3++;
               }
            }

            if ((var5.flagsWS & 1) == 0 || (var5.flagsMain & 2) != 0) {
               this.pendingRequests1.remove(var4--);
               ChunkSaveWorker.instance.Update(var5.chunk);
               if ((var5.flagsUDP & 4) != 0) {
    File var6 = ChunkMapFilenames.instance.getFilename(var5.chunk.wx, var5.chunk.wy);
                  if (var6.exists()) {
                     if (this.NetworkFileDebug) {
                        DebugLog.log(
                           DebugType.NetworkFileDebug, "deleting map_" + var5.chunk.wx + "_" + var5.chunk.wy + ".bin because it doesn't exist on the server"
                        );
                     }

                     var6.delete();
                     ChunkChecksum.setChecksum(var5.chunk.wx, var5.chunk.wy, 0L);
                  }
               }

    ByteBuffer var10 = (var5.flagsWS & 1) != 0 ? nullptr : var5.bb;
               if (var10 != nullptr) {
                  try {
                     var10 = this.decompress(var10);
                  } catch (DataFormatException var9) {
                     DebugLog.General
                        .error("WorldStreamer.loadReceivedChunks: Error while the chunk (" + var5.chunk.wx + ", " + var5.chunk.wy + ") was decompressing");
                     this.chunkRequests1.push_back(var5.chunk);
                     continue;
                  }

                  if (this.bCompare) {
    File var7 = ChunkMapFilenames.instance.getFilename(var5.chunk.wx, var5.chunk.wy);
                     if (var7.exists()) {
                        this.compare(var5, var10, var7);
                     }
                  }
               }

               if ((var5.flagsWS & 8) == 0) {
                  if ((var5.flagsWS & 1) == 0 && !var5.chunk.refs.empty()) {
                     if (var10 != nullptr) {
                        var10.position(0);
                     }

                     this.DoChunk(var5.chunk, var10);
                  } else {
                     if (this.NetworkFileDebug) {
                        DebugLog.log(DebugType.NetworkFileDebug, var5.chunk.wx + "_" + var5.chunk.wy + " refs.empty() SafeWrite=" + (var10 != nullptr));
                     }

                     if (var10 != nullptr) {
    long var11 = ChunkChecksum.getChecksumIfExists(var5.chunk.wx, var5.chunk.wy);
                        this.crc32.reset();
                        this.crc32.update(var10.array(), 0, var10.position());
                        if (var11 != this.crc32.getValue()) {
                           ChunkChecksum.setChecksum(var5.chunk.wx, var5.chunk.wy, this.crc32.getValue());
                           IsoChunk.SafeWrite("map_", var5.chunk.wx, var5.chunk.wy, var10);
                        }
                     }

                     var5.chunk.resetForStore();

                     assert !IsoChunkMap.chunkStore.contains(var5.chunk);

                     IsoChunkMap.chunkStore.push_back(var5.chunk);
                  }
               }

               if (var5.bb != nullptr) {
                  this.releaseBuffer(var5.bb);
               }

               ChunkRequest.release(var5);
            }
         }
      }

      if (var1 && (var2 != 0 || var3 != 0 || !this.pendingRequests1.empty())) {
         DebugLog.log("nReceived=" + var2 + " nCancel=" + var3 + " nPending=" + this.pendingRequests1.size());
      }
   }

    ByteBuffer decompress(ByteBuffer var1) {
      this.decompressor.reset();
      this.decompressor.setInput(var1.array(), 0, var1.position());
    int var2 = 0;
      if (this.inMemoryZip != nullptr) {
         this.inMemoryZip.clear();
      }

      while (!this.decompressor.finished()) {
    int var3 = this.decompressor.inflate(this.readBuf);
         if (var3 != 0) {
            this.inMemoryZip = this.ensureCapacity(this.inMemoryZip, var2 + var3);
            this.inMemoryZip.put(this.readBuf, 0, var3);
            var2 += var3;
         } else if (!this.decompressor.finished()) {
            throw std::make_unique<DataFormatException>();
         }
      }

      this.inMemoryZip.limit(this.inMemoryZip.position());
      return this.inMemoryZip;
   }

    void threadLoop() {
      if (GameClient.bClient && !SystemDisabler.doWorldSyncEnable) {
         this.NetworkFileDebug = DebugType.Do(DebugType.NetworkFileDebug);

         for (IsoChunk var1 = this.chunkRequests0.poll(); var1 != nullptr; var1 = this.chunkRequests0.poll()) {
            while (var1 != nullptr) {
    IsoChunk var2 = var1.next;
               this.chunkRequests1.push_back(var1);
               var1 = var2;
            }
         }

         if (!this.chunkRequests1.empty()) {
            comp.init();
            Collections.sort(this.chunkRequests1, comp);
            this.sendRequests();
         }

         this.loadReceivedChunks();
         this.cancelOutOfBoundsRequests();
         this.resendTimedOutRequests();
      }

      for (IsoChunk var3 = this.jobQueue.poll(); var3 != nullptr; var3 = this.jobQueue.poll()) {
         if (this.jobList.contains(var3)) {
            DebugLog.log("Ignoring duplicate chunk added to WorldStreamer.jobList");
         } else {
            this.jobList.push_back(var3);
         }
      }

      if (this.jobList.empty()) {
         ChunkSaveWorker.instance.Update(nullptr);
         if (ChunkSaveWorker.instance.bSaving) {
            return;
         }

         if (!this.pendingRequests1.empty()) {
            Thread.sleep(20L);
            return;
         }

         Thread.sleep(140L);
      } else {
         for (int var4 = this.jobList.size() - 1; var4 >= 0; var4--) {
    IsoChunk var6 = this.jobList.get(var4);
            if (var6.refs.empty()) {
               this.jobList.remove(var4);
               var6.resetForStore();

               assert !IsoChunkMap.chunkStore.contains(var6);

               IsoChunkMap.chunkStore.push_back(var6);
            }
         }

    bool var5 = !this.jobList.empty();
    IsoChunk var7 = nullptr;
         if (var5) {
            comp.init();
            Collections.sort(this.jobList, comp);
            var7 = this.jobList.remove(this.jobList.size() - 1);
         }

         ChunkSaveWorker.instance.Update(var7);
         if (var7 != nullptr) {
            if (var7.refs.empty()) {
               var7.resetForStore();

               assert !IsoChunkMap.chunkStore.contains(var7);

               IsoChunkMap.chunkStore.push_back(var7);
            } else {
               this.DoChunk(var7, nullptr);
            }
         }

         if (var5 || ChunkSaveWorker.instance.bSaving) {
            return;
         }
      }

      if (!GameClient.bClient && !GameWindow.bLoadedAsClient && PlayerDB.isAvailable()) {
         PlayerDB.getInstance().updateWorldStreamer();
      }

      VehiclesDB2.instance.updateWorldStreamer();
      if (IsoPlayer.getInstance() != nullptr) {
         Thread.sleep(140L);
      } else {
         Thread.sleep(0L);
      }
   }

    void create() {
      if (this.worldStreamer == nullptr) {
         if (!GameServer.bServer) {
            this.bFinished = false;
            this.worldStreamer = std::make_shared<Thread>(ThreadGroups.Workers, () -> {
               while (!this.bFinished) {
                  try {
                     this.threadLoop();
                  } catch (Exception var2) {
                     var2.printStackTrace();
                  }
               }
            });
            this.worldStreamer.setPriority(5);
            this.worldStreamer.setDaemon(true);
            this.worldStreamer.setName("World Streamer");
            this.worldStreamer.setUncaughtExceptionHandler(GameWindow::uncaughtException);
            this.worldStreamer.start();
         }
      }
   }

    void addJob(IsoChunk var1, int var2, int var3, bool var4) {
      if (!GameServer.bServer) {
         var1.wx = var2;
         var1.wy = var3;
         if (GameClient.bClient && !SystemDisabler.doWorldSyncEnable && var4) {
            var1.next = this.chunkHeadMain;
            this.chunkHeadMain = var1;
         } else {
            assert !this.jobQueue.contains(var1);

            assert !this.jobList.contains(var1);

            this.jobQueue.push_back(var1);
         }
      }
   }

    void DoChunk(IsoChunk var1, ByteBuffer var2) {
      if (!GameServer.bServer) {
         this.DoChunkAlways(var1, var2);
      }
   }

    void DoChunkAlways(IsoChunk var1, ByteBuffer var2) {
      if (Core.bDebug && DebugOptions.instance.WorldStreamerSlowLoad.getValue()) {
         try {
            Thread.sleep(50L);
         } catch (InterruptedException var5) {
         }
      }

      if (var1 != nullptr) {
         try {
            if (!var1.LoadOrCreate(var1.wx, var1.wy, var2)) {
               if (GameClient.bClient) {
                  ChunkChecksum.setChecksum(var1.wx, var1.wy, 0L);
               }

               var1.Blam(var1.wx, var1.wy);
               if (!var1.LoadBrandNew(var1.wx, var1.wy)) {
                  return;
               }
            }

            if (var2 == nullptr) {
               VehiclesDB2.instance.loadChunk(var1);
            }
         } catch (Exception var6) {
            DebugLog.General.error("Exception thrown while trying to load chunk: " + var1.wx + ", " + var1.wy);
            var6.printStackTrace();
            if (GameClient.bClient) {
               ChunkChecksum.setChecksum(var1.wx, var1.wy, 0L);
            }

            var1.Blam(var1.wx, var1.wy);
            if (!var1.LoadBrandNew(var1.wx, var1.wy)) {
               return;
            }
         }

         if (var1.jobType != JobType.Convert && var1.jobType != JobType.SoftReset) {
            try {
               if (!var1.refs.empty()) {
                  var1.loadInWorldStreamerThread();
               }
            } catch (Exception var4) {
               var4.printStackTrace();
            }

            IsoChunk.loadGridSquare.push_back(var1);
         } else {
            var1.doLoadGridsquare();
            var1.bLoaded = true;
         }
      }
   }

    void addJobInstant(IsoChunk var1, int var2, int var3, int var4, int var5) {
      if (!GameServer.bServer) {
         var1.wx = var4;
         var1.wy = var5;

         try {
            this.DoChunkAlways(var1, nullptr);
         } catch (Exception var7) {
            var7.printStackTrace();
         }
      }
   }

    void addJobConvert(IsoChunk var1, int var2, int var3, int var4, int var5) {
      if (!GameServer.bServer) {
         var1.wx = var4;
         var1.wy = var5;
         var1.jobType = JobType.Convert;

         try {
            this.DoChunk(var1, nullptr);
         } catch (Exception var7) {
            var7.printStackTrace();
         }
      }
   }

    void addJobWipe(IsoChunk var1, int var2, int var3, int var4, int var5) {
      var1.wx = var4;
      var1.wy = var5;
      var1.jobType = JobType.SoftReset;

      try {
         this.DoChunkAlways(var1, nullptr);
      } catch (Exception var7) {
         var7.printStackTrace();
      }
   }

    bool isBusy() {
      return !GameClient.bClient
            || this.chunkRequests0.empty()
               && this.chunkRequests1.empty()
               && this.chunkHeadMain == nullptr
               && this.waitingToSendQ.empty()
               && this.waitingToCancelQ.empty()
               && this.sentRequests.empty()
               && this.pendingRequests.empty()
               && this.pendingRequests1.empty()
         ? !this.jobQueue.empty() || !this.jobList.empty()
         : true;
   }

    void stop() {
      DebugLog.log("EXITDEBUG: WorldStreamer.stop 1");
      if (this.worldStreamer != nullptr) {
         this.bFinished = true;
         DebugLog.log("EXITDEBUG: WorldStreamer.stop 2");

         while (this.worldStreamer.isAlive()) {
         }

         DebugLog.log("EXITDEBUG: WorldStreamer.stop 3");
         this.worldStreamer = nullptr;
         this.jobList.clear();
         this.jobQueue.clear();
         DebugLog.log("EXITDEBUG: WorldStreamer.stop 4");
         ChunkSaveWorker.instance.SaveNow();
         ChunkChecksum.Reset();
         DebugLog.log("EXITDEBUG: WorldStreamer.stop 5");
      }
   }

    void quit() {
      this.stop();
   }

    void requestLargeAreaZip(int var1, int var2, int var3) {
    ByteBufferWriter var4 = GameClient.connection.startPacket();
      PacketType.RequestLargeAreaZip.doPacket(var4);
      var4.putInt(var1);
      var4.putInt(var2);
      var4.putInt(IsoChunkMap.ChunkGridWidth);
      PacketType.RequestLargeAreaZip.send(GameClient.connection);
      this.requestingLargeArea = true;
      this.largeAreaDownloads = 0;
      GameLoadingState.GameLoadingString = Translator.getText("IGUI_MP_RequestMapData");
    int var5 = 0;
    int var6 = var1 - var3;
    int var7 = var2 - var3;
    int var8 = var1 + var3;
    int var9 = var2 + var3;

      for (int var10 = var7; var10 <= var9; var10++) {
         for (int var11 = var6; var11 <= var8; var11++) {
            if (IsoWorld.instance.MetaGrid.isValidChunk(var11, var10)) {
    IsoChunk var12 = (IsoChunk)IsoChunkMap.chunkStore.poll();
               if (var12 == nullptr) {
                  var12 = std::make_shared<IsoChunk>(IsoWorld.instance.CurrentCell);
               } else {
                  MPStatistics.decreaseStoredChunk();
               }

               this.addJob(var12, var11, var10, true);
               var5++;
            }
         }
      }

      DebugLog.log("Requested " + var5 + " chunks from the server");
    long var23 = System.currentTimeMillis();
    long var24 = var23;
    int var14 = 0;
    int var15 = 0;

      while (this.isBusy()) {
    long var16 = System.currentTimeMillis();
         if (var16 - var24 > 60000L) {
            GameLoadingState.mapDownloadFailed = true;
            throw IOException("map download from server timed out");
         }

    int var18 = this.largeAreaDownloads;
         GameLoadingState.GameLoadingString = Translator.getText("IGUI_MP_DownloadedMapData", var18, var5);
    long var19 = var16 - var23;
         if (var19 / 1000L > var14) {
            DebugLog.log("Received " + var18 + " / " + var5 + " chunks");
            var14 = (int)(var19 / 1000L);
         }

         if (var15 < var18) {
            var24 = var16;
            var15 = var18;
         }

         try {
            Thread.sleep(100L);
         } catch (InterruptedException var22) {
         }
      }

      DebugLog.log("Received " + this.largeAreaDownloads + " / " + var5 + " chunks");
      this.requestingLargeArea = false;
   }

    void cancelOutOfBoundsRequests() {
      if (!this.requestingLargeArea) {
         for (int var1 = 0; var1 < this.pendingRequests1.size(); var1++) {
    ChunkRequest var2 = this.pendingRequests1.get(var1);
            if ((var2.flagsWS & 1) == 0 && var2.chunk.refs.empty()) {
               var2.flagsWS |= 1;
               this.waitingToCancelQ.push_back(var2);
            }
         }
      }
   }

    void resendTimedOutRequests() {
    long var1 = System.currentTimeMillis();

      for (int var3 = 0; var3 < this.pendingRequests1.size(); var3++) {
    ChunkRequest var4 = this.pendingRequests1.get(var3);
         if ((var4.flagsWS & 1) == 0 && var4.time + 8000L < var1) {
            if (this.NetworkFileDebug) {
               DebugLog.log(DebugType.NetworkFileDebug, "chunk request timed out " + var4.chunk.wx + "," + var4.chunk.wy);
            }

            this.chunkRequests1.push_back(var4.chunk);
            var4.flagsWS |= 9;
            var4.flagsMain |= 2;
         }
      }
   }

    void receiveChunkPart(ByteBuffer var1) {
      for (ChunkRequest var2 = this.sentRequests.poll(); var2 != nullptr; var2 = this.sentRequests.poll()) {
         this.pendingRequests.push_back(var2);
      }

    int var10 = var1.getInt();
    int var3 = var1.getInt();
    int var4 = var1.getInt();
    int var5 = var1.getInt();
    int var6 = var1.getInt();
    int var7 = var1.getInt();

      for (int var8 = 0; var8 < this.pendingRequests.size(); var8++) {
    ChunkRequest var9 = this.pendingRequests.get(var8);
         if ((var9.flagsWS & 1) != 0) {
            this.pendingRequests.remove(var8--);
            var9.flagsUDP |= 16;
         } else if (var9.requestNumber == var10) {
            if (var9.bb == nullptr) {
               var9.bb = this.getByteBuffer(var5);
            }

            System.arraycopy(var1.array(), var1.position(), var9.bb.array(), var6, var7);
            if (var9.partsReceived == nullptr) {
               var9.partsReceived = new boolean[var3];
            }

            var9.partsReceived[var4] = true;
            if (var9.isReceived()) {
               if (this.NetworkFileDebug) {
                  DebugLog.log(DebugType.NetworkFileDebug, "received all parts for " + var9.chunk.wx + "," + var9.chunk.wy);
               }

               var9.bb.position(var5);
               this.pendingRequests.remove(var8);
               var9.flagsUDP |= 16;
               if (this.requestingLargeArea) {
                  this.largeAreaDownloads++;
               }
            }
            break;
         }
      }
   }

    void receiveNotRequired(ByteBuffer var1) {
      for (ChunkRequest var2 = this.sentRequests.poll(); var2 != nullptr; var2 = this.sentRequests.poll()) {
         this.pendingRequests.push_back(var2);
      }

    int var8 = var1.getInt();

      for (int var3 = 0; var3 < var8; var3++) {
    int var4 = var1.getInt();
    bool var5 = var1.get() == 1;

         for (int var6 = 0; var6 < this.pendingRequests.size(); var6++) {
    ChunkRequest var7 = this.pendingRequests.get(var6);
            if ((var7.flagsWS & 1) != 0) {
               this.pendingRequests.remove(var6--);
               var7.flagsUDP |= 16;
            } else if (var7.requestNumber == var4) {
               if (this.NetworkFileDebug) {
                  DebugLog.log(DebugType.NetworkFileDebug, "NotRequiredInZip " + var7.chunk.wx + "," + var7.chunk.wy + " delete=" + !var5);
               }

               if (!var5) {
                  var7.flagsUDP |= 4;
               }

               this.pendingRequests.remove(var6);
               var7.flagsUDP |= 16;
               if (this.requestingLargeArea) {
                  this.largeAreaDownloads++;
               }
               break;
            }
         }
      }
   }

    void compare(ChunkRequest var1, ByteBuffer var2, File var3) {
    IsoChunk var4 = (IsoChunk)IsoChunkMap.chunkStore.poll();
      if (var4 == nullptr) {
         var4 = std::make_shared<IsoChunk>(IsoWorld.instance.getCell());
      } else {
         MPStatistics.decreaseStoredChunk();
      }

      var4.wx = var1.chunk.wx;
      var4.wy = var1.chunk.wy;
    IsoChunk var5 = (IsoChunk)IsoChunkMap.chunkStore.poll();
      if (var5 == nullptr) {
         var5 = std::make_shared<IsoChunk>(IsoWorld.instance.getCell());
      } else {
         MPStatistics.decreaseStoredChunk();
      }

      var5.wx = var1.chunk.wx;
      var5.wy = var1.chunk.wy;
    int var6 = var2.position();
      var2.position(0);
      var4.LoadFromBuffer(var1.chunk.wx, var1.chunk.wy, var2);
      var2.position(var6);
      this.crc32.reset();
      this.crc32.update(var2.array(), 0, var6);
      DebugLog.log("downloaded crc=" + this.crc32.getValue() + " on-disk crc=" + ChunkChecksum.getChecksumIfExists(var1.chunk.wx, var1.chunk.wy));
      var5.LoadFromDisk();
      DebugLog.log("downloaded size=" + var6 + " on-disk size=" + var3.length());
      this.compareChunks(var4, var5);
      var4.resetForStore();

      assert !IsoChunkMap.chunkStore.contains(var4);

      IsoChunkMap.chunkStore.push_back(var4);
      var5.resetForStore();

      assert !IsoChunkMap.chunkStore.contains(var5);

      IsoChunkMap.chunkStore.push_back(var5);
   }

    void compareChunks(IsoChunk var1, IsoChunk var2) {
      DebugLog.log("comparing " + var1.wx + "," + var1.wy);

      try {
         this.compareErosion(var1, var2);
         if (var1.lootRespawnHour != var2.lootRespawnHour) {
            DebugLog.log("lootRespawnHour " + var1.lootRespawnHour + " != " + var2.lootRespawnHour);
         }

         for (int var3 = 0; var3 < 10; var3++) {
            for (int var4 = 0; var4 < 10; var4++) {
    IsoGridSquare var5 = var1.getGridSquare(var4, var3, 0);
    IsoGridSquare var6 = var2.getGridSquare(var4, var3, 0);
               this.compareSquares(var5, var6);
            }
         }
      } catch (Exception var7) {
         var7.printStackTrace();
      }
   }

    void compareErosion(IsoChunk var1, IsoChunk var2) {
      if (var1.getErosionData().init != var2.getErosionData().init) {
         DebugLog.log("init " + var1.getErosionData().init + " != " + var2.getErosionData().init);
      }

      if (var1.getErosionData().eTickStamp != var2.getErosionData().eTickStamp) {
         DebugLog.log("eTickStamp " + var1.getErosionData().eTickStamp + " != " + var2.getErosionData().eTickStamp);
      }

      if (var1.getErosionData().moisture != var2.getErosionData().moisture) {
         DebugLog.log("moisture " + var1.getErosionData().moisture + " != " + var2.getErosionData().moisture);
      }

      if (var1.getErosionData().minerals != var2.getErosionData().minerals) {
         DebugLog.log("minerals " + var1.getErosionData().minerals + " != " + var2.getErosionData().minerals);
      }

      if (var1.getErosionData().epoch != var2.getErosionData().epoch) {
         DebugLog.log("epoch " + var1.getErosionData().epoch + " != " + var2.getErosionData().epoch);
      }

      if (var1.getErosionData().soil != var2.getErosionData().soil) {
         DebugLog.log("soil " + var1.getErosionData().soil + " != " + var2.getErosionData().soil);
      }
   }

    void compareSquares(IsoGridSquare var1, IsoGridSquare var2) {
      if (var1 != nullptr && var2 != nullptr) {
         try {
            this.bb1.clear();
            var1.save(this.bb1, nullptr);
            this.bb1.flip();
            this.bb2.clear();
            var2.save(this.bb2, nullptr);
            this.bb2.flip();
            if (this.bb1.compareTo(this.bb2) != 0) {
    bool var3 = true;
    int var4 = -1;
               if (this.bb1.limit() == this.bb2.limit()) {
                  for (int var5 = 0; var5 < this.bb1.limit(); var5++) {
                     if (this.bb1.get(var5) != this.bb2.get(var5)) {
                        var4 = var5;
                        break;
                     }
                  }

                  for (int var9 = 0; var9 < var1.getErosionData().regions.size(); var9++) {
                     if (((Data)var1.getErosionData().regions.get(var9)).dispSeason != ((Data)var2.getErosionData().regions.get(var9)).dispSeason) {
                        DebugLog.log(
                           "season1="
                              + ((Data)var1.getErosionData().regions.get(var9)).dispSeason
                              + " season2="
                              + ((Data)var2.getErosionData().regions.get(var9)).dispSeason
                        );
                        var3 = false;
                     }
                  }
               }

               DebugLog.log(
                  "square " + var1.x + "," + var1.y + " mismatch at " + var4 + " seasonMatch=" + var3 + " #regions=" + var1.getErosionData().regions.size()
               );
               if (var1.getObjects().size() == var2.getObjects().size()) {
                  for (int var10 = 0; var10 < var1.getObjects().size(); var10++) {
    IsoObject var6 = (IsoObject)var1.getObjects().get(var10);
    IsoObject var7 = (IsoObject)var2.getObjects().get(var10);
                     this.bb1.clear();
                     var6.save(this.bb1);
                     this.bb1.flip();
                     this.bb2.clear();
                     var7.save(this.bb2);
                     this.bb2.flip();
                     if (this.bb1.compareTo(this.bb2) != 0) {
                        DebugLog.log("  1: " + var6.getClass().getName() + " " + var6.getName() + " " + (var6.sprite == nullptr ? "no sprite" : var6.sprite.name));
                        DebugLog.log("  2: " + var7.getClass().getName() + " " + var7.getName() + " " + (var7.sprite == nullptr ? "no sprite" : var7.sprite.name));
                     }
                  }
               } else {
                  for (int var11 = 0; var11 < var1.getObjects().size(); var11++) {
    IsoObject var12 = (IsoObject)var1.getObjects().get(var11);
                     DebugLog.log("  " + var12.getClass().getName() + " " + var12.getName() + " " + (var12.sprite == nullptr ? "no sprite" : var12.sprite.name));
                  }
               }
            }
         } catch (Exception var8) {
            var8.printStackTrace();
         }
      } else {
         if (var1 != nullptr || var2 != nullptr) {
            DebugLog.log("one square is nullptr, the other isn't");
         }
      }
   }
}
} // namespace iso
} // namespace zombie
