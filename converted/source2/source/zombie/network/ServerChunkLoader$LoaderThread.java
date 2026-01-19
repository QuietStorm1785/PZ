package zombie.network;

import java.util.ArrayDeque;
import java.util.concurrent.LinkedBlockingQueue;
import zombie.core.logger.LoggerManager;
import zombie.debug.DebugLog;
import zombie.debug.DebugType;
import zombie.iso.IsoChunk;
import zombie.iso.IsoChunkMap;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoWorld;
import zombie.network.ServerMap.ServerCell;

class ServerChunkLoader$LoaderThread extends Thread {
   private final LinkedBlockingQueue<ServerCell> toThread;
   private final LinkedBlockingQueue<ServerCell> fromThread;
   ArrayDeque<IsoGridSquare> isoGridSquareCache;

   private ServerChunkLoader$LoaderThread(ServerChunkLoader var1) {
      this.this$0 = var1;
      this.toThread = new LinkedBlockingQueue<>();
      this.fromThread = new LinkedBlockingQueue<>();
      this.isoGridSquareCache = new ArrayDeque<>();
   }

   @Override
   public void run() {
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
                        if (var8 == null) {
                           var8 = new IsoChunk(null);
                        } else {
                           MPStatistics.decreaseStoredChunk();
                        }

                        this.this$0.threadSave.saveNow(var6, var7);

                        try {
                           if (var8.LoadOrCreate(var6, var7, null)) {
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
               this.fromThread.add(var1);
               MPStatistic.getInstance().LoaderThreadTasks.Processed();
            }
         } catch (Exception var11) {
            var11.printStackTrace();
            LoggerManager.getLogger("map").write(var11);
         }
      }
   }

   public void quit() {
      ServerCell var1 = new ServerCell();
      var1.WX = -1;
      var1.WY = -1;
      this.toThread.add(var1);
      MPStatistic.getInstance().LoaderThreadTasks.Added();
   }
}
