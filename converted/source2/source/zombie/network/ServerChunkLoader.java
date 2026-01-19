package zombie.network;

import java.util.ArrayList;
import java.util.zip.CRC32;
import zombie.GameTime;
import zombie.debug.DebugType;
import zombie.iso.IsoChunk;
import zombie.network.ServerChunkLoader.LoaderThread;
import zombie.network.ServerChunkLoader.RecalcAllThread;
import zombie.network.ServerChunkLoader.SaveChunkThread;
import zombie.network.ServerMap.ServerCell;

public class ServerChunkLoader {
   private long debugSlowMapLoadingDelay = 0L;
   private boolean MapLoading = false;
   private LoaderThread threadLoad;
   private SaveChunkThread threadSave;
   private final CRC32 crcSave = new CRC32();
   private RecalcAllThread threadRecalc;

   public ServerChunkLoader() {
      this.threadLoad = new LoaderThread(this);
      this.threadLoad.setName("LoadChunk");
      this.threadLoad.setDaemon(true);
      this.threadLoad.start();
      this.threadRecalc = new RecalcAllThread(this);
      this.threadRecalc.setName("RecalcAll");
      this.threadRecalc.setDaemon(true);
      this.threadRecalc.setPriority(10);
      this.threadRecalc.start();
      this.threadSave = new SaveChunkThread(this);
      this.threadSave.setName("SaveChunk");
      this.threadSave.setDaemon(true);
      this.threadSave.start();
   }

   public void addJob(ServerCell var1) {
      this.MapLoading = DebugType.Do(DebugType.MapLoading);
      this.threadLoad.toThread.add(var1);
      MPStatistic.getInstance().LoaderThreadTasks.Added();
   }

   public void getLoaded(ArrayList<ServerCell> var1) {
      this.threadLoad.fromThread.drainTo(var1);
   }

   public void quit() {
      this.threadLoad.quit();

      while (this.threadLoad.isAlive()) {
         try {
            Thread.sleep(500L);
         } catch (InterruptedException var3) {
         }
      }

      this.threadSave.quit();

      while (this.threadSave.isAlive()) {
         try {
            Thread.sleep(500L);
         } catch (InterruptedException var2) {
         }
      }
   }

   public void addSaveUnloadedJob(IsoChunk var1) {
      this.threadSave.addUnloadedJob(var1);
   }

   public void addSaveLoadedJob(IsoChunk var1) {
      this.threadSave.addLoadedJob(var1);
   }

   public void saveLater(GameTime var1) {
      this.threadSave.saveLater(var1);
   }

   public void updateSaved() {
      this.threadSave.update();
   }

   public void addRecalcJob(ServerCell var1) {
      this.threadRecalc.toThread.add(var1);
      MPStatistic.getInstance().RecalcThreadTasks.Added();
   }

   public void getRecalc(ArrayList<ServerCell> var1) {
      MPStatistic.getInstance().ServerMapLoaded2.Added(this.threadRecalc.fromThread.size());
      this.threadRecalc.fromThread.drainTo(var1);
      MPStatistic.getInstance().RecalcThreadTasks.Processed();
   }
}
