#pragma once
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoChunkMap.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/network/ServerMap/ServerCell.h"
#include <algorithm>

namespace zombie {
namespace network {


class ServerChunkLoader {
public:
   private const LinkedBlockingQueue<ServerCell> toThread;
   private const LinkedBlockingQueue<ServerCell> fromThread;
   ArrayDeque<IsoGridSquare> isoGridSquareCache;

   private ServerChunkLoader$LoaderThread(ServerChunkLoader var1) {
      this.this$0 = var1;
      this.toThread = std::make_unique<LinkedBlockingQueue<>>();
      this.fromThread = std::make_unique<LinkedBlockingQueue<>>();
      this.isoGridSquareCache = std::make_unique<ArrayDeque<>>();
   }

    void run() {
      while (true) {
         try {
            MPStatistic.getInstance().LoaderThread.End();
    ServerCell var1 = this.toThread.take();
            MPStatistic.getInstance().LoaderThread.Start();
            if (this.isoGridSquareCache.size() < 10000) {
               IsoGridSquare.getSquaresForThread(this.isoGridSquareCache, 10000);
               IsoGridSquare.loadGridSquareCache = this.isoGridSquareCache;
            }

            if (var1.WX == -1 && var1.WY == -1) {
               return;
            }

            if (var1.bCancelLoading) {
               if (this.this$0.MapLoading) {
                  DebugLog.log(DebugType.MapLoading, "LoaderThread: cancelled " + var1.WX + "," + var1.WY);
               }

               var1.bLoadingWasCancelled = true;
            } else {
    long var2 = System.nanoTime();

               for (int var4 = 0; var4 < 5; var4++) {
                  for (int var5 = 0; var5 < 5; var5++) {
    int var6 = var1.WX * 5 + var4;
    int var7 = var1.WY * 5 + var5;
                     if (IsoWorld.instance.MetaGrid.isValidChunk(var6, var7)) {
    IsoChunk var8 = (IsoChunk)IsoChunkMap.chunkStore.poll();
                        if (var8 == nullptr) {
                           var8 = std::make_shared<IsoChunk>(nullptr);
                        } else {
                           MPStatistics.decreaseStoredChunk();
                        }

                        this.this$0.threadSave.saveNow(var6, var7);

                        try {
                           if (var8.LoadOrCreate(var6, var7, nullptr)) {
                              var8.bLoaded = true;
                           } else {
                              ChunkChecksum.setChecksum(var6, var7, 0L);
                              var8.Blam(var6, var7);
                              if (var8.LoadBrandNew(var6, var7)) {
                                 var8.bLoaded = true;
                              }
                           }
                        } catch (Exception var10) {
                           var10.printStackTrace();
                           LoggerManager.getLogger("map").write(var10);
                        }

                        if (var8.bLoaded) {
                           var1.chunks[var4][var5] = var8;
                        }
                     }
                  }
               }

               if (GameServer.bDebug && this.this$0.debugSlowMapLoadingDelay > 0L) {
                  Thread.sleep(this.this$0.debugSlowMapLoadingDelay);
               }

    float var12 = (float)(System.nanoTime() - var2) / 1000000.0F;
               MPStatistic.getInstance().IncrementLoadCellFromDisk();
               this.fromThread.push_back(var1);
               MPStatistic.getInstance().LoaderThreadTasks.Processed();
            }
         } catch (Exception var11) {
            var11.printStackTrace();
            LoggerManager.getLogger("map").write(var11);
         }
      }
   }

    void quit() {
    ServerCell var1 = std::make_shared<ServerCell>();
      var1.WX = -1;
      var1.WY = -1;
      this.toThread.push_back(var1);
      MPStatistic.getInstance().LoaderThreadTasks.Added();
   }
}
} // namespace network
} // namespace zombie
