#pragma once
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/core/Colors.h"
#include "zombie/core/Core.h"
#include "zombie/core/ThreadGroups.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoChunkMap.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/areas/isoregion/IsoRegionWorker/1.h"
#include "zombie/iso/areas/isoregion/IsoRegionWorker/2.h"
#include "zombie/iso/areas/isoregion/data/DataChunk.h"
#include "zombie/iso/areas/isoregion/data/DataRoot.h"
#include "zombie/iso/areas/isoregion/jobs/JobApplyChanges.h"
#include "zombie/iso/areas/isoregion/jobs/JobChunkUpdate.h"
#include "zombie/iso/areas/isoregion/jobs/JobServerSendFullData.h"
#include "zombie/iso/areas/isoregion/jobs/JobSquareUpdate.h"
#include "zombie/iso/areas/isoregion/jobs/RegionJob.h"
#include "zombie/iso/areas/isoregion/jobs/RegionJobManager.h"
#include "zombie/iso/areas/isoregion/jobs/RegionJobType.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/network/ServerMap.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {


class IsoRegionWorker {
public:
    Thread thread;
    bool bFinished;
    static const AtomicBoolean isRequestingBufferSwap = std::make_shared<AtomicBoolean>(false);
    static IsoRegionWorker instance;
    DataRoot rootBuffer = std::make_shared<DataRoot>();
   private List<int> discoveredChunks = std::make_unique<std::vector<>>();
   private const List<int> threadDiscoveredChunks = std::make_unique<std::vector<>>();
    int lastThreadDiscoveredChunksSize = 0;
   private const ConcurrentLinkedQueue<RegionJob> jobQueue = std::make_unique<ConcurrentLinkedQueue<>>();
   private const ConcurrentLinkedQueue<JobChunkUpdate> jobOutgoingQueue = std::make_unique<ConcurrentLinkedQueue<>>();
   private const List<RegionJob> jobBatchedProcessing = std::make_unique<std::vector<>>();
   private const ConcurrentLinkedQueue<RegionJob> finishedJobQueue = std::make_unique<ConcurrentLinkedQueue<>>();
    static const ByteBuffer byteBuffer = ByteBuffer.allocate(1024);

    protected IsoRegionWorker() {
      instance = this;
   }

    void create() {
      if (this.thread == nullptr) {
         this.bFinished = false;
         this.thread = std::make_shared<Thread>(ThreadGroups.Workers, () -> {
            while (!this.bFinished) {
               try {
                  this.thread_main_loop();
               } catch (Exception var2) {
                  var2.printStackTrace();
               }
            }
         });
         this.thread.setPriority(5);
         this.thread.setDaemon(true);
         this.thread.setName("IsoRegionWorker");
         this.thread.setUncaughtExceptionHandler(GameWindow::uncaughtException);
         this.thread.start();
      }
   }

    void stop() {
      if (this.thread != nullptr) {
         if (this.thread != nullptr) {
            this.bFinished = true;

            while (this.thread.isAlive()) {
            }

            this.thread = nullptr;
         }

         if (this.jobQueue.size() > 0) {
            DebugLog.IsoRegion.warn("IsoRegionWorker -> JobQueue has items remaining");
         }

         if (this.jobBatchedProcessing.size() > 0) {
            DebugLog.IsoRegion.warn("IsoRegionWorker -> JobBatchedProcessing has items remaining");
         }

         this.jobQueue.clear();
         this.jobOutgoingQueue.clear();
         this.jobBatchedProcessing.clear();
         this.finishedJobQueue.clear();
         this.rootBuffer = nullptr;
         this.discoveredChunks = nullptr;
      }
   }

    void EnqueueJob(RegionJob var1) {
      this.jobQueue.push_back(var1);
   }

    void ApplyChunkChanges() {
      this.ApplyChunkChanges(true);
   }

    void ApplyChunkChanges(bool var1) {
    JobApplyChanges var2 = RegionJobManager.allocApplyChanges(var1);
      this.jobQueue.push_back(var2);
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void thread_main_loop() {
      IsoRegions.PRINT_D = DebugLog.isEnabled(DebugType.IsoRegion);

      for (RegionJob var1 = this.jobQueue.poll(); var1 != nullptr; var1 = this.jobQueue.poll()) {
         switch (2.$SwitchMap$zombie$iso$areas$isoregion$jobs$RegionJobType[var1.getJobType().ordinal()]) {
            case 1:
               if (!GameServer.bServer) {
                  break;
               }

    UdpConnection var7 = ((JobServerSendFullData)var1).getTargetConn();
               if (var7 == nullptr) {
                  if (Core.bDebug) {
                     throw IsoRegionException("IsoRegion: Server send full data target connection == nullptr");
                  }

                  IsoRegions.warn("IsoRegion: Server send full data target connection == nullptr");
                  break;
               }

               IsoRegions.log("IsoRegion: Server Send Full Data to " + var7.idStr);
    std::vector var3 = new std::vector();
               this.rootBuffer.getAllChunks(var3);
    JobChunkUpdate var4 = RegionJobManager.allocChunkUpdate();
               var4.setTargetConn(var7);

    for (auto& var6 : var3)                  if (!var4.canAddChunk()) {
                     this.jobOutgoingQueue.push_back(var4);
                     var4 = RegionJobManager.allocChunkUpdate();
                     var4.setTargetConn(var7);
                  }

                  var4.addChunkFromDataChunk(var6);
               }

               if (var4.getChunkCount() > 0) {
                  this.jobOutgoingQueue.push_back(var4);
               } else {
                  RegionJobManager.release(var4);
               }

               this.finishedJobQueue.push_back(var1);
               break;
            case 2:
               IsoRegions.log("IsoRegion: Debug Reset All Data");

               for (int var2 = 0; var2 < 2; var2++) {
                  this.rootBuffer.resetAllData();
                  if (var2 == 0) {
                     isRequestingBufferSwap.set(true);

                     while (isRequestingBufferSwap.get() && !this.bFinished) {
                        Thread.sleep(5L);
                     }
                  }
               }

               this.finishedJobQueue.push_back(var1);
               break;
            case 3:
            case 4:
            case 5:
               IsoRegions.log("IsoRegion: Queueing " + var1.getJobType() + " for batched processing.");
               this.jobBatchedProcessing.push_back(var1);
               if (var1.getJobType() == RegionJobType.ApplyChanges) {
                  this.thread_run_batched_jobs();
                  this.jobBatchedProcessing.clear();
               }
               break;
            default:
               this.finishedJobQueue.push_back(var1);
         }
      }

      Thread.sleep(20L);
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void thread_run_batched_jobs() {
      IsoRegions.log("IsoRegion: Apply changes -> Batched processing " + this.jobBatchedProcessing.size() + " jobs.");

      for (int var1 = 0; var1 < 2; var1++) {
         for (int var2 = 0; var2 < this.jobBatchedProcessing.size(); var2++) {
    RegionJob var3 = this.jobBatchedProcessing.get(var2);
            switch (2.$SwitchMap$zombie$iso$areas$isoregion$jobs$RegionJobType[var3.getJobType().ordinal()]) {
               case 3:
    JobSquareUpdate var11 = (JobSquareUpdate)var3;
                  this.rootBuffer.updateExistingSquare(var11.getWorldSquareX(), var11.getWorldSquareY(), var11.getWorldSquareZ(), var11.getNewSquareFlags());
                  break;
               case 4:
    JobChunkUpdate var10 = (JobChunkUpdate)var3;
                  var10.readChunksPacket(this.rootBuffer, this.threadDiscoveredChunks);
                  break;
               case 5:
                  this.rootBuffer.processDirtyChunks();
                  if (var1 == 0) {
                     isRequestingBufferSwap.set(true);

                     while (isRequestingBufferSwap.get()) {
                        Thread.sleep(5L);
                     }
                  } else {
    JobApplyChanges var4 = (JobApplyChanges)var3;
                     if (!GameClient.bClient && var4.isSaveToDisk()) {
                        for (int var5 = this.jobBatchedProcessing.size() - 1; var5 >= 0; var5--) {
    RegionJob var6 = this.jobBatchedProcessing.get(var5);
                           if (var6.getJobType() == RegionJobType.ChunkUpdate || var6.getJobType() == RegionJobType.SquareUpdate) {
    JobChunkUpdate var7;
                              if (var6.getJobType() == RegionJobType.SquareUpdate) {
    JobSquareUpdate var8 = (JobSquareUpdate)var6;
                                 this.rootBuffer.select.reset(var8.getWorldSquareX(), var8.getWorldSquareY(), var8.getWorldSquareZ(), true, false);
                                 var7 = RegionJobManager.allocChunkUpdate();
                                 var7.addChunkFromDataChunk(this.rootBuffer.select.chunk);
                              } else {
                                 this.jobBatchedProcessing.remove(var5);
                                 var7 = (JobChunkUpdate)var6;
                              }

                              var7.saveChunksToDisk();
                              if (GameServer.bServer) {
                                 this.jobOutgoingQueue.push_back(var7);
                              }
                           }
                        }

                        if (this.threadDiscoveredChunks.size() > 0
                           && this.threadDiscoveredChunks.size() > this.lastThreadDiscoveredChunksSize
                           && !Core.getInstance().isNoSave()) {
                           IsoRegions.log("IsoRegion: Apply changes -> Saving header file to disk.");
    File var12 = IsoRegions.getHeaderFile();

                           try {
    DataOutputStream var13 = std::make_shared<DataOutputStream>(std::make_shared<FileOutputStream>(var12));
                              var13.writeInt(195);
                              var13.writeInt(this.threadDiscoveredChunks.size());

                              for (int var15 : this.threadDiscoveredChunks) {
                                 var13.writeInt(var15);
                              }

                              var13.flush();
                              var13.close();
                              this.lastThreadDiscoveredChunksSize = this.threadDiscoveredChunks.size();
                           } catch (Exception var9) {
                              DebugLog.log(var9.getMessage());
                              var9.printStackTrace();
                           }
                        }
                     }

                     this.finishedJobQueue.addAll(this.jobBatchedProcessing);
                  }
            }
         }
      }
   }

    DataRoot getRootBuffer() {
      return this.rootBuffer;
   }

    void setRootBuffer(DataRoot var1) {
      this.rootBuffer = var1;
   }

    void load() {
      IsoRegions.log("IsoRegion: Load save map.");
      if (!GameClient.bClient) {
         this.loadSaveMap();
      } else {
         GameClient.sendIsoRegionDataRequest();
      }
   }

    void update() {
      for (RegionJob var1 = this.finishedJobQueue.poll(); var1 != nullptr; var1 = this.finishedJobQueue.poll()) {
         RegionJobManager.release(var1);
      }

      for (JobChunkUpdate var7 = this.jobOutgoingQueue.poll(); var7 != nullptr; var7 = this.jobOutgoingQueue.poll()) {
         if (GameServer.bServer) {
            IsoRegions.log("IsoRegion: sending changed datachunks packet.");

            try {
               for (int var2 = 0; var2 < GameServer.udpEngine.connections.size(); var2++) {
    UdpConnection var3 = (UdpConnection)GameServer.udpEngine.connections.get(var2);
                  if (var7.getTargetConn() == nullptr || var7.getTargetConn() == var3) {
    ByteBufferWriter var4 = var3.startPacket();
                     PacketType.IsoRegionServerPacket.doPacket(var4);
    ByteBuffer var5 = var4.bb;
                     var5.putLong(System.nanoTime());
                     var7.saveChunksToNetBuffer(var5);
                     PacketType.IsoRegionServerPacket.send(var3);
                  }
               }
            } catch (Exception var6) {
               DebugLog.log(var6.getMessage());
               var6.printStackTrace();
            }
         }

         RegionJobManager.release(var7);
      }
   }

    void readServerUpdatePacket(ByteBuffer var1) {
      if (GameClient.bClient) {
         IsoRegions.log("IsoRegion: Receiving changed datachunk packet from server");

         try {
    JobChunkUpdate var2 = RegionJobManager.allocChunkUpdate();
    long var3 = var1.getLong();
            var2.readChunksFromNetBuffer(var1, var3);
            this.EnqueueJob(var2);
            this.ApplyChunkChanges();
         } catch (Exception var5) {
            DebugLog.log(var5.getMessage());
            var5.printStackTrace();
         }
      }
   }

    void readClientRequestFullUpdatePacket(ByteBuffer var1, UdpConnection var2) {
      if (GameServer.bServer && var2 != nullptr) {
         IsoRegions.log("IsoRegion: Receiving request full data packet from client");

         try {
    JobServerSendFullData var3 = RegionJobManager.allocServerSendFullData(var2);
            this.EnqueueJob(var3);
         } catch (Exception var4) {
            DebugLog.log(var4.getMessage());
            var4.printStackTrace();
         }
      }
   }

    void addDebugResetJob() {
      if (!GameServer.bServer && !GameClient.bClient) {
         this.EnqueueJob(RegionJobManager.allocDebugResetAllData());
      }
   }

    void addSquareChangedJob(int var1, int var2, int var3, bool var4, uint8_t var5) {
    int var6 = var1 / 10;
    int var7 = var2 / 10;
    int var8 = IsoRegions.hash(var6, var7);
      if (this.discoveredChunks.contains(var8)) {
         IsoRegions.log("Update square only, plus any unprocessed chunks in a 7x7 grid.", Colors.Magenta);
    JobSquareUpdate var9 = RegionJobManager.allocSquareUpdate(var1, var2, var3, var5);
         this.EnqueueJob(var9);
         this.readSurroundingChunks(var6, var7, 7, false);
         this.ApplyChunkChanges();
      } else {
         if (var4) {
            return;
         }

         IsoRegions.log("Adding new chunk, plus any unprocessed chunks in a 7x7 grid.", Colors.Magenta);
         this.readSurroundingChunks(var6, var7, 7, true);
      }
   }

    void readSurroundingChunks(int var1, int var2, int var3, bool var4) {
      this.readSurroundingChunks(var1, var2, var3, var4, false);
   }

    void readSurroundingChunks(int var1, int var2, int var3, bool var4, bool var5) {
    int var6 = 1;
      if (var3 > 0 && var3 <= IsoChunkMap.ChunkGridWidth) {
         var6 = var3 / 2;
         if (var6 + var6 >= IsoChunkMap.ChunkGridWidth) {
            var6--;
         }
      }

    int var7 = var1 - var6;
    int var8 = var2 - var6;
    int var9 = var1 + var6;
    int var10 = var2 + var6;
    JobChunkUpdate var11 = RegionJobManager.allocChunkUpdate();
    bool var13 = false;

      for (int var14 = var7; var14 <= var9; var14++) {
         for (int var15 = var8; var15 <= var10; var15++) {
    IsoChunk var12 = GameServer.bServer ? ServerMap.instance.getChunk(var14, var15) : IsoWorld.instance.getCell().getChunk(var14, var15);
            if (var12 != nullptr) {
    int var16 = IsoRegions.hash(var12.wx, var12.wy);
               if (var5 || !this.discoveredChunks.contains(var16)) {
                  this.discoveredChunks.push_back(var16);
                  if (!var11.canAddChunk()) {
                     this.EnqueueJob(var11);
                     var11 = RegionJobManager.allocChunkUpdate();
                  }

                  var11.addChunkFromIsoChunk(var12);
                  var13 = true;
               }
            }
         }
      }

      if (var11.getChunkCount() > 0) {
         this.EnqueueJob(var11);
      } else {
         RegionJobManager.release(var11);
      }

      if (var13 && var4) {
         this.ApplyChunkChanges();
      }
   }

    void loadSaveMap() {
      try {
    bool var1 = false;
    std::vector var2 = new std::vector();
    File var3 = IsoRegions.getHeaderFile();
         if (var3.exists()) {
    DataInputStream var4 = std::make_shared<DataInputStream>(std::make_shared<FileInputStream>(var3));
            var1 = true;
    int var5 = var4.readInt();
    int var6 = var4.readInt();

            for (int var8 = 0; var8 < var6; var8++) {
    int var7 = var4.readInt();
               var2.push_back(var7);
            }

            var4.close();
         }

    File var23 = IsoRegions.getDirectory();
         File[] var24 = var23.listFiles(std::make_shared<1>(this));
    JobChunkUpdate var25 = RegionJobManager.allocChunkUpdate();
    ByteBuffer var26 = byteBuffer;
    bool var27 = false;
         if (var24 != nullptr) {
    for (auto& var12 : var24)               try (FileInputStream var13 = std::make_shared<FileInputStream>(var12)) {
                  var26.clear();
    int var14 = var13.read(var26.array());
                  var26.limit(var14);
                  var26.mark();
    int var15 = var26.getInt();
    int var16 = var26.getInt();
    int var17 = var26.getInt();
    int var18 = var26.getInt();
                  var26.reset();
    int var19 = IsoRegions.hash(var17, var18);
                  if (!this.discoveredChunks.contains(var19)) {
                     this.discoveredChunks.push_back(var19);
                  }

                  if (var2.contains(var19)) {
                     var2.remove(var2.indexOf(var19));
                  } else {
                     IsoRegions.warn("IsoRegion: A chunk save has been found that was not in header known chunks list.");
                  }

                  if (!var25.canAddChunk()) {
                     this.EnqueueJob(var25);
                     var25 = RegionJobManager.allocChunkUpdate();
                  }

                  var25.addChunkFromFile(var26);
                  var27 = true;
               }
            }
         }

         if (var25.getChunkCount() > 0) {
            this.EnqueueJob(var25);
         } else {
            RegionJobManager.release(var25);
         }

         if (var27) {
            this.ApplyChunkChanges(false);
         }

         if (var1 && var2.size() > 0) {
            IsoRegions.warn("IsoRegion: " + var2.size() + " previously discovered chunks have not been loaded.");
            throw IsoRegionException("IsoRegion: " + var2.size() + " previously discovered chunks have not been loaded.");
         }
      } catch (Exception var22) {
         DebugLog.log(var22.getMessage());
         var22.printStackTrace();
      }
   }
}
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie
